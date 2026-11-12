#include <string.h>

typedef struct { int v[6]; } Blk4e7d40;

void __cdecl fcn_004c4eb0(char* s);
void __cdecl fcn_004c4ef0(char* s);
int __cdecl fcn_004c6360(void* info);

typedef struct
{
	unsigned char f00;
	char pad01[3];
	int f04;
	unsigned char f08;
	char pad09[3];
	int f0c;
	unsigned char f10;
	char pad11[5];
} Rec18;
// SIZE 0x18

typedef struct
{
	int owner; unsigned char sel;
	unsigned char alt;
	unsigned char id;
	char pad3;
	int data[6];
} Info4e7d40;
/* SIZE 0x20 */

extern char g_9a9220[];
extern char g_68da68[];

/* ADDRESS: GOLDTL 0x004e7d40 */
int __cdecl fcn_004e7d40(char* a0, int a1)
{
	Info4e7d40 info;
	Rec18* r;
	char* src;
	int i;
	int first;
	int flag;

	int res;

	if (*(unsigned char*) (a0 + 0x168) != 0) {
		return -1;
	}
	i = 0;
	src = g_9a9220 + 8;
	while ((int) *(unsigned char*) src != a1) {
		src += 0x18;
		i++;
		if ((int) src >= (int) 0x9a94f8) {
			return -1;
		}
	}
	if (i >= 0x1e) {
		return -1;
	}
	r = (Rec18*) (g_9a9220 + i * 0x18); src = g_68da68 + (int) r->f08 * 0x18;
	info.id = (unsigned char) a1;
	*(Blk4e7d40*) info.data = *(Blk4e7d40*) src;
	info.sel = 0xff;
	info.alt = 0xff;
	if (info.data[4] != 0) {
		first = 0;
		flag = 0;
		if (r->f04 == -1 && r->f10 == 3 && r->f0c < 4) {
			info.sel = r->f00;
			first = 1;
			info.owner = *(int*) (a0 + 4);
			flag = 1;
		}
		i++;
		if (i <= 0x1d) {
			src = g_9a9220 + 8 + i * 0x18;
			do {
				if ((int) *(unsigned char*) src == a1) { r = (Rec18*) (g_9a9220 + i * 0x18);
					if (i <= 0x1d && r->f04 == -1 && r->f10 == 3 && r->f0c < 4) {
						if (!first) {
							info.sel = r->f00;
							info.owner = *(int*) (a0 + 4);
							fcn_004c4eb0((char*) 0x67eef4);
							res = fcn_004c6360(&info);
							fcn_004c4ef0((char*) 0x67eef4);
							return res;
						}
						info.alt = r->f00;
					}
					break;
				}
				src += 0x18;
				i++;
			} while ((int) src < (int) 0x9a94f8);
		}
		if (flag) {
			fcn_004c4eb0((char*) 0x67eef4);
			res = fcn_004c6360(&info);
			fcn_004c4ef0((char*) 0x67eef4);
			return res;
		}
	}
	r = (Rec18*) (g_9a9220 + i * 0x18);
	if (r->f04 != -1) {
		return -1;
	}
	if (r->f10 != 3) {
		return -1;
	}
	if (r->f0c >= 4) {
		return -1;
	}
	info.owner = *(int*) (a0 + 4);
	info.sel = r->f00;
	fcn_004c4eb0((char*) 0x67eef4);
	res = fcn_004c6360(&info);
	fcn_004c4ef0((char*) 0x67eef4);
	return res;
}
