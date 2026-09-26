// FUNCTION: GOLD 0x449770
// SIZE: 127

extern char* g_5fb5b0;

void __cdecl fcn_00438d40(int, char*, int, void*, void*);
int __cdecl fcn_00449710(char*, char**);

char* __cdecl fcn_00449770(char* o, int flags, char* ptr, char* name)
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
		saved = *(int*) (o + 0x1f0);
		*(int*) (o + 0x1f0) = 0;
	}
	fcn_00438d40((int) g_5fb5b0, o, flags | 0x200, fcn_00449710, st);
	if (o != 0) {
		*(int*) (o + 0x1f0) = saved;
	}
	return st[2];
}
