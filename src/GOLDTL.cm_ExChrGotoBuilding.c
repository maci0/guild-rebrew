#include <string.h>

/* 12-byte block copied to a task record at +0xf0 (fields 4+4+2+1 = 11 bytes). */
typedef struct {
	int a;
	int b;
	short c;
	char d;
} TLBLK11;

/* 18-byte block copied to a task record at +0xf0 (4 dwords + word). */
typedef struct {
	int a;
	int b;
	int c;
	int d;
	short e;
} TLBLK18;

int __cdecl fcn_0064d41a(char*, char*, ...);
char* __cdecl fcn_004032b0(char*);
char* __cdecl gm_StartFilteredEntitySearch(int, int, ...);
int __cdecl gm_CheckEntityType(char*);
int __cdecl fcn_00413190(int);
void __cdecl fcn_004432d0(int, int);
char* __cdecl fcn_00502cd0(int, int, ...);
int __cdecl fcn_00515540(char*);
int __cdecl fcn_005155e0(char*);
int __cdecl fcn_00406670(char*, char*);
char* __cdecl fcn_00406850(char*, char*, char*, int, int, int);
char* __cdecl fcn_00445600(int, int, int, char*);
char* __cdecl fcn_004456e0(char*, int, int, char*);
void __cdecl fcn_00455350(char*, char*, float*);
char __cdecl fcn_0045b990(char*, float*, int*, int*, float*);
char* __cdecl fcn_0040c120(char*, int, ...);
char* __cdecl fcn_0055d630(char*);
char* __cdecl strupr(char*);
void __cdecl fcn_0041d9e0(char*);

extern char g_68b0d8[];
extern char g_6756b8[];
extern char g_675908[];
extern char g_68b1f8[];
extern char g_68b214[];
extern char g_68b1e0[];
extern char g_68b108[];
extern char g_68b13c[];
extern char g_68b174[];
extern char g_68b1ac[];
extern TLBLK11 g_68149c;
extern TLBLK18 g_68b0f4;
extern char* g_99ec10;
extern int g_6b8010;
extern char* g_1043370[];

/* ADDRESS: GOLDTL 0x004ca970 */
int __cdecl cm_ExChrGotoBuilding(char* e, char* out)
{
	char* C;
	int row;
	int col;
	char* B;
	float height;
	float pos[4];
	int saved;
	char* A;
	char buf[0x80];
	char buf2[0x80];
	char* o;
	char* u;
	char* q;
	char* r;
	char* m;
	int k;

	/* chunk 0: native ins 0-99 */
	C = 0;
	fcn_0064d41a(buf2, g_68b0d8, *(int*) (e + 0x10));
	o = fcn_004032b0(buf2);
	if (o == 0)
		return 1;
	A = gm_StartFilteredEntitySearch(1, 0, 0x44);
	if (*(int*) (e + 0x14) != -1) {
		B = gm_StartFilteredEntitySearch(1, 1, *(int*) (e + 0x14));
		if (B == 0)
			return 1;
	} else {
		B = A;
	}
	if (*(int*) (o + 0x2c) != -1)
		C = gm_StartFilteredEntitySearch(1, 1, *(int*) (o + 0x2c));

	/* chunk 1: native ins 100-199 */
	saved = g_6b8010;
	if (C != 0 && gm_CheckEntityType(C) != 0) {
		k = fcn_00413190(*(int*) (o + 0x88));
		fcn_004432d0(k, 1);
		if (k < 0)
			goto end;
		if (*(int*) (o + 0x30) != -1) {
			q = fcn_00502cd0(*(int*) (C + 0x5d), 1, 1, *(int*) (o + 0x30));
			if (q != 0 && *(unsigned short*) q != 0xfd) {
				fcn_0064d41a(buf, g_68b214,
				    strupr(g_99ec10 + *(unsigned short*) q * 0x41 + 1));
				q = fcn_00502cd0(*(int*) (C + 0x5d), 1, 0, 0xfd);
				k = fcn_005155e0(C);
				if (k >= 0 && q != 0) {
					fcn_00406670(o, g_6756b8);
					r = fcn_00406850(o, buf, g_68b1f8, k, *(int*) (C + 1),
					    *(int*) (q + 2));
					if (r != 0)
						strcpy(r + 0x70, e + 0x3d);
				}
			}
		}

		/* chunk 2: native ins 200-299 */
		if (*(int*) (B + 1) != *(int*) (C + 1)) {
			k = fcn_005155e0(B);
			if (k < 0)
				goto end;
			fcn_004432d0(k, 1);
			u = fcn_00445600(0, 0x100, 0, g_68b1e0);
			if (u != 0) {
				m = g_1043370[k * 247];
				fcn_00455350(u, u + 0x4c, pos);
				if (fcn_0045b990(m, pos, &col, &row, &height) != 0) {
					r = fcn_0040c120(o, 0x2d, col, row, k);
					if (r != 0)
						strcpy(r + 0x70, e + 0x3d);
				}
			}

			/* chunk 3: native ins 300-399 */
			fcn_0040c120(o, 0x38, 0);
			r = fcn_0040c120(o, 0x33, 0, -1, -1);
			fcn_0040c120(o, 0x38, 1);
			if (r == 0) {
				fcn_004432d0(saved, 1);
				return 1;
			}
			strcpy(r + 0x70, e + 0x3d);
			if (*(int*) (C + 0x61) != 0) {
				fcn_004432d0(0, 1);
				u = fcn_00445600(*(int*) (C + 0x61), 0x100, 0,
				    (char*) &g_68149c);
				if (u == 0)
					u = fcn_004456e0(*(int*) (C + 0x61), 0x100, 0,
					    (char*) &g_68149c);
				if (u == 0)
					u = *(char**) (C + 0x61);
				fcn_00455350(u, u + 0x4c, pos);
				*(float*) (r + 0x180) = pos[0];
				*(float*) (r + 0x184) = pos[1];
				r[0x17c] = 1;
				*(float*) (r + 0x188) = pos[2];
			}
		}
	} else {
		/* chunk 4: native ins 400-499 */
		if (*(int*) (o + 0x2c) != *(int*) (A + 1)
		    && *(int*) (o + 0x2c) != -1) {
			k = fcn_00413190(*(int*) (o + 0x88));
			fcn_004432d0(k, 1);
			if (k < 0)
				goto end;
			fcn_00406670(o, g_6756b8);
			u = fcn_00445600(0, 0x100, 0, g_675908);
			if (u != 0) {
				m = g_1043370[k * 247];
				fcn_00455350(u, u + 0x4c, pos);
				if (fcn_0045b990(m, pos, &col, &row, &height) != 0) {
					r = fcn_0040c120(o, 0x2d, col, row, k);
					if (r != 0)
						strcpy(r + 0x70, e + 0x3d);
				}
			}

			/* chunk 5: native ins 500-599 */
			fcn_0040c120(o, 0x38, 0);
			r = fcn_0040c120(o, 0x33, 0, -1, -1);
			fcn_0040c120(o, 0x38, 1);
			if (r == 0)
				goto after;
			strcpy(r + 0x70, e + 0x3d);
			*(TLBLK11*) (r + 0xf0) = g_68149c;
			if (C == 0)
				goto after;
			u = fcn_00445600(*(int*) (C + 0x61), 0x100, 0,
			    (char*) &g_68149c);
			if (u != 0) {
				fcn_00455350(u, u + 0x4c, pos);
			} else if (*(int*) (C + 0x61) != 0) {
				u = *(char**) (C + 0x61);
				fcn_00455350(u, u + 0x4c, pos);
			} else {
				fcn_0041d9e0(g_68b1ac);
			}
			r[0x17c] = 1;
			*(float*) (r + 0x180) = pos[0];
			*(float*) (r + 0x184) = pos[1];
			*(float*) (r + 0x188) = pos[2];
		}
	}

after:
	/* chunk 6: native ins 600-699 */
	if (gm_CheckEntityType(B) != 0)
		goto b3;
	fcn_004432d0(0, 1);
	if (e[0x1d] != 0) {
		u = fcn_00445600(0, 0x100, 0, e + 0x1d);
	} else if (*(int*) (B + 0x61) != 0) {
		if (*(int*) (o + 0x124) != 0) {
			u = fcn_0055d630(*(char**) (B + 0x61));
		} else {
			u = fcn_00445600(*(int*) (B + 0x61), 0x100, 0,
			    (char*) &g_68149c);
			if (u == 0) {
				u = fcn_004456e0(*(int*) (B + 0x61), 0x100, 0,
				    (char*) &g_68149c);
				if (u == 0)
					u = *(char**) (B + 0x61);
			}
		}
	}
	if (u != 0) {
		m = g_1043370[0];
		fcn_00455350(u, u + 0x4c, pos);
		if (fcn_0045b990(m, pos, &col, &row, &height) != 0) {
			r = fcn_0040c120(o, 0x2d, col, row, 0);
			if (r != 0)
				strcpy(r + 0x70, e + 0x3d);
		}
	}

	/* chunk 7: native ins 700-799 */
	if (e[0x1c] != 0)
		goto saved_exit;
	if (*(int*) (e + 0x18) != -1) {
		k = fcn_00515540(fcn_00502cd0(*(int*) (B + 0x5d), 1, 1,
		    *(int*) (e + 0x18)));
		if (k < 0) {
			fcn_0041d9e0(g_68b108);
			goto diag39;
		}
	} else {
		k = 0;
	}
	if (*(int*) (e + 0x18) != -1) {
		q = fcn_00502cd0(*(int*) (B + 0x5d), 1, 1, *(int*) (e + 0x18));
		if (q == 0)
			fcn_0041d9e0(g_68b13c);
	} else {
		fcn_0041d9e0(g_68b174);
	}
	fcn_0040c120(o, 0x38, 0);
	r = fcn_0040c120(o, 0x33, k, *(int*) (B + 1), *(int*) (e + 0x18));
	if (r != 0)
		strcpy(r + 0x70, e + 0x3d);
	fcn_0040c120(o, 0x38, 1);
diag39:
	r = fcn_0040c120(o, 0x39, k);
	if (r != 0)
		strcpy(r + 0x70, e + 0x3d);
	goto saved_exit;

b3:
	/* chunk 8: native ins 800-899 */
	if (*(int*) (B + 1) != *(int*) (o + 0x2c)) {
		fcn_004432d0(0, 1);
		u = fcn_00445600(*(int*) (B + 0x61), 0x100, 0,
		    (char*) &g_68149c);
		if (u == 0)
			u = fcn_004456e0(*(int*) (B + 0x61), 0x100, 0,
			    (char*) &g_68149c);
		if (u != 0) {
			m = g_1043370[0];
			fcn_00455350(u, u + 0x4c, pos);
			if (fcn_0045b990(m, pos, &col, &row, &height) != 0) {
				r = fcn_0040c120(o, 0x2d, col, row, 0);
				if (r != 0)
					strcpy(r + 0x70, e + 0x3d);
			}
		}
	}
	if (e[0x1c] != 0)
		goto saved_exit;

	/* chunk 9: native ins 900-957 */
	q = fcn_00502cd0(*(int*) (B + 0x5d), 1, 1, *(int*) (e + 0x18));
	if (q == 0)
		q = fcn_00502cd0(*(int*) (B + 0x5d), 1, 0, 0xfd);
	if (q == 0) {
		k = fcn_005155e0(B);
		if (k < 0)
			goto saved_exit;
		fcn_0040c120(o, 0x38, 0);
		r = fcn_0040c120(o, 0x33, k, *(int*) (B + 1), -1);
		if (r != 0) {
			strcpy(r + 0x70, e + 0x3d);
			*(TLBLK18*) (r + 0xf0) = g_68b0f4;
		}
		fcn_0040c120(o, 0x38, 1);
	} else if (*(unsigned short*) q != 0xfd) {
		k = fcn_00515540(q);
		fcn_0064d41a(buf, g_68b214,
		    strupr(g_99ec10 + *(unsigned short*) q * 0x41 + 1));
		if (C != 0) {
			r = fcn_00406850(o, buf, g_675908, k, *(int*) (C + 1),
			    *(int*) (q + 2));
			if (r != 0)
				strcpy(r + 0x70, e + 0x3d);
		}
	} else {
		if (*(int*) (B + 1) == *(int*) (o + 0x2c))
			goto saved_exit;
		k = fcn_005155e0(B);
		if (k < 0)
			goto end;
		fcn_0040c120(o, 0x38, 0);
		r = fcn_0040c120(o, 0x33, k, *(int*) (B + 1), *(int*) (q + 2));
		if (r != 0) {
			strcpy(r + 0x70, e + 0x3d);
			memcpy(r + 0xf0, g_68b1e0, 0x18);
		}
		fcn_0040c120(o, 0x38, 1);
		fcn_004432d0(k, 1);
		if (*(int*) (o + 0x124) != 0)
			u = fcn_00445600(0, 0x100, 0, (char*) &g_68b0f4);
		else
			u = fcn_00445600(0, 0x100, 0, g_675908);
		if (u == 0)
			goto saved_exit;
		m = g_1043370[k * 247];
		fcn_00455350(u, u + 0x4c, pos);
		if (fcn_0045b990(m, pos, &col, &row, &height) != 0) {
			r = fcn_0040c120(o, 0x2d, col, row, k);
			if (r != 0)
				strcpy(r + 0x70, e + 0x3d);
		}
	}

saved_exit:
	fcn_004432d0(saved, 1);
	if (out != 0) {
		out[0] = 1;
		out[1] = 7;
		*(char**) (out + 6) = o;
	}
end:
	return 0;
}
