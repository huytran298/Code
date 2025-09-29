import csv
import time

filename = '/Users/huytranquoc/Documents/Code/Python/temperatures.csv'

# Write header if file is empty or doesn't exist
try:
    with open(filename, 'x', newline='') as csvfile:
        writer = csv.writer(csvfile)
        writer.writerow(['Second', 'Temperature'])
except FileExistsError:
    pass

print("Enter temperatures (type 'q' to quit):")
start_time = time.time()

while True:
    temp = input("Temperature: ")
    if temp.lower() == 'q':
        break
    try:
        temp_val = float(temp)
    except ValueError:
        print("Invalid input. Please enter a number.")
        continue
    elapsed = int((time.time() - start_time) * 1000)  # milliseconds
    with open(filename, 'a', newline='') as csvfile:
        writer = csv.writer(csvfile)
        writer.writerow([elapsed, temp_val])
    print(f"Recorded: {elapsed}ms, {temp_val}")