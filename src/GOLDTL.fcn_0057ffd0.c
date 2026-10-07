// FUNCTION: GOLD 0x577a00
// FUNCTION: GOLDTL 0x0057ffd0

extern int* g_665f08;
extern char g_6a8354[];
extern char g_6a2f5c[];
extern int g_772514;

void __cdecl fcn_00545670(int, int, int, char*, int);
void __cdecl fcn_00471d80(int, int);
void __cdecl fcn_00471b60(int);
void __cdecl fcn_004727a0(int, int);
void __cdecl fcn_005340f0(int);
int __cdecl fcn_00519190(char*, ...);
int __cdecl fcn_00472250(int, int, int);

int __cdecl fcn_0057ffd0(void)
{
	int o;
	int v;

	o = g_665f08[7];
	if (o == 0) {
		return -4;
	}
	if (*(int*) (o + 0x74) != 0) {
		return -4;
	}
	fcn_00545670(o, 0, 0, g_6a8354, 0x5ec);
	v = *(int*) (g_665f08[7] + 0x74);
	if (v == 0) {
		return -1;
	}
	fcn_00471d80(*(int*) (v + 8), 3);
	fcn_00471b60(*(int*) (*(int*) (g_665f08[7] + 0x74) + 8));
	fcn_004727a0(*(int*) (*(int*) (g_665f08[7] + 0x74) + 8), 0);
	fcn_005340f0(g_772514);
	fcn_004727a0(*(int*) (*(int*) (g_665f08[7] + 0x74) + 8), 3);
	g_665f08[8] = fcn_00472250(*(int*) (*(int*) (g_665f08[7] + 0x74) + 8), 3, fcn_00519190(g_6a2f5c, 0x7d));
	return 0;
}
