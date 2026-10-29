#include <string.h>

typedef struct Msg {
	unsigned char type;
	char pad[3];
	int a;
	int b;
	int c;
	int d;
	float f;
} Msg;
// SIZE 0x18

int __cdecl fcn_004aa240(int a1, int a2, int a3, Msg* a, Msg* b);

/* ADDRESS: GOLDTL 0x0049cf80 */
int __cdecl fcn_0049cf80(int a1, int a2, int k, Msg* out1, Msg* out2)
{
	Msg a;
	Msg b;

	if (!k) {
		memset(&a, 0, sizeof(a));
		memset(&b, 0, sizeof(b));
		a.type = 0x10;
		a.a = 8;
		a.b = 0;
		if (fcn_004aa240(a1, a2, 0, &a, &b)) {
			*out1 = a;
			*out2 = b;
			return 0x2b;
		}
	}
	return 0;
}
