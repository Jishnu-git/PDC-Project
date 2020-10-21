#include "ParseGraph.hxx"
#include <thrust/host_vector.h>
#include <thrust/device_vector.h>

#define MAX 1024

using namespace std;

__global__
void isInfected(long long *person, long long *solution, bool *visited, bool *status, long long n) {
    long long ind = blockIdx.x * blockDim.x + threadIdx.x;
    if (ind >= n) return;
    visited[person[ind] - 1] = true;
    if (status[person[ind] - 1]) {
        *solution = person[ind] - 1;
    }
}


int main(void) {
    readNames();
    makeGraph();
    bool *h_Status = new bool[Status.size()];
    copy(Status.begin(), Status.end(), h_Status);
    bool *d_Status;
    cudaMalloc((void**)&d_Status, sizeof(bool) * Status.size());
    cudaMemcpy(d_Status, h_Status, sizeof(bool) * Status.size(), cudaMemcpyHostToDevice);
    delete h_Status;

    vector<long long> neighbors;
    bool *visited;
    long long *solution;
    cudaMallocManaged((void**)&solution, sizeof(long long));
    cudaMallocManaged((void**)&visited, sizeof(bool) * People.size());
    *solution = -1;
    
    cout << "Enter ID of person: ";
    long long id; cin >> id;

    if (id < 1 || id >= People.size()) {
        cerr << "\nID out of range\n";
        return -1;
    }
    neighbors.push_back(id);

    Timer timer;
    while (!neighbors.empty() && *solution == -1) {
        long long *d_neighbors;
        cudaMalloc((void**)&d_neighbors, sizeof(long long) * neighbors.size());
        cudaMemcpy(d_neighbors, &neighbors[0], sizeof(long long) * neighbors.size(), cudaMemcpyHostToDevice);
        isInfected<<<neighbors.size() / MAX + 1, MAX>>>(d_neighbors, solution, visited, d_Status, neighbors.size());
        cudaDeviceSynchronize();
        cudaFree(d_neighbors);
        
        if (*solution != -1) {
            cout << "Closest Infected Person: \n" << People[*solution].info() << endl;
            break;
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

    if (*solution == -1) {
        cout << "\nPerson has not come in contact with an infected person\n";
    }

    cout << "\nTime Take: " << time << endl;

    cudaFree(solution);
    cudaFree(visited);
    
    return 0;
}