

extern int g_772514;
extern unsigned short g_774970;
extern char g_7f4ca0[];
extern char g_6a9694[];

int __cdecl fcn_004f4830(int, int*);
void __cdecl d2_SetForm(int, int);
int __cdecl fcn_0046f740(int, int, int, int);
int __cdecl fcn_00519190(char*, ...);
void __cdecl fcn_00534210(int, int, char*, int, int);

void __cdecl fcn_005c9220(int* o)
{
	int info[9];
	int i;

	if (o[0] != -1) {
		if (fcn_004f4830(o[5], info) != 0 && info[6] != 0 && info[3] != 0) {
			d2_SetForm(o[0], o[1]);
			for (i = 0; i < info[3]; i++) {
				fcn_0046f740(5 + i * 16, 5, 0x526, g_772514);
			}
		}
		if (o[4] <= 4) {
			d2_SetForm(o[0], o[2]);
			fcn_00519190(g_6a9694, o[4] + 0x16b7);
			d2_SetForm(o[0], o[3]);
			fcn_00534210(0, 6, g_7f4ca0 + g_774970 * 540, o[4], 0x4df);
		}
	}
}
