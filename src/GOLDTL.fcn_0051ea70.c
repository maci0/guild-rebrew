extern int g_6b8010;
extern unsigned char* g_90e094;

#pragma pack(1)
// SIZE 0xa
struct ref_fb5761 {
	char type;
	char pad[4];
	int ref;
	char pad2;
};
#pragma pack()

extern struct ref_fb5761 g_fb5761[0x8000];

// FUNCTION: GOLDTL 0x51ea70

void __cdecl fcn_004432d0(int, int);
int __cdecl fcn_00508e40(int);
int __cdecl gm_FindRecordById(int);
int __cdecl gm_SearchTable67(int);
int __cdecl fcn_004e6a30(int);

void __cdecl fcn_0051ea70(void)
{
	int save;
	int i;
	char* e;

	save = g_6b8010;
	fcn_004432d0(0, 1);
	for (i = 0; i < 0x100; i++) {
		e = ((char*)g_90e094) + i * 0xa9;
		if (*e != 0 && *(char**) (e + 0x61) != 0) {
			*(char**) (*(char**) (e + 0x61) + 0x204) = e;
		}
	}
	fcn_004432d0(save, 1);
	for (i = 0; i < 0x8000; i++) {
		if (g_fb5761[i].ref != 0) {
			if (g_fb5761[i].type == 1) {
				g_fb5761[i].ref = fcn_00508e40(g_fb5761[i].ref);
			}
			if (g_fb5761[i].type == 3) {
				g_fb5761[i].ref = gm_FindRecordById(g_fb5761[i].ref);
			}
			if (g_fb5761[i].type == 2) {
				g_fb5761[i].ref = gm_SearchTable67(g_fb5761[i].ref);
			}
			if (g_fb5761[i].type == 9) {
				g_fb5761[i].ref = fcn_004e6a30(g_fb5761[i].ref);
			}
		}
	}
}
