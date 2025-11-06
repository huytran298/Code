import sys
from pathlib import Path
import matplotlib.pyplot as plt
import math
import numpy as np
from functools import lru_cache

@lru_cache(maxsize=None)
def C(i, j, m, z):
    if z == 0:
        diff = abs(j - i)
        # *** Giữ nguyên điều kiện > 2 theo yêu cầu của bạn ***
        # Tuy nhiên, cần định nghĩa rõ cho diff == 2
        if diff > 2:
            return 0
        elif diff == 1:
            return 1
        elif diff == 0: # j == i
            return -2
        else: # diff == 2
             # Giá trị này không rõ ràng từ code gốc hay paper
             # Giả sử là 0, nhưng có thể cần điều chỉnh
             return 0
    else:
        current_sum = 0
        for l in range(i - m, i + m + 1):
            current_sum += C(l, j, m, z - 1)
        return current_sum

def parse_cnf_txt(file_path: Path):
    energies = []
    counts = []
    in_channel_section = False
    header_skipped = False

    with file_path.open("r", encoding="utf-8", errors="ignore") as f:
        lines = f.readlines() # Đọc hết file một lần để xử lý header dễ hơn

    for idx, line in enumerate(lines):
        line = line.strip()

        if not in_channel_section:
            if line.startswith("# Channel data"):
                in_channel_section = True
                header_skipped = False
            continue

        if in_channel_section and not header_skipped:
             # Tìm dòng header thực sự (ví dụ: '# n energy(keV) counts rate(1/s)')
             # và dòng gạch ngang sau nó
            if line.strip().startswith('#') and 'energy(keV)' in line and 'counts' in line:
                 if idx + 1 < len(lines) and lines[idx+1].strip().startswith("---"):
                     header_skipped = True
                     # Bỏ qua cả dòng gạch ngang bằng cách không làm gì, vòng lặp sẽ tự next
                     continue # Bỏ qua dòng header
                 else: # Nếu không có dòng gạch ngang, format lạ
                      print(f"Warning: Expected separator line after header, not found near line {idx+1}")
                      # Vẫn thử coi dòng tiếp theo là data
                      header_skipped = True
                      continue
            else:
                 # Nếu chưa phải header mong đợi, cứ bỏ qua
                 continue


        if not header_skipped: # Nếu chưa bỏ qua header thì tiếp tục
             continue

        # Đã bỏ qua header, giờ xử lý data
        if line.startswith("#") or not line:
            if not line:
                continue
            # Gặp comment khác -> có thể dừng (hoặc bỏ qua)
            # break # Hoặc continue
            continue


        parts = line.split()
        if len(parts) < 4:
            continue

        try:
            energy_keV = float(parts[1])
            count = int(parts[2])
            energies.append(energy_keV)
            counts.append(count)
        except (ValueError, IndexError):
            continue

    if not counts:
        raise ValueError("No channel data found. Check file format or section markers.")

    return energies, counts


def find_peaks(Sw, F, channels, n1_expected, epsilon):
    """
    Quét qua Sw và F để tìm các đỉnh thỏa mãn điều kiện Mariscotti.

    Args:
        Sw (list): Danh sách giá trị S_i(z,w).
        F (list): Danh sách giá trị F_i(z,w).
        channels (list): Danh sách các chỉ số kênh i tương ứng với Sw và F.
        n1_expected (int): Số kênh dự kiến trong vùng âm (n1).
        epsilon (int): Dung sai cho các điều kiện kiểm tra.

    Returns:
        list: Danh sách các chỉ số kênh i_4 (hoặc centroid) của các đỉnh được tìm thấy.
    """
    peaks_found = []
    i = 0
    n = len(Sw)

    while i < n:
        # Bước 1: Tìm i1 - bắt đầu vùng dương tiềm năng (S > F)
        if Sw[i] > F[i]:
            i1 = channels[i]
            # Bước 2: Tìm i2 - kết thúc vùng dương tiềm năng
            j = i
            while j < n and Sw[j] > F[j]:
                j += 1
            # j bây giờ là chỉ số *sau* vùng dương
            if j == i: # Vùng dương chỉ có 1 điểm -> không thể là đỉnh -> bỏ qua
                 i += 1
                 continue
            i2 = channels[j - 1] # Chỉ số kênh của điểm cuối cùng trong vùng dương
            idx_after_positive = j # Lưu chỉ số index trong Sw/F ngay sau vùng dương

            # Bước 3: Tìm i3 - bắt đầu vùng âm (S < 0)
            # Bắt đầu tìm từ ngay sau vùng dương
            k = idx_after_positive
            while k < n and Sw[k] >= 0:
                 k += 1

            if k == n: # Không tìm thấy vùng âm sau vùng dương -> kết thúc
                break
            if Sw[k] < 0:
                 i3 = channels[k]

                 # Bước 4: Tìm i5 - kết thúc vùng âm
                 l_idx = k # index trong Sw/F
                 while l_idx < n and Sw[l_idx] < 0:
                     l_idx += 1
                 # l_idx bây giờ là chỉ số *sau* vùng âm
                 if l_idx == k: # Vùng âm chỉ có 1 điểm -> không chắc là đỉnh -> bỏ qua? (hoặc xử lý khác)
                      i = l_idx # Chuyển đến điểm tiếp theo sau điểm âm này
                      continue
                 i5 = channels[l_idx - 1] # Chỉ số kênh của điểm cuối cùng trong vùng âm
                 idx_after_negative = l_idx # Lưu chỉ số index trong Sw/F ngay sau vùng âm

                 # Đã có i1, i2, i3, i5 -> tìm i4 và kiểm tra điều kiện
                 # Tìm i4: chỉ số kênh của điểm cực tiểu trong vùng [i3, i5]
                 min_val = float('inf')
                 i4 = -1
                 i4_idx = -1 # index trong Sw/F tương ứng i4
                 # Duyệt trong khoảng index [k, l_idx - 1] tương ứng với [i3, i5]
                 for m_idx in range(k, l_idx):
                      if Sw[m_idx] < min_val:
                           min_val = Sw[m_idx]
                           i4 = channels[m_idx]
                           i4_idx = m_idx

                 if i4_idx == -1: # Không tìm thấy cực tiểu (lỗi logic?)
                      i = idx_after_negative # Bỏ qua, đi tiếp
                      continue

                 # Tính n2, n3
                 # Cẩn thận chia cho 0 nếu S[i4_idx] rất nhỏ
                 s_i4_abs = abs(Sw[i4_idx])
                 f_i4 = F[i4_idx]
                 if s_i4_abs < 1e-9: # Ngưỡng nhỏ để tránh chia cho 0
                      ratio_R = float('inf') # Hoặc xử lý khác nếu S_i4 quá nhỏ
                 else:
                      ratio_R = f_i4 / s_i4_abs

                 # Dùng cận trên n1 + epsilon
                 n1_eff = n1_expected + epsilon
                 n2 = abs(int(ratio_R * 0.5 * n1_eff + 0.5))
                 n3 = abs(int(n1_eff * (1.0 - 2.0 * ratio_R) + 0.5))

                 # Kiểm tra 4 điều kiện
                 cond1 = s_i4_abs > 2 * f_i4
                 cond2 = abs((i5 - i3 + 1) - n1_expected) <= epsilon
                 cond3 = (i3 - i2 - 1) <= max(1, n2) # max(1, n2) xử lý trường hợp n2=0
                 cond4 = (i2 - i1 + 1) >= n3

                 if cond1 and cond2 and cond3 and cond4:
                     # ---- Đỉnh được xác nhận ----
                     # Tính centroid theo công thức (27) nếu muốn chính xác hơn i4
                     sum_centroid_num = 0.0
                     sum_centroid_den = 0.0
                     for m_idx in range(k, l_idx): # Duyệt vùng âm [i3, i5]
                          channel_m = channels[m_idx]
                          s_m = Sw[m_idx] # Giá trị S_i âm
                          sum_centroid_num += channel_m * s_m # i * S_i (S_i < 0)
                          sum_centroid_den += s_m         # S_i (S_i < 0)

                     if abs(sum_centroid_den) > 1e-9:
                          centroid = sum_centroid_num / sum_centroid_den
                     else:
                          centroid = i4 # Dự phòng nếu mẫu số quá nhỏ

                     # peaks_found.append(i4) # Lưu i4 nếu muốn
                     peaks_found.append(centroid) # Lưu centroid tính được
                     print(f"Peak found near channel {i4}, centroid: {centroid:.2f}")
                     print(f"  i1={i1}, i2={i2}, i3={i3}, i4={i4}, i5={i5}")
                     print(f"  n1={n1_expected}, n2={n2}, n3={n3}")
                     print(f"  Cond1:{cond1}, Cond2:{cond2}, Cond3:{cond3}, Cond4:{cond4}")

                     # Chuyển i đến sau vùng âm đã xác định để tránh nhận dạng lại
                     i = idx_after_negative
                 else:
                     # Không phải đỉnh -> chuyển i đến sau vùng dương này để tìm tiếp
                     # Hoặc có thể chỉ tăng i lên 1 để kiểm tra các vùng gối nhau?
                     # Theo flowchart Fig 10, có vẻ nó xử lý tuần tự -> chuyển qua vùng âm đã xét
                     print(f"Candidate rejected near {i4}: Cond1:{cond1}, Cond2:{cond2} [len={i5-i3+1}], Cond3:{cond3} [gap={i3-i2-1}], Cond4:{cond4} [pos_len={i2-i1+1}]")
                     i = idx_after_negative # Bỏ qua ứng viên này, bắt đầu tìm lại từ sau vùng âm

            else: # Không tìm thấy vùng âm ngay sau vùng dương -> bỏ qua vùng dương này
                 i = k # Chuyển đến cuối vùng >= 0 vừa quét
        else:
            # Nếu Sw[i] <= F[i], chỉ cần tăng i lên 1 để tìm điểm bắt đầu i1 tiếp theo
            i += 1

    return peaks_found

def main():
    if len(sys.argv) > 1:
        input_path = Path(sys.argv[1]).expanduser().resolve()
    else:
        input_path = Path(__file__).parent / "Eu-152-16122019.cnf.txt"
        input_path = input_path.resolve()

    if not input_path.exists():
        print(f"Input file not found: {input_path}")
        sys.exit(1)

    energies, counts = parse_cnf_txt(input_path)
    counts_np = np.array(counts, dtype=float)
    N_max = len(counts_np)

    # --- Tính S cơ bản (chỉ để tham khảo/vẽ) ---
    S_basic = []
    channels_basic = list(range(1, N_max - 1))
    for i in channels_basic:
        S_basic.append(counts_np[i + 1] - 2 * counts_np[i] + counts_np[i - 1])

    # --- Tính S_i(z,w) và F_i(z,w) ---
    m = 1
    z = 5
    limit = z * m + 1

    Sw = [] # S generalized
    F = []  # F generalized
    channels_generalized = list(range(limit, N_max - limit))

    print(f"Calculating S(i, z={z}, m={m}) and F(i, z={z}, m={m}) for i from {limit} to {N_max - limit - 1}...")
    for i in channels_generalized:
        sum_S = 0.0
        sum_F_sq = 0.0
        j_min = max(0, i - limit)
        j_max = min(N_max, i + limit + 1)
        for j in range(j_min, j_max):
            Cvalue = C(i, j, m, z)
            if Cvalue != 0:
                count_j = counts_np[j]
                sum_S += Cvalue * count_j
                sum_F_sq += (Cvalue ** 2) * count_j
        Sw.append(sum_S)
        F.append(math.sqrt(max(0, sum_F_sq)))
    print("Calculation complete.")
    # Plot generalized S and F
    fig_sf, axes_sf = plt.subplots(2, 1, sharex=True, figsize=(10, 6))

    axes_sf[0].plot(channels_generalized, Sw, color='C1', linewidth=1, label='S(i)')
    axes_sf[0].axhline(0, color='k', linestyle='--', linewidth=0.6, alpha=0.5)
    axes_sf[0].set_ylabel('S')
    axes_sf[0].set_title(f'Generalized S and F (z={z}, m={m})')
    axes_sf[0].grid(True, alpha=0.3)
    axes_sf[0].legend()

    axes_sf[1].plot(channels_generalized, F, color='C2', linewidth=1, label='F(i)')
    axes_sf[1].set_xlabel('Channel')
    axes_sf[1].set_ylabel('F')
    axes_sf[1].grid(True, alpha=0.3)
    axes_sf[1].legend()

    fig_sf.tight_layout()
    # --- Xác định đỉnh ---
    w = 2 * m + 1
    # Ước tính FWHM ban đầu
    # Lưu ý: Ước tính này có thể không chính xác nếu m không được chọn phù hợp
    # Bài báo nói người dùng cung cấp w (hoặc m) dựa trên ước tính FWHM
    # Ở đây ta tính ngược lại FWHM từ m=1 (có thể không tối ưu)
    FWHM_est = w / 0.6
    print(f"Estimated FWHM based on m={m}: {FWHM_est:.2f} channels")

    # Tính n1
    # Hệ số k_z(omega=0.6, z=5) ~ 1.22 từ Fig 8
    k_z = 1.22
    n1 = abs(int(k_z * FWHM_est + 0.5))
    epsilon = 2 # Dung sai theo đề xuất trong bài báo
    print(f"Expected n1 (negative region width): {n1}, epsilon: {epsilon}")

    # Tìm đỉnh
    found_peak_centroids = find_peaks(Sw, F, channels_generalized, n1, epsilon)

    print(f"\nFound {len(found_peak_centroids)} peaks at centroids: ")
    print([f"{p:.2f}" for p in found_peak_centroids])


    
    # Đồ thị gốc
    all_channels = np.arange(N_max)
    

    # Đồ thị gốc với các đỉnh được đánh dấu
    plt.plot(all_channels, counts_np, color="C0", linewidth=1, label="Counts")
    plt.plot(found_peak_centroids, np.interp(found_peak_centroids, all_channels, counts_np),
               'rv', markersize=8, label='Found Peaks') # Đánh dấu đỉnh bằng mũi tên đỏ
    plt.title("Original Spectrum with Found Peaks")
    plt.xlabel("Channel")
    plt.ylabel("Counts")
    plt.yscale('log')
    plt.grid(True, alpha=0.3)
    plt.legend()
    # axes[2].set_yscale('log') # Có thể bật log scale


    plt.tight_layout()
    plt.show()


if __name__ == "__main__":
    main()