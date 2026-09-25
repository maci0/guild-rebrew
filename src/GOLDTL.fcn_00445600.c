// FUNCTION: GOLDTL 0x445600
// SIZE: 127

extern int g_67a370;

void __cdecl fcn_004379a0(int, char*, int, void*, void*);
int __cdecl fcn_00445560(char*, char**);

char* __cdecl fcn_00445600(char* o, int flags, char* ptr, char* name)
{
	char* st[3];
	int saved;

	if (ptr == 0 && name == 0) {
		return 0;
	}
	st[1] = ptr;
	st[0] = name;
	st[2] = 0;
	if (o != 0) {
		saved = *(int*) (o + 0x1f4);
		*(int*) (o + 0x1f4) = 0;
	}
	fcn_004379a0(g_67a370, o, flags | 0x200, fcn_00445560, st);
	if (o != 0) {
		*(int*) (o + 0x1f4) = saved;
	}
	return st[2];
}
