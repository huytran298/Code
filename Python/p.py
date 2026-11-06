import numpy as np
from scipy.integrate import nquad

def calculate_fg(Rs, Rde, d):
    """
    Tính hệ số hình học fg.
    Rs: bán kính nguồn
    Rde: bán kính detector
    d: khoảng cách giữa nguồn và detector
    """
    
    # Hàm số dưới dấu tích phân (3 lớp)
    # delta_phi tương đương với (phi1 - phi2)
    def integrand(r1, r2, delta_phi):
        # Tính mẫu số
        # Lũy thừa 3 của căn bậc 2 tương đương lũy thừa 1.5 của biểu thức trong căn
        denominator = (r1**2 + r2**2 - 2*r1*r2*np.cos(delta_phi) + d**2)**1.5
        
        # Tránh lỗi chia cho 0 nếu có (dù thực tế d thường > 0)
        if denominator == 0:
            return 0 
            
        return (r1 * r2 * d) / denominator

    # Cận tích phân (theo thứ tự: r1, r2, delta_phi)
    limits = [
        [0, Rs],        # Cận của r1
        [0, Rde],       # Cận của r2
        [0, 2*np.pi]    # Cận của delta_phi (0 đến 2pi)
    ]

    # Tính diện tích nguồn S1
    S1 = np.pi * Rs**2
    
    # Hằng số nhân bên ngoài sau khi đã tối ưu (1 / 2*S1)
    prefactor = 1 / (2 * S1)

    # Thực hiện tích phân 3 lớp bằng nquad
    # nquad sẽ trả về kết quả và sai số ước lượng
    result, error = nquad(integrand, limits)
    
    fg = prefactor * result
    return fg, error

# ==========================================
# CHẠY THỬ VỚI SỐ LIỆU GIẢ ĐỊNH
# (Bạn hãy thay bằng số liệu thực tế của bài thực hành)
# ==========================================
Rs_val = 24/(2 * 10)       # Ví dụ: 1 cm
Rde_val = 39.03/(2 * 10)      # Ví dụ: 2 cm
d_val = 0.9        # Ví dụ: 5 cm

fg_value, err = calculate_fg(Rs_val, Rde_val, d_val)

print(f"Giá trị fg tính được: {fg_value:.6f}")
print(f"Sai số ước lượng: {err:.2e}")