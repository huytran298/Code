t = int(input())
while t > 0 :
    s = input()
    a = s.split(' ')
    ans = ""
    for i in a : 
        ans = ans + i[0]
    print(ans)
    t -= 1