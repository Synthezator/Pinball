#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>

/* K&R syntax for function declaration is used here. 
 * It's outdated, so it's better to use ANSI syntax: int main(int argc, char **argv)
 * */
int main(argc, argv)
    int argc; 
    char **argv;
{
    /* Play with const char * */
    /* How to write bare metal program * */

#if 0
    umask(0);
    int file_descr = open("temp.txt", O_RDWR | O_CREAT, 0666);
    if (file_descr == -1)
    {
        perror("Couldn't create file\n");
        return 2;
    }
    printf("file_descr: %d\n", file_descr);
    long res_seek = lseek(file_descr, 200, SEEK_SET);
    printf("res_seek: %ld\n", res_seek);
    
    char *text_to_write = "Niwo text";
    int res = write(file_descr, text_to_write, 9);
    printf("res_write: %d\n", res);

    return res == - 1 ? 1 : 0;
#endif

    char str[] = "savage";
    char *ptr = "rufus";

    str[3] = ptr[3];
    /* Cannot be assigned: ptr data is readonly, ptr itself is not.
     * And vise versa for str, so this line won't compile:
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

    FILE* source_code_file;
    source_code_file = fopen("args_test.c", "r");
    if (!source_code_file)
    {
        perror("Error opening file args_test.c");
        return 1;
    }

    int c;
    while ((c = fgetc(source_code_file)) != EOF)
    {
        putchar(c);
    }
    return 0;
}
