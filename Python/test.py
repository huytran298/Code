import matplotlib.pyplot as plt
import numpy as np
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
plt.show()