

#include <string.h>

void __cdecl fcn_00458a10(char* src, char* pos, float* out);
char* __cdecl fcn_00501190(int, int);
char* __cdecl fcn_00501030(void);
int __cdecl fcn_00451840(char* a, char* b, float range);
void __cdecl fcn_0058fa60(char*, int);

void __cdecl fcn_0058fb00(char* e)
{
	float pa[4];
	float pb[4];
	int ok;
	char* o;
	char* s;
	char* p;
	char* q;

	ok = 1;
	o = *(char**) (e + 0x1f8);
	if (o != 0) {
		fcn_00458a10(o, o + 0x4c, pa);
		p = fcn_00501190(1, 6);
		while (p != 0) {
			q = *(char**) (p + 0x61);
			if (q != 0) {
				fcn_00458a10(q, q + 0x4c, pb);
				if (fcn_00451840((char*) pb, (char*) pa, 100.0f)) {
					ok = 0;
					break;
				}
			}
			p = fcn_00501030();
		}
	}
	for (s = *(char**) (e + 0x1fc); s != 0; s = *(char**) (s + 0x1f0)) {
		if (strncmp(s, "bk_", 3) == 0 || strncmp(s, "!bk_", 4) == 0) {
			fcn_00458a10(s, s + 0x4c, pa);
			p = fcn_00501190(1, 6);
			while (p != 0) {
				q = *(char**) (p + 0x61);
				if (q != 0) {
					fcn_00458a10(q, q + 0x4c, pb);
					if (fcn_00451840((char*) pb, (char*) pa, 100.0f)) {
						ok = 0;
						goto done;
					}
				}
				p = fcn_00501030();
			}
		}
	}
done:
	fcn_0058fa60(e, ok);
}
