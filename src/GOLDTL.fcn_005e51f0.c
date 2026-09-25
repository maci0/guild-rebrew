// FUNCTION: GOLDTL 0x005e51f0
// SIZE: 442

extern int g_7746d8;
extern int g_7746a0;
extern int g_14b5be4;
extern int g_14ab314;
extern int g_14b5bb8;
extern int g_14ad0f0;
extern int g_14ad100;
extern int g_14a7b50;
extern int g_14a7d28;
extern char s_6ad414[];
extern char s_6ad3f0[];
extern char s_6ad3e0[];
extern char s_6a9580[];
extern char s_6a956c[];
extern char s_6aa34c[];
extern char s_6a9924[];

void __cdecl fcn_005338a0(void);
int __cdecl fcn_005373e0(void*, int);
int __cdecl fcn_005338d0(char*, int, int);
void __cdecl fcn_005be140(char*, int);
void __cdecl fcn_005944d0(char*);
void __cdecl fcn_005ba8e0(char*);
void __cdecl fcn_005b6300(char*, char*);
void __cdecl fcn_005cf560(char*);
void __cdecl fcn_0059e740(char*, int);
void __cdecl fcn_005e5130(char*, int);
void __cdecl fcn_00597ec0(char*);

void __cdecl fcn_005e51f0(char* obj, int arg)
{
	int info;
	int trade;
	int build;
	int stats;
	int family;
	int title;
	int diary;

	info = 0;
	stats = 0;
	family = 0;
	title = 0;
	diary = 0;
	trade = 0;
	build = 0;
	fcn_005338a0();
	while (fcn_005373e0(fcn_005e51f0, 0x67fff)) {
		if (g_7746d8 & 0x200) {
			info = fcn_005338d0(s_6ad414, g_14b5be4, 0x13);
			trade = fcn_005338d0(s_6ad3f0, g_14ab314, 0x16);
			build = fcn_005338d0(s_6ad3e0, g_14b5bb8, 0xc);
		}
		if (g_7746d8 & 0x400) {
			stats = fcn_005338d0(s_6a9580, g_14ad0f0, 0xe);
			family = fcn_005338d0(s_6a956c, g_14ad100, 0x15);
			title = fcn_005338d0(s_6aa34c, g_14a7b50, 0xc);
			diary = fcn_005338d0(s_6a9924, g_14a7d28, 0x16);
		}
		if (g_7746a0) {
			if (g_7746a0 == stats) {
				fcn_005be140(obj, *(int*) (obj + 0x5d));
			} else if (g_7746a0 == info) {
				fcn_005944d0(obj);
			} else if (g_7746a0 == family) {
				fcn_005ba8e0(obj);
			} else if (g_7746a0 == title) {
				fcn_005b6300(obj, s_6aa34c);
			} else if (g_7746a0 == diary) {
				fcn_005cf560(obj);
			} else if (g_7746a0 == trade) {
				fcn_0059e740(obj, arg);
			} else if (g_7746a0 == build) {
				fcn_005e5130(obj, arg);
			}
		}
		fcn_00597ec0(obj);
	}
	fcn_005338a0();
}
