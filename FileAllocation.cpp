#include <bits/stdc++.h>

using namespace std;

void showtable(vector<int> &files,vector<int> &start){
    // index | start address | end address | size of file
    cout << endl << "\t\tAllocation Table" << endl;
    cout << "id \t start address \t end address \t size of file" << endl;
    for (int i = 0; i < files.size(); i++)
    {
        if(start[i]==-1){
            cout << i+1 << "\t" << "Not Allocated" << "\t" << "Not Allocated" << "\t\t" << files[i] << endl;
        }
        else{
            cout << i+1 << "\t\t" << start[i] << "\t\t" << start[i]+files[i] << "\t\t" << files[i] << endl;
        }
    }
    
}
void allocate(vector<int> &file, vector<pair<int,int>> &blocks, int n_files, int n_blocks){
    vector<int> start(n_files,-1);
    for (int i = 0; i < n_files; i++)
    {

        for (int j = 0; j < n_blocks; j++)
        {
            if(blocks[j].second>=file[i]){
                start[i] = blocks[j].first;
                blocks[j].first += file[i];
                blocks[j].second -= file[i];
                break;
            }
        }
        
    }
    showtable(file,start);
    
}

int main(int argc, char const *argv[])
{
    int n_files, n_blocks;
    // takes free blocks
    cin >> n_blocks;
    vector<pair<int,int>> blocks(n_blocks); // starting, size
    for(int i=0;i<n_blocks;i++){
        cin >> blocks[i].first >> blocks[i].second;
    }
    // takes files
    cin >> n_files;
    vector<int> files(n_files); // starting, size
    for(int i=0;i<n_files;i++){
        cin >> files[i];
    }
    allocate(files,blocks,n_files,n_blocks);

    return 0;
}


// 3
// 1 5 
// 7 6 
// 20 4
// 3
// 6
// 4
// 10