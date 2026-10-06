extern int g_67a370;

// SIZE 0x21c
struct s_7f4ca0 {
	char pad[2];
	char kind;
	char pad2[0x219];
};

extern char g_7f4ca0[];

// FUNCTION: GOLDTL 0x52d9d0

void __cdecl fcn_004379a0(int, char*, int, void*, char*);
char __cdecl fcn_0052d860(char*, char*);

void __cdecl fcn_0052d9d0(char* e)
{
	char* o;
	int saved;
	char k;

	o = *(char**) (e + 0x61);
	if (o == 0) {
		return;
	}
	if (*(unsigned short*) (e + 0x27) == 0xffff) {
		return;
	}
	k = ((struct s_7f4ca0*)g_7f4ca0)[*(unsigned short*) (e + 0x27)].kind;
	if (k == 6 || k == 7 || k == 5) {
		if ((o[0x214] & 1) == 0) {
			saved = *(int*) (o + 0x1f4);
			*(int*) (o + 0x1f4) = 0;
			fcn_004379a0(g_67a370, *(char**) (e + 0x61), 0x100, (void*) fcn_0052d860, e);
			*(int*) (*(char**) (e + 0x61) + 0x1f4) = saved;
		} else {
			fcn_004379a0(g_67a370, o, 0x100, (void*) fcn_0052d860, e);
		}
	}
}
