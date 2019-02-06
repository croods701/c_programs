
char *intb(int x)
{

    unsigned int i, j;
    static char binary[sizeof(int) * __CHAR_BIT__];
    for (i = __INT32_MAX__ + 1, j = 0; i >= 1; ++j, i /= 2)
    {
        if ((x & i) != 0)
            binary[j] = 49;
        else
            binary[j] = 48;
    }
    return binary;
}

