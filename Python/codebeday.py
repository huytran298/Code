import os
import numpy as np
from scipy.optimize import curve_fit

def gaussian(x, a, x0, sigma, c):
    return a * np.exp(-(x - x0)**2 / (2 * sigma**2)) + c

def fit_16_nuclear_peaks_with_errors(folder_path, file_name):
    file_path = os.path.join(folder_path, file_name)
    print(f"Đang xử lý file: {file_path}")
    
    # Đọc dòng header để lấy tên file
    try:
        with open(file_path, 'r', encoding='utf-8') as f:
            header_line = f.readline().strip()
            # Xóa dấu # ở đầu nếu có và tách các từ
            headers = header_line.lstrip('#').split()
            
            if len(headers) < 2:
                print("Lỗi: Header không có đủ thông tin (cần ít nhất cột channel và 1 cột dữ liệu).")
                return
            
            # Bỏ qua cột đầu tiên (channel), lấy danh sách tên file
            column_names = headers[1:]
    except Exception as e:
        print(f"Lỗi khi đọc header file: {e}")
        return

    # Đọc dữ liệu số, bỏ qua dòng header (skiprows=1)
    try:
        data = np.loadtxt(file_path, skiprows=1)
    except Exception as e:
        print(f"Lỗi khi đọc dữ liệu số: {e}")
        return
        
    x = data[:, 0]
    
    x_left = float(input("Nhập marker trái (X): "))
    x_right = float(input("Nhập marker phải (X): "))
    
    mask = (x >= x_left) & (x <= x_right)
    x_fit = x[mask]
    
    if len(x_fit) == 0:
        print("Lỗi: Không có dữ liệu trong vùng đã chọn.")
        return

    print("\n" + "="*125)
    print(f"{'Tên File':<15} | {'Tâm x0 ± Sai số':<20} | {'Độ rộng σ ± Sai số':<20} | {'Chiều cao a ± Sai số':<20} | {'Diện tích ± Sai số':<25}")
    print("-" * 125)
    
    # Xác định số lượng cột Y dựa trên kích thước dữ liệu (tối đa 16 hoặc theo số tên file lấy được)
    num_columns = min(data.shape[1] - 1, len(column_names), 16)
    
    for i in range(1, num_columns + 1):
        col_name = column_names[i-1]
        # Cắt ngắn tên file nếu quá dài để bảng hiển thị đẹp hơn
        if len(col_name) > 15:
            col_name = col_name[:12] + "..."
            
        try:
            y = data[:, i]
        except IndexError:
            break
            
        y_fit = y[mask]
        
        a_guess = np.max(y_fit) - np.min(y_fit)
        x0_guess = x_fit[np.argmax(y_fit)]
        sigma_guess = (x_right - x_left) / 4.0
        c_guess = np.min(y_fit)
        p0 = [a_guess, x0_guess, sigma_guess, c_guess]
        
        try:
            popt, pcov = curve_fit(gaussian, x_fit, y_fit, p0=p0)
            a, x0, sigma, c = popt
            
            perr = np.sqrt(np.diag(pcov))
            err_a, err_x0, err_sigma, err_c = perr
            
            sigma_abs = np.abs(sigma)
            area = a * sigma_abs * np.sqrt(2 * np.pi)
            
            df_da = sigma_abs * np.sqrt(2 * np.pi)
            df_dsigma = a * np.sqrt(2 * np.pi) * np.sign(sigma)
            
            var_a = pcov[0, 0]
            var_sigma = pcov[2, 2]
            cov_a_sigma = pcov[0, 2]
            
            var_area = (df_da**2 * var_a) + (df_dsigma**2 * var_sigma) + (2 * df_da * df_dsigma * cov_a_sigma)
            err_area = np.sqrt(var_area) if var_area > 0 else 0
            
            print(f"{col_name:<15} | {x0:>8.3f} ± {err_x0:<8.3f} | {sigma_abs:>8.3f} ± {err_sigma:<8.3f} | {a:>8.3f} ± {err_a:<8.3f} | {area:>10.3f} ± {err_area:<10.3f}")
            
        except RuntimeError:
            print(f"{col_name:<15} | {'Lỗi: Không thể hội tụ cho phổ này':<100}")
        except Exception as e:
            print(f"{col_name:<15} | Lỗi khác: {str(e):<90}")
    print("="*125)

# --- CÁCH SỬ DỤNG ---
# thu_muc = r"C:\ThuMucCuaToi\DuLieuPho"
# ten_file = "data_kem_header.txt"
# fit_16_nuclear_peaks_with_errors(thu_muc, ten_file)
thu_muc = r"C:\Users\huyhuyne\Downloads\filebeday"
ten_file = "vvv.txt"

# Gọi hàm
fit_16_nuclear_peaks_with_errors(thu_muc, ten_file)