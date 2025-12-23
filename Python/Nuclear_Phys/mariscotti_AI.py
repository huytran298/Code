import numpy as np
import matplotlib.pyplot as plt
from pathlib import Path
from typing import Tuple
from scipy.signal import find_peaks
import sys

# --- (Toàn bộ các hàm parse_cnf_txt, get_mariscotti_kernel, 
#      calculate_mariscotti_functions của bạn giữ nguyên ở đây) ---
def parse_cnf_txt(file_path: Path):
    energies = []
    counts = []

    in_channel_section = False
    header_skipped = False

    with file_path.open("r", encoding="utf-8", errors="ignore") as f:
        for line in f:
            line = line.strip()

            # Find start of channel data section
            if not in_channel_section:
                if line.startswith("# Channel data"):
                    in_channel_section = True
                    header_skipped = False  # next lines will be headers to skip
                continue

            # Skip the header lines right after "# Channel data"
            if in_channel_section and not header_skipped:
                # Expect two lines: column headers and dashed separator
                header_skipped = True  # this marks we saw the header title
                next(f, None)          # skip dashed separator line
                continue

            # Stop if we hit another comment block (unlikely in this file)
            if line.startswith("#") or not line:
                # allow blank lines; continue reading
                if not line:
                    continue

            # Parse data rows: n, energy(keV), counts, rate(1/s)
            parts = line.split()
            if len(parts) < 4:
                continue

            try:
                energy_keV = float(parts[1])
                count = int(parts[2])
            except ValueError:
                continue

            energies.append(energy_keV)
            counts.append(count)

    if not energies or not counts:
        raise ValueError("No channel data found. Check file format or section markers.")

    return energies, counts



def get_mariscotti_kernel(w: int, z: int = 5) -> np.ndarray:
    """
    Tính toán nhân (kernel) C_ij(z, w) của Mariscotti.
    """
    if not isinstance(w, int) or w <= 0 or w % 2 == 0:
        raise ValueError("Cửa sổ 'w' phải là một số nguyên dương, lẻ.")
    
    # Bắt đầu với nhân (kernel) z=0 (sai phân bậc hai đơn giản)
    kernel = np.array([1.0, -2.0, 1.0])
    
    # Cửa sổ tổng di động (moving sum)
    sum_window = np.ones(w)
    
    # Lặp lại phép tích chập 'z' lần để làm mượt
    for _ in range(z):
        kernel = np.convolve(kernel, sum_window, mode='full')
    
    return kernel

def calculate_mariscotti_functions(counts: list, w: int, z: int = 5) -> Tuple[np.ndarray, np.ndarray]:
    """
    Tính toán hàm Sai phân bậc hai tổng quát S_i(z, w) và Độ lệch chuẩn F_i(z, w).
    """
    N = np.asarray(counts, dtype=float)
    
    # 1. Lấy nhân Mariscotti C_ij(z, w)
    kernel = get_mariscotti_kernel(w, z)
    
    # 2. Tính S_i(z, w) bằng cách tích chập N_i với nhân
    S_i = np.convolve(N, kernel, mode='same')
    
    # 3. Tính hệ số phi(z, w) = Σ_j C_ij^2(z, w)
    phi = np.sum(kernel**2)
    
    # 4. Tính Độ lệch chuẩn F_i(z, w) ≈ sqrt(phi(z, w) * N_i)
    N_positive = np.maximum(N, 0) # Đảm bảo không lấy căn số âm
    F_i = np.sqrt(phi * N_positive)
    
    # Xử lý trường hợp N_i = 0 để tránh F_i = 0
    F_i[F_i == 0] = 1.0 
    
    return S_i, F_i
# --- HẾT PHẦN HÀM ---


# --- XỬ LÝ ĐƯỜNG DẪN FILE ---
try:
    if len(sys.argv) > 1:
        input_path = Path(sys.argv[1]).expanduser().resolve()
    else:
        # Default to the sample file in the same directory as this script
        # *** LƯU Ý ***: Nếu bạn chạy trong môi trường (ví dụ: Jupyter), 
        # __file__ sẽ bị lỗi. Hãy thay thế bằng đường dẫn tuyệt đối.
        # input_path = Path("/đường/dẫn/tuyệt/đối/tới/file/Eu-152-16122019.cnf.txt")
        input_path = Path(__file__).parent / "Eu-152-16122019.cnf.txt"
        input_path = input_path.resolve()

except NameError:
    print("Lỗi: Không tìm thấy biến '__file__'.")
    print("Vui lòng sửa code và cung cấp đường dẫn tuyệt đối đến file .cnf.txt")
    # Thay thế bằng đường dẫn của bạn ở đây
    input_path = Path("Eu-152-16122019.cnf.txt").expanduser().resolve() 
    if not input_path.exists():
        print(f"Đã thử đường dẫn mặc định nhưng vẫn không tìm thấy: {input_path}")
        sys.exit(1)


if not input_path.exists():
    print(f"Input file not found: {input_path}")
    sys.exit(1)

print(f"Đang đọc file: {input_path}")
# Đọc file, trả về 2 list
energies_list, counts_list = parse_cnf_txt(input_path)

# *** SỬA LỖI Ở ĐÂY ***
# Chuyển từ list sang mảng NumPy
channels = np.array(energies_list)
counts = np.array(counts_list)
# *** KẾT THÚC SỬA LỖI ***

w_parameter = 55

try:
    # 1. Tính toán hàm S_i và F_i
    # Giờ 'counts' đã là mảng NumPy, truyền vào là chính xác
    S_i, F_i = calculate_mariscotti_functions(counts, w_parameter)

    # 2. Tìm đỉnh (Peak Finding)
    # 'prominence' giúp lọc các đỉnh dựa trên "độ nổi bật" của chúng trong hàm -S_i
    # Tăng prominence để lọc nhiễu tốt hơn
    peak_indices, _ = find_peaks(-S_i, prominence=100) # Tăng giá trị này nếu có quá nhiều đỉnh nhiễu
    
    # 3. Lọc đỉnh dựa trên điều kiện Mariscotti
    significant_peak_indices = [
        i for i in peak_indices if S_i[i] < -F_i[i]
    ]

    # 4. Lấy tọa độ (channel, count) của các đỉnh đã xác định
    # *** KHÔNG CÒN LỖI ***
    # Vì 'channels' và 'counts' là mảng NumPy, chúng có thể được
    # truy cập bằng một list các chỉ số (significant_peak_indices)
    peak_channels = channels[significant_peak_indices]
    peak_counts = counts[significant_peak_indices]

    print(f"Đã xác định được {len(peak_channels)} đỉnh.")
    if len(peak_channels) > 0:
        print("Các đỉnh (Năng lượng, Số đếm):")
        for k, c in zip(peak_channels, peak_counts):
            print(f"- {k:.2f} keV, {c} counts")


    # 5. BẮT ĐẦU PHẦN PLOT DỮ LIỆU
    plt.figure(figsize=(12, 7))
    
    # Vẽ dữ liệu thô (số đếm)
    plt.plot(channels, counts, '-', label='Dữ liệu thô (Counts)', linewidth=0.7, alpha=0.8)
    
    # Đánh dấu các đỉnh đã tìm thấy
    if len(peak_channels) > 0:
        plt.scatter(
            peak_channels, 
            peak_counts, 
            color='red', 
            marker='x', 
            s=100,
            linewidth=2,
            label=f'Đỉnh được xác định ({len(peak_channels)})'
        )
    
    plt.title(f'Phân tích phổ - {input_path.name}')
    plt.xlabel('Năng lượng (keV)') # Đổi thành Năng lượng thay vì Kênh
    plt.ylabel('Số đếm (Counts)')
    plt.legend()
    plt.grid(True, linestyle='--', alpha=0.6)
    plt.yscale('log') # Thêm thang log để dễ nhìn các đỉnh nhỏ
    plt.tight_layout()
    
    # *** THÊM DÒNG NÀY ĐỂ HIỂN THỊ BIỂU ĐỒ ***
    plt.show()

except ValueError as e:
    print(f"Lỗi: {e}")
except Exception as e:
    print(f"Đã xảy ra lỗi không xác định: {e}")