


extern int g_7746d8;
extern int g_7746a0;
extern int g_14a80b8;
extern int g_14a80d8;
extern int g_14a80b0;
extern char g_6aa684[];
extern char g_6aa674[];
extern char g_6aa668[];

void __cdecl fcn_005338a0(void);
int __cdecl main_RunFrameLoop(void*, int);
int __cdecl RegisterStatusText(char*, int, int);
void __cdecl d2_RunHandelSuchenDialog(int, int);

void __cdecl d2_RunAlchemistCreatureHud(int entity, int mode)
{
	int option;

	fcn_005338a0();
	while (main_RunFrameLoop(d2_RunAlchemistCreatureHud, 0x67fff) != 0) {
		if (g_7746d8 & 0x200) {
			RegisterStatusText(g_6aa684, g_14a80b8, 0x16);
			RegisterStatusText(g_6aa674, g_14a80d8, 0x16);
			option = RegisterStatusText(g_6aa668, g_14a80b0, 0x16);
			if (g_7746a0 == option) {
				d2_RunHandelSuchenDialog(entity, mode);
			}
		}
	}
}
