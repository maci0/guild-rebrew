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

unsigned char* __cdecl gm_StartFilteredEntitySearch(int, int, int);
unsigned char* __cdecl gm_FindNextFilteredEntity(void);
unsigned char* __cdecl gm_NextEntityQueryMatch(void);
int __cdecl gm_CalculateGebaeudeValue(int, int);
int __cdecl gm_SumTreasury(unsigned short*);
int __cdecl fcn_00502cd0(int, int, ...);
int __cdecl fcn_005085f0(int, unsigned char);
int __cdecl io_FormatTextBuffer(char*, int, ...);
void __cdecl cm_BeginPacketFieldDelta(char*, int);
void __cdecl cm_AppendPacketFieldDelta(unsigned char, unsigned char, int, char*);
void __cdecl cm_AppendCommandSyncField(int, int, int, char*);
void __cdecl cm_RequestMoveCredits(int, int, char, int);
void __cdecl cm_RequestChangeAttribute(void);
int __cdecl cm_SendSetAttribute(void);
void __cdecl cm_RequestChangeBits(int, int, int, int, int);
void __cdecl cm_RequestChangeFloat(int, int, float);
int __cdecl cm_SendCopyEntityData(Packet*);
void __cdecl cm_SendRemoveLinkedObject(int, int, int);
void __cdecl cm_SendSetGebBesitzer(int, int, int);
float __cdecl gm_RandomQuadratic(void);

/* ADDRESS: GOLD 0x00506e70 */
void __cdecl fcn_00506e70(unsigned short* entity, char* outputText, int a2)
{
	char buf[0x800];
	Packet pkt;
	unsigned char ui_pos, ui_b0a, ui_b0b, ui_b34; int ui_f08, ui_f0c, ui_f14, ui_f30;
	unsigned char* list[128];
	unsigned char* stop;
	unsigned char* p;
	unsigned char* prev;
	unsigned char* cur;
	int count;
	int best;
	int score;
	int mask;
	int bit;
	int i;
	int r;
	float h;
	char* sp;
	char* q;

	stop = *(unsigned char**) (entity + 0xb8);
	prev = 0;
	count = 0;
	best = 0;
	sp = (*(char**) 0x6f1bf8);
	p = gm_StartFilteredEntitySearch(1, 3, *entity);
	while (p != 0) {
		mask = 0;
		bit = 0;
		if (*(unsigned char*) (g_entity_type_table + *p * 0x24d) > 0x1f) {
			bit = 1 << (*(unsigned char*) (g_entity_type_table + *p * 0x24d) - 0x20);
		}
		else {
			mask = 1 << *(unsigned char*) (g_entity_type_table + *p * 0x24d);
		}
		cur = 0;
		if (((*(unsigned int*) 0x5eed78) & mask) != 0 || ((*(unsigned int*) 0x5eed7c) & bit) != 0) {
			score = gm_CalculateGebaeudeValue((int) p, (int) (char) p[0x5c]);
			if (score > best) {
				if (prev != 0) {
					list[count++] = prev;
					cur = prev;
				}
				prev = p;
				best = score;
			} else {
				list[count++] = p;
				cur = p;
			}
		}
		else if (p != stop && mask == 4) {
			list[count++] = p;
			cur = p;
		}
		if (cur != 0) {
			cm_SendSetGebBesitzer(*(int*) (cur + 1), *(int*) (sp + 4), *(int*) (sp + 4));
			pkt.type = 0x1b;
			pkt.x8 = *(int*) (*(char**) 0x6f1bf8 + 4);
			pkt.xc = -1;
			pkt.x36 = 2;
			pkt.x58 = *(int*) (cur + 1);
			pkt.x5c = gm_CalculateGebaeudeValue((int) cur, (int) (char) cur[0x5c]);
			cm_SendCopyEntityData(&pkt);
			q = (char*) 0x770b84;
			do {
				if (*(unsigned char**) (q + 0x168) == cur && *(int*) q != *(int*) (entity + 2)) {
					memset(&pkt, 0, sizeof(pkt));
					pkt.type = 0x31;
					pkt.x8 = *(int*) (*(char**) 0x6f1bf8 + 4);
					pkt.xc = *(int*) (cur + 1);
					pkt.name = *(Name14*) 0x770ae0;
					pkt.x36 = 1;
					pkt.x58 = *(int*) q;
					cm_SendCopyEntityData(&pkt);
				}
				q += 0x21c;
			} while ((int) q < 0x7d5f84);
		}
		p = gm_FindNextFilteredEntity();
	}
	r = gm_SumTreasury(entity);
	cm_RequestMoveCredits(*(int*) (sp + 4), -1, (*(unsigned char*) 0x6f1bc5), r);
	p = (unsigned char*) fcn_00502cd0(*(int*) (entity + 0xbc), 1, 5);
	while (p != 0) {
		cm_SendRemoveLinkedObject(*(int*) (entity + 2), -1, *(int*) (p + 2));
		p = gm_NextEntityQueryMatch();
	}
	cm_RequestMoveCredits(*(int*) (entity + 2), -1, (*(unsigned char*) 0x6f1bc5), fcn_005085f0(0x5dc, (*(unsigned char*) 0x6f1bc5)));
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
		cm_BeginPacketFieldDelta((char*) entity, *(int*) (entity + 2));
		cm_AppendPacketFieldDelta(1, 1, ((int) entity - *(int*) 0xa68d2c) + 8, (char*) &ui_pos);
		cm_AppendPacketFieldDelta(2, 1, ((int) entity - *(int*) 0xa68d2c) + 10, (char*) &ui_f08);
		cm_AppendPacketFieldDelta(4, 1, ((int) entity - *(int*) 0xa68d2c) + 0x194, (char*) &ui_f14);
		cm_AppendPacketFieldDelta(4, 1, ((int) entity - *(int*) 0xa68d2c) + 0x198, (char*) &ui_f30);
		cm_AppendPacketFieldDelta(4, 1, ((int) entity - *(int*) 0xa68d2c) + 0x19c, (char*) &ui_f30);
		cm_AppendPacketFieldDelta(4, 1, ((int) entity - *(int*) 0xa68d2c) + 0x1a0, (char*) &ui_f30);
		cm_AppendPacketFieldDelta(4, 1, ((int) entity - *(int*) 0xa68d2c) + 0x1a4, (char*) &ui_f30);
		cm_AppendPacketFieldDelta(4, 1, ((int) entity - *(int*) 0xa68d2c) + 0x1a8, (char*) &ui_f30);
		cm_AppendPacketFieldDelta(1, 1, ((int) entity - *(int*) 0xa68d2c) + 0x1b0, (char*) &ui_b0b);
		cm_AppendPacketFieldDelta(1, 1, ((int) entity - *(int*) 0xa68d2c) + 0x1b1, (char*) &ui_b0a);
		cm_RequestChangeBits(*(int*) (entity + 2), 0x1c8, 4, 0x800000, 0);
		cm_RequestChangeAttribute();
		cm_BeginPacketFieldDelta((char*) entity, *(int*) (entity + 2));
		for (i = 0; i < 8; i++) {
			cm_AppendPacketFieldDelta(4, 1, (i * 4 + 0x5c - *(int*) 0xa68d2c) + (int) entity, (char*) &ui_f0c);
		}
		cm_AppendPacketFieldDelta(4, 1, ((int) entity - *(int*) 0xa68d2c) + 0x24, (char*) &ui_f30);
		ui_f0c = 0;
		cm_AppendPacketFieldDelta(4, 1, ((int) entity - *(int*) 0xa68d2c) + 0x2c, (char*) &ui_f0c);
		cm_AppendPacketFieldDelta(2, 1, ((int) entity - *(int*) 0xa68d2c) + 0x28, (char*) &ui_f30);
		cm_RequestChangeAttribute();
		cm_RequestChangeFloat(*(int*) (entity + 2), 0x7c, -*(float*) (entity + 0x3e));
		h = gm_RandomQuadratic();
		cm_RequestChangeFloat(*(int*) (entity + 2), 0x14, (float) h * 7.0f + 30.0f - *(float*) (entity + 10));
		cm_RequestChangeFloat(*(int*) (entity + 2), 0x1c, 1000.0f - *(float*) (entity + 0xe));
		cm_RequestChangeFloat(*(int*) (entity + 2), 0x18, 1000.0f - *(float*) (entity + 0xc));
		cm_RequestChangeFloat(*(int*) (entity + 2), 0x20, 12.0f - *(float*) (entity + 0x10));
		cm_BeginPacketFieldDelta((char*) entity, *(int*) (entity + 2));
		for (i = 0; i < 5; i++) {
			ui_b34 = 0;
			cm_AppendCommandSyncField(1, 1, (i - (*(int*) 0xa68d2c)) + 0x80 + (int) entity, (char*) &ui_b34);
		}
		r = cm_SendSetAttribute();
	}
	io_FormatTextBuffer(outputText, 0x1c4f, *entity, fcn_005085f0(0x5dc, (*(unsigned char*) 0x6f1bc5)));
	if (prev != 0) {
		io_FormatTextBuffer(buf, 0x61ac78, prev);
		strcat(outputText, buf);
	}
	if (stop != 0) {
		io_FormatTextBuffer(buf, 0x61ac78, stop);
		strcat(outputText, buf);
	}
	if (count == 0) {
		return;
	}
	io_FormatTextBuffer(buf, 0x1c50);
	strcat(outputText, buf);
	if (count <= 0) {
		return;
	}
	i = 0;
	do {
		if (i >= 6)
			break;
		io_FormatTextBuffer(buf, 0x61ac78, list[i]);
		strcat(outputText, buf);
		i++;
	} while (i < count);
	if (count <= i) {
		return;
	}
	io_FormatTextBuffer(buf, 0xb6, count - i);
	strcat(outputText, buf);
}
