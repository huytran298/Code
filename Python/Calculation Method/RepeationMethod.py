import math 
def f(x) :
    return x*x - 2023
def f1(x) :
    return 2*x
def f2(x) :
    return 2

def NewtonMethod():
    x0 = float(input('input x0 : '))
    epsilon = float(input('input epsilon : '))
    if abs(f(x0) * f2(x0) / f1(x0) ** 2) >= 1 : 
        print('Not covered')
        return 
    x1 = x0 - f(x0)/f1(x0)
    step = 1
    while abs(x1 - x0) > epsilon:
        x0 = x1
        x1 = x0 - f(x0)/f1(x0)
        step += 1
        if step > 20 :
            print('The function does not converge')
            return 
    print('step =', step)
    print('Value is ', x1)
def L_k(n, k, X, x):
    prd = 1
    for i in range(0, n):
        if i != k:    
            prd *= (x - X[i]) / (X[k] - X[i])
    return prd               
def LagrangeMethod():
    X = list(map(float, input('Nhap day X: ').split()))
    
    Y = list(map(float, input('Nhap day Y: ').split()))
    n = int(input('Nhap so diem muon xet : '))
    x = int(input('Nhap diem muon xet :'))
    sum = 0
    for k in range(0, n):
        sum += Y[k] * L_k(n, k, X, x)
    print('Value is ', sum)
def RepeationMethod():
    x0 = float(input('input x0 : '))
    epsilon = float(input('input epsilon : '))
    
    step = 0
    while abs(f(x0) - x0) >= epsilon :
        x0 = f(x0)
        step += 1
    print(f'step : {step}')
    print(f'value : {x0}')
def diff(A, k, i):
    k = min(len(A) - 1, k)
    if k == 0:
        return A[i]
    return diff(A, k - 1, i + 1) - diff(A, k - 1, i)
def NewtonTien():
    X = list(map(float, input().split(' ')))
    y = list(map(float, input().split(' ')))
    x = float(input())
    n = int(input())
    dec = int(input())
    u = round((x - X[0]) / abs(X[1] - X[0]), dec)
    tmp = 1
    ans = 0
    error = 1
    for i in range(0, n):
        ans += round(tmp * round(diff(y, i, 0), dec), dec)
        #print(f'{tmp}')
        tmp *= (u - i) / (i + 1)    
    for i in range(0, n):
        error *= round((u - i) / (i + 1), dec)
    error *= diff(y, n, 0)
    print(f'value is {round(ans, dec)}')
    print(f'error {error}')
def u_k(u, k):
    st = 1
    ans = 1
    for i in range(1, k):
        ans *= (u + i - 1) / i
    return ans


def NewtonLui():
    X = list(map(float, input().split(' ')))
    y = list(map(float, input().split(' ')))
    x = float(input())
    dec = 5
    st = list(map(int, input().split(' ')))
    n = len(st)
    ans = 0
    cnt = 1
    u = (x - X[len(X) - 2]) / abs(X[0] - X[1])
    for i in range(0, n):
        tmp = 1
        for j in range(1, i + 1):
            tmp *= (u + j - 1) / j
        print(diff(y, i, st[n - i - 1]))
        ans += tmp * diff(y, i, st[n - i - 1])
    error = 1
    
    print(ans)
    
NewtonMethod()