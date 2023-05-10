#include <bits/stdc++.h>

using namespace std;

int Optimal(vector<int> &pages,int nf){
    unordered_map<int,deque<int>> mp;
    for(int i=0;i<pages.size();i++) mp[pages[i]].push_back(i);
    for(auto k:mp){mp[k.first].push_back(INT_MAX);}
    vector<int> opti;
    int pfs = 0;
    for(int p:pages){
        mp[p].pop_front();
        if(find(opti.begin(),opti.end(),p)!=opti.end()) continue;
        pfs++;
        if(opti.size()<nf) {opti.push_back(p);continue;}
        int pageToReplace=0;
        for(int i=0;i<opti.size();i++){
            if(mp[opti[pageToReplace]] < mp[opti[i]]) {pageToReplace = i;}
        }
        opti[pageToReplace] = p;
    }
    return pfs;

}

int main()
{
    int n_frames;
    cout << "Enter number of frames: ";
    cin >> n_frames;
    int n_pages;
    cout << "Enter number of pages: ";
    cin >> n_pages;
    vector<int> pages(n_pages);
    cout << "Enter pages: ";
    for (int i = 0; i < n_pages; i++)
    {
        cin >> pages[i];
    }
    cout << "Number of page faults: " << Optimal(pages,n_frames);

    return 0;
}

// Enter number of frames: 4
// Enter number of pages: 20
// Enter pages: 7 0 1 2 0 3 0 4 2 3 0 3 2 1 2 0 1 7 0 1
// Number of page faults: 8