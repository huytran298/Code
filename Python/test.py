import time, datetime

timeNow = datetime.datetime.now().time()
print(timeNow)
if timeNow >= datetime.time(7,0,0) and datetime.time(15,0,0) :
    print("YES")
else :
    print("NO")
secs = (15 * 3600) - (timeNow.hour * 3600 + timeNow.minute * 60 + timeNow.second)

print(secs)