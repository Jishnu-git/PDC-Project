#include<iostream>
#include<string>
#include<fstream>
#include<list>
#include <sstream>
#include<iterator>
#include<vector>
#include<stdio.h>
#include<map>
using namespace std;
class Time {
    string time;
    string location;
    string places;
    string contacts;

    public:
    void setDetails(string contacts, string time,string location, string place){
        this->time = time;
        this->location = location;
        this->places = place;
        this->contacts = contacts;
    }
    void getDetails(){
        cout<<"Time: "<<time<<' ';
        cout<<"Location: "<<location<<' ';
        cout<<"Place: "<<places<<' ';
        cout<<"Contacts: "<<contacts<<' ';
    }
    string retLocation(){
        return location+places;
    }
};
class Dates {
    string Date;
    int search_date;
    list<Time> times;
    public:
    void setDetails(string dates, Time time ){
        this->Date = dates;
        string tempDate;
        char* date = new char[dates.size() + 1];
        strcpy(date,dates.c_str());
        char *token = strtok(date, "-"); 
        while (token != NULL) 
        {
            tempDate+=token;
            token = strtok(NULL, "-"); 
        }
        this->search_date = stoi(tempDate);
        times.push_back(time);
    }
    void getDetails(){
        list<Time> :: iterator it;
        cout<<"\nDate: "<<Date<<' ';
        for(it = times.begin(); it != times.end(); ++it){
            (*it).getDetails();
        }
    }
    string getDate(){
        return Date;
    }
    int getSDate(){
        return search_date;
    }
    vector<string> retLocVect(){
        vector<string> vec;
        list<Time> :: iterator it;
        for(it = times.begin(); it != times.end(); ++it){
            vec.push_back((*it).retLocation());
        }
        return vec;
    }
};
class Person {
    int ID;
    string first_name;
    string last_name;
    bool status;
    list<Dates>dates;

    public:
    void setDetails(int Id, string first, string last,string stat){
        this->ID = Id;
        this->first_name = first;
        this->last_name = last;
        if(stat == "unknown"){
            this->status = false;
        }else{
            this->status = true;
        }
    }
    
    void setDate(Dates date){
        bool flag = false;
        list<Dates> :: iterator it;
        for(it = dates.begin(); it != dates.end(); ++it){
            if((*it).getDate() == date.getDate()){
                flag = true;
                break;
            }
        }
        if(!flag)
        dates.push_back(date);
    }

    void getDetails(){
        list<Dates> :: iterator it;
            cout<<"ID: "<<ID<<" Name: "<<first_name<<" "<<last_name;
        for(it = dates.begin(); it != dates.end(); ++it){
            (*it).getDetails();
        }
    }
    
    void getDetails(string date){
        list<Dates> :: iterator it;
        for(it = dates.begin(); it != dates.end(); ++it){
            if((*it).getDate() == date){
                (*it).getDetails();
                break;
            }
        }
    }
    bool getStatus(){
        return status;
    }
    bool wasPresent(string date){
        list<Dates> :: iterator it;
        for(it = dates.begin(); it != dates.end(); ++it){
            if((*it).getDate() == date){
                return true;
            }
        }
        return false;
    }
    vector<pair<string,vector<string>>> getDateRange(string date, int range){
        vector<pair<string,vector<string>>> retLocs;
        list<Dates> :: iterator it;
        for(it = dates.begin(); it != dates.end(); ++it){
            if(stoi(date) - (*it).getSDate() <= 5){
                vector<string> temp = (*it).retLocVect();
                retLocs.push_back({(*it).getDate(),temp});
            }
        }
        return retLocs;
    }
};
Person p[1001];
map<string, vector<int>> locs;
void loc_display(){
        for (map<string,vector<int>>::iterator it=locs.begin(); it!=locs.end(); ++it)
    {
        cout << it->first<<' ';
        for(vector<int>::iterator iter=locs.at(it->first).begin(); iter!=locs.at(it->first).end();++iter)
        cout<<*iter<<" ";
        cout<<'\n';
    }
}
int CreateGraph(){

    fstream f;
    string line,word;
    f.open("D:/Projects/PDC-Project/Data/Names.csv",ios::in);
    vector <string> row;
    if(!f){
        cout<<"Error file";
        return 0;
    }
    int count = 0;
    while (!f.eof()) {
        count++; 
        row.clear(); 
        getline(f, line); 
        stringstream s(line); 
  
        while (getline(s, word, ',') && count>1) { 
            row.push_back(word); 
        }
        int id;
        if(count>1){
            try{
                id = stoi(row[0]);
            }
            catch(const std::exception& e){
                std::cerr << e.what() <<" "<<row[0] <<'\n';
                break;
            }
            p[id].setDetails(id,row[1],row[2],row[3]);
        }
    }
    f.close();
    count = 0;
    fstream f1;
    f1.open("D:/Projects/PDC-Project/Data/Logs.csv",ios::in);
    if(!f1){
        cout<<"Error file 1";
        return 0;
    }
    while (!f1.eof()) { 
        count++;
        Time t;
        Dates d;
        row.clear(); 
        getline(f1, line); 
        stringstream s(line); 
        while (getline(s, word, ',')&&count > 1) { 
            row.push_back(word); 
        }
        if(count > 1){
            int it = 7;
            string contacts="";
            while(it < row.size()){
                contacts += row[it++];
            }
            t.setDetails(contacts,row[6],row[3],row[4]);
            d.setDetails(row[5],t);
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
                p[id].setDate(d);
            }
            catch(const std::exception& e)
            {
                std::cerr << e.what() << '\n';
                break;
            }
        }
    }
    f1.close();
    return 0;
}
void person_display(int id){
    p[id].getDetails();
}
void getLocation(string area_code, string location_code =""){
    map<string, vector<int>>::iterator start = locs.lower_bound(area_code+location_code);
    map<string, vector<int>>::iterator end = locs.lower_bound(to_string(stoi(area_code+location_code)+1));
    for (map<string, vector<int>>::iterator i = start; i!=end; i++){
        cout<<i->first<<": ";
        for (vector<int>::iterator j = locs[i->first].begin(); j!= locs[i->first].end(); j++){
            if(p[*j].getStatus()){
                cout<<"Infection Possible";
                break;
            }
        }
        cout<<'\n';
    }
    

}