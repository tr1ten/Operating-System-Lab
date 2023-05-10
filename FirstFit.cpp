#include <bits/stdc++.h>

using namespace std;
using namespace std;
typedef vector<int> VI;
typedef vector<VI> VII;
typedef long long ll;
typedef pair<int, int> pi;
#define FOR(i,a,b) for (int i = (a); i < (b); i++)
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

void firstfit(VI &bs,int n,VI &ps,int m){
    VI mems(m,-1);
    vector<bool> visited(n,false);
    FOR(i,0,m){
        FOR(j,0,n){
            if(bs[j]>=ps[i]){
                mems[i] = j;
                bs[j] -= ps[i];
                visited[j] = true;
                break;
            }
        }
    }
    pprint(mems,bs,visited,m);
}


int main(int argc, char const *argv[])
{
    int n,m; // n free fragemnets, m 
    cin >> n >> m;
    VI blockSize(n);
    VI processSize(m);
    take_vec(blockSize,n);
    take_vec(processSize,m);
    firstfit(blockSize,n,processSize,m);
    return 0;
}

// 5 4
// 100
// 500 
// 200 
// 300
// 600
// 212 
// 417
// 112
// 426