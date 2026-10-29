


#include <string.h>

typedef struct
{
	int x0;
	int x4;
	__int64 mask;
	int x10;
	char pad14[0x3c];
} Query;
// SIZE 0x50

extern __int64 g_666018;

char* __cdecl fcn_00508e40(int);
int __cdecl fcn_004946f0(char*, char*, int);
void __cdecl fcn_004c6ae0(int, int);
void __cdecl fcn_004c54c0(int, int, int, int);
void __cdecl fcn_0051af00(void*, int, ...);
int __cdecl fcn_005cd440(Query*, char*, int, void*);
int __cdecl fcn_005d6ea0(unsigned short*);

int __cdecl fcn_005d70c0(char* e, char* o)
{
	int r;
	int n;
	int v;
	char* p;

	r = 0;
	if (e[2] != 6 && e[2] != 7) {
		n = *(int*) (o + 4);
		if (*(int*) (e + 0x194) < n || n < 1 || n > 5) {
			return 0x60;
		}
		p = fcn_00508e40(*(int*) (o + 0x214));
		if (p == 0) {
			return 0x60;
		}
		n = *(int*) (o + 4);
		v = fcn_004946f0(e, p, n);
		fcn_004c6ae0(*(int*) (e + 4), -n);
		fcn_004c54c0(*(int*) (e + 4), *(int*) (p + 4), v, 1);
		return 0x10;
	} else {
		Query q;
		char buf[0x40];

		memset(&q, 0, sizeof(q));
		q.x4 = 0x400;
		q.x10 = 6;
		q.mask = g_666018;
		if (e[9] == 0) {
			fcn_0051af00(buf, 0x1dae, 0x1daf);
		} else {
			fcn_0051af00(buf, 0x1dae, 0x1db0);
		}
		if (fcn_005cd440(&q, buf, 0, (void*) fcn_005d6ea0) != 0) {
			r = 1;
		}
	}
	return r;
}
