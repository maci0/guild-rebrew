#include "client_types.h"

extern pos14_7f4c00 g_7f4c00;
extern char* g_aed32c;
extern char g_7f4ca4[];

int __cdecl fcn_00500cb0(void*, char*);
void __cdecl fcn_00500bb0(void*, int, int, int);
int __cdecl gm_ResolveEntityById(void**, void**, void**, int);
void __cdecl fcn_0041d9e0(const char*);
void __cdecl m_FreeTracked(int);
void __cdecl fcn_004c4510(char*, int);
int __cdecl fcn_004c4670(unsigned char, unsigned char, short, void*);
void __cdecl fcn_004c5360(void);
int __cdecl gm_StartFilteredEntitySearch(int, ...);
int __cdecl fcn_0050dc90(int);
int __cdecl fcn_005049a0(void*);
void __cdecl fcn_0051af00(char*, int, ...);
void __cdecl he_MessageBoxQuickjump(int, int, char*, int, int, int, int, int, char*);

/* ADDRESS: GOLDTL 0x0055ffe0 */
void __cdecl he_RunLagerErweitern(int a0)
{
	char* q;
	int v5[2];
	char buf[1024];
	int ent;
	char* info;
	int cat;
	int msg;
	int rem;
	int px;
	int v9;
	int v10;

	switch (*(int*) ((char*) a0 + 0x70)) {
	case 0:
		*(int*) ((char*) a0 + 0x70) = *(int*) ((char*) a0 + 0x70) + 1;
		return;
	case 1:
		q = (char*) a0 + 0x52;
		break;
	case 0xfffffffe:
	case 0xffffffff:
		m_FreeTracked(a0);
		return;
	default:
		return;
	}
	if (fcn_00500cb0(q, (char*) &g_7f4c00) >= 0)
		return;
	v5[1] = 1;
	gm_ResolveEntityById(0, (void**) v5, 0, *(unsigned int*) ((char*) a0 + 0xac));
	if (!v5[0]) {
		fcn_0041d9e0("he_RunLagerErweitern():Wrong LagerID...");
		m_FreeTracked(a0);
		return;
	}
	fcn_004c4510((char*) v5[0], *(int*) ((char*) v5[0] + 2));
	fcn_004c4670(4, 1, (short) ((v5[0] - (int) g_aed32c) + 0xe), &v5[1]);
	fcn_004c5360();
	rem = *(int*) ((char*) a0 + 0xb0) - 1;
	*(int*) ((char*) a0 + 0xb0) = rem;
	if (rem > 0) {
		*(pos14_7f4c00*) q = g_7f4c00;
		fcn_00500bb0(q, 0, 0xf, 0);
		return;
	}
	msg = 0x606;
	ent = (int) gm_StartFilteredEntitySearch(1, 1, *(unsigned int*) ((char*) a0 + 0x10));
	if (ent) {
		info = (char*) fcn_0050dc90(ent);
		if (info != 0 && (*(unsigned char*) (info + 0x1b4) & 1))
			msg = 0x60b;
		cat = fcn_005049a0((void*) ent);
		fcn_0051af00(buf, 0x1bbb, ent);
		px = *(int*) (g_7f4ca4 + (*(unsigned short*) ((char*) a0 + 8)) * 0x21c);
		v9 = *(int*) ((char*) ent + 1);
		if (cat) {
			v10 = *(int*) ((char*) cat + 2);
			he_MessageBoxQuickjump(px, (int) ent, buf, 0, msg, v9, v10, 0, 0);
		} else {
			he_MessageBoxQuickjump(px, -1, buf, 0, msg, v9, -1, 0, 0);
		}
	}
	m_FreeTracked(a0);
}
