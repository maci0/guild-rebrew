#include <string.h>

typedef struct {
	int v[9];
} blk24;
// SIZE 0x24

extern blk24 g_68bef4;

char __cdecl fcn_0045b990(char*, float*, int*, int*, float*);
char* __cdecl fcn_004cef30(int);
char* __cdecl fcn_004ce610(char*);
char* __cdecl fcn_0040c230(char*, void (__cdecl*)(int), int, int, int);
char* __cdecl fcn_0040c120(char*, int, ...);
int __cdecl fcn_00406340(char*, char*, int);
void __cdecl fcn_004234e0(char*, char*, int, int, int, int, int);
unsigned int __cdecl fcn_004e6cb0(unsigned int);
int __cdecl fcn_004c30a0(int, int, char*, int, int);
int __cdecl fcn_004d31d0(char*, int, int, int, unsigned int*, unsigned int*);
int __cdecl fcn_004c6680(char*, int, int, char*);
void __cdecl fcn_004d4950(void);
void __cdecl fcn_004d4e30(void);
int __cdecl gm_RandomMod(unsigned short);

extern int g_67a370;
extern char* g_772e9c;
extern int g_772edc;
extern int g_772ee0;
extern int g_772ec4;
extern unsigned short* g_772f24;
extern int g_68b79c;
extern int g_102d020;
extern int g_102d024;

/* ADDRESS: GOLDTL 0x004d8200 */
/* Dispatches the message task of one order record: looks up the order and its
   entity, picks the dialog page by order kind and entity state, and creates the
   message task. */
void __cdecl fcn_004d8200(int* p)
{
	char* map;
	char* r;
	char* q;
	char* c;
	char* task;
	unsigned short* rec;
	int* ent;
	unsigned int v13;
	int save;
	int i;
	int ext;
	float height;

	map = *(char**) (((char*) g_67a370) + 0xb0);
	if (p[1] == 0) {
		return;
	}
	if (p[0] == -1) {
		return;
	}
	rec = (unsigned short*) fcn_004cef30(p[0]);
	r = fcn_004ce610((char*) rec);
	save = *(int*) ((char*) rec + 0x16c);
	ent = (int*) fcn_004cef30(p[4]);
	if (ent != 0) {
		*(int*) ((char*) ent + 0x24) = p[10];
	}
	if (r != 0) {
		if (*(int*) r == 0x174) {
			goto block_174;
		}
		if (*(int*) r == 0x176) {
			goto check_174;
		}
	}
	if (*((char*) p + 0x1d) != 0) {
		q = *(char**) ((char*) rec + 0x184);
		c = *(char**) (q + 0x128);
		if (c == 0 || c[9] == '-' || c[9] == ':') {
			goto make_task;
		}
	}
	goto check_174;
make_task:
	if ((unsigned short) gm_RandomMod(10) > 8) {
		if (*(int*) (save + 4) != *(int*) (g_772e9c + 4)) {
			fcn_004c30a0(*rec, g_772ee0, "_K_C2C_ANGRIFF", -1, 500);
		} else {
			fcn_004c30a0(*rec, g_772edc, "_K_C2C_ANGRIFF", -1, 500);
		}
	}
	i = p[8];
	ext = p[9];
	if (i != 0) {
		*(int*) ((char*) ent + 0x24) -= ext;
	}
	if (r == 0) {
		fcn_00406340(*(char**) ((char*) rec + 0x184), "kampf/schlagen1",
		             1);
	} else {
		task = fcn_0040c230(*(char**) ((char*) rec + 0x184),
		                    (void (__cdecl*)(int)) fcn_004d4950,
		                    *(int*) r == 0 ? (i != 0 ? 8 : 2)
		                                   : (i != 0 ? 6 : 2),
		                    0x2e, 1);
		*(float*) (task + 0x178) = 1.4f;
		*(int**) (task + 0x17c) = ent;
		*(unsigned short**) (task + 0x180) = rec;
		*(int*) (task + 0x184) = ext;
		*(int*) (task + 0x188) = *(int*) (save + 4);
		strcpy(task + 0xf0, r + 0x11);
		if ((*(int*) r == 0x16e || *(int*) r == 0x172) && i != 0) {
			p[0] = -1;
			p[1] = 0;
		}
	}
	fcn_0040c120(*(char**) ((char*) rec + 0x184), 0x3b,
	             fcn_004e6cb0(0x1e) + 0x8c);
check_174:
	if (*(int*) r != 0x174) {
		goto label_4d84fc;
	}
block_174:
	if (p[8] == 0) {
		goto label_4d84fc;
	}
	task = fcn_0040c230(*(char**) ((char*) rec + 0x184),
	                    (void (__cdecl*)(int)) 0x4d4d80, 6, 0x2e, 1);
	*(int**) (task + 0x17c) = ent;
	*(unsigned short**) (task + 0x180) = rec;
	*(int*) (task + 0x184) = p[5];
	*(int*) (task + 0x188) = p[6];
	*(blk24*) (task + 0xf0) = g_68bef4;
	if (*(int*) (((char*) g_772f24) + 4) == g_68b79c) {
		q = *(char**) ((char*) rec + 0x184);
		if (!fcn_0045b990(map, (float*) (*(int*) (q + 0x34) + 0x4c),
		                  &g_102d020, &g_102d024, &height)) {
			return;
		}
		fcn_004d31d0((char*) rec, g_102d020, g_102d024, 8, &v13,
		             (unsigned int*) &ent);
		fcn_004c6680((char*) *(int*) (q + 0x34), v13, (int) ent, 0);
		p[0] = -1;
		p[1] = 0;
	}
label_4d84fc:
	if (*(int*) r != 0x176) {
		return;
	}
	if (*((char*) p + 0x1d) == 0) {
		return;
	}
	task = fcn_0040c230(*(char**) ((char*) rec + 0x184),
	                    (void (__cdecl*)(int)) fcn_004d4e30, 5, 0x2e, 1);
	*(unsigned short**) (task + 0x17c) = rec;
	*(int*) (task + 0x180) = p[5];
	*(int*) (task + 0x184) = p[6];
	*(int*) (task + 0x188) = *(int*) (save + 4);
	strcpy(task + 0xf0, r + 0x11);
	fcn_0040c120(*(char**) ((char*) rec + 0x184), 0x3b,
	             fcn_004e6cb0(0x1e) + 0x8c);
	fcn_004234e0((char*) g_772ec4, "topfwerfen_s", 1, 0x3f, 0x7f, 0, 0);
	p[0] = -1;
	p[1] = 0;
}
