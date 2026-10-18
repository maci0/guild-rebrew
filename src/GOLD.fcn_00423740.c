/* ADDRESS: GOLD 0x00423740 */
int __cdecl fcn_00423740(int a)
{
    char* p;
    int result;

    p = *(char**) 0x6323a4;
    result = 0;
    if (p != 0) {
        do {
            if (*(int*) (p + 0x114) == a)
                break;
            p = *(char**) (p + 4);
        } while (p != 0);
        result = (int) p;
    }
    return result;
}
