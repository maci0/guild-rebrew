char* __cdecl gm_NextEntityQueryMatch(void);

// SIZE 0x21c
struct s_7f4ca0 {
	unsigned short id;
	char kind;
	char pad[0x169];
	char* p;
	char pad2[0x44];
	unsigned char flags;
	char pad3[0x67];
};

extern char g_7f4ca0[];




char* __cdecl fcn_00502cd0(int, int, int, int, int);

void __cdecl fcn_00531b80(void)
{
	char* e;
	int i;

	for (e = fcn_00502cd0(0, 2, 7, 4, 0x1d); e != 0; e = gm_NextEntityQueryMatch()) {
		*(int*) (e + 0x20) = 0;
		for (i = 0; i < 768; i++) {
			if (((struct s_7f4ca0*)g_7f4ca0)[i].id != 0xffff && ((struct s_7f4ca0*)g_7f4ca0)[i].kind == 1 && ((struct s_7f4ca0*)g_7f4ca0)[i].p != 0 &&
			    *(int*) (((struct s_7f4ca0*)g_7f4ca0)[i].p + 1) == *(int*) (e + 0x1c) && (((struct s_7f4ca0*)g_7f4ca0)[i].flags & 1) != 0) {
				*(int*) (e + 0x20) |= 1;
			}
		}
	}
}
