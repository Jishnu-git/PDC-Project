#include "PersonTree.hxx"
using namespace std;
map<pair<int,string>,bool> idVec;
void addtoVec(string code,string date){
    for(vector<int>::iterator it = locs.at(code).begin(); it!=locs.at(code).end();it++){
           if(p[*it].wasPresent(date)){
                idVec.insert(pair<pair<int,string>,bool>({*it,date},p[*it].getStatus()));
           }
       }
}
int main(){
    CreateGraph();
    string loc_code, area_code, date;
    cout<<"Enter Location Code: "<<'\n';
    cin>>loc_code;
    cout<<"Enter Area Code: "<<'\n';
    cin>>area_code;
    cout<<"Enter Date (yyyy-mm-dd)";
    cin>>date;


    try{
       //idVec = locs.at(loc_code+area_code);
       
    }
    catch(const std::exception& e){
        cout<<"No data regarding given location and area";
        return 0;
    }
    bool flag = false;
    for(map<pair<int,string>,bool>::iterator it = idVec.begin(); it!=idVec.end();it++){
        if(it->second){
            flag = true;
            break;
        }else{
            vector<pair<string,vector<string>>> templocs;
            templocs = p[it->first.first].getDateRange(it->first.second,5);
            for (vector<pair<string,vector<string>>>::iterator it = templocs.begin(); it != templocs.end(); it++){
                for(vector<string>::iterator i=(*it).second.begin();i!=(*it).second.end();i++){
                    addtoVec(*i,(*it).first);
                }
            }
            
        }
    }
    if(flag){
        cout<<"Infected";
    }else{
        cout<<"Not Infected";
    }
    
    return 0;
}