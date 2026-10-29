extern int g_772f3c;
extern unsigned char* g_7746c4;
extern unsigned char* g_7746c8;
extern int* g_772f40;
extern int g_77250c;
extern unsigned char* g_772f50;
extern unsigned char* lpGebaeudePROT;
extern int g_6b8058;
extern int g_772f48;
extern char g_7f3b40[];
extern signed char g_7f3b00[];
extern char g_1043695[];
extern int g_1040490;
extern int g_1040494;
extern char g_67d67c[];

int __cdecl fcn_00476970(int);
void __cdecl fcn_00473150(unsigned char*);
void __cdecl fcn_004730c0(int, int, int, int, char*, int, int);
int __cdecl fcn_00502cd0(int, int, int, int);
int __cdecl fcn_00505370(unsigned char*);
void __cdecl init_LoadGebaeudeScene(int);
void __cdecl fcn_00510c90(int);
void __cdecl fcn_004432d0(int, int);
void __cdecl fcn_005167c0(unsigned char*, unsigned int);
void __cdecl fcn_0043aa30(char);

/* ADDRESS: GOLDTL 0x004e4230 */
void __cdecl fcn_004e4230(unsigned char* a0, unsigned int a1)
{
	int v;

	if (g_772f3c) {
		return;
	}
	if ((g_7746c4 == a0 && *(unsigned short*) (a0 + 0x29) == a1) ||
	    (g_7746c8 == a0 && *(unsigned short*) (a0 + 0x29) == a1)) {
		if (*((unsigned char*) g_772f40 + 0x26) & 0x20) {
			fcn_00476970(g_77250c);
		}
		if (g_772f50) {
			fcn_00473150(g_772f50);
			g_772f50 = 0;
			fcn_004730c0(0, 0, g_1040494, g_1040490, g_67d67c, 0x5a, 0xa);
		}
	}
	else {
		if (fcn_00502cd0(*(int*) (a0 + 0x5d), 1, 0, a1)) {
			if (!fcn_00505370(a0)) {
				if (g_7f3b40[a1] != -2) {
					if (g_7f3b40[a1] == -1 ||
					    g_1043695[g_7f3b40[a1] * 0x3dc]) {
						fcn_00510c90(a1);
					}
					fcn_004432d0(g_7f3b40[a1], 0);
					fcn_005167c0(a0, a1);
				}
			}
			else {
				if (g_7f3b00[lpGebaeudePROT[*a0 * 0x24d]]) {
					if (g_7f3b00[lpGebaeudePROT[*a0 * 0x24d]] == -1 ||
					    g_1043695[g_7f3b00[lpGebaeudePROT[*a0 * 0x24d]] * 0x3dc]) {
						init_LoadGebaeudeScene(lpGebaeudePROT[*a0 * 0x24d]);
					}
					fcn_004432d0(g_7f3b00[lpGebaeudePROT[*a0 * 0x24d]], 0);
					fcn_005167c0(a0, 0xfd);
				}
			}
		}
		v = g_6b8058;
		if (v) {
			g_772f48 = v;
			fcn_0043aa30(v & 0xfd);
			g_772f48 &= 0xfffffffd;
		}
		if (*((unsigned char*) g_772f40 + 0x26) & 0x20) {
			fcn_00476970(g_77250c);
		}
		if (g_772f50) {
			fcn_00473150(g_772f50);
			g_772f50 = 0;
			fcn_004730c0(0, 0, g_1040494, g_1040490, g_67d67c, 0x5a, 0xa);
		}
	}
}
