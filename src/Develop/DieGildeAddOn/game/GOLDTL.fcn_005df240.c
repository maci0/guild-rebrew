


#include <stdlib.h>
#include <string.h>

typedef struct Cand {
	unsigned char id;
	unsigned char kind;
	char pad2[0x14 - 2];
	char active;
	char pad15[3];
	int ptr;
	char pad1c[0x24 - 0x1c];
} Cand;
// SIZE 0x24

extern __int64 g_666018;
extern int g_66601c;
extern char g_68ff68[];

void __cdecl fcn_0051af00(char*, int, ...);
char* __cdecl fcn_005cd440(int*, char*, int, int);
char* __cdecl fcn_00508e40(int);
int __cdecl fcn_005c6270(char*, int);
void __cdecl fcn_004f4f60(int, int, int, int, int);
void __cdecl fcn_00545d40(int, int, char*, int, int, int);
char* __cdecl fcn_005c6220(int, int*);
void __cdecl fcn_005dbe90(char*);

int __cdecl fcn_005df240(char* ent, int* arg)
{
	int ok;
	int tmp;
	int desc[20];
	int list[29];
	char name[0x100];
	char text[0x400];
	char* obj;
	char* rec;
	int twice;
	int n;
	int r;
	int i;

	ok = 0;
	if (ent[2] == 6) {
		memset(desc, 0, sizeof(desc));
		memset(desc + 7, 0xff, 8 * sizeof(int));
		fcn_0051af00(name, 0x9c);
		desc[2] = (*(int*)&g_666018);
		desc[0] = 1;
		desc[1] = 0x400;
		desc[4] = 6;
		desc[3] = g_66601c;
		obj = fcn_005cd440(desc, name, 0, 0);
		if (obj == 0) {
			goto end;
		}
		ok = 1;
	} else {
		obj = fcn_00508e40(arg[1]);
		if (obj == 0) {
			goto end;
		}
		ok = 1;
	}
	twice = fcn_005c6270(ent, 0x2c5) != 0;
	n = 0;
	for (i = 0; i < 29; i++) {
		if (((Cand*)g_68ff68)[i].kind == 2 && ((Cand*)g_68ff68)[i].active && ((Cand*)g_68ff68)[i].ptr) {
			list[n++] = ((Cand*)g_68ff68)[i].id;
		}
	}
	if (n == 0) {
		fcn_0051af00(text, 0xfff);
		fcn_00545d40(*(int*) (obj + 4), -1, text, 0, 0x5fa, 0);
		return 0;
	}
	r = rand() % n;
	fcn_004f4f60(list[r], 1, *(int*) (obj + 4), *(int*) (ent + 4),
	    *(char**) (ent + 0x170) ? *(int*) (*(char**) (ent + 0x170) + 1) : -1);
	r = rand() % n;
	fcn_004f4f60(list[r], 1, *(int*) (obj + 4), *(int*) (ent + 4),
	    *(char**) (ent + 0x170) ? *(int*) (*(char**) (ent + 0x170) + 1) : -1);
	if (twice) {
		r = rand() % n;
		fcn_004f4f60(list[r], 1, *(int*) (obj + 4), *(int*) (ent + 4),
		    *(char**) (ent + 0x170) ? *(int*) (*(char**) (ent + 0x170) + 1) : -1);
		r = rand() % n;
		fcn_004f4f60(list[r], 1, *(int*) (obj + 4), *(int*) (ent + 4),
		    *(char**) (ent + 0x170) ? *(int*) (*(char**) (ent + 0x170) + 1) : -1);
	}
	if (obj[2] == 6 || obj[2] == 7) {
		fcn_0051af00(text, 0xfff);
		fcn_00545d40(*(int*) (obj + 4), -1, text, 0, 0x5fb, 0);
	}
	if (ent[2] == 6) {
		rec = fcn_005c6220(**(unsigned short**) arg, &tmp);
		arg[4] = 1;
		fcn_0051af00(text, 0xfe8, *(unsigned short*) (rec + 0x18) + 1, *(unsigned short*) obj);
		fcn_005dbe90(text);
	}
end:
	return ok;
}
