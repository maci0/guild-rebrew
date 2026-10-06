// FUNCTION: GOLD 0x5d26d0
// FUNCTION: GOLDTL 0x005dec00

#include <string.h>

typedef struct Ent {
	char pad0[9];
	char b9;
	char pada[0x21c - 0xa];
} Ent;
// SIZE 0x21c

extern char g_7f4ca0[];
extern unsigned short g_774970;
extern __int64 g_666018;
extern int g_66601c;

void __cdecl fcn_0051af00(char*, int, ...);
char* __cdecl fcn_005cd440(int*, char*, int, int);
char* __cdecl fcn_00508e40(int);
void __cdecl fcn_004c54c0(int, int, int, int);
void __cdecl fcn_00545d40(int, int, char*, int, int, int);
char* __cdecl fcn_005c6220(int, int*);
void __cdecl fcn_005dbe90(char*);

int __cdecl fcn_005dec00(char* ent, int* arg)
{
	int tmp;
	int desc[20];
	char name[0x100];
	char text[0x400];
	char* obj;
	char* rec;
	int ok;

	ok = 0;
	if (ent[2] == 6) {
		memset(desc, 0, sizeof(desc));
		memset(desc + 7, 0xff, 8 * sizeof(int));
		fcn_0051af00(name, 0x9c);
		desc[0] = 1;
		desc[1] = ((((Ent*)g_7f4ca0)[g_774970].b9 != 0) + 1) | 0x400;
		desc[4] = 6;
		desc[2] = (*(int*)&g_666018);
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
	fcn_004c54c0(*(int*) (ent + 4), *(int*) (obj + 4), 0x19, ok);
	if (obj[2] == 6 || obj[2] == 7) {
		fcn_0051af00(text, 0xffa, *(unsigned short*) ent);
		fcn_00545d40(*(int*) (obj + 4), -1, text, 0, 0x5ec, 0);
	}
	if (ent[2] == 6) {
		rec = fcn_005c6220(**(unsigned short**) arg, &tmp);
		arg[4] = ok;
		fcn_0051af00(text, 0xfe8, *(unsigned short*) (rec + 0x18) + 1, *(unsigned short*) obj);
		fcn_005dbe90(text);
	}
end:
	return ok;
}
