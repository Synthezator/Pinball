#include <stdio.h>

int main(argc, argv)
    int argc; 
    char **argv;
{
    char str[] = "savage";
    char *ptr = "rufus";

    str[3] = ptr[3];
    /* Cannot be assigned: ptr data is readonly, ptr itself is not
     * And vise versa for str
    ptr[1] = str[1];
     * */

    printf("%c\n", *(str+3));                           
    printf("%c\n", *(ptr+3));

    printf("argc: %d\n", argc);

    for (int i = 0; i < argc; i++)
    {
        /* Why argv+i instead argv+i*sizeof(char*)?
         * Because when ++ is called for an instance of char**, it's automatically 
         * increased by sizeof(char*).
         * 
         printf("%ld %d %ld\n", argv, i, (char**)(void*)((long)(void*)argv + i));
         char *addr = *((char**)(void*)((long)(void*)argv + i)); */
        printf("%p %d %p\n", argv, i, argv + i);
        char *addr = *(argv + i);
        printf("%p\n", addr);
        char symbol = *addr;
        int j = 0;
        while ((symbol = *(addr + j)))
        {
            printf("%c", symbol);
            j++;
        }

        printf("\n");
    }

    printf("Press Ctrl+D to end the program.\n");

    int c;
    while ((c = getchar()) != EOF)
    {
        putchar(c);
    }
}
