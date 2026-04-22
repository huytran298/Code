import math
xt = 3.35
sumz = 0
ft = 1
r = [1, 9, 20, 24, 19, 11, 11, 0, 3, 1]
for i in range(0, len(r)):
    ft = ft * i
    if i == 0:
        ft = 1
    sumz += (i - xt) ** 2 * r[i] * (xt ** i * math.exp(-xt) / ft)
print(sumz)
print(sumz / (sum(r) - 1))
print(math.sqrt(sumz))