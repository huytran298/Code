def RowEchelonForm(a, n, m):
    for i in range (0, n):
        for j in range(0, m):
            if a[i][j] != 0:
                for k in range(i + 1, n):
                    for q in range(0, m):
                        a[k][q] -= a[k][j] / a[i][j] * a[i][q]
            else :
                check = -1
                for k in range(i + 1, n):
                    for q in range(0, m):
                        if a[k][q] != 0:
                            check = k
                            break
                    if check != -1:
                        break
                if check != -1:
                    for q in range(0, m):
                        a[check][q] -= a[check][j] / a[i][j] * a[i][q]