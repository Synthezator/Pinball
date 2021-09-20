#include <stdio.h>

int main(argc, argv)
    int argc; 
    char **argv;
{
    printf("argc: %d\n", argc);

    for (int i = 0; i < argc; i++)
    {
        int j = 0;
        /* Why argv+i instead argv+i*sizeof(char*)?
         * Because when ++ is called for an instance of char**, it's automatically 
         * increased by sizeof(char*).
         * 
         printf("%ld %d %ld\n", argv, i, (char**)(void*)((long)(void*)argv + i));
         char *addr = *((char**)(void*)((long)(void*)argv + i)); */
        printf("%ld %d %ld\n", (long)argv, i, (long)(argv + i));
        char *addr = *(argv + i);
        printf("0x%lX\n", (long)addr);
        char symbol = *addr;
        while ((symbol = *(addr + j)))
        {
            printf("%c", symbol);
            j++;
        }

        printf("\n");
    }

    printf("End of program.\n");
}
