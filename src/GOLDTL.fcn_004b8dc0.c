// FUNCTION: GOLDTL 0x004b8dc0
// SIZE: 618

#include <string.h>

// SIZE 0x2f4
typedef struct {
	char name[0x2f4];
} Dyn;

extern Dyn g_868060[];

char *__cdecl fcn_00508e40(int);
int __cdecl fcn_005c6270(char *, int);
char *__cdecl fcn_005463a0(int, int, int);
char *__cdecl fcn_005462a0(void);
char *__cdecl gm_FindRecordById(int);
void __cdecl fcn_005015e0(char **, int, int, int);
int __cdecl gm_CheckEntityType(char *);
unsigned short __cdecl fcn_0042e410(int);
int __cdecl fcn_0064d228(void);
void __cdecl fcn_004c4510(char *, int);
void __cdecl fcn_004c4570(int, int, int, char *);
void __cdecl fcn_004c5360(void);
void __cdecl fcn_0051af00(char *, int, ...);
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
	p = fcn_00508e40(*msg);
	if (p == 0) {
		return 1;
	}
	if (fcn_005c6270(p, 0x290) != 0) {
		return 0x400;
	}
	for (e = fcn_005463a0(1, 0, 0xf); e != 0 && n < 8; e = fcn_005462a0()) {
		r = gm_FindRecordById(*(int *) (e + 0xac));
		if (r != 0 && *(int *) (r + 0xa) == *(unsigned short *) p) {
			fcn_005015e0(&a, 0, 0, *(int *) (e + 0xb4));
			fcn_005015e0(&b, 0, 0, *(int *) (e + 0xb0));
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
	k = fcn_0042e410(n);
	e = ents[k];
	r = recs[k];
	fcn_005015e0(&b, 0, 0, *(int *) (e + 0xb0));
	fcn_005015e0(&a, 0, 0, *(int *) (e + 0xb4));
	val = (char) (*(unsigned char *) (r + 0x12) * ((fcn_0042e410(0x23) + 0x3c) * 0.01f));
	fcn_004c4510(r, *(int *) (r + 2));
	fcn_004c4570(1, 1, 0x12, &val);
	fcn_004c5360();
	if (*b == 0x47) {
		fcn_0051af00(buf, *(unsigned short *) ((char *) msg + 4) + 0x12e7, g_868060[*(int *) (b + 0x65)].name, g_868060[0].name);
	} else {
		fcn_0051af00(buf, *(unsigned short *) ((char *) msg + 4) + 0x12e7, g_868060[0].name, g_868060[*(int *) (a + 0x65)].name);
	}
	fcn_00545d40(*(int *) (p + 4), *(int *) (p + 4), buf, strlen(buf) > 0x100, 0x603, 0);
	return 0;
}
