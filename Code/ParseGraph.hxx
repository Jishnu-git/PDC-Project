#include <vector>
#include <map>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>

using namespace std;

class Person {
    int id;
    string fname;
    string lname;
    bool infected;

public:
    Person(int id, std::string fname, std::string lname, bool infected):
        id(id), fname(fname), lname(lname), infected(infected)
        {}

    bool isInfected() {
        return infected;
    }

    string getFname() {
        return fname;
    }

    string getLname() {
        return lname;
    }

    int getID() {
        return id;
    }
};

map<long, vector<long>> Graph;
vector<Person> People;

void makeGraph() {
    cout << "Generating graph from Logs.csv...";
    fstream logs;
    logs.open("../Data/Logs.csv", ios::in);//logs.open("H:/PDC Project/Data/Logs.csv", ios::in);

    vector<string> row;
    string line, word;
    getline(logs, line);
    long count = 0;
    while(!logs.eof()) {
        row.clear();
        getline(logs, line);
        if (line.compare("") == 0) {
            continue;
        }
        stringstream ss(line);

        while(getline(ss, word, ',')) {
            row.push_back(word);
        }

        long id = stol(row[0]);
        vector<long> contacts;
        if (Graph.find(id) != Graph.end()) {
            contacts = Graph[id];
        }

        if (row[7].compare("None") != 0) {
            int i = 7, n = row.size();
            if (i == n - 1) {
                contacts.push_back(stol(row[i]));
            } else {
                for (;i < n - 1; i++) {
                    contacts.push_back(stol(row[i].substr(1)));
                }
                contacts.push_back(stol(row[n - 1].substr(0, n - 1)));
            }
            
        }

        vector<long>::iterator len = unique(contacts.begin(), contacts.end());
        contacts.resize(distance(contacts.begin(), len));
        cout << "\rReading Logs.csv: " << ++count << " entries processed...";
        cout.flush();
        Graph[id] = contacts;
    }
    cout << "\nReading Logs.csv: Done" << endl;
    logs.close();
}

void readNames() {
    cout << "Reading Names.csv...";
    fstream names;
    names.open("../Data/Names.csv", ios::in);//names.open("H:/PDC Project/Data/Names.csv", ios::in);

    vector<string> row;
    string line, word;
    getline(names, line);
    while (!names.eof()) {
        row.clear();
        getline(names, line);
        if (line.compare("") == 0) {
            continue;
        }
        stringstream ss(line);

        while (getline(ss, word, ',')) {
            row.push_back(word);
        }

        int status;
        if (row[3].compare("unknown") == 0) {
            status = 0;
        } else if (row[3].compare("infected") == 0) {
            status = 1;
        } else {
            status = -1;
        }
        
        cout << "\rReading Names.csv: " << row[0] << " entries processed...";
        cout.flush();
        People.push_back(Person(stol(row[0]), row[1], row[2], status));
    }

    cout << "\nReading Names.csv: Done" << endl;

    names.close();
}

