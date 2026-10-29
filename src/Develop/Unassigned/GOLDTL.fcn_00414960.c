#include <stdlib.h>

extern char* g_6b8014;

void __cdecl fcn_00438100(char* obj, char* cam, char force);
int __cdecl fcn_00414830(void);

/* ADDRESS: GOLDTL 0x00414960 */
void __cdecl fcn_00414960(float* a0, float* a1, char* obj)
{
	float* p;
	char* node;
	int i;

	if (*(int*) (obj + 0x1cc) == 0) {
		return;
	}
	if ((*(unsigned char*) (obj + 0x216) & 0x20) == 0) {
		fcn_00438100(obj, g_6b8014, 0);
	}
	p = (float*) (*(int (__cdecl**) (char*, int, int)) (*(int*) (*(int*) (obj + 0x1cc) + 0x318) + 0x1f0)) (obj, *(int*) (obj + 0x1cc), *(int*) (obj + 0x1ec) + 8);
	if (p != 0) {
		a0[0] = p[0];
		a0[1] = p[1];
		a0[2] = p[2];
		a1[0] = p[0];
		a1[1] = p[1];
		a1[2] = p[2];
		p += 0x14;
		for (i = 7; i != 0; i--) {
			a0[0] = __min(a0[0], p[0]);
			a0[1] = __min(a0[1], p[1]);
			a0[2] = __min(a0[2], p[2]);
			a1[0] = __max(a1[0], p[0]);
			a1[1] = __max(a1[1], p[1]);
			a1[2] = __max(a1[2], p[2]);
			p += 0x14;
		}
	}
	node = *(char**) (obj + 0x200);
	while (node != 0) {
		fcn_00414830((char*) a0, (char*) a1, node);
		node = *(char**) (node + 0x1f4);
	}
}
