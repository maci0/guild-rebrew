#include "Develop/DieGildeAddOn/game/spiel.h"


#include <string.h>

// SIZE 0x2f4
typedef struct {
	char name[0x2f4];
} Dyn;

extern char g_868060[];

char *__cdecl gm_LookupEntityRecordById(int);
int __cdecl fcn_005c6270(char *, int);
char *__cdecl fcn_005463a0(int, int, int);
char *__cdecl he_fn_Handlung(void);
char *__cdecl gm_FindRecordById(int);

int __cdecl gm_CheckEntityType(char *);
unsigned short __cdecl gm_RandomMod(int);
int __cdecl _ftol(void);
#include "client_packet_builder.h"
void __cdecl fcn_004c4570(int, int, int, char *);
void __cdecl fcn_004c5360(void);
void __cdecl io_FormatTextBuffer(char *, int, ...);
void __cdecl fcn_00545d40(int, int, char *, int, int, int);

int __cdecl fcn_004b8dc0(int *msg)
{
	char val;
	char *b;
	char *a;
	char *recs[8];
	char *ents[8];
	char buf[0x200];
	char *p;
	char *e;
	char *r;
	int n;
	int k;

	n = 0;
	p = gm_LookupEntityRecordById(*msg);
	if (p == 0) {
		return 1;
	}
	if (fcn_005c6270(p, 0x290) != 0) {
		return 0x400;
	}
	for (e = fcn_005463a0(1, 0, 0xf); e != 0 && n < 8; e = he_fn_Handlung()) {
		r = gm_FindRecordById(*(int *) (e + 0xac));
		if (r != 0 && *(int *) (r + 0xa) == *(unsigned short *) p) {
			gm_ResolveEntityById((void**) (&a), 0, 0, *(int *) (e + 0xb4));
			gm_ResolveEntityById((void**) (&b), 0, 0, *(int *) (e + 0xb0));
			if ((a != 0 && gm_CheckEntityType(a) != 0) || (b != 0 && gm_CheckEntityType(b) != 0)) {
				if ((b != 0 && a != 0 && *b == 0x47) || *a == 0x47) {
					ents[n] = e;
					recs[n] = r;
					n++;
				}
			}
		}
	}
	if (n == 0) {
		return 0x400;
	}
	k = gm_RandomMod(n);
	e = ents[k];
	r = recs[k];
	gm_ResolveEntityById((void**) (&b), 0, 0, *(int *) (e + 0xb0));
	gm_ResolveEntityById((void**) (&a), 0, 0, *(int *) (e + 0xb4));
	val = (char) (*(unsigned char *) (r + 0x12) * ((gm_RandomMod(0x23) + 0x3c) * 0.01f));
	fcn_004c4510(r, *(int *) (r + 2));
	fcn_004c4570(1, 1, 0x12, &val);
	fcn_004c5360();
	if (*b == 0x47) {
		io_FormatTextBuffer(buf, *(unsigned short *) ((char *) msg + 4) + 0x12e7, ((Dyn*)g_868060)[*(int *) (b + 0x65)].name, ((Dyn*)g_868060)[0].name);
	} else {
		io_FormatTextBuffer(buf, *(unsigned short *) ((char *) msg + 4) + 0x12e7, ((Dyn*)g_868060)[0].name, ((Dyn*)g_868060)[*(int *) (a + 0x65)].name);
	}
	fcn_00545d40(*(int *) (p + 4), *(int *) (p + 4), buf, strlen(buf) > 0x100, 0x603, 0);
	return 0;
}
