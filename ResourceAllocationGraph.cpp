#include <bits/stdc++.h>

using namespace std;
void print_adj(vector<vector<int>> adj,int n_resources,int n_process){
    int N = n_process + n_resources;
    for(int i=0;i<N;i++){
        cout <<(i<n_process ? "P" : "R") << (i%n_process+1) << " -> ";
        for(int j=0;j<adj[i].size();j++){
            cout << (adj[i][j]<n_process ? "P" : "R") << (adj[i][j]%n_process+1) << " ";
        }
        cout << endl;
    }
}
bool dfs(vector<vector<int>> &adj,int node,vector<int> &visited,vector<int> &recStack){
    visited[node] = 1;
    recStack[node] = 1;
    for(int i=0;i<adj[node].size();i++){
        int child = adj[node][i];
        if(!visited[child]){
            if(dfs(adj,child,visited,recStack))
                return true;
        }
        else if(recStack[child])
            return true;
    }
    recStack[node] = 0;
    return false;
}
bool detectCycle(vector<vector<int>> &adj){
    int N = adj.size();
    vector<int> visited(N,0);
    vector<int> recStack(N,0);
    for(int i=0;i<N;i++){
        if(!visited[i]){
            if(dfs(adj,i,visited,recStack))
                return true;
        }
    }
    return false;
}
int main(int argc, char const *argv[])
{
    int n_resources,n_process;
    cin >> n_resources >> n_process;
    int N = n_process + n_resources;
    vector<vector<int>> adj(N);
    // take resources allocated by each process
    for(int i=0;i<n_process;i++){
        int n_allocated;
        cin >> n_allocated;
        for(int j=0;j<n_allocated;j++){
            int resource;
            cin >> resource;
            adj[resource + n_process - 1].push_back(i);
        }
    }
    // take resources requested by each process
    for(int i=0;i<n_process;i++){
        int n_requested;
        cin >> n_requested;
        for(int j=0;j<n_requested;j++){
            int resource;
            cin >> resource;
            adj[i].push_back(resource + n_process - 1);
        }
    }
    print_adj(adj,n_resources,n_process);
    if(detectCycle(adj))
        cout << "Cycle Exist, Deadlock may occur" << endl;
    else
        cout << "No Cycle, No Deadlock" << endl;
    return 0;
}

// single instance
// 2
// 2
// 1
// 1
// 1
// 2
// 1
// 2
// 1
// 1
    
// multi instance
// 2
// 3
// 1
// 1
// 1
// 2    
// 0
// 0
// 0
// 2
// 1 2
