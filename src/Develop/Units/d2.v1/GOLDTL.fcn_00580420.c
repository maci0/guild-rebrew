


extern int* g_665f08;
extern char g_6b5c60[];
extern char g_6811b0[];

void __cdecl fcn_00533a40(char*);
void __cdecl d2_SetForm(int, int);
int __cdecl fcn_00519190(char*, ...);
void __cdecl fcn_00471af0(int, int);
int __cdecl fcn_00423460(int);
void __cdecl fcn_004237f0(int, int);
int __cdecl fcn_004c3030(int, int, int, int);

/* ADDRESS: GOLD 0x00577e50 */
void __cdecl fcn_00580420(void)
{
	if (g_665f08[6] != 0 && *(int*) (g_665f08[6] + 0x1c) != 0) {
		fcn_00533a40(g_6b5c60);
		d2_SetForm(g_665f08[13], 0);
		fcn_00519190(g_6811b0);
		fcn_00519190(*(char**) (g_665f08[6] + 0x1c));
		fcn_00471af0(g_665f08[13], 1);
		if (*(int*) (g_665f08[6] + 0x20) != 0) {
			if (g_665f08[5] != 0) {
				if (fcn_00423460(g_665f08[5]) != 0) {
					fcn_004237f0(g_665f08[5], 0);
				}
				g_665f08[5] = 0;
			}
			g_665f08[5] = fcn_004c3030(-7, 0, *(int*) (g_665f08[6] + 0x20), -1);
		}
	}
}
