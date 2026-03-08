using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;

public class CNFReader
{
    public static Dictionary<string, object> ReadCnfFile(string filename, bool writeOutput = false)
    {
        var readDic = new Dictionary<string, object>();
        
        using (FileStream fs = new FileStream(filename, FileMode.Open, FileAccess.Read))
        using (BinaryReader reader = new BinaryReader(fs))
        {
            int i = 0;
            while (true)
            {
                // Danh sách các địa chỉ header
                long secHeader = 0x70 + i * 0x30;
                i++;
                
                // ID của section
                uint secIdHeader = UInt32At(reader, secHeader);

                // Nếu ID bằng 0, tức là kết thúc danh sách section
                if (secIdHeader == 0x00)
                    break;

                // Vị trí bắt đầu của section
                long secLoc = UInt32At(reader, secHeader + 0x0a);

                // Section thông số (thời gian, hiệu chuẩn năng lượng...)
                if (secIdHeader == 0x00012000)
                {
                    long offsParam = secLoc;
                    MergeDicts(readDic, GetEnergyCalibration(reader, offsParam));
                    MergeDicts(readDic, GetDateTime(reader, offsParam));
                    MergeDicts(readDic, GetShapeCalibration(reader, offsParam));
                }
                // Section chuỗi văn bản
                else if (secIdHeader == 0x00012001)
                {
                    long offsStr = secLoc;
                    MergeDicts(readDic, GetStrings(reader, offsStr));
                }
                // Section markers (điểm đánh dấu)
                else if (secIdHeader == 0x00012004)
                {
                    long offsMark = secLoc;
                    MergeDicts(readDic, GetMarkers(reader, offsMark));
                }
                // Section dữ liệu kênh
                else if (secIdHeader == 0x00012005)
                {
                    long offsChan = secLoc;
                    // Ta cần tìm lại offs_param từ header 0x00012000 (giả định đã được đọc)
                    // Ở đây để an toàn, ta tìm lại vị trí offs_param:
                    long paramHeader = FindSectionLocation(fs, 0x00012000);
                    MergeDicts(readDic, GetChannelData(reader, paramHeader, offsChan));
                }

                // Kiểm tra định dạng (header lặp lại ở thân block)
                if (secIdHeader != UInt32At(reader, secLoc))
                {
                    Console.WriteLine($"File {filename}: Format error");
                }
            }
        }

        // Tính toán các thông số dẫn xuất
        if (readDic.ContainsKey("Channels") && readDic.ContainsKey("Energy coefficients"))
        {
            MergeDicts(readDic, ChanToEnergy(readDic));
        }

        if (readDic.ContainsKey("Channels data") && readDic.ContainsKey("Left marker") && readDic.ContainsKey("Right marker"))
        {
            MergeDicts(readDic, MarkersIntegration(readDic));
        }

        Console.WriteLine(new string('=', 50));
        Console.WriteLine($"          File {filename} succesfully read!          ");
        Console.WriteLine(new string('=', 50));

        if (writeOutput)
        {
            WriteToFile(filename + ".txt", readDic);
        }

        return readDic;
    }

    #region Helper Functions for Binary Reading

    private static byte UInt8At(BinaryReader reader, long pos)
    {
        reader.BaseStream.Seek(pos, SeekOrigin.Begin);
        return reader.ReadByte();
    }

    private static ushort UInt16At(BinaryReader reader, long pos)
    {
        reader.BaseStream.Seek(pos, SeekOrigin.Begin);
        return reader.ReadUInt16();
    }

    private static uint UInt32At(BinaryReader reader, long pos)
    {
        reader.BaseStream.Seek(pos, SeekOrigin.Begin);
        return reader.ReadUInt32();
    }

    private static ulong UInt64At(BinaryReader reader, long pos)
    {
        reader.BaseStream.Seek(pos, SeekOrigin.Begin);
        return reader.ReadUInt64();
    }

    // Chuyển đổi định dạng PDP11 32bit float sang IEEE 754 32bit
    private static float Pdp11fAt(BinaryReader reader, long pos)
    {
        reader.BaseStream.Seek(pos, SeekOrigin.Begin);
        ushort tmp1 = reader.ReadUInt16();
        ushort tmp2 = reader.ReadUInt16();

        // Hoán đổi vị trí 2 block 16bit
        byte[] bytes = new byte[4];
        byte[] b2 = BitConverter.GetBytes(tmp2);
        byte[] b1 = BitConverter.GetBytes(tmp1);
        
        bytes[0] = b2[0]; bytes[1] = b2[1];
        bytes[2] = b1[0]; bytes[3] = b1[1];

        float f = BitConverter.ToSingle(bytes, 0);
        return f / 4.0f;
    }

    private static double TimeAt(BinaryReader reader, long pos)
    {
        ulong val = UInt64At(reader, pos);
        return (~val) * 1e-7;
    }

    private static ulong DateTimeAt(BinaryReader reader, long pos)
    {
        ulong val = UInt64At(reader, pos);
        return (val / 10000000) - 3506716800;
    }

    private static string StringAt(BinaryReader reader, long pos, int length)
    {
        reader.BaseStream.Seek(pos, SeekOrigin.Begin);
        byte[] bytes = reader.ReadBytes(length);
        string s = Encoding.UTF8.GetString(bytes).Replace("\0", "").TrimEnd();
        return s == "" ? "READ ERROR" : s;
    }

    // Tìm lại vị trí (offset) của một section bất kỳ theo ID
    private static long FindSectionLocation(FileStream fs, uint targetSecId)
    {
        using (BinaryReader r = new BinaryReader(fs, Encoding.Default, true))
        {
            int i = 0;
            while (true)
            {
                long secHeader = 0x70 + i * 0x30;
                uint secId = UInt32At(r, secHeader);
                if (secId == 0) break;
                if (secId == targetSecId) return UInt32At(r, secHeader + 0x0a);
                i++;
            }
        }
        return 0;
    }

    #endregion

    #region Section Readers

    private static Dictionary<string, object> GetStrings(BinaryReader reader, long offsStr)
    {
        return new Dictionary<string, object>
        {
            { "Sample name", StringAt(reader, offsStr + 0x0030, 0x40) },
            { "Sample id", StringAt(reader, offsStr + 0x0070, 0x10) },
            { "Sample type", StringAt(reader, offsStr + 0x00b0, 0x10) },
            { "Sample units", StringAt(reader, offsStr + 0x00c4, 0x10) },
            { "Sample geometry", StringAt(reader, offsStr + 0x00d4, 0x10) },
            { "User name", StringAt(reader, offsStr + 0x02d6, 0x18) },
            { "Sample description", StringAt(reader, offsStr + 0x036e, 0x100) }
        };
    }

    private static Dictionary<string, object> GetEnergyCalibration(BinaryReader reader, long offsParam)
    {
        long offsCalib = offsParam + 0x30 + UInt16At(reader, offsParam + 0x22);
        float[] A = new float[4];
        A[0] = Pdp11fAt(reader, offsCalib + 0x44);
        A[1] = Pdp11fAt(reader, offsCalib + 0x48);
        A[2] = Pdp11fAt(reader, offsCalib + 0x4c);
        A[3] = Pdp11fAt(reader, offsCalib + 0x50);

        string energyUnit = StringAt(reader, offsCalib + 0x5c, 0x11);
        string mcaType = StringAt(reader, offsCalib + 0x9c, 0x10);
        string dataSource = StringAt(reader, offsCalib + 0x108, 0x10);

        return new Dictionary<string, object>
        {
            { "Energy coefficients", A },
            { "Energy unit", energyUnit },
            { "MCA type", mcaType },
            { "Data source", dataSource }
        };
    }

    private static Dictionary<string, object> GetShapeCalibration(BinaryReader reader, long offsParam)
    {
        long offsCalib = offsParam + 0x30 + UInt16At(reader, offsParam + 0x22);
        float[] B = new float[4];
        B[0] = Pdp11fAt(reader, offsCalib + 0xdc);
        B[1] = Pdp11fAt(reader, offsCalib + 0xe0);
        B[2] = Pdp11fAt(reader, offsCalib + 0xe4);
        B[3] = Pdp11fAt(reader, offsCalib + 0xe8);

        return new Dictionary<string, object> { { "Shape coefficients", B } };
    }

    private static Dictionary<string, object> GetChannelData(BinaryReader reader, long offsParam, long offsChan)
    {
        int nChannels = UInt8At(reader, offsParam + 0x00ba) * 256;
        
        reader.BaseStream.Seek(offsChan + 0x200, SeekOrigin.Begin);
        uint[] chanData = new uint[nChannels];
        ulong totalCounts = 0;

        for (int i = 0; i < nChannels; i++)
        {
            chanData[i] = reader.ReadUInt32();
            totalCounts += chanData[i];
        }

        string measMode = StringAt(reader, offsParam + 0xb0, 0x03);

        int[] channels = new int[nChannels];
        for (int i = 0; i < nChannels; i++) channels[i] = i + 1;

        return new Dictionary<string, object>
        {
            { "Number of channels", nChannels },
            { "Channels data", chanData },
            { "Channels", channels },
            { "Total counts", totalCounts },
            { "Measurement mode", measMode }
        };
    }

    private static Dictionary<string, object> GetDateTime(BinaryReader reader, long offsParam)
    {
        long offsTimes = offsParam + 0x30 + UInt16At(reader, offsParam + 0x24);

        ulong startTimeUnix = DateTimeAt(reader, offsTimes + 0x01);
        double realTime = TimeAt(reader, offsTimes + 0x09);
        double liveTime = TimeAt(reader, offsTimes + 0x11);

        // Chuyển đổi Unix timestamp sang Date string
        DateTime dtDateTime = new DateTime(1970, 1, 1, 0, 0, 0, 0, DateTimeKind.Utc);
        dtDateTime = dtDateTime.AddSeconds(startTimeUnix);
        string startTimeStr = dtDateTime.ToString("dd-MM-yyyy, HH:mm:ss");

        return new Dictionary<string, object>
        {
            { "Real time", realTime },
            { "Live time", liveTime },
            { "Start time", startTimeStr }
        };
    }

    private static Dictionary<string, object> GetMarkers(BinaryReader reader, long offsMark)
    {
        uint markerLeft = UInt32At(reader, offsMark + 0x007a);
        uint markerRight = UInt32At(reader, offsMark + 0x008a);

        return new Dictionary<string, object>
        {
            { "Left marker", markerLeft },
            { "Right marker", markerRight }
        };
    }

    #endregion

    #region Derived Calcs & File Writing

    private static Dictionary<string, object> ChanToEnergy(Dictionary<string, object> dic)
    {
        float[] A = (float[])dic["Energy coefficients"];
        int[] ch = (int[])dic["Channels"];
        double[] energy = new double[ch.Length];

        for (int i = 0; i < ch.Length; i++)
        {
            double c = ch[i];
            energy[i] = A[0] + A[1] * c + A[2] * c * c + A[3] * c * c * c;
        }

        return new Dictionary<string, object> { { "Energy", energy } };
    }

    private static Dictionary<string, object> MarkersIntegration(Dictionary<string, object> dic)
    {
        uint[] chanData = (uint[])dic["Channels data"];
        uint lMarker = (uint)dic["Left marker"];
        uint rMarker = (uint)dic["Right marker"];
        ulong markerCounts = 0;

        // Tính tổng số đếm trong khoảng mốc (tương tự chan_data[l_marker-1:r_marker-1] của numpy)
        for (uint i = lMarker - 1; i < rMarker - 1 && i < chanData.Length; i++)
        {
            markerCounts += chanData[i];
        }

        return new Dictionary<string, object> { { "Counts in markers", markerCounts } };
    }

    private static void WriteToFile(string filename, Dictionary<string, object> dic)
    {
        using (StreamWriter writer = new StreamWriter(filename))
        {
            writer.WriteLine("#");
            writer.WriteLine($"# Sample name: {dic["Sample name"]}");
            writer.WriteLine();

            writer.WriteLine($"# Sample id: {dic["Sample id"]}");
            writer.WriteLine($"# Sample type: {dic["Sample type"]}");
            writer.WriteLine($"# User name: {dic["User name"]}");
            writer.WriteLine($"# Sample description: {dic["Sample description"]}");
            writer.WriteLine("#");

            writer.WriteLine($"# Start time: {dic["Start time"]}");
            writer.WriteLine($"# Real time (s): {((double)dic["Real time"]):F3}");
            writer.WriteLine($"# Live time (s): {((double)dic["Live time"]):F3}");
            writer.WriteLine("#");

            writer.WriteLine($"# Total counts: {dic["Total counts"]}");
            writer.WriteLine("#");

            if (dic.ContainsKey("Left marker")) writer.WriteLine($"# Left marker: {dic["Left marker"]}");
            if (dic.ContainsKey("Right marker")) writer.WriteLine($"# Right marker: {dic["Right marker"]}");
            if (dic.ContainsKey("Counts in markers")) writer.WriteLine($"# Counts: {dic["Counts in markers"]}");
            writer.WriteLine("#");

            writer.WriteLine("# Energy calibration coefficients (E = sum(Ai * n**i))");
            float[] A = (float[])dic["Energy coefficients"];
            for (int j = 0; j < A.Length; j++)
            {
                writer.WriteLine($"#    A{j} = {A[j]:E6}");
            }
            writer.WriteLine($"# Energy unit: {dic["Energy unit"]}");
            writer.WriteLine("#");

            writer.WriteLine("# Shape calibration coefficients (FWHM = B0 + B1*E^(1/2)  Low Tail= B2 + B3*E)");
            float[] B = (float[])dic["Shape coefficients"];
            for (int j = 0; j < B.Length; j++)
            {
                writer.WriteLine($"#    B{j} = {B[j]:E6}");
            }
            writer.WriteLine($"# Energy unit: {dic["Energy unit"]}");
            writer.WriteLine("#");

            writer.WriteLine("# Channel data");
            writer.WriteLine($"#     n     energy({dic["Energy unit"]})     counts     rate(1/s)");
            writer.WriteLine("#" + new string('-', 50));

            int[] channels = (int[])dic["Channels"];
            double[] energy = (double[])dic["Energy"];
            uint[] chanData = (uint[])dic["Channels data"];
            double liveTime = (double)dic["Live time"];

            for (int i = 0; i < channels.Length; i++)
            {
                writer.WriteLine($"{channels[i],4}\t{energy[i]:E3}\t{chanData[i]}\t{(chanData[i] / liveTime):E3}");
            }
        }
    }

    private static void MergeDicts(Dictionary<string, object> target, Dictionary<string, object> source)
    {
        foreach (var kvp in source)
        {
            target[kvp.Key] = kvp.Value;
        }
    }

    #endregion
}

// Lớp chứa hàm Main để chạy thử nghiệm nghiệm tương tự như `if __name__ == "__main__":` trong Python
class Program
{
    static void Main(string[] args)
    {
        string filename;
        if (args.Length < 1)
        {
            string directory = "";
            string name = "Eu-152-16122019.cnf";
            filename = Path.Combine(directory, name);
            Console.WriteLine(new string('*', 10) + "No input file was given\n");
            Console.WriteLine(new string('*', 10) + "Reading file:" + filename + "\n");
        }
        else
        {
            filename = args[0];
        }

        try
        {
            var c = CNFReader.ReadCnfFile(filename, true);

            Console.WriteLine($"Sample id: {c["Sample id"]}");
            Console.WriteLine($"Measurement mode: {c["Measurement mode"]}");

            int[] chan = (int[])c["Channels"];
            int n_chan = (int)c["Number of channels"];
            uint[] chan_data = (uint[])c["Channels data"];
            double[] energy = (double[])c["Energy"];

            Console.WriteLine($"Number of channels used: {n_chan}");

            // Test tại kênh (channel) 250
            int inchan = 250;
            int index = Array.IndexOf(chan, inchan);
            if (index >= 0)
            {
                Console.WriteLine($"At channel {inchan}:");
                Console.WriteLine($"\t Counts: {chan_data[index]}");
                Console.WriteLine($"\t Energy: {energy[index]}");
            }
            
            // Lưu ý: C# không có sẵn thư viện vẽ đồ thị tương đương `matplotlib.pyplot` trực tiếp trong Console.
            // Để vẽ biểu đồ, bạn sẽ cần tích hợp các thư viện UI (như ScottPlot, OxyPlot, v.v.) vào project WPF hoặc WinForms.
            Console.WriteLine("\n[Note: Data is loaded. Use ScottPlot or OxyPlot to plot chart in C#.]");
        }
        catch (Exception ex)
        {
            Console.WriteLine("Error reading file: " + ex.Message);
        }
        
        Console.ReadLine();
    }
}