t = int(input())
while t > 0:
    t -= 1
    n = int(input())
    tbl = []
    for i in range(0, n):
        inp = input()
        tbl.append(list(map(int, inp.split(' '))))
    a = [0] * (2 * n + 1)
    for i in range(0, n):
        for j in range(0, n):  
            a[i + j + 2] = tbl[i][j]
            
    found = False
    
    for i in range(1, 2 * n + 1):
        found = True
        for j in a:
            if i == j : 
                found = False
                break
        if found :
            a[1] = i
            break
    
    for i in range(1, 2 * n + 1) : 
        print(a[i], end=" ")    
    print('')
