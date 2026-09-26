extern int g_6b8010;
extern unsigned char* g_90e094;

#pragma pack(1)
// SIZE 0xa
struct ref_fb5761 {
	char type;
	char pad[4];
	char* ref;
	char pad2;
};
#pragma pack()

extern struct ref_fb5761 g_fb5761[0x8000];

// FUNCTION: GOLDTL 0x51e9d0
// SIZE: 151

void __cdecl fcn_004432d0(int, int);

void __cdecl fcn_0051e9d0(void)
{
	int save;
	int i;

	save = g_6b8010;
	fcn_004432d0(0, 1);
	for (i = 0; i < 0x100; i++) {
		if (((char*)g_90e094)[i * 0xa9] != 0 && *(char**) (((char*)g_90e094) + i * 0xa9 + 0x61) != 0) {
			*(int*) (*(char**) (((char*)g_90e094) + i * 0xa9 + 0x61) + 0x204) =
			    *(int*) (((char*)g_90e094) + i * 0xa9 + 1);
		}
	}
	fcn_004432d0(save, 1);
	for (i = 0; i < 0x8000; i++) {
		if (g_fb5761[i].ref != 0) {
			if (g_fb5761[i].type == 1) {
				g_fb5761[i].ref = *(char**) (g_fb5761[i].ref + 4);
			}
			if (g_fb5761[i].type == 3) {
				g_fb5761[i].ref = *(char**) (g_fb5761[i].ref + 2);
			}
			if (g_fb5761[i].type == 2) {
				g_fb5761[i].ref = *(char**) (g_fb5761[i].ref + 1);
			}
			if (g_fb5761[i].type == 9) {
				g_fb5761[i].ref = *(char**) g_fb5761[i].ref;
			}
		}
	}
}
