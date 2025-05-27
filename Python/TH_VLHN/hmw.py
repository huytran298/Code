import matplotlib.pyplot as plot


nameOfFile = '/Users/quochuytran/Documents/Code/Python/TH_VLHN/Cd-109.txt'
beginTable = False
table = [[],[],[],[]]
isheader = 0
with open(nameOfFile, 'r', encoding='utf8') as file :
    for line in file : 
        line = line.strip()
        if not line : 
            continue
        #print(line)
        if beginTable :
            if not table and isheader < 2 :
                isheader += 1
            else :
                try :
                    row = list(map(float, line.split()))
                    for i in range(0, 4):
                        table[i].append(row[i])
                except :
                    continue
        if '# Channel data' in line : 
            beginTable = True
    #print(table[3][1])
    plot.title("Đường chuẩn năng lượng")
    plot.xlabel("Số kênh")
    plot.ylabel("Năng lượng")
    plot.plot(table[1], table[2])
    plot.show()
    
