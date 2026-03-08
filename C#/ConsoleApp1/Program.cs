using System;
using System.Collections.Generic;
using System.IO;
using System.Text;

namespace CNFReaderApp
{
    class Program
    {
        static void Main(string[] args)
    {
        string filePath = @"/Users/huytranquoc/Dev/Code/C#/ConsoleApp1/Eu-152-16122019.cnf";

        try
        {
            // 1. Chỉ cần khởi tạo Object truyền vào path
            // Mọi dữ liệu sẽ được đọc và lưu vào trong biến cnf
            CNFFile cnf = new CNFFile(filePath);

            // 2. Tự do truy xuất các biến theo nhu cầu
            Console.WriteLine($"Sample ID của mẫu: {cnf.SampleId}");
            Console.WriteLine($"Loại đo lường (Measurement Mode): {cnf.MeasurementMode}");
            Console.WriteLine($"Thời gian sống (Live time): {cnf.LiveTime} giây");
            Console.WriteLine($"Tổng số kênh (Number of channels): {cnf.NumberOfChannels}");
            Console.WriteLine($"Tổng số đếm (Total counts): {cnf.TotalCounts}");
            Console.WriteLine($"Đơn vị : {cnf.EnergyUnit}");
            // Bạn có thể dễ dàng lấy mảng dữ liệu để vẽ biểu đồ
            int[] channels = cnf.Channels;
            double[] energies = cnf.Energy;
            uint[] counts = cnf.ChannelsData;

            // Ví dụ lấy giá trị ở kênh thứ 250 (chú ý mảng bắt đầu từ index 0 nên cần trừ đi 1 nếu map theo ID)
            int targetChannel = 250;
            int index = Array.IndexOf(channels, targetChannel);
            if (index >= 0)
            {
                Console.WriteLine($"\nTại kênh số {targetChannel}:");
                Console.WriteLine($"- Số đếm (Counts): {counts[index]}");
                Console.WriteLine($"- Năng lượng (Energy): {energies[index]} {cnf.EnergyUnit}");
            }
        }
        catch (Exception ex)
        {
            Console.WriteLine($"Đã xảy ra lỗi khi đọc file: {ex.Message}");
        }

        Console.ReadLine();
    }
    }
    public class CNFFile
{
    // ==========================================
    // CÁC THUỘC TÍNH (PROPERTIES) CHỨA DỮ LIỆU
    // ==========================================
    public string SampleName { get; private set; }
    public string SampleId { get; private set; }
    public string SampleType { get; private set; }
    public string SampleUnits { get; private set; }
    public string SampleGeometry { get; private set; }
    public string UserName { get; private set; }
    public string SampleDescription { get; private set; }

    public float[] EnergyCoefficients { get; private set; }
    public string EnergyUnit { get; private set; }
    public string McaType { get; private set; }
    public string DataSource { get; private set; }

    public float[] ShapeCoefficients { get; private set; }

    public int NumberOfChannels { get; private set; }
    public uint[] ChannelsData { get; private set; }
    public int[] Channels { get; private set; }
    public ulong TotalCounts { get; private set; }
    public string MeasurementMode { get; private set; }

    public double RealTime { get; private set; }
    public double LiveTime { get; private set; }
    public string StartTime { get; private set; }

    public uint LeftMarker { get; private set; }
    public uint RightMarker { get; private set; }

    // Dữ liệu tính toán dẫn xuất
    public double[] Energy { get; private set; }
    public ulong CountsInMarkers { get; private set; }

    // ==========================================
    // HÀM KHỞI TẠO (CONSTRUCTOR)
    // ==========================================
    public CNFFile(string filePath)
    {
        if (!File.Exists(filePath))
        {
            throw new FileNotFoundException($"Không tìm thấy file tại đường dẫn: {filePath}");
        }

        using (FileStream fs = new FileStream(filePath, FileMode.Open, FileAccess.Read))
        using (BinaryReader f = new BinaryReader(fs))
        {
            int i = 0;
            long offsParam = 0;

            while (true)
            {
                long secHeader = 0x70 + i * 0x30;
                i++;

                // Đọc ID của Section
                uint secIdHeader = UInt32At(f, secHeader);

                if (secIdHeader == 0x00)
                {
                    break; // Kết thúc danh sách
                }

                // Vị trí bắt đầu của section
                long secLoc = UInt32At(f, secHeader + 0x0a);

                if (secIdHeader == 0x00012000)
                {
                    offsParam = secLoc;
                    ReadEnergyCalibration(f, offsParam);
                    ReadDateTime(f, offsParam);
                    ReadShapeCalibration(f, offsParam);
                }
                else if (secIdHeader == 0x00012001)
                {
                    ReadStrings(f, secLoc);
                }
                else if (secIdHeader == 0x00012004)
                {
                    ReadMarkers(f, secLoc);
                }
                else if (secIdHeader == 0x00012005)
                {
                    ReadChannelData(f, offsParam, secLoc);
                }
            }
        }

        // Tính toán các thông số dẫn xuất sau khi đã đọc xong toàn bộ file
        CalculateDerivedData();
    }

    // ==========================================
    // CÁC HÀM XỬ LÝ NỘI BỘ (PRIVATE METHODS)
    // ==========================================
    private void ReadStrings(BinaryReader f, long offsStr)
    {
        SampleName = StringAt(f, offsStr + 0x0030, 0x40);
        SampleId = StringAt(f, offsStr + 0x0070, 0x10);
        SampleType = StringAt(f, offsStr + 0x00b0, 0x10);
        SampleUnits = StringAt(f, offsStr + 0x00c4, 0x10);
        SampleGeometry = StringAt(f, offsStr + 0x00d4, 0x10);
        UserName = StringAt(f, offsStr + 0x02d6, 0x18);
        SampleDescription = StringAt(f, offsStr + 0x036e, 0x100);
    }

    private void ReadEnergyCalibration(BinaryReader f, long offsParam)
    {
        long offsCalib = offsParam + 0x30 + UInt16At(f, offsParam + 0x22);
        EnergyCoefficients = new float[4];
        EnergyCoefficients[0] = Pdp11fAt(f, offsCalib + 0x44);
        EnergyCoefficients[1] = Pdp11fAt(f, offsCalib + 0x48);
        EnergyCoefficients[2] = Pdp11fAt(f, offsCalib + 0x4c);
        EnergyCoefficients[3] = Pdp11fAt(f, offsCalib + 0x50);

        EnergyUnit = StringAt(f, offsCalib + 0x5c, 0x11);
        McaType = StringAt(f, offsCalib + 0x9c, 0x10);
        DataSource = StringAt(f, offsCalib + 0x108, 0x10);
    }

    private void ReadDateTime(BinaryReader f, long offsParam)
    {
        long offsTimes = offsParam + 0x30 + UInt16At(f, offsParam + 0x24);

        ulong startTimeUnix = DateTimeAt(f, offsTimes + 0x01);
        RealTime = TimeAt(f, offsTimes + 0x09);
        LiveTime = TimeAt(f, offsTimes + 0x11);

        DateTime epoch = new DateTime(1970, 1, 1, 0, 0, 0, DateTimeKind.Utc);
        StartTime = epoch.AddSeconds(startTimeUnix).ToString("dd-MM-yyyy, HH:mm:ss");
    }

    private void ReadShapeCalibration(BinaryReader f, long offsParam)
    {
        long offsCalib = offsParam + 0x30 + UInt16At(f, offsParam + 0x22);
        ShapeCoefficients = new float[4];
        ShapeCoefficients[0] = Pdp11fAt(f, offsCalib + 0xdc);
        ShapeCoefficients[1] = Pdp11fAt(f, offsCalib + 0xe0);
        ShapeCoefficients[2] = Pdp11fAt(f, offsCalib + 0xe4);
        ShapeCoefficients[3] = Pdp11fAt(f, offsCalib + 0xe8);
    }

    private void ReadChannelData(BinaryReader f, long offsParam, long offsChan)
    {
        NumberOfChannels = UInt8At(f, offsParam + 0x00ba) * 256;

        f.BaseStream.Seek(offsChan + 0x200, SeekOrigin.Begin);
        ChannelsData = new uint[NumberOfChannels];
        TotalCounts = 0;

        for (int i = 0; i < NumberOfChannels; i++)
        {
            ChannelsData[i] = f.ReadUInt32();
            TotalCounts += ChannelsData[i];
        }

        MeasurementMode = StringAt(f, offsParam + 0xb0, 0x03);

        Channels = new int[NumberOfChannels];
        for (int i = 0; i < NumberOfChannels; i++)
        {
            Channels[i] = i + 1;
        }
    }

    private void ReadMarkers(BinaryReader f, long offsMark)
    {
        LeftMarker = UInt32At(f, offsMark + 0x007a);
        RightMarker = UInt32At(f, offsMark + 0x008a);
    }

    private void CalculateDerivedData()
    {
        // Tính mảng Năng lượng dựa trên kênh
        if (Channels != null && EnergyCoefficients != null)
        {
            Energy = new double[Channels.Length];
            for (int i = 0; i < Channels.Length; i++)
            {
                double c = Channels[i];
                Energy[i] = EnergyCoefficients[0] + 
                            EnergyCoefficients[1] * c + 
                            EnergyCoefficients[2] * c * c + 
                            EnergyCoefficients[3] * c * c * c;
            }
        }

        // Tính tổng lượng count trong khoảng đánh dấu (markers)
        if (ChannelsData != null && LeftMarker > 0 && RightMarker > 0)
        {
            CountsInMarkers = 0;
            for (uint i = LeftMarker - 1; i < RightMarker - 1 && i < ChannelsData.Length; i++)
            {
                CountsInMarkers += ChannelsData[i];
            }
        }
    }

    // ==========================================
    // CÁC HÀM ĐỌC BINARY CẤP THẤP
    // ==========================================
    private static byte UInt8At(BinaryReader f, long pos)
    {
        f.BaseStream.Seek(pos, SeekOrigin.Begin);
        return f.ReadByte();
    }

    private static ushort UInt16At(BinaryReader f, long pos)
    {
        f.BaseStream.Seek(pos, SeekOrigin.Begin);
        return f.ReadUInt16();
    }

    private static uint UInt32At(BinaryReader f, long pos)
    {
        f.BaseStream.Seek(pos, SeekOrigin.Begin);
        return f.ReadUInt32();
    }

    private static ulong UInt64At(BinaryReader f, long pos)
    {
        f.BaseStream.Seek(pos, SeekOrigin.Begin);
        return f.ReadUInt64();
    }

    private static float Pdp11fAt(BinaryReader f, long pos)
    {
        f.BaseStream.Seek(pos, SeekOrigin.Begin);
        ushort tmp1 = f.ReadUInt16();
        ushort tmp2 = f.ReadUInt16();

        byte[] bytes = new byte[4];
        byte[] b2 = BitConverter.GetBytes(tmp2);
        byte[] b1 = BitConverter.GetBytes(tmp1);

        bytes[0] = b2[0]; bytes[1] = b2[1];
        bytes[2] = b1[0]; bytes[3] = b1[1];

        return BitConverter.ToSingle(bytes, 0) / 4.0f;
    }

    private static double TimeAt(BinaryReader f, long pos)
    {
        ulong val = UInt64At(f, pos);
        return (~val) * 1e-7;
    }

    private static ulong DateTimeAt(BinaryReader f, long pos)
    {
        ulong val = UInt64At(f, pos);
        return (val / 10000000) - 3506716800;
    }

    private static string StringAt(BinaryReader f, long pos, int length)
    {
        f.BaseStream.Seek(pos, SeekOrigin.Begin);
        byte[] bytes = f.ReadBytes(length);
        try
        {
            return Encoding.UTF8.GetString(bytes).Replace("\0", "").Trim();
        }
        catch
        {
            return "READ ERROR";
        }
    }
}
}