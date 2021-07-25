#include <stdio.h>

int main(argc, argv)
    int argc; 
    char **argv;
{
    printf("argc: %d\n", argc);

    for (int i = 0; i < argc; i++)
    {
        int j = 0;
        char symbol = **(argv + i);
        do
        {
            printf("%c", symbol);
            j++;
            symbol = *(*(argv + i) + j);
        }
        while (symbol != 0);

        printf("\n");
    }

    for (int i = 0; i < argc; i++)
    {
        printf("%s\n", *(argv + i));
    }

    printf("End of program.\n");
}
