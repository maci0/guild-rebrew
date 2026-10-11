#include <stdio.h>

typedef struct
{
	char name[0x30];
	int ofs;
	char* data;
	int size;
	int fmt;
	char pad40[0x54 - 0x40];
} fcn_004659c0_Def;
// SIZE 0x54

extern char* g_772500;
extern int g_772508;
extern int g_67d36c;
extern FILE* g_772564;
extern char g_102d040[];
extern int g_7725b0;
extern char* g_7725ac;
extern int g_67dabc;
extern char s_67d410[];
extern char s_67d3d4[];

int __cdecl fcn_00465850(void);
char* __cdecl fcn_0041db70(int size, char* tag);
int __cdecl fcn_0065f220(const char* a, const char* b);
char* __cdecl fcn_0047acf0(char* p);
void __cdecl m_FreeTracked(char* p);

// FUNCTION: GOLDTL 0x4659c0
int __cdecl fcn_004659c0(int idx, char* path)
{
	int i;
	int save;
	char* old;
	char buf[0x80];

	if (((fcn_004659c0_Def*)g_772500)[idx].data == 0) {
		while (((fcn_004659c0_Def*)g_772500)[idx].size + g_772508 > g_67d36c) {
			if (fcn_00465850() == 0) {
				break;
			}
		}
		((fcn_004659c0_Def*)g_772500)[idx].data = fcn_0041db70(((fcn_004659c0_Def*)g_772500)[idx].size, s_67d410);
		if (((fcn_004659c0_Def*)g_772500)[idx].data == 0) {
			sprintf(buf, s_67d3d4, idx, &((fcn_004659c0_Def*)g_772500)[idx]);
			return 0;
		}
		if (path != 0) {
			g_772564 = fopen(path, "rb");
		} else {
			g_772564 = fopen(g_102d040, "rb");
		}
		if (g_772564 == 0) {
			return 0;
		}
		fseek(g_772564, ((fcn_004659c0_Def*)g_772500)[idx].ofs, 0);
		fread(((fcn_004659c0_Def*)g_772500)[idx].data, ((fcn_004659c0_Def*)g_772500)[idx].size, 1, g_772564);
		if (((fcn_004659c0_Def*)g_772500)[idx].fmt < 0x10) {
			save = g_67dabc;
			for (i = 0; i < g_7725b0; i++) {
				if (fcn_0065f220(g_7725ac + i * 0x30, ((fcn_004659c0_Def*)g_772500)[idx].name) == 0) {
					g_67dabc = 0;
					break;
				}
			}
			old = ((fcn_004659c0_Def*)g_772500)[idx].data;
			((fcn_004659c0_Def*)g_772500)[idx].data = fcn_0047acf0(old);
			m_FreeTracked(old);
			g_67dabc = save;
		}
		g_772508 += ((fcn_004659c0_Def*)g_772500)[idx].size;
	}
	fclose(g_772564);
	return 1;
}
