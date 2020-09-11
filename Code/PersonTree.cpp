#include<iostream>
#include<string>
#include<fstream>
#include<list>
#include <sstream>
#include<iterator>
#include<vector>
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
};
class Dates {
    string Date;
    list<Time> times;

    public:
    void setDetails(string dates, Time time ){
        this->Date = dates;
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
};
class Person {
    int ID;
    string first_name;
    string last_name;
    list<Dates>dates;

    public:
    void setDetails(int Id, string first, string last){
        this->ID = Id;
        this->first_name = first;
        this->last_name = last;
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
            cout<<ID<<" "<<first_name<<" "<<last_name;
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
};
int main(){
    Person p[1001];
    fstream f;
    string line,word;
    f.open("D:/Projects/PDC-Project/Data/Names.csv",ios::in);
    vector <string> row;
    if(!f){
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
            p[id].setDetails(id,row[1],row[2]);
        }
    }
    f.close();
    count = 0;
    fstream f1;
    f1.open("D:/Projects/PDC-Project/Data/Logs.csv",ios::in);
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
                p[stoi(row[0])].setDate(d);
            }
            catch(const std::exception& e)
            {
                std::cerr << e.what() << '\n';
                break;
            }
        }
    }
    f1.close();
    int id;
    string date;
    cout<<"Enter the ID of the person to be searched: ";
    cin>>id;
    p[id].getDetails();
    cout<<"\n\nEnter the ID of the person and the date (yyyy-mm-dd) to be searched: ";
    cin>>id>>date;
    p[id].getDetails(date);
    return 0;
}