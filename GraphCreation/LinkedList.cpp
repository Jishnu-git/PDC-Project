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

    public:
    void setDetails(string time,string location, string place){
        this->time = time;
        this->location = location;
        this->places = place;
    }
    void getDetails(){
        cout<<"Time: "<<time<<'\n';
        cout<<"Location: "<<location<<'\n';
        cout<<"Place: "<<places<<'\n';
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
        cout<<"Date: "<<Date<<'\n';
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
};
int main(){
    Person p[10001];
    fstream f;
    string line,word,temp;
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
            int id;
            try
            {
                id = stoi(row[0]);
            }
            catch(const std::exception& e)
            {
                std::cerr << e.what() <<" "<<row[0] <<'\n';
                break;
            }
            p[id].setDetails(id,row[1],row[2]);
            //cout<<word<<" ";
        }
        //cout<<'\n';
        // cout<<row<<'\n';
    }
    f.close();
    count = 0;
    cout<<"Finished 1";
    fstream f1;
    f1.open("D:/Projects/PDC-Project/Data/Logs.csv",ios::in);
    while (f1 >> temp) { 
        count++;
        Time t;
        Dates d;
  
        row.clear(); 
        getline(f1, line); 
  
        cout<<line;
        stringstream s(line); 
        while (getline(s, word, ',')&&count > 1) { 
            row.push_back(word); 
            t.setDetails(row[6],row[3],row[4]);
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
            cout<<row[0]<<'\n';
        }
    }
    f1.close();
    p[1].getDetails();
    return 0;
}