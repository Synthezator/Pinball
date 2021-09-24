extern int sys_write(const char *string, int length);

extern int test_args(long arg1, long arg2, long arg3);

int write(const char *string)
{
    int strlen = 0;
    while (string[strlen])
    {
        strlen++;
    }
    return sys_write(string, strlen);
}

int main_c(int argc, char **argv)
{
#if 0
    int test = 7;
    test_args(1, 2, 3);
    return 10;
#endif

    if (argc < 2)
    {
        write("Error\n");
        return 1;
    }

    write("Hi, ");
    write(argv[1]);
    write("!\n");

    return 0;
}
