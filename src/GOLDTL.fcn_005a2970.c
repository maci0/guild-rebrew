#include <string.h>

extern int g_772514;
extern char* g_772500;
extern char* g_77255c;
extern unsigned short g_774970;
extern int g_774654;
extern int g_67d370;
extern int g_100f1dc;
extern int g_14ce8e0;
extern unsigned char g_773d75;

/* Slot row passed to fcn_005ca560/fcn_005ca740. */
struct sel {
	char* who;
	char pad4[0x0c];
	int x10;
	int x14;
	char pad18[0x18];
	int used;
	char pad34[4];
};
/* SIZE 0x38 */

int __cdecl fcn_00470820(int a, int b, char* name);
void __cdecl fcn_00471b60(int handle);
void __cdecl fcn_004727a0(int handle, int page);
void __cdecl fcn_005340f0(int a);
void __cdecl fcn_00473a90(int a, int b);
int __cdecl fcn_004f7120(int id, char* record, int* out1, int* out2, int* idx);
void __cdecl fcn_0046f2c0(int a, int b);
int __cdecl fcn_00519190(int id, ...);
int __cdecl fcn_005ca560(struct sel* s);
void __cdecl fcn_005ca740(int x, int y, int a, int b, struct sel* s, int c);
void __cdecl fcn_0051af00(char* buf, int id, ...);
void __cdecl fcn_005c91c0(char* buf, int x, int y, int a, int b);
void __cdecl fcn_00526120(char* text, int value);
int __cdecl fcn_00526010(char* record, unsigned int value, char flag);
void __cdecl fcn_004c4eb0(char* text);
void __cdecl fcn_004c4ef0(char* text);
void __cdecl fcn_004c68c0(void* msg);
void __cdecl fcn_004c58b0(int a, unsigned int b);
void __cdecl fcn_004c51a0(unsigned int a, unsigned int b, int c, unsigned int d);
int __cdecl fcn_005373e0(void* fn, int id);
void __cdecl fcn_00471e30(int handle);
void __cdecl fcn_005a2580(char* a, char* b, char* c);

/* ADDRESS: GOLDTL 0x005a2970 */
void __cdecl fcn_005a2970(char* a0, char* a1)
{
	struct sel sel[3];
	unsigned int out2[6];
	char buf[512];
	int seen[3];
	int vals[3];
	int idx[3];
	int out1;
	int handle;
	int changed;
	int line;
	int x;
	int height;
	int j;
	int i;
	int found;
	int id;
	char* p;

	seen[0] = -1;
	seen[1] = -1;
	seen[2] = -1;
	memset(sel, 0, sizeof(sel));
	vals[0] = 0;
	vals[1] = 0;
	vals[2] = 0;
	handle = fcn_00470820(0, 0, "locations\\Wirtshaus\\DUNKLEECKE");
	fcn_00471b60(handle);
	fcn_004727a0(handle, 0);
	fcn_005340f0(g_772514);
	fcn_00473a90(0, 0);
	memset(sel, 0, sizeof(sel));
	changed = 1;
	do {
		for (j = 0; j < 3; j++) {
			id = *(int*) (a1 + 0x1c + j * 4);
			if (fcn_004f7120(id, (char*) ((*(unsigned short*) (a0 + 0x27)) * 0x21c + 0x7f4ca0),
				&out1, out2, &idx[j])) {
				if (seen[j] != id)
					changed = 1;
				seen[j] = id;
				vals[j] = out1;
				sel[j].who = (char*) ((out2[0] & 0xffff) * 0x21c + 0x7f4ca0);
			} else if (seen[j] != -1) {
				changed = 1;
				sel[j].who = 0;
				seen[j] = -1;
				vals[j] = 0;
			}
		}
		if (changed) {
			fcn_004727a0(handle, 1);
			fcn_0046f2c0(g_772514, 1);
			fcn_00519190(0x18a3);
			line = 0x46;
			x = *(int*) (g_77255c + 0xc) / 2;
			height = *(short*) (g_772500 + 0x1ebd8);
			for (j = 0; j < 3; j++) {
				sel[j].x14 = line - 0x1e;
				sel[j].x10 = (x - height) - 0x28;
				sel[j].used = (sel[j].who != 0);
				fcn_005ca560(&sel[j]);
				fcn_005ca740(sel[j].x10, sel[j].x14, g_772514, 0x54, &sel[j], 1);
				if (seen[j] != -1)
					fcn_0051af00(buf, 0x18a5, idx[j] * 5 + 0x13fd, vals[j]);
				else
					fcn_0051af00(buf, 0x18a6);
				fcn_005c91c0(buf, x, line, 0xf0, 0x54);
				line += 0x69;
			}
			changed = 0;
		}
		if (g_100f1dc != -1) {
			for (j = 0; j < 3; j++) {
				if (g_67d370 == *(int*) &sel[j])
					break;
			}
			if (j < 3) {
				for (i = 0; i < 3; i++) {
					if (*(int*) (a1 + 0x1c + i * 4) == seen[j]) {
						if (fcn_00526010((char*) (g_774970 * 0x21c + 0x7f4ca0),
							vals[j], (char) g_773d75)) {
							out2[1] = 0x62757920;
							out2[2] = *(unsigned int*) (g_774970 * 0x21c + 0x7f4ca4);
							out2[3] = *(unsigned int*) (a0 + 1);
							out2[4] = seen[j];
							out2[5] = vals[j];
							fcn_004c4eb0("buy dunkle ecke");
							fcn_004c68c0(&out2[1]);
							fcn_004c58b0(seen[j],
								*(unsigned int*) (g_774970 * 0x21c + 0x7f4ca4));
							fcn_004c51a0(
								*(unsigned int*) ((*(unsigned short*) (a0 + 0x27)) * 0x21c + 0x7f4ca4),
								*(unsigned int*) (g_774970 * 0x21c + 0x7f4ca4), 0, vals[j]);
							fcn_004c4ef0("buy dunkle ecke");
						}
						break;
					}
				}
				if (j == 3)
					fcn_00526120("$Z$NDiese Information steht nicht mehr zum verkauf!", 0);
			}
		} else if (g_14ce8e0 != 0) {
			g_774654 = 1;
		}
	} while (fcn_005373e0(fcn_005a2580, 0x677c7) != 0);
	fcn_00471e30(handle);
}
