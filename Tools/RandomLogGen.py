import random
import os
import csv
import sys
import datetime

# majorPlaces = ["place1", "place2", "place3"]
# minorPlaces = {
#     "place1": ["m1place1", "m2place1", "m3place1"],
#     "place2": ["m1place2", "m2place2", "m3place2"],
#     "place3": ["m1place3", "m2place3", "m3place3"],
# }

sym = ["|", "/", "-", "\\"]
ind = 0
totEntries = 0

cur_loc = os.path.dirname(__file__)
srcPath = os.path.realpath(os.path.join(cur_loc, "..", "Data", "Names.csv"))
dstPath = os.path.realpath(os.path.join(cur_loc, "..", "Data", "Logs.csv"))

if not os.path.exists(srcPath):
    sys.stderr.write("Names.csv file not found in Data folder, generate one using RandomNameGen.py\nExiting...");
    sys.stderr.flush()
    exit(0)

with open(srcPath, "r", newline = "") as srcFile, open(dstPath, "w", newline = "") as dstFile:
    names = list(csv.DictReader(srcFile)) 
    logs = csv.writer(dstFile)

    logs.writerow(["ID", "First Name", "Last Name", "Area Code", "Location Code", "Date", "Time", "Contact"])
    for i, person in enumerate(names):
        if "count" not in person.keys():
            names[i]["count"] = 0
            person["count"] = 0
    
        if person["count"] >= 7:
            continue
        elif person["count"] == 0:
            count = random.randint(1, 7)
        else:
            count = random.randint(0, 7 - person["count"])
        
        for _ in range(count):
            #generate place
            majorPlace = random.randint(10000,15000)
            minorPlace = random.randint(1,100)

            #generate time
            time = str(random.randrange(7, 24)) + ":" + random.choice(["00", "30"])

            #generate date
            date = datetime.date(2020, 8, 8) + datetime.timedelta(days = random.randint(1, 7))

            #generate contacts
            if random.random() > 0.5:
                contacts = random.choices(range(1, len(names) + 1), k = random.randint(1, 4))
            else:
                contacts = "None"
            
            if contacts != "None" and i in contacts:
                contacts.remove(i)

            contactList = contacts
            if contacts != "None":
                contacts = ", ".join([str(cnt) for cnt in contacts])

            #write activity
            logs.writerow([person["ID"], person["First Name"], person["Last Name"], majorPlace, minorPlace,date, time, contacts])
            totEntries += 1
            if contactList == "None":
                continue

            #write activity of people involved
            for contact in contactList:
                logs.writerow([names[contact - 1]["ID"], names[contact - 1]["First Name"], names[contact - 1]["Last Name"], majorPlace, minorPlace,date, time, contacts.replace(str(contact), str(i + 1))])
                totEntries += 1 
                if "count" not in names[contact - 1].keys():
                    names[contact - 1]["count"] = 1
                else:
                    names[contact - 1]["count"] += 1
        if i % 1000 == 0:
            ind = (ind + 1) % 4
        sys.stdout.write("\r" + sym[ind] + "Processed " + str(i + 1) + " entries" + sym[(4 - ind) % 4])
    sys.stdout.write("\rGenerated " + str(totEntries) + " entries  ")
            
print("\nSuccesfuly generated " + str(totEntries) + " entries and saved at " + dstPath)

            

            
            
            






