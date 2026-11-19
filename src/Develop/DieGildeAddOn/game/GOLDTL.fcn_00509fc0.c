#include "client_types.h"
void* __cdecl memset(void*, int, unsigned int);
#pragma intrinsic(memset)
char* __cdecl strcat(char*, const char*);





/* SIZE 0xe */

typedef struct
{
	int x0;
	unsigned char type;
	char pad5[3];
	int x8;
	int xc;
	char pad10[0x18];
	pos14_7f4c00 name;
	unsigned char x36;
	char pad37[0x21];
	int x58;
	int x5c;
	int x60;
	char pad64[0x94];
} Packet;
/* SIZE 0xf8 */


extern unsigned char* lpGebaeudePROT;
extern char* gm_CityEntity;
extern unsigned char g_773d75;
extern int g_666028;
extern int g_66602c;
extern int g_aed32c;
extern char g_7f4ca4[];
extern char s_6999a8[];
#include "client_types.h"
extern pos14_7f4c00 gm_GameTime;

unsigned char* __cdecl gm_StartFilteredEntitySearch(int, int, int);
unsigned char* __cdecl gm_FindNextFilteredEntity(void);
unsigned char* __cdecl gm_NextEntityQueryMatch(void);
int __cdecl fcn_0050cf50(int, int);
int __cdecl gm_SumTreasury(unsigned short*);
int __cdecl fcn_00502cd0(int, int, ...);
int __cdecl fcn_0050b710(int, unsigned char);
int __cdecl fcn_0050b750(int, unsigned char);
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

/* ADDRESS: GOLDTL 0x00509fc0 */
void __cdecl fcn_00509fc0(unsigned short* subjectRecord, char* reportText, int a2)
{
	char buf[0x800];
	Packet pkt;
	unsigned char ui_pos, ui_b0a, ui_b0b, ui_b34; int ui_f08, ui_f0c, ui_f14, ui_f30;
	unsigned char* list[128];
	unsigned char* stop;
	unsigned char* p;
	unsigned char* prev;
	unsigned char* cur;
	int n;
	int count;
	int best;
	int score;
	int mask;
	int bit;
	int i;
	int send;
	int r;
	float h;
	char* sp;
	char* q;

	stop = *(unsigned char**) (subjectRecord + 0xb8);
	prev = 0;
	n = 0;
	count = 0;
	best = 0;
	sp = gm_CityEntity;
	p = gm_StartFilteredEntitySearch(1, 3, *subjectRecord);
	while (p != 0) {
		mask = 0;
		bit = 0;

		if (lpGebaeudePROT[*p * 0x24d] > 0x1f) {
			bit = 1 << (lpGebaeudePROT[*p * 0x24d] - 0x20);
		}
		else {
			mask = 1 << lpGebaeudePROT[*p * 0x24d];
		}
		send = 0;
		cur = 0;
		if ((g_666028 & mask) != 0 || (g_66602c & bit) != 0) {
			score = fcn_0050cf50((int) p, (int) (char) p[0x5c]);
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
			pkt.x8 = *(int*) (sp + 4);
			pkt.xc = -1;
			pkt.x36 = 2;
			pkt.x5c = fcn_0050cf50((int) cur, (int) (char) cur[0x5c]);
			fcn_004c5530(&pkt);
			q = (char*) g_7f4ca4;
			do {
				if (*(unsigned char**) (q + 0x168) == cur && *(int*) q != *(int*) (subjectRecord + 2)) {
					memset(&pkt, 0, sizeof(pkt));
					pkt.type = 0x31;
					pkt.x8 = *(int*) (sp + 4);
					pkt.xc = *(int*) (cur + 1);
					pkt.name = *(pos14_7f4c00*) &gm_GameTime;
					pkt.x36 = 1;
					pkt.x58 = *(int*) q;
					fcn_004c5530(&pkt);
				}
				q += 0x21c;
			} while ((int) q < 0x85a0a4);
			n = count;
		}
		p = gm_FindNextFilteredEntity();
	}
	r = gm_SumTreasury(subjectRecord);
	fcn_004c5150(*(int*) (sp + 4), -1, g_773d75, r);
	p = (unsigned char*) fcn_00502cd0(*(int*) (subjectRecord + 0xbc), 1, 5);
	while (p != 0) {
		fcn_004c5a60(*(int*) (subjectRecord + 2), -1, *(int*) (p + 2));
		p = gm_NextEntityQueryMatch();
	}
	fcn_004c5150(*(int*) (subjectRecord + 2), -1, g_773d75, fcn_0050b750(0x5dc, g_773d75));
	if (a2 != 0) {
		i = 100;
		ui_f08 = 0x10;
		ui_f14 = 3;
		ui_f30 = 0;
		ui_f30 = 0;
		ui_f30 = 0;
		ui_f30 = 0;
		ui_f30 = 0;
		ui_b0b = 0;
		ui_b0a = 0;
		ui_f0c = -1;
		ui_f30 = 0;
		ui_f30 = 0;
		ui_pos = (unsigned char) i;
		fcn_004c4510((char*) subjectRecord, *(int*) (subjectRecord + 2));
		fcn_004c4570(1, 1, (unsigned short) ((int) subjectRecord + (8 - g_aed32c)), (char*) &ui_pos);
		fcn_004c4570(2, 1, (unsigned short) ((int) subjectRecord + (10 - g_aed32c)), (char*) &ui_f08);
		fcn_004c4570(4, 1, (unsigned short) ((int) subjectRecord + (0x194 - g_aed32c)), (char*) &ui_f14);
		fcn_004c4570(4, 1, (unsigned short) ((int) subjectRecord + (0x198 - g_aed32c)), (char*) &ui_f30);
		fcn_004c4570(4, 1, (unsigned short) ((int) subjectRecord + (0x19c - g_aed32c)), (char*) &ui_f30);
		fcn_004c4570(4, 1, (unsigned short) ((int) subjectRecord + (0x1a0 - g_aed32c)), (char*) &ui_f30);
		fcn_004c4570(4, 1, (unsigned short) ((int) subjectRecord + (0x1a4 - g_aed32c)), (char*) &ui_f30);
		fcn_004c4570(4, 1, (unsigned short) ((int) subjectRecord + (0x1a8 - g_aed32c)), (char*) &ui_f30);
		fcn_004c4570(1, 1, (unsigned short) ((int) subjectRecord + (0x1b0 - g_aed32c)), (char*) &ui_b0b);
		fcn_004c4570(1, 1, (unsigned short) ((int) subjectRecord + (0x1b1 - g_aed32c)), (char*) &ui_b0a);
		fcn_004c5420(*(int*) (subjectRecord + 2), 0x1c8, 4, 0x800000, 0);
		fcn_004c5360();
		fcn_004c4510((char*) subjectRecord, *(int*) (subjectRecord + 2));
		for (i = 0; i < 8; i++) {
			fcn_004c4570(4, 1, (unsigned short) ((i * 4 + 0x5c - g_aed32c) + (int) subjectRecord), (char*) &ui_f0c);
		}
		fcn_004c4570(4, 1, (unsigned short) ((int) subjectRecord + (0x24 - g_aed32c)), (char*) &ui_f30);
		ui_f0c = 0;
		fcn_004c4570(4, 1, (unsigned short) ((int) subjectRecord + (0x2c - g_aed32c)), (char*) &ui_f0c);
		fcn_004c4570(2, 1, (unsigned short) ((int) subjectRecord + (0x28 - g_aed32c)), (char*) &ui_f30);
		fcn_004c5360();
		fcn_004c5480(*(int*) (subjectRecord + 2), 0x7c, -*(float*) (subjectRecord + 0x3e));
		h = gm_RandomQuadratic();
		fcn_004c5480(*(int*) (subjectRecord + 2), 0x14, (float) h * 7.0f + 30.0f - *(float*) (subjectRecord + 10));
		fcn_004c5480(*(int*) (subjectRecord + 2), 0x1c, 1000.0f - *(float*) (subjectRecord + 0xe));
		fcn_004c5480(*(int*) (subjectRecord + 2), 0x18, 1000.0f - *(float*) (subjectRecord + 0xc));
		fcn_004c5480(*(int*) (subjectRecord + 2), 0x20, 12.0f - *(float*) (subjectRecord + 0x10));
		fcn_004c4510((char*) subjectRecord, *(int*) (subjectRecord + 2));
		for (i = 0; i < 5; i++) {
			ui_b34 = 0;
			fcn_004c4700(1, 1, (i - g_aed32c) + 0x80 + (int) subjectRecord, (char*) &ui_b34);
		}
		r = fcn_004c53a0();
	}
	io_FormatTextBuffer(reportText, 0x1c4f, *subjectRecord, fcn_0050b750(0x5dc, g_773d75));
	if (prev != 0) {
		io_FormatTextBuffer(buf, s_6999a8, prev);
		strcat(reportText, buf);
	}
	if (stop != 0) {
		io_FormatTextBuffer(buf, s_6999a8, stop);
		strcat(reportText, buf);
	}
	if (count == 0) {
		return;
	}
	io_FormatTextBuffer(buf, 0x1c50);
	strcat(reportText, buf);
	if (count <= 0) {
		return;
	}
	i = 0;
	while (i <= 5) {
		io_FormatTextBuffer(buf, s_6999a8, list[i]);
		strcat(reportText, buf);
		i++;
		if (count <= i) {
			return;
		}
	}
	if (count <= i) {
		return;
	}
	io_FormatTextBuffer(buf, 0xb6, count - i);
	strcat(reportText, buf);
}
