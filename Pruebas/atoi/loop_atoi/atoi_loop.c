int
atoi_loop(char *p)
{
    int num = 0;

    while (*p != 0)
    {
        num = num * 10 + (*p - '0');
        p ++;
    }

    return  num;
}

