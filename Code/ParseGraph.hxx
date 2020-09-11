#include <vector>
#include <map>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <ctime>

using namespace std;

class Person {
    long long id;
    string fname;
    string lname;
    bool infected;

public:
    Person(long long id, std::string fname, std::string lname, bool infected):
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

    long long getID() {
        return id;
    }
};

map<long long, vector<long long>> Graph;
vector<Person> People;

void makeGraph() {
    cout << "Generating graph from Logs.csv...";
    fstream logs;
    logs.open("../Data/Logs.csv", ios::in);//logs.open("H:/PDC Project/Data/Logs.csv", ios::in);

    vector<string> row;
    string line, word;
    getline(logs, line);
    long long count = 0;
    clock_t timer = clock();
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

        long long id = stoll(row[0]);
        vector<long long> contacts;
        if (Graph.find(id) != Graph.end()) {
            contacts = Graph[id];
        }

        if (row[7].compare("None") != 0) {
            int i = 7, n = row.size();
            if (i == n - 1) {
                contacts.push_back(stoll(row[i]));
            } else {
                for (;i < n - 1; i++) {
                    contacts.push_back(stoll(row[i].substr(1)));
                }
                contacts.push_back(stoll(row[n - 1].substr(0, n - 1)));
            }
            
        }

        vector<long long>::iterator len = unique(contacts.begin(), contacts.end());
        contacts.resize(distance(contacts.begin(), len));
        if ((float)(clock() - timer) / CLOCKS_PER_SEC >= 0.1) {
            cout << "\rReading Logs.csv: " << count << " entries processed...";
            cout.flush();
            timer = clock();
        }
        count++;        
        Graph[id] = contacts;
    }
    cout << "\rReading Logs.csv: " << count << " entries processed...";
    cout.flush();
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
    clock_t timer = clock();
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

        if ((float)(clock() - timer) / CLOCKS_PER_SEC >= 0.1) {
            cout << "\rReading Names.csv: " << row[0] << " entries processed...";
            cout.flush();
            timer = clock();
        }
        People.push_back(Person(stoll(row[0]), row[1], row[2], status));
    }
    cout << "\rReading Names.csv: " << row[0] << " entries processed...";
    cout.flush();

    cout << "\nReading Names.csv: Done" << endl;

    names.close();
}

