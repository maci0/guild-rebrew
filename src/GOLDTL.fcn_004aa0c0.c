// FUNCTION: GOLD 0x004a9fa0
// SIZE: 382
// FUNCTION: GOLDTL 0x4aa0c0
// SIZE: 382

#include <string.h>

typedef struct Query {
	int kind;
	int a;
	int b;
	char padc[0x214 - 0xc];
	int c;
	int d;
	char* p;
} Query;
// SIZE 0x220

char* __cdecl fcn_005463a0(int, int, int);
char* __cdecl fcn_005462a0(void);
char* __cdecl fcn_00508e40(int id);
int __cdecl fcn_004fa5b0(int k, char* e, Query* q);

int __cdecl fcn_004aa0c0(char* e, char* cmd, char* a3)
{
	Query q;
	char* r;
	int k;

	if (*cmd != 0x10) {
		return 0;
	}
	memset(&q, 0, sizeof(q));
	q.p = 0;
	if ((*(int*) (e + 0x1c8) & 0x100) && *(int*) (cmd + 8) == 4) {
		for (r = fcn_005463a0(1, 0, 0x45); r != 0; r = fcn_005462a0()) {
			if (*(int*) (r + 0xac) == *(int*) (e + 4)) {
				break;
			}
		}
		if (r == 0) {
			return 0;
		}
		q.p = fcn_00508e40(*(int*) (r + 0xb0));
	}
	q.kind = *(int*) (cmd + 8);
	k = *(int*) (cmd + 4);
	switch (k) {
	case 0x13:
	case 0x14:
		q.a = *(int*) (a3 + 4);
		q.b = *(int*) (a3 + 8);
		break;
	case 0x1c:
		q.c = *(int*) (a3 + 4);
		q.a = *(int*) (a3 + 8);
		break;
	case 0x27:
		q.c = *(int*) (a3 + 4);
		break;
	case 0x25:
	case 0x28:
	case 0x2a:
		q.c = *(int*) (a3 + 4);
		q.d = *(int*) (a3 + 8);
		break;
	case 0x2b:
		q.a = *(int*) (cmd + 0x10);
		break;
	case 0x12:
	case 0x2c:
	case 0x31:
	case 0x32:
	case 0x35:
	case 0x37:
		q.c = *(int*) (a3 + 4);
		break;
	case 0x1d:
	case 0x21:
	case 0x24:
	case 0x29:
	case 0x2d:
		break;
	default:
		return 0;
	}
	return !(fcn_004fa5b0(k, e, &q) & 0x60);
}
