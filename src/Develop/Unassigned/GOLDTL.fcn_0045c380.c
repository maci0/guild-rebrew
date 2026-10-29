#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern char* g_104049c;
extern unsigned int g_10404a0;
extern int g_10405c0;

/* SIZE 0x70 */
typedef struct Tex {
	char name[0x40];          /* 0x00 */
	int refs;                 /* 0x40 */
	int idx44;                /* 0x44 */
	int color48;              /* 0x48 */
	int pad4c;                /* 0x4c */
	int field50;              /* 0x50 */
	unsigned char b0 : 1;     /* 0x54 */
	unsigned char b1 : 1;
	unsigned char dxt : 1;
	unsigned char b3 : 1;
	unsigned char b4 : 1;
	unsigned char b5 : 1;
	unsigned char b67 : 2;
	unsigned char field55 : 5; /* 0x55 */
	unsigned char x55 : 3;
	unsigned char field56 : 5; /* 0x56 */
	unsigned char x56 : 3;
	char pad57;               /* 0x57 */
	unsigned int id;          /* 0x58 */
	unsigned char field5c;    /* 0x5c */
	unsigned char field5d;    /* 0x5d */
	unsigned char field5e : 4; /* 0x5e */
	unsigned char x5e : 4;
	char pad5f;               /* 0x5f */
	unsigned int format60;    /* 0x60 */
	int field64;              /* 0x64 */
	int field68;              /* 0x68 */
	unsigned int pattern6c;   /* 0x6c */
} Tex;

typedef struct Col {
	unsigned char a;
	unsigned char b;
	unsigned char fl;
	unsigned char d;
} Col;

char __cdecl fcn_00401090(char*);
char* __cdecl fcn_0045bde0(const char*);
int __cdecl fcn_0045be40(char*);
Tex* __cdecl fcn_0045c5b0(char*, Col, unsigned int, unsigned int);

/* ADDRESS: GOLDTL 0x0045c380 */
void __cdecl fcn_0045c380(Tex* t, Col c, unsigned int flags, unsigned int flags2)
{
	char name[0x100];
	char buf2[0x40];
	char buf1[0x40];
	char buf0[0x40];
	Col out;
	char found;
	char* p;
	char* q;
	unsigned int len;
	unsigned int i;
	int n;
	Tex* e;
	unsigned int k;

	found = 0;
	strcpy(buf0, t->name);
	strcpy(buf1, buf0);
	strcpy(buf2, buf0);
	strupr(buf2);
	i = strlen(buf0);
	while (isdigit(buf0[--i]) && i > 0) {
		found = 1;
	}
	len = strlen(buf0);
	if (i < len - 1 && i > 1 && buf2[i - 1] == 'A' && buf2[i - 2] == '_'
	    && found != 0) {
		n = atoi(&buf0[i + 1]);
		if (n == 0 || (c.fl & 4) != 0) {
			out = c;
			out.fl |= 4;
			t->color48 = g_10405c0;
			t->field5d = (unsigned char) n;
			buf1[i + 1] = 0;
			p = (char*) fcn_0045be40(buf0);
			if (p != 0) {
				q = strrchr(p, '/');
				if (q != 0) {
					*q = 0;
				}
				sprintf(name, "%s/%s%i.bmp", p, buf1, n + 1);
				if (fcn_00401090(name) != 0) {
					sprintf(name, "%s%i", buf1, n + 1);
					fcn_0045c5b0(name, out, flags, flags2);
				} else {
					e = (Tex*) g_104049c;
					k = 0;
					while (k < g_10404a0) {
						if (e->refs > 0
						    && e->color48 == g_10405c0) {
							if (strstr((char*) e, buf1) != 0) {
								e->field5c = (unsigned char) (n + 1);
							}
						}
						k++;
						e = (Tex*) ((char*) e + 0x70);
					}
					g_10405c0++;
				}
			}
		}
	}
}
