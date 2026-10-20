/* Session cutscene command: resolves up to four participant entities, builds
 * the cutscene dialog and runs its message loop until the user leaves it. */

extern char* g_77255c;
extern int g_772514;
extern int g_68bfb8;
extern int g_100f1dc;
extern int g_774654;
extern int g_67d370;

int __cdecl fcn_004e8af0(char*, void*);
int __cdecl fcn_004e8b40(int, void*);
int __cdecl fcn_004e9310(int, int, void*);
char* __cdecl fcn_00508e40(int);
int __cdecl fcn_004aae50(char*, int, int*, void*);
int __cdecl fcn_00470820(int, int, char*);
void __cdecl fcn_00471d80(int, int);
void __cdecl fcn_004727a0(int, int);
unsigned int __cdecl fcn_00519190();
int __cdecl fcn_00472250(int, int, char*);
int __cdecl fcn_004677e0(int, int, int, int, int, int, int, int);
int __cdecl fcn_004e6e20(int, int, int);
int __cdecl fcn_005373e0(void*, int);
void __cdecl fcn_00471e30(int);

/* ADDRESS: GOLDTL 0x004dc3a0 */
int __cdecl fcn_004dc3a0(char* a0, int a1, int* a2, int* a3)
{
	char info[0x18];
	char buf[24];
	void* ents[4];
	int handles[4];
	int ret;
	int n;
	int i;
	int found;
	int gui;
	int result;

	*a3 = 0;
	if (fcn_004e8af0(a0, info) == 0) {
		return -1;
	}
	if (fcn_004e8b40(*(int*) (info + 8) & 0xff, buf) == 0) {
		return -1;
	}
	n = fcn_004e9310(*(int*) (info + 8) & 0xff, 2, ents);
	i = 0;
	found = 0;
	for (; i < 4; i++) {
		char* e;

		e = fcn_00508e40(a2[i]);
		if (e != 0) {
			ents[found] = e;
			found++;
		}
	}
	if (found == 0) {
		return -1;
	}
	result = fcn_004aae50(a0, a1, a2, &ret);
	gui = fcn_00470820(0, 0, (char*) 0x68c340);
	fcn_00471d80(gui, 1);
	fcn_004727a0(gui, 0);
	if (n < 2) {
		fcn_00519190(0x12dc, *(unsigned short*) a2, *(unsigned short*) a2,
		    (*(int*) (info + 8) & 0xff) + 0x253);
	} else {
		fcn_00519190(0x12dd, *(unsigned short*) a2, *(unsigned short*) a2,
		    (*(int*) (info + 8) & 0xff) + 0x253);
	}
	for (i = 0; i < found; i++) {
		handles[i] = fcn_00472250(gui, 0,
		    (char*) fcn_00519190(0x68c354, *(unsigned short*) ents[i]));
	}
	for (i = found; i < 4; i++) {
		handles[i] = -1;
	}
	n = fcn_004677e0((*(int*) (g_77255c + 0xc) - 300) / 2 - 8, 8, 300, 0, 100,
	    0x75, 0x42, g_772514);
	fcn_004e6e20(n, 0x5dc, 1);
	g_100f1dc = -1;
	while (fcn_005373e0((void*) 0x4dc230, g_68bfb8) != 0) {
		if (fcn_004e6e20(n, 0, 0) != 0) {
			if (g_100f1dc != -1) {
				for (i = 0; i < found; i++) {
					if (g_67d370 == handles[i]) {
						result = *(int*) ((char*) ents[i] + 4);
						goto setflag;
					}
				}
			}
			goto next;
		}
setflag:
		g_774654 = 1;
next:
		;
	}
	fcn_00471e30(gui);
	return result;
}
