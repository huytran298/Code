import pandas as pd
import numpy as np
from scipy.stats import linregress

# ==========================================
# 1. THIẾT LẬP THÔNG SỐ FILE VÀ VẬT LIỆU
# ==========================================
file_csv = 'data.csv'           
cot_x = 'BeDay_mm'              
cot_N = 'N'                     

# Nhập khối lượng riêng của vật liệu (đơn vị: g/cm^3)
# VÍ DỤ: Nhôm (Al) = 2.7, Sắt (Fe) = 7.87, Chì (Pb) = 11.34
rho = 7.87  # <--- BẠN HÃY SỬA SỐ NÀY CHO ĐÚNG VỚI VẬT LIỆU CỦA BẠN

rho = float(input('Input rho please : '))
# ==========================================
# 2. ĐỌC VÀ XỬ LÝ DỮ LIỆU
# ==========================================
try:
    df = pd.read_csv(file_csv, sep='\s+')
except FileNotFoundError:
    print(f"LỖI: Không tìm thấy file '{file_csv}'.")
    exit()

x = df[cot_x].values
N = df[cot_N].values
Y = np.log(N)

# ==========================================
# 3. HỒI QUY TUYẾN TÍNH (Y = b + a*x)
# ==========================================
ket_qua = linregress(x, Y)

a = ket_qua.slope
b = ket_qua.intercept
sai_so_a = ket_qua.stderr
sai_so_b = ket_qua.intercept_stderr

# ==========================================
# 4. TÍNH TOÁN MU VÀ MU PHẨY CÙNG SAI SỐ
# ==========================================
# Tính mu theo đơn vị gốc của x (mm^-1)
mu_mm = -a
sai_so_mu_mm = sai_so_a

# Đổi mu sang cm^-1 để đồng nhất đơn vị với rho (g/cm^3)
mu_cm = mu_mm * 10
sai_so_mu_cm = sai_so_mu_mm * 10

# Tính mu phẩy (cm^2/g)
mu_phay = mu_cm / rho
sai_so_mu_phay = sai_so_mu_cm / rho

# ==========================================
# 5. IN KẾT QUẢ RA MÀN HÌNH
# ==========================================
print("=" * 55)
print("           KẾT QUẢ FITTING DỮ LIỆU GAMMA")
print("=" * 55)
print(f"Hệ số a (độ dốc)           = {a:.6f} ± {sai_so_a:.6f}")
print(f"Hệ số b (ln(N0))           = {b:.6f} ± {sai_so_b:.6f}")
print("-" * 55)
print(f"Hệ số hấp thụ tuyến tính (mu) = {mu_mm:.6f} ± {sai_so_mu_mm:.6f} (mm^-1)")
print(f"                              = {mu_cm:.6f} ± {sai_so_mu_cm:.6f} (cm^-1)")
print("-" * 55)
print(f"Khối lượng riêng (rho)        = {rho} (g/cm^3)")
print(f"Hệ số hấp thụ khối (mu')      = {mu_phay:.6f} ± {sai_so_mu_phay:.6f} (cm^2/g)")
print("=" * 55)
