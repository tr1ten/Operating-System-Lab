#include <bits/stdc++.h>
using namespace std;
typedef vector<int> VI;
typedef vector<VI> VII;
typedef long long ll;
typedef pair<int, int> pi;
void printTurnaroundTime(vector<vector<int>> &process, int n, vector<int> &completion)
{
    vector<int> turnaround(n,0);
    vector<int> waiting(n,0);
    // calculate turnaround and waiting time
    for(int i=0;i<n;i++){
        turnaround[i] = completion[i] - process[i][0];
        waiting[i] = turnaround[i] - process[i][1];
    }
    // print
    cout << endl;
    cout << "Completion Time " << endl;
    for(int i=0;i<n;i++){
        cout << completion[i] << " ";
    }
    cout << endl;
    int ts = 0;
    cout << "Turnaround Time " << endl;
    for(int i=0;i<n;i++){
        cout << turnaround[i] << " ";
        ts+=turnaround[i];
    }
    cout << endl;
    cout << "Waiting Time " << endl;
    int wts = 0;
    for(int i=0;i<n;i++){
        wts +=waiting[i];
        cout << waiting[i] << " ";
    }
    cout << endl;
    cout << "average turnaround time " << ts*1.0/n << endl;
    cout << "average waiting time " << wts*1.0/n << endl; 
    cout << endl;
}
void priority(VII &process){
    vector<vector<int>> process2 = process;
    int n = process.size();
    vector<int> completion(n,0);

    sort(process.begin(),process.end()); // sort by first index (arrival time) 
    // min priority queue
    priority_queue<pair<pi,int>,vector<pair<pi,int>>,greater<pair<pi,int>>> pq; // ((priority,arrival time),index)
    int time = process[0][0]; // 1st process arrival time
    int i =0;
    while (i<n) {
        time = max(time,process[i][0]);
        while(i<n && process[i][0]<=time){
            pair<pi,int> pa = {{-process[i][3],process[i][0]},i}; // (priority,arrival time),index
            pq.push(pa);
            i++;
        }
        if(!pq.empty()){ // process is running
            time += process[pq.top().second][1];
            completion[process[pq.top().second][2]] = time;
            pq.pop();
        }
    }
    while (!pq.empty()) {
        time += process[pq.top().second][1]; // add burst time  
        completion[process[pq.top().second][2]] = time;
        pq.pop();
    }
    printTurnaroundTime(process2,n,completion);
    
    return;
}

void premptive(vector<vector<int>> process){
    vector<vector<int>> process2 = process;
    int n = process.size();
    vector<int> completion(n,-1);
    int cnt=0; // count completed process
    int t = 0; // timer
    int cur=-1; // currently running process
    while (cnt<n)
    {
        for (int j = 0; j < n; j++) { // check if higher priority remaining time exist
            if(completion[j]!=-1 || process[j][0]>t) continue;
            if(cur==-1 || process[cur][3]<process[j][3]){ // if such process exist then context switch
                cur = j; // this will handle the case where two or more process having same priority then follow fcfs
            }
        }
        process[cur][1]--; // decrease execution time of running process
        t++; // increase the timer
        if(process[cur][1]==0) { // if completed
            completion[cur] = t;
            cur =-1;
            cnt++;
        }
    }
    printTurnaroundTime(process2,n,completion);
    return;
}

int main(int argc, char const *argv[]) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int N;
    cin>>N;
    vector<vector<int>> process(N,vector<int>(4,0));
    int i=0;
    for(vector<int> &p:process){
        cin >> p[0] >> p[1] >> p[3];
        p[2] = i++;
    }
    premptive(process);
    // priority(process);
    return 0;
}


// 5
// 0 11 2
// 5 28 0
// 12 2 3
// 2 10 1
// 9 16 4