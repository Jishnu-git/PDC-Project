#include "ParseGraph.hxx"

using namespace std;

int main(void) {
    readNames();
    makeGraph();
    for (vector<long>::iterator i = Graph[4].begin(); i != Graph[4].end(); i++) {
        cout << *i << endl;
    }
    return 0;
}