#include <bits/stdc++.h>
using namespace std;
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
void fcfs(vector<vector<int>> &process){
    int n = process.size();
    auto temp = process;
    sort(process.begin(),process.end());
    vector<int> completion(n,0);
    vector<int> pref(n,0);
    pref[0] = process[0][1];
    for (int i = 1; i < n; i++) {
        pref[i] = pref[i-1]+process[i][1];
    }
    for (int i = 0; i < n; i++) {
        completion[process[i][2]] = pref[i];
    }
    printTurnaroundTime(temp,n,completion);
}


// driver code
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int N;
    cin>>N;
    vector<vector<int>> process(N,vector<int>(3,0));
    int i=0;
    for(vector<int> &p:process){
        cin >> p[0] >> p[1];
        p[2] = i++;
    }
    fcfs(process);
    return 0;
}
// 5 
// 2 6
// 5 2
// 1 8
// 0 3
// 4 4