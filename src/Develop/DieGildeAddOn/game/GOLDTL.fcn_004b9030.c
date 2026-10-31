#include "Develop/DieGildeAddOn/game/spiel.h"

#include <string.h>

// SIZE 0x2f4
typedef struct {
	char name[0x2f4];
} Dyn;

extern char g_868060[];
extern char g_7f4c00[];

char *__cdecl gm_LookupEntityRecordById(int);
int __cdecl fcn_005c6270(char *, int);
char *__cdecl fcn_005463a0(int, int, int);
char *__cdecl he_fn_Handlung(void);
int __cdecl gm_FindRecordById(int);
unsigned short __cdecl gm_RandomMod(int);
int __cdecl _ftol(void);
float __cdecl eval_ObjektPreis2Credits(int, int);
void *__cdecl fcn_00502cd0(int, int, ...);
void *__cdecl gm_NextEntityQueryMatch(void);
void __cdecl fcn_004c5a60(int, int, int);
void __cdecl fcn_004c5620(int, void *);
void __cdecl io_FormatTextBuffer(char *, int, ...);
void __cdecl fcn_00545d40(int, int, char *, int, int, int);

/* ADDRESS: GOLDTL 0x004b9030 */
int __cdecl fcn_004b9030(int *msg)
{
	char *a;
	char *b;
	int t;
	char *p;
	char *recs[8];
	char *ents[8];
	char buf[0x200];
	char *e;
	char *r;
	char *x;
	double d;
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
		r = (char *) gm_FindRecordById(*(int *) (e + 0xac));
		if (r != 0 && *(int *) (r + 0xa) == *(unsigned short *) p) {
			gm_ResolveEntityById((void **) (&a), 0, 0, *(int *) (e + 0xb4));
			gm_ResolveEntityById((void **) (&b), 0, 0, *(int *) (e + 0xb0));
			if ((a != 0 && gm_CheckEntityType(a) != 0) || (b != 0 && gm_CheckEntityType(b) != 0)) {
				if ((b != 0 && a != 0 && *b == 0x47) || *a == 0x47) {
					recs[n] = r;
					ents[n] = e;
					n++;
				}
			}
		}
	}
	if (n == 0) {
		return 0x400;
	}
	k = gm_RandomMod(n);
	r = recs[k];
	e = ents[k];
	d = eval_ObjektPreis2Credits(*(unsigned short *) r, *(char *) (r + 0x12));
	t = _ftol();
	x = (char *) fcn_00502cd0(*(int *) (r + 0x14), 2, 5, 6);
	while (x != 0) {
		d = eval_ObjektPreis2Credits(*(unsigned short *) x, *(char *) (r + 0x12));
		d = d * (*(int *) (x + 0xe));
		d = d + t;
		t = _ftol();
		x = (char *) gm_NextEntityQueryMatch();
	}
	*(int *) (e + 0x52) = *(int *) (g_7f4c00 + 0);
	*(int *) (e + 0x56) = *(int *) (g_7f4c00 + 4);
	*(int *) (e + 0x5a) = *(int *) (g_7f4c00 + 8);
	*(short *) (e + 0x5e) = *(short *) (g_7f4c00 + 0xc);
	fcn_004c5a60(-1, -1, *(int *) (r + 2));
	fcn_004c5620(-1, e);
	gm_ResolveEntityById((void **) (&b), 0, 0, *(int *) (e + 0xb0));
	gm_ResolveEntityById((void **) (&a), 0, 0, *(int *) (e + 0xb4));
	if (b != 0 && a != 0) {
		if (*b == 0x47) {
			io_FormatTextBuffer(buf, *(unsigned short *) ((char *) msg + 4) + 0x12e7,
			             ((Dyn *) g_868060)[*(int *) (b + 0x65)].name,
			             ((Dyn *) g_868060)[0].name, t);
		} else {
			io_FormatTextBuffer(buf, *(unsigned short *) ((char *) msg + 4) + 0x12e7,
			             ((Dyn *) g_868060)[0].name,
			             ((Dyn *) g_868060)[*(int *) (a + 0x65)].name, t);
		}
		fcn_00545d40(*(int *) (p + 4), *(int *) (p + 4), buf, strlen(buf) > 0x100, 0x603, 0);
	}
	return 0;
}
