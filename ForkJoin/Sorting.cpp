#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <string.h>
#include <unistd.h>
#include <bits/stdc++.h>
#include <sys/wait.h>

using namespace std;
void *create_shared_memory(size_t size)
{
    // Our memory buffer will be readable and writable:
    int protection = PROT_READ | PROT_WRITE;

    // The buffer will be shared (meaning other processes can access it), but
    // anonymous (meaning third-party processes cannot obtain an address for it),
    // so only this process and its children will be able to use it:
    int visibility = MAP_SHARED | MAP_ANONYMOUS;

    // but the manpage for `mmap` explains their purpose.
    return mmap(NULL, size, protection, visibility, -1, 0);
}
void print_arr(int *arr, int n)
{
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");
}
int main()
{
    int seq[6] = {1,2,1,0,12,3};

    void *shmem = create_shared_memory(6);

    memcpy(shmem, seq, sizeof(seq));

    int pid = fork();

    if (pid == 0)
    {
        waitpid(1, NULL, 0); // wait for parent process to finish
        int *arr = (int *)shmem;
        printf("Child reads: ");
        print_arr(arr, 6);
        reverse(arr, arr + 6);
        printf("Child writes: ");
        print_arr(arr, 6);
    }
    else
    {
        int *arr = (int *)shmem;
        printf("Parent reads: ");
        print_arr(arr, 6);
        sort(arr, arr + 6);
        reverse(arr, arr + 6);
        printf("Parent writes: ");
        print_arr(arr, 6);
    }
}