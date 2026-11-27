#include <stdio.h>

typedef struct Shape {
	unsigned int len;
	short pad4;
	unsigned short w;
	short pad8;
	unsigned short h;
	unsigned char type;
} Shape;
// SIZE 0xd

typedef struct Bank {
	char magic[8];
	char ver;
	char pad9;
	char name[0x2a - 0xa];
	unsigned short count;
	unsigned short maxw;
	unsigned short maxh;
	unsigned int size;
	unsigned char type;
} Bank;
// SIZE 0x35

typedef struct Tex {
	char pad0[0x10];
	int pw;
} Tex;
// SIZE 0x14

extern char s_67da68[];
extern int g_100ef80;
extern int g_67d96c;

void __cdecl d2_DrawGrayscaleRleSprite(int x, int y, Tex* t, char* sh);

/* ADDRESS: GOLDTL 0x00479b70 */
int __cdecl d2_DrawGrayscaleShapeFrame(int x, int y, Tex* tex, Bank* bank, int idx)
{
	char msg[0x80];
	char* shape;
	int saved;

	if (!bank) {
		return 0;
	}
	if (idx > bank->count) {
		sprintf(msg, s_67da68, bank->name);
		return 0;
	}
	shape = (char*) bank + *(unsigned int*) ((char*) bank + 0x45 + idx * 4);
	if (g_100ef80 == 0) {
		saved = g_67d96c;
		g_67d96c = tex->pw;
		switch (((Shape*) shape)->type) {
		case 0:
			return 0;
		case 1:
			d2_DrawGrayscaleRleSprite(x, y, tex, shape);
			break;
		case 2:
			break;
		default:
			g_67d96c = saved;
			break;
		}
	}
	return 1;
}
