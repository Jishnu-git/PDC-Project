//#include "ParseGraph.hxx"
#include "PersonTree.hxx"
using namespace std;

int main(void) {
    CreateGraph();
    //loc_display();
    vector<pair<string,vector<string>>> l = p[2].getDateRange("2020-08-15",5);
    for (vector<pair<string,vector<string>>>::iterator i = l.begin(); i != l.end(); i++){
        cout<<(*i).first<<" ";
    }
    
    return 0;
}