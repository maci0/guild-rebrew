/* fcn_00401180 calls fcn_00430bd0(b, 1, 1, a). */

int __cdecl fcn_00430bd0(void*, int, int, int);

int __cdecl fcn_00401180(int a, void* b)
{
	return fcn_00430bd0(b, 1, 1, a);
}

char* __cdecl fcn_004011a0(int stream, char* text)
{
    char* cursor;

    cursor = text;
    do {
        fcn_00401180(stream, cursor++);
    } while (cursor[-1] != 0);
    return cursor - 1;
}
