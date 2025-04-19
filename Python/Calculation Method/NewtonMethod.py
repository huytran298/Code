def f(x) :
    return x**2 - 91
def g(x) :
    return 2*x

x0 = 10
x1 = x0 - f(x0)/g(x0)
epsilon = 0.0005
step = 1
while abs(x1 - x0) > epsilon:
    x0 = x1
    x1 = x0 - f(x0)/g(x0)
    step += 1
print('step =', step)
print(x1)
