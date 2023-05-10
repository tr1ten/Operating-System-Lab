#include <cstdio>
#include <bits/stdc++.h>

using namespace std;
typedef vector<int> VI;
typedef vector<VI> VII;
typedef long long ll;
typedef pair<int, int> pi;
#define take_vec(vec, sz) FOR(i, 0, sz) cin >> vec[i]
typedef pair<int, int> pi;
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
            completion[process[index][2]] = time;
        }
        else
        {
            // else push to last of queue
            ready.push(index);
        }
    }
    printTurnaroundTime(pcopy,n,completion);
}

int main(int argc, char const *argv[])
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int N;
    cin >> N;
    vector<vector<int>> process(N, vector<int>(3, 0));
    int i = 0;
    for (vector<int> &p : process)
    {
        cin >> p[0] >> p[1];
        p[2] = i++;
    }
    roundRobin(process, 2);
    return 0;
}


// 3
// 0 4 3
// 0 3 1
// 10 5 1

// 3
// 0 4
// 0 3
// 6 3