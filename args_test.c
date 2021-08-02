#include <stdio.h>
#include <stdlib.h>

void memoryLeakTest();

int main(argc, argv)
    int argc; 
    char **argv;
{
    // memoryLeakTest();

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

void memoryLeakTest()
{
    int index = 0;
    while (1)
    {
        malloc(1 << 30);
        index++;
        if (index % 1000 == 0)
        {
            printf("%i\n", index);
        }
    }
}
