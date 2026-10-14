#include "client_types.h"
typedef Slot_1043340 Slot_4392c0;
// SIZE 0x3dc

typedef void (__cdecl* node_fn_4392c0)(char* node);

extern char g_6b8018;
extern int g_6b8010;
extern Slot_1043340 g_1043340[64];
extern char* g_1043254;
extern char g_1042340[];
extern char* g_1040c74;
extern char g_1040640[];
extern int g_6b8484;
extern int g_6b8300;
extern int g_6b89c0;
extern int g_67a370;
extern char* g_1042c38;
extern char g_1042d00[];
extern char* g_1042320;
extern char g_1052a40[];

void __cdecl fcn_004432d0(int a, int b);
void __cdecl fcn_004398d0(char* p);
void __cdecl fcn_00452420(char* p);
void __cdecl fcn_0043bcf0(int a);
void __cdecl fcn_00459b40(int a);
void __cdecl m_FreeTracked(void* p);
void __cdecl fcn_00452300(void);
void __cdecl fcn_00452280(void);
void __cdecl fcn_00434760(char* p, int b);
void __cdecl fcn_0045c110(void);

/* ADDRESS: GOLDTL 0x004392c0 */
void __cdecl fcn_004392c0(void)
{
	int saved;
	int i;

	if (g_6b8018 == 0) {
		return;
	}
	saved = g_6b8010;
	for (i = 0; i < 64; i++) {
		if (i != saved && g_1043340[i].used != 0) {
			fcn_004432d0(i, 1);
			while (g_1043254 != g_1042340) {
				fcn_004398d0(g_1043254);
			}
			g_6b8484 = 0;
			while (g_1040c74 != g_1040640) {
				fcn_00452420(g_1040c74);
			}
			if (g_6b8300 != 0) {
				fcn_0043bcf0(g_6b8300);
				g_6b8300 = 0;
			}
			if (g_6b89c0 != 0) {
				fcn_00459b40(g_6b89c0);
				g_6b89c0 = 0;
			}
			if (*(void**) (((char*)g_67a370) + 0x3c8) != 0) {
				m_FreeTracked(*(void**) (((char*)g_67a370) + 0x3c8));
				*(void**) (((char*)g_67a370) + 0x3c8) = 0;
			}
		}
	}
	if (saved != g_6b8010) {
		fcn_004432d0(saved, 1);
	}
	while (g_1043254 != g_1042340) {
		fcn_004398d0(g_1043254);
	}
	if (g_6b8300 != 0) {
		fcn_0043bcf0(g_6b8300);
		g_6b8300 = 0;
	}
	if (g_6b89c0 != 0) {
		fcn_00459b40(g_6b89c0);
		g_6b89c0 = 0;
	}
	if (*(void**) (((char*)g_67a370) + 0x3c8) != 0) {
		m_FreeTracked(*(void**) (((char*)g_67a370) + 0x3c8));
		*(void**) (((char*)g_67a370) + 0x3c8) = 0;
	}
	fcn_00452300();
	fcn_00452280();
	while (g_1042c38 != g_1042d00) {
		(*(node_fn_4392c0*) (g_1042c38 + 0x1ec))(g_1042c38);
	}
	while (g_1042320 != g_1052a40) {
		fcn_00434760(g_1042320, 1);
	}
	fcn_0045c110();
}
