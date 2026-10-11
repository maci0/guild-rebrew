int __cdecl fcn_0064d470(char*, int);
void __cdecl fcn_00425bf0(void*, int, char*);

int __cdecl CharacterSitsDown(char** object)
{
    unsigned char* p;

    p = (unsigned char*) *object;
    if (p == 0) {
        fcn_00425bf0(*(void**) 0x6b7e98,
            *(int*) ((char*) *(void**) 0x6b7e98 + 0x118),
            (char*) 0x67635c);
        return 0;
    }
    return (p[0x8c] >> 4) & 1;
}



int __cdecl fcn_0040e150(char** a1, int* a2)
{
	char* p;

	p = *a1;
	if (p == 0) {
		fcn_00425bf0(*(void**) 0x6b7e98, *(int*) ((char*) *(void**) 0x6b7e98 + 0x118), (char*) 0x676384);
		return 0;
	}
	return fcn_0064d470(p + 8, *a2) != 0;
}
