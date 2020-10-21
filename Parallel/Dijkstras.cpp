#include "ParseGraph.hxx"
#include <omp.h>

using namespace std;

int main(void) {
    readNames();
    makeGraph();
    omp_set_num_threads(6);
    
    while (true) {
        vector<long long> neighbors;
        vector<bool> visited(People.size(), false);
        long long solution = -1;

        cout << "Enter ID of person: ";
        long long id; cin >> id;

        if (id < 1 || id >= People.size()) {
            cerr << "\nID out of range\n";
            return -1;
        }
        neighbors.push_back(id);

        cout << "\nProcessing...";
        Timer timer, op;
        while (!neighbors.empty() && solution == -1) {
            if (op.GetTime() >= 0.1) {
                cout << "\rEntries Processed: " << count_if(visited.begin(), visited.end(), [](bool status) {
                    return status;
                });
                cout.flush();
                op.Reset();
            }

            #pragma omp parallel for
            for (long long ind = 0; ind < neighbors.size(); ind++) {
                visited[neighbors[ind] - 1] = true;
                if (Status[neighbors[ind] - 1]) {
                    solution = neighbors[ind] - 1;
                }
            }
            
            vector<long long> newNeighbors;
            for (auto neighbor: neighbors) {
                copy_if(Graph[neighbor - 1].begin(), Graph[neighbor - 1].end(), back_inserter(newNeighbors), [visited](long long id) {
                    return !visited[id];
                });
            }
            neighbors.clear();
            neighbors = newNeighbors;
        }   
        double time = timer.Stop();

        cout << "\rEntries Processed: " << count_if(visited.begin(), visited.end(), [](bool status) {
                    return status;
                }) 
            << "... Done" << endl;
        if (solution == -1) {
            cout << "\nPerson has not come in contact with an infected person\n";
        } else {
            cout << "Closest Infected Person: \n" << People[solution].info() << endl;
        }
        cout << "\nTime Takken: " << time << "s" << endl;
    }
    return 0;
}