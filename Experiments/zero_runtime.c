extern int sys_write(long length, const char *string);

int write(const char *string)
{
    long strlen = 0;
    while (string[strlen])
    {
        strlen++;
    }
    return sys_write(strlen, string);
}

int main_c(int argc, char **argv)
{
    if (argc < 2)
    {
        write("Error\n");
        return 1;
    }

    write("Hi, ");
    write(argv[1]);
    write("\n");

    return 0;
}
