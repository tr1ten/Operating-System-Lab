#include <bits/stdc++.h>

using namespace std;
typedef vector<int> VI;
typedef vector<VI> VII;
typedef long long ll;
typedef pair<int, int> pi;
typedef pair<int, int> pi;
int startTime;
void printTurnaroundTime(vector<vector<int>> &process, int n, vector<int> &completion)
{
    vector<int> turnaround(n, 0);
    vector<int> waiting(n, 0);
    // calculate turnaround and waiting time
    for (int i = 0; i < n; i++)
    {
        turnaround[i] = completion[i] - process[i][0];
        waiting[i] = turnaround[i] - process[i][1];
    }
    // print
    cout << endl;
    cout << "Completion Time " << endl;
    for (int i = 0; i < n; i++)
    {
        cout << completion[i] << " ";
    }
    cout << endl;
    int ts = 0;
    cout << "Turnaround Time " << endl;
    for (int i = 0; i < n; i++)
    {
        cout << turnaround[i] << " ";
        ts += turnaround[i];
    }
    cout << endl;
    cout << "Waiting Time " << endl;
    int wts = 0;
    for (int i = 0; i < n; i++)
    {
        wts += waiting[i];
        cout << waiting[i] << " ";
    }
    cout << endl;
    cout << "average turnaround time " << ts * 1.0 / n << endl;
    cout << "average waiting time " << wts*1.0/ n << endl;
    cout << endl;
}

void roundRobin(VII &process, int q)
{
    VII pcopy = process;
    int n = process.size();
    sort(process.begin(), process.end());
    queue<int> ready;
    vector<int> completion(n, 0);
    int time = 0;
    int ind = 1; // keep track of new processes
    ready.push(0);
    // simulate round robin, assuming ready queue will only be empty when all process done
    while (!ready.empty())
    {
        int index = ready.front(); // get first process from ready queue
        ready.pop();
        int dt = min(process[index][1], q);
        process[index][1] -= dt;
        time += dt;
        while (ind<n && process[ind][0]<=time)
        {
            ready.push(ind);
            ind++;
        }
        if (process[index][1] == 0)
        { // if process finished
            completion[process[index][2]] =  time;
        }
        else
        {
            // else push to last of queue
            ready.push(index);
        }
    }
    // update start Time 
    startTime = time;
    printTurnaroundTime(pcopy,n,completion);

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
        completion[process[i][2]] = startTime+ pref[i];
    }
    printTurnaroundTime(temp,n,completion);
}
int main(int argc, char const *argv[])
{
    VII round_process;
    VII fcfs_process;
    int n;
    cin >> n;
    // 5 less priority round robin
    for (int i = 0; i < n; i++) {
        VI temp(3);
        int priority;
        cin >> temp[0] >> temp[1] >> priority;
        if (priority < 5) {
            temp[2] = round_process.size();
            round_process.push_back(temp);
        } else {
            temp[2] = fcfs_process.size();
            fcfs_process.push_back(temp);
        }
    }
    startTime = 0;
    cout << "Round Robin Queue Status" << endl;
    roundRobin(round_process, 2);
    cout << "FCFS Queue Status" << endl;
    fcfs(fcfs_process);

    return 0;
}

// 5
// 0 11 7
// 5 28 0
// 12 2 3
// 2 10 9
// 9 16 4

// 4
// 0 4 3
// 0 3 1
// 0 8 7
// 10 5 1