#include "Develop/DieGildeAddOn/game/spiel.h"


#include <string.h>

// SIZE 0x2f4
typedef struct {
	char name[0x2f4];
} Dyn;

extern char gm_TownTable[];

char *__cdecl gm_LookupEntityRecordById(int);
int __cdecl gm_HasActiveSpecialObject(char *, int);
char *__cdecl he_StartHandlungSearch(int, int, int);
char *__cdecl he_fn_Handlung(void);
char *__cdecl gm_FindRecordById(int);

int __cdecl gm_CheckEntityType(char *);
unsigned short __cdecl gm_RandomMod(int);
int __cdecl _ftol(void);
#include "Develop/DieGildeAddOn/command/client_packet_builder.h"
void __cdecl cm_AppendPacketFieldDelta(int, int, int, char *);
void __cdecl cm_RequestChangeAttribute(void);
void __cdecl io_FormatTextBuffer(char *, int, ...);
void __cdecl he_PostEntityMessage(int, int, char *, int, int, int);

int __cdecl gm_SabotageHandlungItem(int *msg)
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
	if (gm_HasActiveSpecialObject(p, 0x290) != 0) {
		return 0x400;
	}
	for (e = he_StartHandlungSearch(1, 0, 0xf); e != 0 && n < 8; e = he_fn_Handlung()) {
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
	cm_BeginPacketFieldDelta(r, *(int *) (r + 2));
	cm_AppendPacketFieldDelta(1, 1, 0x12, &val);
	cm_RequestChangeAttribute();
	if (*b == 0x47) {
		io_FormatTextBuffer(buf, *(unsigned short *) ((char *) msg + 4) + 0x12e7, ((Dyn*)gm_TownTable)[*(int *) (b + 0x65)].name, ((Dyn*)gm_TownTable)[0].name);
	} else {
		io_FormatTextBuffer(buf, *(unsigned short *) ((char *) msg + 4) + 0x12e7, ((Dyn*)gm_TownTable)[0].name, ((Dyn*)gm_TownTable)[*(int *) (a + 0x65)].name);
	}
	he_PostEntityMessage(*(int *) (p + 4), *(int *) (p + 4), buf, strlen(buf) > 0x100, 0x603, 0);
	return 0;
}
