import matplotlib.pyplot as plt
import numpy as np
import math

x = np.linspace(-1, 0, 100)
y = 1 + x
plt.plot(x, y, 'g', label='F(x) = 1 + x')
x1 = np.linspace(0, 1, 100)
y1 = 1 - x1
plt.plot(x1, y1, 'r', label='F(x) = 1 - x')
x2 = np.linspace(-2, -1, 100)
y2 = 0 * x2
plt.plot(x2, y2, 'b', label='F(x) = 0')
x2 = np.linspace(1, 2, 100)
y2 = 0 * x2
plt.plot(x2, y2, 'b')
plt.legend()
plt.grid()
plt.show()