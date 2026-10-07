// FUNCTION: GOLD 0x005a50c0
// FUNCTION: GOLDTL 0x005ae3e0

extern int g_7746d8;
extern int g_14ad118;
extern int g_14ad168;
extern int g_14ad0f0;
extern int g_14ad100;
extern int g_7746a0;
extern char* g_7746cc;

void __cdecl fcn_005338a0(void);
int __cdecl fcn_005373e0(void*, int);
int __cdecl fcn_005338d0(char*, int, int);
void __cdecl fcn_005be140(char*, int);
void __cdecl fcn_005ba8e0(char*);
void __cdecl fcn_005c72f0(char*);
void __cdecl fcn_005c79a0(char*);

void __cdecl fcn_005ae3e0(char* e)
{
	int lager;
	int transport;
	int ausruesten;
	int regen;

	lager = 0;
	transport = 0;
	ausruesten = 0;
	regen = 0;
	fcn_005338a0();
	while (fcn_005373e0((void*) fcn_005ae3e0, 0x67fff) != 0) {
		if (g_7746d8 & 0x200) {
			ausruesten = fcn_005338d0("contact_AUSRUESTEN", g_14ad118, 0xd);
			regen = fcn_005338d0("contact_REGENERATION", g_14ad168, 0x17);
		}
		if (g_7746d8 & 0x400) {
			lager = fcn_005338d0("contact_LAGER", g_14ad0f0, 0xe);
			transport = fcn_005338d0("contact_TRANSPORT", g_14ad100, 0x15);
		}
		if (g_7746a0 != 0) {
			if (g_7746a0 == lager) {
				fcn_005be140(e, *(int*) (g_7746cc + 0x14));
			} else if (g_7746a0 == transport) {
				fcn_005ba8e0(e);
			} else if (g_7746a0 == ausruesten) {
				fcn_005c72f0(e);
			} else if (g_7746a0 == regen) {
				fcn_005c79a0(e);
			}
		}
	}
}
