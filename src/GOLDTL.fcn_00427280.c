#include <string.h>

extern char* g_6b7e98;

void __cdecl fcn_00425bf0(char*, int, char*);
void __cdecl fcn_00426680(int, int*);
int __cdecl fcn_00428800(int);
int __cdecl fcn_004263b0(int);
int __cdecl fcn_00426340(void);

/* ADDRESS: GOLDTL 0x00427280 */
int __cdecl fcn_00427280(void)
{
	char* dat;
	char* rec;
	int* elem;
	char* s;
	int len;
	int pos;
	int v10;
	int v8;
	int n;
	int r;

	dat = g_6b7e98;
	s = (char*) 0x14cb3c0;
	len = strlen(s);
	pos = *(int*) (dat + 0x118);
	fcn_00426680(pos, &v8);
	if (v8 != 1 || v10 != 0xc) {
		fcn_00425bf0(dat, *(int*) (dat + 0x118), "Syntax error: '(' missing!");
		return 0;
	}
	r = fcn_00428800(0);
	rec = *(char**) (dat + 0xc28);
	n = *(int*) (rec + 8);
	elem = (int*) (rec + (n + 3) * 16);
	elem[0] = 0;
	elem[1] = 0;
	elem[2] = 0;
	elem[3] = 0;
	*(int*) (rec + n * 16 + 0x38) = 2;
	elem[0] = pos - len;
	*(int*) (rec + n * 16 + 0x34) = r;
	pos = *(int*) (dat + 0x118);
	fcn_00426680(pos, &v8);
	if (v8 != 1 || v10 != 8) {
		*(char*) (rec + n * 16 + 0x3c) = 1;
		*(int*) (dat + 0x118) = pos;
	} else {
		*(char*) (rec + n * 16 + 0x3c) = 0;
	}
	rec = *(char**) (dat + 0xc28);
	(*(int*) (rec + 8))++;
	rec = *(char**) (dat + 0xc28);
	if (*(int*) (rec + 8) > 8) {
		fcn_00425bf0(dat, *(int*) (dat + 0x118), "Too many looplevel...");
		*(int*) (rec + 8) -= 1;
	}
	if (r)
		return 0;
	dat = g_6b7e98;
	if (v8 != 1) {
		if (!fcn_00426340()) {
			fcn_00425bf0(dat, *(int*) (g_6b7e98 + 0x118), "Syntax error: ';' missing!");
			return 0;
		}
	} else {
		if (v10 != 8)
			return 0;
		*(int*) (dat + 0x118) = pos;
		fcn_004263b0(1);
	}
	*(int*) (g_6b7e98 + 0x118) -= 1;
	return 0;
}
