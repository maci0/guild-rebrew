


void __cdecl io_FormatTextBuffer(void*, int, ...);
int  __cdecl fcn_00526120(void*, int);

int __cdecl fcn_00525f60(void* a1, int a2)
{
	char buf[0x80];

	if (*(int*) ((char*) a1 + 0x194) < a2 && a2 != 0) {
		io_FormatTextBuffer(buf, 0x74, a2);
		fcn_00526120(buf, 0);
		return 0;
	}
	return 1;
}
