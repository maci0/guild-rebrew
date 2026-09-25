// FUNCTION: GOLDTL 0x005dd1a0
// SIZE: 335

#include <string.h>

// SIZE 0x50
typedef struct {
	int a;
	int size;
	__int64 cd;
	int kind;
	int f14;
	int pad18;
	int ids[8];
	int pad3c[5];
} Req;

// SIZE 0x21c
typedef struct {
	char pad0[9];
	unsigned char b9;
	char pada[0x212];
} House;

extern __int64 g_666018;
extern House g_7f4ca0[];
extern unsigned short g_774970;

void __cdecl fcn_0051af00(char*, int, ...);
unsigned char* __cdecl fcn_005cd440(Req*, char*, int, int);
unsigned char* __cdecl fcn_00508e40(int);
int __cdecl fcn_005c6270(unsigned char*, int);
void __cdecl fcn_004c54c0(int, int, int, int);
void __cdecl fcn_00545d40(int, int, char*, int, int, int);

int __cdecl fcn_005dd1a0(unsigned char* obj, int* arg)
{
	Req req;
	char text[0x100];
	char text2[0x400];
	unsigned char* e;
	int result;
	int k;

	result = 0;
	if (obj[2] == 6) {
		memset(&req, 0, sizeof(req));
		memset(req.ids, 0xff, sizeof(req.ids));
		fcn_0051af00(text, 0x9c);
		result = 1;
		req.kind = 6;
		req.a = 1;
		req.size = (g_7f4ca0[g_774970].b9 ? 1 : 2) | 0x400;
		req.cd = g_666018;
		e = fcn_005cd440(&req, text, 0, 0);
		if (e == 0) {
			return 0;
		}
	} else {
		e = fcn_00508e40(arg[1]);
		if (e != 0) {
			result = 1;
		}
	}
	if (result) {
		k = (fcn_005c6270(obj, 0x2c5) != 0) + 1;
		fcn_004c54c0(*(int*) (obj + 4), *(int*) (e + 4), k * 25, 1);
		if (e[2] == 6 || e[2] == 7) {
			fcn_0051af00(text2, 0xfe9, *(unsigned short*) obj);
			fcn_00545d40(*(int*) (e + 4), -1, text2, 0, 0x5ec, 0);
		}
	}
	return result;
}
