#include <bits/stdc++.h>

using namespace std;

struct Node{
    public:
    int val=-1;
    int sz;
    Node *next=nullptr;
};

void printPartition(Node *node){
    // current val, next val, partition size, parition number
    int i=1;
    while(node!=nullptr){
        cout << node->val << " " << (node->next==nullptr?-1:node->next->val) << " " << node->sz << " " << i << endl;
        node = node->next;
        i++;
    }
}

void showtable(vector<int> &files,vector<Node *> &start){
    // index | start address | end address | size of file
    cout << endl << "\t\tAllocation Table" << endl;
    cout << "id \t start address  \t size of file" << endl;
    for (int i = 0; i < files.size(); i++)
    {
        if(start[i]==nullptr){
            cout << i+1 << "\t" << "Not Allocated" << "\t\t" << files[i] << endl;
        }
        else{
            cout << i+1 << "\t\t" << start[i]->val << "\t\t" << files[i] << endl;
        }
    }
    cout << endl << "\t\tPartition Tables" << endl;
    cout << "current addr  next addr  partition size  partition number" << endl;
    for (int i = 0; i < files.size(); i++)
    {
        if(start[i]==nullptr){
            cout << "File " << i+1 << " is not allocated" << endl;
        }
        else{
            cout << "File " << i+1 << " is allocated in following partitions" << endl;
            printPartition(start[i]);
        }
    }
    
}
void allocate(vector<int> &file, vector<pair<int,int>> &blocks, int n_files, int n_blocks){
    vector<Node *> start(n_files, nullptr);
    vector<int> cpy(file.begin(),file.end());
    vector<int> index_blocks(n_files,-1); // store index of file blocks
    for (int i = 0; i < n_files; i++)
    {
        Node *dummy = new Node();
        auto temp = dummy;
        for (int j = 0; j < n_blocks; j++)
        {

            if(blocks[j].second!=0 && index_blocks[i]==-1){
                index_blocks[i] = j;
                blocks[j].second = 0;
            }
            if(blocks[j].second!=0){
                Node *node = new Node();
                node->sz = min(file[i],blocks[j].second);
                node->val = blocks[j].first;
                file[i] -= node->sz;
                blocks[j].first += node->sz;
                blocks[j].second -= node->sz;
                temp->next = node;
                temp = node;
                if(file[i]==0){
                    break;
                }
            }
        }
        start[i] = dummy->next;
        
    }
    // print indices 
    cout << "File id \tIndex of block" << endl;
    for (int i = 0; i < n_files; i++)
    {
        cout << i+1 << "\t\t" << index_blocks[i] << endl;
    }
    showtable(cpy,start);
    
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