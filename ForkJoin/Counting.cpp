#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <string.h>
#include <unistd.h>

const char vow[] = "aeiou";
int main()
{
    char sentance[] = "The quick brown fox jumps over the lazy dog"; // parent process will write this message
    int pid = fork();

    if (pid == 0)
    {
        // count spaces
        printf("Child read: %s\n", sentance);
        int cnt  = 0;
        for(int i=0;i<strlen(sentance);i++){
            if(sentance[i] == ' ')
                cnt++;
        }
        printf("Child: Words in sentance: %d\n",cnt+1);
    }
    else
    {
        // count vowels in sentance
        printf("Parent read: %s\n", sentance);
        int *vowels = (int *)malloc(sizeof(int) * 5);
        for (int i = 0; i < 5; i++)
            vowels[i] = 0;
        for (int i = 0; i < strlen(sentance); i++)
        {
            for (int j = 0; j < 5; j++)
            {
                if (sentance[i] == vow[j])
                    vowels[j]++;
            }
        }
        printf("Parent: Vowels in sentance: %d\n", strlen(sentance));
        for (int i = 0; i < 5; i++)
            printf("%c: %d\n", vow[i], vowels[i]);
        

    }
}