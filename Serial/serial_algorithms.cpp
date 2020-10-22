#include "ParseGraph.hxx"
#include <bits/stdc++.h> 
#include <omp.h>
#include "../Parallel/Timer.hxx"

using namespace std;

int infected_bfs(int id, int n){
	long count = 0;
	vector<bool> visited;
	visited.assign(n, false);
	queue<int> que; 
	que.push(id); 
    visited[id] = true; 
    while (!que.empty()) {   
        int front = que.front(); 
        que.pop();
        cout << front << " in consideration"<<endl;
        for (vector<long long>::iterator i = Graph[front].begin(); i != Graph[front].end(); i++) {
        	if(visited[*i]==false){
        		count+=1;
        		if(People[*i-1].isInfected()){
        			cout<<endl<<"Closest Infect Person is "<<People[*i-1].getFname()<<" "<<People[*i-1].getLname();
        			return count;
				}
				else{
					cout<<*i<<" ";
					que.push(*i);
					visited[*i]=true;
				}
			}
    	}
    	cout<<endl;
    }
    cout<<"No infected person found"<<endl;
    return count;
}
int infected_dfs(int id, int n){
	long count = 0;
	vector<bool> visited;
	visited.assign(n, false);
	stack<int> stack; 
	stack.push(id); 
    visited[id] = true; 
    while (!stack.empty()) {   
        int front = stack.top(); 
        stack.pop();
        cout << front << " in consideration"<<endl;
        for (vector<long long>::iterator i = Graph[front].begin(); i != Graph[front].end(); i++) {
        	if(visited[*i]==false){
        		count += 1;
        		if(People[*i-1].isInfected()){
        			cout<<endl<<"Closest Infect Person is "<<People[*i-1].getFname()<<" "<<People[*i-1].getLname();
        			return count;
				}
				else{
					cout<<*i<<" ";
					stack.push(*i);
					visited[*i]=true;
				}
			}
    	}
    	cout<<endl;
    }
    cout<<"No infected person found"<<endl;
    return count;
}
int main(void) {
    readNames();
    makeGraph();
    int id = 0, choice;
    cout<<"Enter the id of the person: ";
    cin>>id;
    cout<<"Select the search algorithm (DFS - 0, BFS - 1)";
    cin>>choice;
    if(choice==1){
    	Timer clock;
    	long count = infected_bfs(id,Graph.size());
    	double time = clock.GetTime();
    	cout<<endl<<"Time Taken:\t"<<time<<"\t No. of Nodes Visited:\t"<<count;
	}
    else{
    	Timer clock;
    	long count = infected_dfs(id,Graph.size());
    	double time = clock.Stop();
    	cout<<endl<<"Time Taken:\t"<<time<<"\t No. of Nodes Visited:\t"<<count;
	}
    return 0;
}
