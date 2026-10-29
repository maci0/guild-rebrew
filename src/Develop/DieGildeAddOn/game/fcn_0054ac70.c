#include "client_types.h"
#include "client_dialog_helpers.h"

extern int g_7f4c00;
extern int g_7f4c04;
extern int g_7f4c08;
extern unsigned short g_7f4c0c;
extern unsigned short g_774970;
extern char g_7f4ca4[];

int __cdecl fcn_004c4450(int id);
int __cdecl fcn_004c5620(int a, char* unit);
void __cdecl fcn_004c5980(void* msg);
void __cdecl fcn_00500bb0(pos14_7f4c00* when, int h, int m, int s);
void __cdecl fcn_00546190(char* unit);
char* __cdecl fcn_00508e40(int id);

/* ADDRESS: GOLDTL 0x0054ac70 */
void __cdecl fcn_0054ac70(char* e)
{
	unsigned int pkt[0x45];
	char text[0x1f0];
	unsigned char* a;
	unsigned char* b;
	unsigned char* c;
	unsigned char* d;
	unsigned char* f;
	unsigned char* g;
	unsigned char kind;
	unsigned char* m;
	int i;
	int w;

	if (*(int*) (e + 0x70) == -1 || *(int*) (e + 0x70) == -2) {
		fcn_00546190(e);
		return;
	}
	if (*(unsigned char*) (e + 0x78) & 4)
		return;
	w = *(int*) (e + 0x84);
	if (w != -1 && !fcn_004c4450(w))
		return;
	*(int*) (e + 0x84) = -1;
	switch (*(int*) (e + 0x70)) {
	case 0:
		kind = (unsigned char) fcn_004c4450(*(int*) (e + 0xd4));
		if (!kind)
			return;
		a = (unsigned char*) fcn_00508e40(*(int*) (e + 0xb0));
		b = (unsigned char*) fcn_00508e40(*(int*) (e + 0xac));
		c = (unsigned char*) fcn_00508e40(*(int*) (e + 0xb4));
		d = (unsigned char*) fcn_00508e40(*(int*) (e + 0xb8));
		f = (unsigned char*) fcn_00508e40(*(int*) (e + 0xbc));
		g = (unsigned char*) fcn_00508e40(*(int*) (e + 0xc0));
		if (kind == 1) {
			*(pos14_7f4c00*) (e + 0x52) = *(pos14_7f4c00*) (e + 0xc5);
			if (a[2] == 6 || a[2] == 7) {
				fcn_0051af00(text, 0x1bc0, *(unsigned short*) b, e + 0x52,
							 *(unsigned short*) (e + 0x56), *(unsigned short*) c,
							 *(unsigned short*) d, *(unsigned short*) f);
				fcn_00545d40(*(int*) (a + 4), *(int*) (a + 4), text, 0, 0x5f5,
							 (char*) 0x6a59e8);
			}
			if (b[2] == 6 || a[2] == 7) {
				fcn_0051af00(text, 0x1bbf, *(unsigned short*) a, e + 0x52,
							 *(unsigned short*) (e + 0x56), *(unsigned short*) c,
							 *(unsigned short*) d, *(unsigned short*) f);
				fcn_00545d40(*(int*) (b + 4), *(int*) (b + 4), text, 1, 0x5f5,
							 (char*) 0x6a59d4);
			}
			fcn_0051af00(text, 0x1bc1, *(unsigned short*) b, *(unsigned short*) a,
						 e + 0x52, *(unsigned short*) (e + 0x56));
			if (d[2] == 6 || d[2] == 7)
				fcn_00545d40(*(int*) (d + 4), *(int*) (d + 4), text, 0, 0x5f5,
							 (char*) 0x6a59c0);
			if (f[2] == 6 || f[2] == 7)
				fcn_00545d40(*(int*) (f + 4), *(int*) (f + 4), text, 0, 0x5f5,
							 (char*) 0x6a59c0);
			fcn_0051af00(text, 0x1bc2, *(unsigned short*) b, *(unsigned short*) a,
						 e + 0x52, *(unsigned short*) (e + 0x56));
			if (c[2] == 6 || c[2] == 7)
				fcn_00545d40(*(int*) (c + 4), *(int*) (c + 4), text, 0, 0x5f5,
							 (char*) 0x6a59ac);
			if (g != 0 && (g[2] == 6 || g[2] == 7))
				fcn_00545d40(*(int*) (g + 4), *(int*) (g + 4), text, 0, 0x5f5,
							 (char*) 0x6a59ac);
			fcn_004c5620(1, e);
			return;
		}
		if (kind != 2)
			return;
		if (b[2] == 6 || a[2] == 7) {
			fcn_0051af00(text, 0x1bbe, *(unsigned short*) a);
			fcn_00545d40(*(int*) (b + 4), *(int*) (b + 4), text, 0, 0x5f5, 0);
		}
		*(pos14_7f4c00*) (e + 0x52) = *(pos14_7f4c00*) &g_7f4c00;
		*(int*) (e + 0x58) = *(int*) (e + 0x58) + 2;
		fcn_004c5620(-1, e);
		return;
	case 1:
		m = (unsigned char*) pkt;
		for (i = 0; i < 0x45; i++)
			pkt[i] = 0;
		*(unsigned char*) (m + 0x74) = *(unsigned char*) (e + 0xc4);
		*(int*) (m + 0x28) = *(int*) (e + 0xb0);
		*(int*) (m + 0x34) = *(int*) (e + 0xbc);
		*(int*) (m + 0x6c) = *(int*) (e + 4);
		*(int*) (m + 0x2c) = *(int*) (e + 0xb4);
		*(int*) (m + 0x38) = *(int*) (e + 0xc0);
		*(int*) (m + 0x30) = *(int*) (e + 0xb8);
		*(int*) (m + 0x24) = *(int*) (e + 0xac);
		*(unsigned char*) (m + 0x20) =
			(unsigned char) ((*(int*) (e + 0xc0) != -1) + 5);
		*(int*) (m + 0x10) = g_7f4c08;
		*(int*) (m + 0x04) = -1;
		*(int*) (m + 0x0c) = g_7f4c04;
		*(unsigned short*) (m + 0x14) = g_7f4c0c;
		*(int*) (m + 0x08) = g_7f4c00;
		*(unsigned char*) (m + 0x16) = 0xa2;
		*(int*) (m + 0) = *(int*) (g_7f4ca4 + (unsigned short) g_774970 * 0x21c);
		fcn_00500bb0((pos14_7f4c00*) m, 0, 0x2d, 0);
		fcn_004c5980(pkt);
		fcn_00500bb0((pos14_7f4c00*) (e + 0x52), 0, 2, 0);
		*(int*) (e + 0x84) = fcn_004c5620(-1, e);
		return;
	}
}
