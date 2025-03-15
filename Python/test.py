import matplotlib.pyplot as plt
import numpy as np
<<<<<<< HEAD
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
=======
from scipy.optimize import curve_fit

# Define the exponential function
def exponential_func(x, a, b, c):
    return a * np.exp(b * x) + c

# Data points
x = np.array([-2, -2.5, -3, -3.5, -4, -4.5])
y = np.array([300, 63, 10, 6, 0.38, 0.225])

# Fit the exponential model to the data
popt, pcov = curve_fit(exponential_func, x, y, p0=(1, 1, 1))

# Extract the parameters
a, b, c = popt

# Generate x values for the fitted curve
x_fit = np.linspace(min(x), max(x), 100)
y_fit = exponential_func(x_fit, a, b, c)

# Plot the original data points
plt.plot(x, y, 'o', label='Data', color='blue')

# Plot the fitted exponential curve
plt.plot(x_fit, y_fit, '-', label='Exponential fit', color='red')

# Add title and labels
plt.title('Exponential Regression')
plt.xlabel('X')
plt.ylabel('Y')
plt.legend()

# Show the plot
>>>>>>> 3269157784b89b8515d9406cf94517df638197f3
plt.show()