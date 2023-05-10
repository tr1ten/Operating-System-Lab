#include <bits/stdc++.h>

using namespace std;

int LRU(vector<int> &pages,int nf){
    deque<int> lru;
    int pfs = 0;
    for(int p:pages){
        if(find(lru.begin(),lru.end(),p)!=lru.end()){
            lru.erase(find(lru.begin(),lru.end(),p));
        }
        else{pfs++;}
        if(lru.size()>=nf) {lru.pop_front();}
        lru.push_back(p);
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
    cout << "Number of page faults: " << LRU(pages,n_frames);

    return 0;
}

// Enter number of frames: 4
// Enter number of pages: 15
// Enter pages: 2 0 1 2 4 0 5 1 4 6 4 2 1 3 0
// Number of page faults: 10