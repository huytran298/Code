import numpy as np
import matplotlib.pyplot as plt
from scipy.optimize import curve_fit

# Dữ liệu từ hình ảnh
x_data = np.array([2, 5, 6.1, 8.3, 10.1, 12.4, 16.5, 20.4, 30.2, 39.9, 50.1, 60.1, 70.5, 79.8, 90.8, 100.5])
y_data = np.array([19081,43960,52144,66875,77943,90096,108909,121942,145122,158810,167976,172064,174666,175816,177387,176861])

# Định nghĩa hàm cần fit
def func(x, I_s, mu_s):
    return I_s * (1 - np.exp(-mu_s * x))

# Thực hiện curve fit
p0 = [350000, 0.05]
popt, pcov = curve_fit(func, x_data, y_data, p0=p0)

# Trích xuất các tham số tối ưu
I_s_opt, mu_s_opt = popt

# Tính sai số chuẩn từ ma trận hiệp phương sai (pcov)
perr = np.sqrt(np.diag(pcov))
I_s_err, mu_s_err = perr

print(f"Các tham số tối ưu (kèm sai số chuẩn):")
print(f"I_s  = {I_s_opt:.2f} ± {I_s_err:.2f}")
print(f"mu_s = {mu_s_opt:.6f} ± {mu_s_err:.6f}")

# Vẽ đồ thị
x_fit = np.linspace(min(x_data), max(x_data), 100)

y_fit = func(x_fit, I_s_opt, mu_s_opt)

plt.figure(figsize=(10, 6))
plt.scatter(x_data, y_data, label='Dữ liệu thực tế', color='blue')
plt.plot(x_fit, y_fit, label=f'Đường fit', color='red')
plt.xlabel('Độ dày')
plt.ylabel('I')
plt.title(f'$I = {I_s_opt:.0f}(1 - exp(-{mu_s_opt:.3f}x)$')
plt.legend()
plt.grid(True)
plt.show()