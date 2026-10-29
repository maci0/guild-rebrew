


extern char g_6a9ae8[];
extern char g_6a9ad0[];
extern char g_6a9ac4[];

char* __cdecl strcpy(char*, const char*);
#pragma intrinsic(strcpy)
char* __cdecl fcn_0066080a(char*);
int __cdecl fcn_0064d41a(char*, const char*, ...);
int __cdecl fcn_0042dc90(char*);
int __cdecl fcn_00470820(int, int, char*);
void __cdecl fcn_00471b60(int);
void __cdecl d2_SetForm(int, int);
int __cdecl fcn_00519190(char*, ...);

int __cdecl fcn_005913e0(char* name)
{
	char base[0x80];
	char path[0x100];
	int idx;
	int h;

	strcpy(base, name);
	fcn_0066080a(base);
	fcn_0064d41a(path, g_6a9ae8, base);
	idx = fcn_0042dc90(path);
	if (idx == -1) {
		return -1;
	}
	h = fcn_00470820(0, 0, g_6a9ad0);
	fcn_00471b60(h);
	d2_SetForm(0, 1);
	fcn_00519190(g_6a9ac4, idx);
	d2_SetForm(0, 2);
	fcn_00519190((char*) (idx + 1));
	return h;
}
