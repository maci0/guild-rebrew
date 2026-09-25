#include <string.h>

#pragma pack(1)
struct s36_4ce430 {
	int v[9];
};
// SIZE 0x24

struct s87_4ce430 {
	int v[21];
	short w;
	char b;
};
// SIZE 0x57
#pragma pack()

struct s72_4ce430 {
	int a;
	int b;
	char text[0x40];
};
// SIZE 0x48

extern struct s36_4ce430 g_9baa20;
extern int g_9baa08;
extern int g_9baa04;

int* __cdecl fcn_004cdf00(int);
struct s87_4ce430* __cdecl fcn_004cded0(void);
void __cdecl fcn_004cdf40(int, int, char*);

// FUNCTION: GOLD 0x4cd870
// SIZE: 352
// FUNCTION: GOLDTL 0x4ce430
// SIZE: 348

int __cdecl fcn_004ce430(char* rec, char* out)
{
	struct s72_4ce430 tmp;
	int* r;

	if (out != 0)
		out[0] = 2;
	switch (*(int*) (rec + 0x10)) {
	case 0:
		g_9baa20 = *(struct s36_4ce430*) (rec + 0x14);
		break;
	case 1:
		r = fcn_004cdf00(*(int*) (rec + 0x14));
		if (r == 0)
			return -2;
		r[0] = *(int*) (rec + 0x14);
		r[1] = *(int*) (rec + 0x18);
		break;
	case 2:
		r = (int*) fcn_004cded0();
		if (r == 0)
			return -1;
		*(struct s87_4ce430*) r = *(struct s87_4ce430*) (rec + 0x14);
		break;
	case 3:
		r = fcn_004cdf00(*(int*) (rec + 0x14));
		if (r == 0)
			return -2;
		if (*(int*) (rec + 0x18) == 1)
			g_9baa08 = 1;
		memset(r, 0, sizeof(struct s87_4ce430));
		break;
	case 4:
		r = fcn_004cdf00(*(int*) (rec + 0x14));
		if (r == 0)
			return -2;
		*(struct s87_4ce430*) r = *(struct s87_4ce430*) (rec + 0x14);
		break;
	case 5:
		r = fcn_004cdf00(*(int*) (rec + 0x14));
		if (r == 0)
			return -2;
		*(struct s87_4ce430*) r = *(struct s87_4ce430*) (rec + 0x14);
		break;
	case 6:
		tmp = *(struct s72_4ce430*) (rec + 0x14);
		fcn_004cdf40(tmp.a, tmp.b, tmp.text);
		break;
	default:
		return 1;
	}
	if (out != 0)
		out[0] = 1;
	g_9baa04 = 1;
	return 0;
}
