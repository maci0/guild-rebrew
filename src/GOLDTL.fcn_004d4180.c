// FUNCTION: GOLDTL 0x4d4180
// SIZE: 206

typedef struct {
	int id;
	int f4;
	int f8;
	char fc;
	char padd[3];
	char name[0x10];
	int f20;
	int f24;
	int f28;
} ent2c;
// SIZE 0x2c

extern char* g_772eb4;
extern unsigned short* g_772e9c;
extern char g_9b0e20[];

char* __cdecl fcn_004cef30(int);
ent2c* __cdecl fcn_004ceac0(char*, char*);
int __cdecl fcn_004c4450(int);
void __cdecl fcn_004d4250(char*, char*);

void __cdecl fcn_004d4180(char* x)
{
	char* rec;
	int* base;
	int i;
	char* e;
	ent2c* d;

	rec = 0;
	for (i = 0; i < ((unsigned char*)g_772eb4)[0x30]; i++) {
		if (*(int*) (((unsigned char*)g_772eb4) + 0x34 + i * 4) == *(int*) (x + 4)) {
			rec = g_9b0e20 + i * 0x35c;
			break;
		}
	}
	if (x == ((char*)g_772e9c))
		base = (int*) (((unsigned char*)g_772eb4) + 0xc0);
	else
		base = (int*) (((unsigned char*)g_772eb4) + 0x80);
	for (i = 0; i < 16; i++) {
		if (base[i] == -1)
			continue;
		e = fcn_004cef30(base[i]);
		if (e == 0)
			continue;
		d = fcn_004ceac0(rec, e);
		if (d->f8 == 1 || fcn_004c4450(d->f8) != 0) {
			d->f8 = -1;
			if (d->f4 == 0 && *(int*) (*(char**) (*(char**) (e + 0x184) + 0x34) + 0x218) != 1)
				fcn_004d4250(rec, e);
		}
	}
}
