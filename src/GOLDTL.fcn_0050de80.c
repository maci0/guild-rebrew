// FUNCTION: GOLD 0x0050aa00
// SIZE: 233
// FUNCTION: GOLDTL 0x0050de80
// SIZE: 233

#include <string.h>

typedef struct
{
	int x0;
	int n;
	int x8[16];
	unsigned short x48[16];
	int x68[16];
	int xa8;
	int xac;
	int xb0;
	char* xb4;
} Stats;
// SIZE 0xb8

char* __cdecl fcn_00502cd0(int list, int a, int b, ...);
char* __cdecl fcn_00502850(void);
int __cdecl fcn_0050dfd0(char* q, int id);
float __cdecl fcn_0050b980(int id, int n);

int __cdecl fcn_0050de80(char* e, Stats* s)
{
	char* q;
	char* r;

	memset(s, 0, sizeof(Stats));
	q = fcn_00502cd0(*(int*) (e + 0x14), 1, 0, 0x1dd);
	if (q == 0) {
		return 0;
	}
	r = fcn_00502cd0(*(int*) (q + 0x14), 1, 5);
	s->x0 = *(unsigned char*) (q + 0x1c);
	while (r != 0) {
		s->x68[s->n] = *(int*) (r + 0xe);
		s->x8[s->n] = fcn_0050dfd0(q, *(unsigned short*) r);
		s->xa8 += s->x8[s->n];
		s->xac += *(int*) (r + 0xe);
		s->x48[s->n] = *(unsigned short*) r;
		s->n++;
		s->xb0 = (int) (fcn_0050b980(*(unsigned short*) r, 100) * *(int*) (r + 0xe) + s->xb0);
		r = fcn_00502850();
	}
	s->xb4 = q;
	return 1;
}
