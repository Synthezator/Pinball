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
        do
        {
            printf("%c", symbol);
            j++;
            char co = 'n';
            symbol = co;
            symbol = *(addr + j);
        }
        while (symbol != 0);

        printf("\n");
    }

    printf("End of program.\n");
}
