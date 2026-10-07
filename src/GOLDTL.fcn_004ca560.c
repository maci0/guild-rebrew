#include <string.h>

extern char g_68b0d8[];
extern int g_6b8010;

int __cdecl fcn_0064d41a(char*, char*, ...);
char* __cdecl fcn_004032b0(char*);
char* __cdecl gm_StartFilteredEntitySearch(int, int, int, ...);
char* __cdecl fcn_00502cd0(int, int, int, ...);
int __cdecl fcn_00515540(char*);
int __cdecl fcn_005155e0(char*);
int __cdecl gm_CheckEntityType(char*);
char* __cdecl fcn_00508e40(int);
void __cdecl fcn_004fdcf0(char*);
char* __cdecl fcn_0040c120(char*, int, ...);
void __cdecl fcn_004432d0(int, int);
char* __cdecl fcn_00445600(int, int, int, char*);
void __cdecl fcn_00455350(char*, char*, char*);

// FUNCTION: GOLDTL 0x004ca560
int __cdecl fcn_004ca560(char* x, char* out)
{
	char buf[0x80];
	char* o;
	int id;
	char* s;
	char* d;
	char* r;
	char* t;
	char* m;
	int k;
	int dk;
	int saved;

	s = 0;
	d = 0;
	id = -1;
	fcn_0064d41a(buf, g_68b0d8, *(int*) (x + 0x10));
	o = fcn_004032b0(buf);
	if (o == 0)
		return 1;
	if (*(int*) (x + 0x14) != -1) {
		s = gm_StartFilteredEntitySearch(1, 1, *(int*) (x + 0x14));
		if (s == 0)
			return 2;
	}
	if (*(int*) (x + 0x18) != -1) {
		d = fcn_00502cd0(*(int*) (s + 0x5d), 1, 1, *(int*) (x + 0x18));
		if (d == 0)
			return 3;
	}
	if (d != 0 && *(short*) d != 0xfd) {
		k = fcn_00515540(d);
	} else if (s != 0 && gm_CheckEntityType(s) != 0) {
		k = fcn_005155e0(s);
		d = fcn_00502cd0(*(int*) (s + 0x5d), 1, 0, 0xfd);
	} else {
		k = 0;
	}
	if (k >= 0) {
		dk = -1;
		if (d != 0)
			dk = *(int*) (d + 2);
		if (s != 0)
			id = *(int*) (s + 1);
		if (k != 0) {
			t = fcn_00508e40(*(int*) (x + 0x10));
			if (t != 0)
				fcn_004fdcf0(t);
		}
		fcn_0040c120(o, 0x38, 0);
		if (k != 0) {
			r = fcn_0040c120(o, 0x33, k, id, dk);
			if (r != 0)
				strcpy(r + 0xf0, x + 0x1c);
		} else if (*(int*) (s + 0x61) != 0) {
			r = fcn_0040c120(o, 0x33, 0, -1, -1);
			if (r != 0) {
				saved = g_6b8010;
				fcn_004432d0(0, 1);
				m = fcn_00445600(*(int*) (s + 0x61), 0x100, 0, x + 0x1c);
				if (m != 0) {
					fcn_00455350(m, m + 0x4c, r + 0x180);
					r[0x17c] = 1;
				} else {
					strcpy(r + 0xf0, x + 0x1c);
				}
				fcn_004432d0(saved, 1);
			}
		}
		fcn_0040c120(o, 0x38, 1);
	}
	if (out != 0) {
		out[0] = 2;
		out[1] = 0;
		*(int*) (out + 6) = 0;
	}
	return 0;
}
