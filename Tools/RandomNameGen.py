import names #pip install names
import os
import csv
import sys
import random

sym = ["|", "/", "-", "\\"]
ind = 0

n = int(input("Enter number of entries to generate: "))
ninf = int(input("Enter number of infected individuals: "))
if n <= 0:
    sys.stderr.write("Enter a number greater than or equal to 1\nExiting...");
    sys.stderr.flush()
    exit(0)

path = os.path.realpath(os.path.join(__file__, os.path.relpath("Data", start = __file__), "Names.csv"))
with open(path, "w", newline = "") as file:
    data = csv.writer(file)
    data.writerow(["ID", "First Name", "Last Name", "Infection Status"])
    infected = random.choices(range(n), k = ninf)
    for i in range(n):
        if i in infected:
            status = "infected"
        else:
            status = "unknown"
        data.writerow([str(i + 1), names.get_first_name(), names.get_last_name(), status])
        if i % 15 == 0:
            ind = (ind + 1) % 4
        sys.stdout.write("\r" + sym[ind] + "Generated " + str(i + 1) + " entries" + sym[(4 - ind) % 4])
    sys.stdout.write("\rGenerated " + str(n) + " entries  ")

print("\nSuccesfuly generated " + str(n) + " entries and saved at " + path)
