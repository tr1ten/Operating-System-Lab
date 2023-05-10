#include <bits/stdc++.h>
#include <unistd.h>
using namespace std;

int main(int argc, char const *argv[])
{
    cout << " HEllo " << endl;
    if(fork() || fork()) {
        cout << "First" << endl;}
    else cout << " Second " << endl;
    return 0;
}
