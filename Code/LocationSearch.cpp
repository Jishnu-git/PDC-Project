#include "PersonTree.hxx"
using namespace std;
map<pair<int,string>,vector<int>> idVec;
void addtoVec(string code,string date, vector<int>contactArr){
    for(vector<int>::iterator it = locs.at(code).begin(); it!=locs.at(code).end();it++){
        if(p[*it].wasPresent(date)){
            vector<int>temp = contactArr;
            // try{
            //    temp = idVec.at({*it,date}); 
            // }
            // catch(const std::exception& e){
            //     std::cerr << e.what() << '\n';
            // }
            temp.push_back(*it);
            idVec.insert(pair<pair<int,string>,vector<int>>({*it,date},temp));
        }
    }
}
int main(){
    CreateGraph();
    vector<int>contactArr;
    string loc_code, area_code, date;
    cout<<"Enter Location Code: "<<'\n';
    cin>>loc_code;
    cout<<"Enter Area Code: "<<'\n';
    cin>>area_code;
    cout<<"Enter Date (yyyy-mm-dd)";
    cin>>date;
    addtoVec(loc_code+area_code, date, contactArr);
    bool flag = false;
    for(map<pair<int,string>,vector<int>>::iterator it = idVec.begin(); it!=idVec.end();it++){
        if(p[it->first.first].getStatus()){
            cout<<"Possibility of Infection Found...\n";
            cout<<"Infection Chain: ";
            // cout<<it->first.first<<' ';
            flag = true;
            for (vector<int>::iterator i = it->second.begin(); i != it->second.end(); i++){
                cout<<*i<<"<--";
            }
            cout<<"Infection\n";
            
            break;
        }else{
            vector<pair<string,vector<string>>> templocs;
            templocs = p[it->first.first].getDateRange(it->first.second,5);
            for (vector<pair<string,vector<string>>>::iterator iter = templocs.begin(); iter != templocs.end(); iter++){
                for(vector<string>::iterator i=(*iter).second.begin();i!=(*iter).second.end();i++){
                    addtoVec(*i,(*iter).first, it->second);
                }
            }
            
        }
    }
    if(!flag){
        cout<<"Not Infected";
    }    
    return 0;
}