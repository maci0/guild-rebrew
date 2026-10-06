// FUNCTION: GOLDTL 0x44f0e0

extern int g_6b7fdc;
extern char g_6750e8[];

void* __cdecl fcn_0042ff50(char*, char*, int);
int __cdecl vfs_ReadData(void*, int, int, void*);
void __cdecl fcn_00401180(void*, char*);
void __cdecl fcn_004011f0(void*, void*);
int __cdecl CloseVfsStream(void* stream);

char __cdecl fcn_0044f0e0(char* name)
{
	int v;
	int magic;
	char c;
	char ok;
	void* h;

	ok = 1;
	h = fcn_0042ff50(name, g_6750e8, g_6b7fdc);
	if (h != 0) {
		vfs_ReadData(&magic, 4, 1, h);
		fcn_00401180(h, &c);
		fcn_004011f0(h, &v);
		fcn_00401180(h, &c);
		fcn_004011f0(h, &v);
		fcn_00401180(h, &c);
		if (c == 2) {
			fcn_00401180(h, &c);
			if ((c & 2) == 2) {
				ok = 0;
			}
		}
		CloseVfsStream(h);
	}
	return ok;
}
