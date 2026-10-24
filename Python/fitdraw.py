import numpy as np
import matplotlib.pyplot as plt
from scipy.optimize import curve_fit

# 1. Nhập dữ liệu
x_data = np.array([2, 5, 6.1, 8.3, 10.1, 12.4, 16.5, 20.4, 30.2, 39.9, 
                   50.1, 60.1, 70.5, 79.8, 90.8, 100.5])
y_data = np.array([30752, 75193, 90351, 119334, 142280, 168048, 210225, 
                   242610, 305480, 344997, 373844, 389224, 399157, 
                   405987, 410467, 411367])

# 2. Định nghĩa hàm cần khớp
def model_func(x, I_s, mu_s):
    return I_s * (1 - np.exp(-mu_s * x))

# 3. Thực hiện khớp đường cong
initial_guess = [415000, 0.05]
popt, pcov = curve_fit(model_func, x_data, y_data, p0=initial_guess)

I_s_opt, mu_s_opt = popt

# Tính sai số từ đường chéo của ma trận hiệp phương sai (pcov)
perr = np.sqrt(np.diag(pcov))
I_s_err, mu_s_err = perr

# In kết quả đi kèm sai số
print(f"Giá trị I_s : {I_s_opt:.2f} ± {I_s_err:.2f}")
print(f"Giá trị mu_s: {mu_s_opt:.5f} ± {mu_s_err:.5f}")

# 4. Vẽ đồ thị
x_fit = np.linspace(min(x_data), max(x_data), 200)
y_fit = model_func(x_fit, I_s_opt, mu_s_opt)

plt.figure(figsize=(9, 6))
plt.scatter(x_data, y_data, color='red', label='Dữ liệu thực nghiệm', zorder=5)
plt.plot(x_fit, y_fit, color='blue', label='Đường khớp', linewidth=2)

title_equation = f'$y = {I_s_opt:.0f} \\cdot (1 - e^{{-{mu_s_opt:.4f} \\cdot x}})$'
plt.title(title_equation, fontsize=14, pad=15)
plt.xlabel('Bề dày (cm)', fontsize=12)
plt.ylabel('Số đếm', fontsize=12)
plt.legend(fontsize=11)
plt.grid(True, linestyle='--', alpha=0.7)
plt.show()