import numpy as np
import matplotlib.pyplot as plt
from scipy.optimize import curve_fit

# 1. Định nghĩa hàm vật lý cần fit
def inverse_square_law(r, a):
    """Hàm biểu diễn định luật bình phương nghịch đảo"""
    return a / (r**2)

# 2. Khai báo dữ liệu
R = np.array([0.1, 0.2, 0.3, 0.4, 0.6, 0.8, 1.0, 1.5, 2.0])

# Dữ liệu vị trí chính tâm (0)
P_0 = np.array([
    [1100, 1100, 1100], [1100, 1100, 1100], [396.8, 394, 395.6],
    [68.97, 70.08, 69.23], [20.13, 22.46, 20.8], [8.94, 9.13, 8.87],
    [4.18, 4.1, 4.15], [1.17, 1.174, 1.16], [0.73, 0.646, 0.581]
])

# Dữ liệu vị trí lệch (+0.3)
P_pos03 = np.array([
    [7.586, 7.828, 7.756], [14.31, 14.56, 14.89], [22.9, 21.23, 22.4],
    [13.92, 14.02, 13.87], [5.4, 5.5, 5.57], [2.37, 2.302, 2.314],
    [1.24, 1.27, 1.26], [0.5, 0.48, 0.47], [0.267, 0.305, 0.272]
])

# Dữ liệu vị trí lệch (-0.3)
P_neg03 = np.array([
    [7.151, 7.417, 7.647], [15.77, 15.51, 15.63], [24.25, 23.63, 24.19],
    [13.84, 13.97, 14.41], [5.305, 5.485, 5.582], [2.458, 2.446, 2.506],
    [1.07, 1.06, 1.15], [0.4, 0.36, 0.35], [0.275, 0.287, 0.293]
])

# 3. Sử dụng SciPy để tìm hệ số tối ưu
# Loại bỏ 2 khoảng cách đầu (bị bão hòa). Lấy từ R=0.3 trở đi.
R_valid = R[2:]
P_valid = P_0[2:]

# Trải phẳng (flatten) dữ liệu để đưa toàn bộ 21 điểm đo lẻ vào fit, thay vì chỉ lấy trung bình
R_data_flat = np.repeat(R_valid, 3) # Lặp lại mỗi R 3 lần cho khớp với 3 lần đo
P_data_flat = P_valid.flatten()

# Chạy curve_fit
popt, pcov = curve_fit(inverse_square_law, R_data_flat, P_data_flat)
a_optimal = popt[0]

print(f"Hệ số 'a' tìm được bằng SciPy curve_fit là: {a_optimal:.4f}")

# 4. Vẽ đồ thị
plt.figure(figsize=(12, 7))

# Vẽ dữ liệu thực nghiệm
for i in range(3):
    lbl_0 = 'Trục chính (0)' if i == 0 else ""
    lbl_pos = 'Lệch (+0.3)' if i == 0 else ""
    lbl_neg = 'Lệch (-0.3)' if i == 0 else ""
    
    plt.scatter(R, P_0[:, i], color='blue', alpha=0.6, edgecolors='k', s=45, label=lbl_0)
    plt.scatter(R, P_pos03[:, i], color='orange', marker='^', alpha=0.6, edgecolors='k', s=45, label=lbl_pos)
    plt.scatter(R, P_neg03[:, i], color='purple', marker='v', alpha=0.6, edgecolors='k', s=45, label=lbl_neg)

# Đánh dấu vùng bão hòa
sat_r = [0.1]*3 + [0.2]*3
sat_p = [1100]*6

# Vẽ đường cong từ hàm fit của SciPy
R_curve = np.linspace(0.24, 2.1, 200)
P_curve = inverse_square_law(R_curve, a_optimal)
plt.plot(R_curve, P_curve, color='green', linestyle='-', linewidth=2.5,
         label=f'$P(r) = {a_optimal:.2f} / r^2$', zorder=5)

# Định dạng đồ thị
plt.title('Đồ thị Suất liều Thực nghiệm và đường Fit', fontsize=14, fontweight='bold', pad=15)
plt.xlabel('Khoảng cách R', fontsize=12)
plt.ylabel('Suất liều P', fontsize=12)
plt.grid(True, linestyle=':', alpha=0.6)
plt.legend(loc='upper right', fontsize=10, frameon=True, shadow=True)
plt.ylim(-50, 1250)
plt.xlim(0, 2.2)

plt.tight_layout()
plt.show()