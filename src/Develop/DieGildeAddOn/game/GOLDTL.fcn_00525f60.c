


void __cdecl io_FormatTextBuffer(void*, int, ...);
int  __cdecl fcn_00526120(void*, int);

int __cdecl d2_CheckActionBlocker(void* obj, int value)
{
	char buf[0x80];

	if (*(int*) ((char*) obj + 0x194) < value && value != 0) {
		io_FormatTextBuffer(buf, 0x74, value);
		fcn_00526120(buf, 0);
		return 0;
	}
	return 1;
}
