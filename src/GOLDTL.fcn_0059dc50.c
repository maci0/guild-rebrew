// FUNCTION: GOLDTL 0x0059dc50
// SIZE: 158

#include <string.h>

typedef struct
{
	int x0;
	int x4;
	unsigned int x8;
	int xc;
	int x10;
	char pad14[0x38];
	int x4c;
} Query;
// SIZE 0x50

int __cdecl fcn_00525fb0(char*);
void __cdecl fcn_0052a0c0(char*, int);
void __cdecl fcn_0051af00(void*, int, ...);
void __cdecl fcn_005bdc30(int, Query*, char*, void*, int);
void __cdecl fcn_0059da50(char*);
void __cdecl fcn_0052a2d0(void);
void __cdecl fcn_0052ae70(void);

void __cdecl fcn_0059dc50(char* e)
{
	Query q;
	char buf[0x400];

	if (fcn_00525fb0(e) != 0) {
		return;
	}
	memset(&q, 0, sizeof(q));
	q.x4 = 0x400;
	if (e == 0) {
		return;
	}
	fcn_0052a0c0(e, 0);
	q.x4c = 0x727;
	q.x10 = 6;
	q.x8 = 0xa07443a0;
	q.xc = 1;
	fcn_0051af00(buf, 0x1a83);
	fcn_005bdc30(1, &q, buf, (void*) fcn_0059da50, 0);
	fcn_0052a2d0();
	fcn_0052ae70();
}
