extern int sys_write(const char *string);

int main(int argc, char **argv)
{
    if (argc < 2)
    {
        sys_write("Error\n");
        return 1;
    }

    sys_write("Hi, ");
    sys_write(argv[1]);
    sys_write("!\n");

    return 0;
}
