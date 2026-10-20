#include <string.h>

#pragma optimize("y", off)

typedef struct Hit4ad6a0 {
	char* p;
	float f;
} Hit4ad6a0;

/* Message record handed to the guild request buffer. The native frame holds
 * 0xe8 bytes for it; only the fields written below are evidenced. */
typedef struct Msg4ad6a0 {
	char pad0[4];
	unsigned char type;   /* +0x04 */
	char pad5[3];
	int id;               /* +0x08 */
	int unk_c;            /* +0x0c */
	char pad10[0x18];     /* +0x10 */
	int year;             /* +0x28 */
	int month;            /* +0x2c */
	int day;              /* +0x30 */
	unsigned short hour;  /* +0x34 */
	unsigned char flag;   /* +0x36 */
	char pad37[0x31];     /* +0x37 */
	int unk_68;           /* +0x68 */
	int unk_6c;           /* +0x6c */
	char pad70[0x78];     /* +0x70 */
} Msg4ad6a0;

extern int g_7728d0;
extern int g_664e10[];
extern int g_664e34[];
extern char g_7f4ca0[];
extern int g_7f4c00;
extern int g_7f4c04;
extern int g_7f4c08;
extern unsigned short g_7f4c0c;

int __cdecl fcn_004e8a80(int id, int* out);
char* __cdecl fcn_004e9110(int kind);
float __cdecl fcn_004ad500(unsigned char* a1, unsigned short* a2, int a3, int a4);
void __cdecl fcn_004c5420(int a1, int a2, int a3, int a4, int a5);
int __cdecl fcn_004e8240(unsigned char a1, char* a2, char* a3, int a4, int a5);
void __cdecl fcn_004c5530(char* msg);
void __cdecl fcn_004ad4d0(int a1);

/* Rates every listed entity against the office record, then hands the highest
 * scoring owner to the office and notifies the other guild masters. */
/* ADDRESS: GOLDTL 0x004ad6a0 */
void __cdecl fcn_004ad6a0(void)
{
	Hit4ad6a0 hits[4];
	int info[6];
	Msg4ad6a0 msg;
	char* obj;
	char* best;
	char* rec;
	int id;
	int mask;
	int count;
	int i;
	int v;
	float bv;

	if ((unsigned int) g_7728d0 >= 3) {
		return;
	}
	id = g_664e10[g_7728d0];
	mask = g_664e34[g_7728d0];
	if (fcn_004e8a80(id, info) == 0) {
		return;
	}
	memset(hits, 0, sizeof(hits));
	count = 0;
	rec = g_7f4ca0;
	do {
		if (count >= 4) {
			break;
		}
		if (*(int*) (rec + 0x1cc) & mask) {
			hits[count].p = rec;
			count++;
		}
		rec += 0x21c;
	} while ((int) rec < 0x85a0a0);
	obj = fcn_004e9110(id);
	if (obj == 0) {
		if (count > 0) {
			i = 0;
			while (hits[i].p != 0) {
				fcn_004c5420(*(int*) (hits[i].p + 4), 0x1cc, 4, 0, mask);
				i++;
				if (i >= count) {
					fcn_004ad4d0(-1);
					return;
				}
			}
		}
	} else {
		best = 0;
		bv = -1.0f;
		for (i = 0; i < count; i++) {
			hits[i].f = fcn_004ad500((unsigned char*) hits[i].p,
			    (unsigned short*) obj, id, 1);
		}
		for (i = 0; i < count; i++) {
			if (hits[i].f > bv) {
				bv = hits[i].f;
				best = hits[i].p;
			}
		}
		if (best != 0) {
			fcn_004e8240((unsigned char) info[0], best, 0, 1, 0xff);
			if (best[2] == 6 || best[2] == 7 || best[2] == 5) {
				v = *(int*) (best + 4);
				msg.type = 0xa5;
				msg.id = v;
				msg.unk_c = -1;
				msg.year = g_7f4c00;
				msg.month = g_7f4c04;
				msg.day = g_7f4c08;
				msg.hour = g_7f4c0c;
				msg.flag = 1;
				msg.unk_68 = v;
				msg.unk_6c = id;
				fcn_004c5530((char*) &msg);
				for (rec = g_7f4ca0; (int) rec < 0x85a0a0; rec += 0x21c) {
					if (*(unsigned short*) rec != 0xffff && rec != best &&
					    (rec[2] == 6 || rec[2] == 7)) {
						v = *(int*) (rec + 4);
						msg.unk_68 = v;
						fcn_004c5530((char*) &msg);
					}
				}
			}
		}
	}
	fcn_004ad4d0(-1);
}
