#include <bits/stdc++.h>

using namespace std;
using namespace std;
typedef vector<int> VI;
typedef vector<VI> VII;
typedef long long ll;
typedef pair<int, int> pi;
#define FOR(i, a, b) for (int i = (a); i < (b); i++)
#define take_vec(vec, sz) FOR(i, 0, sz) cin >> vec[i]
typedef pair<int, int> pi;

void pprint(VI &address,VI &bs,vector<bool> &visited,int m){
    cout << "Memory Allocations" << endl;
    cout << "Process ID\t Address" << endl;
    FOR(i,0,m){
        if(address[i]==-1) cout << (i+1) << "\t\t" << "Not allocated" << endl;
        else cout << (i+1) << "\t\t" << (address[i]+1) << endl;
    }
    cout << "Internal Fragmentation ";
    int extfrag = 0;
    FOR(i,0,bs.size()){
        if(visited[i]) cout << bs[i] << " ";
        else extfrag += bs[i];
    }
    cout <<endl << "Total External fragmentation " << extfrag << endl;



}

void bestfit(VI &bs, int n, VI &ps, int m)
{
    VI mems(m, -1);
    vector<bool> visited(n,false);
    FOR(i, 0, m)
    {
        int res = -1;
        FOR(j, 0, n)
        {
            if (bs[j] >= ps[i] && (res == -1 || bs[res] > bs[j]))
            {
                res = j;
            }
        }
        if (res != -1)
        {
            mems[i] = res;
            bs[res] -= ps[i];
            visited[res] = true;
        }
    }
    pprint(mems,bs,visited, m);
}

int main(int argc, char const *argv[])
{
    int n, m; // n free fragemnets, m
    cin >> n >> m;
    VI blockSize(n);
    VI processSize(m);
    take_vec(blockSize, n);
    take_vec(processSize, m);
    bestfit(blockSize, n, processSize, m);
    return 0;
}
