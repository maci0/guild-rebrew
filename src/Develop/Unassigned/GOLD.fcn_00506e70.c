#include <string.h>

typedef struct
{
	char b[14];
} Name14;
/* SIZE 0xe */

typedef struct
{
	int x0;
	unsigned char type;
	char pad5[3];
	int x8;
	int xc;
	char pad10[0x18];
	Name14 name;
	unsigned char x36;
	char pad37[0x21];
	int x58;
	int x5c;
	int x60;
	char pad64[0x94];
} Packet;
/* SIZE 0xf8 */






















extern char* g_entity_type_table;
extern char g_770b80[];

unsigned char* __cdecl gm_StartFilteredEntitySearch(int, int, int);
unsigned char* __cdecl gm_FindNextFilteredEntity(void);
unsigned char* __cdecl gm_NextEntityQueryMatch(void);
int __cdecl fcn_00509b40(int, int);
int __cdecl gm_SumTreasury(unsigned short*);
int __cdecl fcn_00502cd0(int, int, ...);
int __cdecl fcn_005085f0(int, unsigned char);
int __cdecl io_FormatTextBuffer(char*, int, ...);
void __cdecl fcn_004c4510(char*, int);
void __cdecl fcn_004c4570(unsigned char, unsigned char, unsigned short, char*);
void __cdecl fcn_004c4700(int, int, int, char*);
void __cdecl fcn_004c5150(int, int, char, int);
void __cdecl fcn_004c5360(void);
int __cdecl fcn_004c53a0(void);
void __cdecl fcn_004c5420(int, int, int, int, int);
void __cdecl fcn_004c5480(int, int, float);
int __cdecl fcn_004c5530(Packet*);
void __cdecl fcn_004c5a60(int, int, int);
void __cdecl fcn_004c5f60(int, int, int);
float __cdecl gm_RandomQuadratic(void);

/* ADDRESS: GOLD 0x00506e70 */
void __cdecl fcn_00506e70(unsigned short* a0, char* a1, int a2)
{
	char buf[0x800];
	Packet pkt;
	unsigned char ui_pos, ui_b0a, ui_b0b, ui_b34; int ui_f08, ui_f0c, ui_f14, ui_f18, ui_f1c, ui_f20, ui_f24, ui_f28, ui_f2c, ui_f30;
	unsigned char* list[128];
	unsigned char* stop;
	unsigned char* p;
	unsigned char* prev;
	unsigned char* cur;
	int n;
	int count;
	int best;
	int score;
	int mask; unsigned char building_type;
	int bit;
	int i;
	int send;
	int r;
	float h;
	char* sp;
	char* q;

	stop = *(unsigned char**) (a0 + 0xb8);
	prev = 0;
	n = 0;
	count = 0;
	best = 0;
	sp = (*(char**) 0x6f1bf8);
	p = gm_StartFilteredEntitySearch(1, 3, *a0);
	while (p != 0) {
		mask = 0;
		bit = 0;
		building_type = *(unsigned char*) (g_entity_type_table + *p * 0x24d);
		if (building_type > 0x1f) {
			bit = 1u << ((building_type - 0x20) & 31);
		}
		else {
			mask = 1u << (building_type & 31);
		}
		send = 0;
		cur = 0;
		if (((*(unsigned int*) 0x5eed78) & mask) != 0 || ((*(unsigned int*) 0x5eed7c) & bit) != 0) {
			score = fcn_00509b40((int) p, (int) (char) p[0x5c]);
			if (score > best) {
				if (prev != 0) {
					list[n] = prev;
					n++;
					cur = prev;
					count = n;
				}
				best = score;
				prev = p;
				send = 1;
			} else {
				list[n++] = p;
				cur = p;
				count = n;
				send = 1;
			}
		}
		else if (p != stop && mask == 4) {
			list[n] = p;
			n++;
			cur = p;
			count = n;
			send = 1;
		}
		if (send && cur != 0) {
			fcn_004c5f60(*(int*) (cur + 1), *(int*) (sp + 4), *(int*) (sp + 4));
			pkt.x58 = *(int*) (cur + 1);
			pkt.type = 0x1b;
			pkt.x8 = *(int*) (*(char**) 0x6f1bf8 + 4);
			pkt.xc = -1;
			pkt.x36 = 2;
			pkt.x5c = fcn_00509b40((int) cur, (int) (char) cur[0x5c]);
			fcn_004c5530(&pkt);
			q = (char*) (g_770b80 + 4);
			do {
				if (*(unsigned char**) (q + 0x168) == cur && *(int*) q != *(int*) (a0 + 2)) {
					memset(&pkt, 0, sizeof(pkt));
					pkt.type = 0x31;
					pkt.x8 = *(int*) (*(char**) 0x6f1bf8 + 4);
					pkt.xc = *(int*) (cur + 1);
					pkt.name = *(Name14*) 0x770ae0;
					pkt.x36 = 1;
					pkt.x58 = *(int*) q;
					fcn_004c5530(&pkt);
				}
				q += 0x21c;
			} while ((int) q < 0x7d5f84);
			n = count;
		}
		p = gm_FindNextFilteredEntity();
	}
	r = gm_SumTreasury(a0);
	fcn_004c5150(*(int*) (sp + 4), -1, (*(unsigned char*) 0x6f1bc5), r);
	p = (unsigned char*) fcn_00502cd0(*(int*) (a0 + 0xbc), 1, 5);
	while (p != 0) {
		fcn_004c5a60(*(int*) (a0 + 2), -1, *(int*) (p + 2));
		p = gm_NextEntityQueryMatch();
	}
	fcn_004c5150(*(int*) (a0 + 2), -1, (*(unsigned char*) 0x6f1bc5), fcn_005085f0(0x5dc, (*(unsigned char*) 0x6f1bc5)));
	if (a2 != 0) {
		i = 100;
		ui_f08 = 0x10;
		ui_f14 = 3;
		ui_f30 = 0;
		ui_f20 = 0;
		ui_f2c = 0;
		ui_f28 = 0;
		ui_f18 = 0;
		ui_b0b = 0;
		ui_b0a = 0;
		ui_f0c = -1;
		ui_f1c = 0;
		ui_f24 = 0;
		ui_pos = (unsigned char) i;
		fcn_004c4510((char*) a0, *(int*) (a0 + 2));
		fcn_004c4570(1, 1, (unsigned short) ((int) a0 + (8 - (*(int*) 0xa68d2c))), (char*) &ui_pos);
		fcn_004c4570(2, 1, (unsigned short) ((int) a0 + (10 - (*(int*) 0xa68d2c))), (char*) &ui_f08);
		fcn_004c4570(4, 1, (unsigned short) ((int) a0 + (0x194 - (*(int*) 0xa68d2c))), (char*) &ui_f14);
		fcn_004c4570(4, 1, (unsigned short) ((int) a0 + (0x198 - (*(int*) 0xa68d2c))), (char*) &ui_f30);
		fcn_004c4570(4, 1, (unsigned short) ((int) a0 + (0x19c - (*(int*) 0xa68d2c))), (char*) &ui_f20);
		fcn_004c4570(4, 1, (unsigned short) ((int) a0 + (0x1a0 - (*(int*) 0xa68d2c))), (char*) &ui_f2c);
		fcn_004c4570(4, 1, (unsigned short) ((int) a0 + (0x1a4 - (*(int*) 0xa68d2c))), (char*) &ui_f28);
		fcn_004c4570(4, 1, (unsigned short) ((int) a0 + (0x1a8 - (*(int*) 0xa68d2c))), (char*) &ui_f18);
		fcn_004c4570(1, 1, (unsigned short) ((int) a0 + (0x1b0 - (*(int*) 0xa68d2c))), (char*) &ui_b0b);
		fcn_004c4570(1, 1, (unsigned short) ((int) a0 + (0x1b1 - (*(int*) 0xa68d2c))), (char*) &ui_b0a);
		fcn_004c5420(*(int*) (a0 + 2), 0x1c8, 4, 0x800000, 0);
		fcn_004c5360();
		fcn_004c4510((char*) a0, *(int*) (a0 + 2));
		for (i = 0; i < 8; i++) {
			fcn_004c4570(4, 1, (unsigned short) ((i * 4 + 0x5c - (*(int*) 0xa68d2c)) + (int) a0), (char*) &ui_f0c);
		}
		fcn_004c4570(4, 1, (unsigned short) ((int) a0 + (0x24 - (*(int*) 0xa68d2c))), (char*) &ui_f1c);
		ui_f0c = 0;
		fcn_004c4570(4, 1, (unsigned short) ((int) a0 + (0x2c - (*(int*) 0xa68d2c))), (char*) &ui_f0c);
		fcn_004c4570(2, 1, (unsigned short) ((int) a0 + (0x28 - (*(int*) 0xa68d2c))), (char*) &ui_f24);
		fcn_004c5360();
		fcn_004c5480(*(int*) (a0 + 2), 0x7c, -*(float*) (a0 + 0x3e));
		h = gm_RandomQuadratic();
		fcn_004c5480(*(int*) (a0 + 2), 0x14, (float) h * 7.0f + 30.0f - *(float*) (a0 + 10));
		fcn_004c5480(*(int*) (a0 + 2), 0x1c, 1000.0f - *(float*) (a0 + 0xe));
		fcn_004c5480(*(int*) (a0 + 2), 0x18, 1000.0f - *(float*) (a0 + 0xc));
		fcn_004c5480(*(int*) (a0 + 2), 0x20, 12.0f - *(float*) (a0 + 0x10));
		fcn_004c4510((char*) a0, *(int*) (a0 + 2));
		for (i = 0; i < 5; i++) {
			ui_b34 = 0;
			fcn_004c4700(1, 1, (i - (*(int*) 0xa68d2c)) + 0x80 + (int) a0, (char*) &ui_b34);
		}
		r = fcn_004c53a0();
	}
	io_FormatTextBuffer(a1, 0x1c4f, *a0, fcn_005085f0(0x5dc, (*(unsigned char*) 0x6f1bc5)));
	if (prev != 0) {
		io_FormatTextBuffer(buf, (int) "%1G$A", prev);
		strcat(a1, buf);
	}
	if (stop != 0) {
		io_FormatTextBuffer(buf, (int) "%1G$A", stop);
		strcat(a1, buf);
	}
	if (count == 0) {
		return;
	}
	io_FormatTextBuffer(buf, 0x1c50);
	strcat(a1, buf);
	if (count <= 0) {
		return;
	}
	i = 0;
	while (i <= 5) {
		io_FormatTextBuffer(buf, (int) "%1G$A", list[i]);
		strcat(a1, buf);
		i++;
		if (count <= i) {
			return;
		}
	}
	if (count <= i) {
		return;
	}
	io_FormatTextBuffer(buf, 0xb6, count - i);
	strcat(a1, buf);
}
