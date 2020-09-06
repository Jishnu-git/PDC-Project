import os
import csv
import sys
import random

sym = ["|", "/", "-", "\\"]
ind = 0

n = int(input("Enter number of entries to generate: "))
if n <= 0:
    sys.stderr.write("Enter a number greater than or equal to 1\nExiting...")
    sys.stderr.flush()
    exit(0)

path = os.path.realpath(os.path.join(__file__, os.path.relpath("Data", start = __file__), "Places.csv"))
with open(path, "w", newline = "") as file:
    data = csv.writer(file)
    data.writerow(["Major Place","Minor Place"])
    for i in range(n):
        major = random.randint(10000,15000)
        minor = random.randint(1,100)
        data.writerow([str(i + 1), major,minor])
        if i % 15 == 0:
            ind = (ind + 1) % 4
        sys.stdout.write("\r" + sym[ind] + "Generated " + str(i + 1) + " entries" + sym[(4 - ind) % 4])
    sys.stdout.write("\rGenerated " + str(n) + " entries  ")

print("\nSuccesfuly generated " + str(n) + " entries and saved at " + path)
