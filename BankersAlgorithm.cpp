#include <bits/stdc++.h>

using namespace std;
vector<int> vec_add(vector<int> &v1, vector<int> &v2)
{
    int n = v1.size();
    vector<int> res;
    for (int i = 0; i < n; i++)
    {
        res.push_back(v1[i] + v2[i]);
    }
    return res;
}
vector<int> vec_sub(vector<int> &v1, vector<int> &v2)
{
    int n = v1.size();
    vector<int> res;
    for (int i = 0; i < n; i++)
    {
        res.push_back(v1[i] - v2[i]);
    }
    return res;
}
void print_vec(vector<int> &v)
{
    for (int i = 0; i < v.size(); i++)
    {
        cout << v[i] << " ";
    }
    cout << endl;
}
bool safe_algorithm(vector<int> &available,
                    vector<vector<int>> &max,
                    vector<vector<int>> &allocation,
                    vector<vector<int>> &need,
                    int n_resources,
                    int n_process)
{
    vector<int> work = available;
    vector<bool> finish(n_process, false);
    int count = 0;
    vector<int> safe_seq;
    while (count < n_process)
    {
        int idx = -1;
        for (int i = 0; i < n_process; i++)
        {
            if (!finish[i] && need[i] <=work)
            {
                idx = i;
                break;
            }
        }
        if (idx == -1)
            return false;
        work = vec_add(work, allocation[idx]);
        finish[idx] = true;
        safe_seq.push_back(idx);
        count++;
    }
    cout << "\nSafe Sequence: ";
    print_vec(safe_seq);

    return reduce(finish.begin(), finish.end(), 0) == n_process;
}

void resource_request(vector<int> &available,
                      vector<vector<int>> &max,
                      vector<vector<int>> &allocation,
                      vector<vector<int>> &need,
                      int n_resources,
                      int n_process)
{
    int process;
    cout << "Enter process number: ";
    cin >> process;
    vector<int> request(n_resources);
    cout << "Enter request: ";
    for (int i = 0; i < n_resources; i++)
        cin >> request[i];
    if (request > need[process])
    {
        cout << "Request exceeds need" << endl;
        return;
    }
    if (request > available)
    {
        cout << "Request exceeds available" << endl;
        return;
    }
    available = vec_sub(available, request);
    allocation[process] = vec_add(allocation[process], request);
    need[process] = vec_sub(need[process], request);
    if (safe_algorithm(available, max, allocation, need, n_resources, n_process))
    {
        cout << "Request granted" << endl;
    }
    else
    {
        cout << "Request denied" << endl;
        available = vec_add(available, request);
        allocation[process] = vec_sub(allocation[process], request);
        need[process] = vec_add(need[process], request);
    }
}

int main(int argc, char const *argv[])
{
    int n_resources, n_process;
    cin >> n_resources >> n_process;
    vector<int> available(n_resources);
    vector<vector<int>> max(n_process, vector<int>(n_resources));
    vector<vector<int>> allocation(n_process, vector<int>(n_resources));
    vector<vector<int>> need(n_process, vector<int>(n_resources));
    for (int i = 0; i < n_resources; i++)
        cin >> available[i];
    for (int i = 0; i < n_process; i++)
    {
        for (int j = 0; j < n_resources; j++)
            cin >> max[i][j];
    }
    for (int i = 0; i < n_process; i++)
    {
        for (int j = 0; j < n_resources; j++)
            cin >> allocation[i][j];
    }
    for (int i = 0; i < n_process; i++)
    {
        for (int j = 0; j < n_resources; j++)
            need[i][j] = max[i][j] - allocation[i][j];
    }
    // cout << safe_algorithm(available, max, allocation, need, n_resources, n_process) << endl;
    resource_request(available, max, allocation, need, n_resources, n_process);
    return 0;
}
// sample input
// 3 5
// 3 3 2
// 7 5 3
// 3 2 2
// 9 0 2
// 2 2 2
// 4 3 3
// 0 1 0
// 2 0 0
// 3 0 2
// 2 1 1
// 0 0 2

// Resources request 
// 1
// 1 0 2
