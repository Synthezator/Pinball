extern int sys_write(const char *string, int length);

int write(const char *string)
{
    int strlen = 0;
    while (string[strlen])
    {
        strlen++;
    }
    return sys_write(string, strlen);
}

int main(int argc, char **argv)
{
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
