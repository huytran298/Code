import numpy as np
from scipy.special import sph_harm
from mpl_toolkits.mplot3d import Axes3D
import matplotlib.pyplot as plt

# Hằng số Bohr (đơn vị a0=1)
a0 = 1.0

# Định nghĩa R_{10}(r)
def R10(r):
    return 2*(1/a0)**1.5 * np.exp(-r/a0)

# Vì Y_0^0 = 1/√(4π) nên ψ_100 = R10(r) * Y00
Y00 = 1/np.sqrt(4*np.pi)
def psi100(r):
    return R10(r) * Y00

# Tạo lưới cầu
n_pts = 2000
# Sinh mẫu r ngẫu nhiên theo phân bố thuận tiện
u = np.random.rand(n_pts)
r = -a0 * np.log(1 - u)  # biến đổi ngẫu nhiên để tập trung points gần nhân
theta = np.arccos(1 - 2*np.random.rand(n_pts))
phi = 2*np.pi*np.random.rand(n_pts)

# Chuyển sang toạ độ Descartes
x = r * np.sin(theta) * np.cos(phi)
y = r * np.sin(theta) * np.sin(phi)
z = r * np.cos(theta)

# Tính biên độ
amp = np.abs(psi100(r))

# Vẽ scatter 3D
fig = plt.figure(figsize=(8,6))
ax = fig.add_subplot(111, projection='3d')
p = ax.scatter(x, y, z,
               c=amp,   # màu theo biên độ
               s=5,     # kích thước điểm
               cmap='viridis',
               alpha=0.6)
ax.set_xlabel('x/a₀')
ax.set_ylabel('y/a₀')
ax.set_zlabel('z/a₀')
fig.colorbar(p, label=r'$|\psi_{1s}|$')
plt.title('Phân phối biên độ trạng thái 1s nguyên tử hydro')
plt.show()
