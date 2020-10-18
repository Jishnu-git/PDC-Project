#include<iostream>
#include<string>
#include<fstream>
#include<list>
#include <sstream>
#include<iterator>
#include<vector>
#include<map>
using namespace std;
void display(map<string, vector<int>>locs){
        for (map<string,vector<int>>::iterator it=locs.begin(); it!=locs.end(); ++it)
    {
        cout << it->first<<' ';
        for(vector<int>::iterator iter=locs.at(it->first).begin(); iter!=locs.at(it->first).end();++iter)
        cout<<*iter<<" ";
        cout<<'\n';
    }
}
void createLocationGraph(){
    map<string, vector<int>> locs;
    int count = 0;
    fstream f1;
    vector <string> row;
    string line,word;
    f1.open("D:/Projects/PDC-Project/Data/Logs.csv",ios::in);
    if(!f1){
        cout<<"No";
        return;
    }
    while (!f1.eof()) { 
        count++;
        row.clear(); 
        getline(f1, line); 
        stringstream s(line); 
        while (getline(s, word, ',')&&count > 1) { 
            row.push_back(word); 
        }
        if(count > 1){
            int it = 7;
            string contacts="";
            try
            {
                vector <int> ids;
                try{
                    ids = locs.at(row[3]+row[4]);
                }
                catch(const std::exception& e){

                }
                int id = stoi(row[0]);
                ids.push_back(id);
                locs.insert_or_assign((row[3]+row[4]),ids); 
                
            }
            catch(const std::exception& e)
            {
                std::cerr <<"Error: "<< e.what() << '\n';
                break;
            }
        }
    }
    f1.close();
    display(locs);
}
