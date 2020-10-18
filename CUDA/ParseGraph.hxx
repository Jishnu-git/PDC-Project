#ifndef PARSE_GRAPH_GPU_HEADER
#define PARSE_GRAPH_GPU_HEADER

#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>
#include "Timer.hxx"

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

    string info() {
        string op =  "Name: " + fname + " " + lname + "\nID: " + to_string(id) + "\nStatus: ";
        if (!infected) {
            op += "Not ";
        }
        op += "Infected";
        return op;
    }
};

vector<vector<long long>> Graph;
vector<bool> Status;
vector<Person> People;

void makeGraph() {
    cout << "Generating graph from Logs.csv...";
    fstream logs;
    logs.open("../Data/Logs.csv", ios::in);//logs.open("H:/PDC Project/Data/Logs.csv", ios::in);
    Graph.resize(People.size());

    vector<string> row;
    string line, word;
    getline(logs, line);
    long long count = 0;
    Timer timer;
    while (!logs.eof()) {
        row.clear();
        getline(logs, line);
        if (line.compare("") == 0) {
            continue;
        }
        stringstream ss(line);

        while (getline(ss, word, ',')) {
            row.push_back(word);
        }

        long long id = stoll(row[0]);
        vector<long long> contacts;
        if (Graph.size() >= id) {
            contacts = Graph[id - 1];
        }

        if (row[7].compare("None") != 0) {
            int i = 7, n = row.size();
            if (i == n - 1) {
                contacts.push_back(stoll(row[i]));
            } else {
                for (; i < n - 1; i++) {
                    contacts.push_back(stoll(row[i].substr(1)));
                }
                contacts.push_back(stoll(row[n - 1].substr(0, n - 1)));
            }
        }
        
        if (timer.GetTime() >= 0.1) {
            cout << "\rReading Logs.csv: " << count << " entries processed...";
            cout.flush();
            timer.Reset();
        }
        count++;
        Graph[id - 1] = contacts;
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
    Timer timer;
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

        bool status;
        if (!row[3].compare("unknown")) {
            status = false;
        } else {
            status = true;
        }

        if (timer.GetTime() >= 0.1) {
            cout << "\rReading Names.csv: " << row[0] << " entries processed...";
            cout.flush();
            timer.Reset();
        }

        People.push_back(Person(stoll(row[0]), row[1], row[2], status));
        Status.push_back(status);
    }
    cout << "\rReading Names.csv: " << row[0] << " entries processed...";
    cout.flush();
    cout << "\nReading Names.csv: Done" << endl;
    names.close();
}

#endif