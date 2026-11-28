#include <string.h>
#include "Develop/client_types.h"

typedef struct Hit4ad6a0 {
	char* p;
	float f;
} Hit4ad6a0;

/* Message record handed to the guild request buffer: the 0xf8-byte guild request
 * record, only the fields written below are evidenced. */
typedef struct Msg4ad6a0 {
	char pad0[4];
	unsigned char type;   /* +0x04 */
	char pad5[3];
	int id;               /* +0x08 */
	int unk_c;            /* +0x0c */
	double unk_10;        /* +0x10 */
	int unk_18;           /* +0x18 */
	int unk_1c;           /* +0x1c */
	int unk_20;           /* +0x20 */
	int unk_24;           /* +0x24 */
	pos14_7f4c00 timestamp; /* +0x28 */
	unsigned char flag;   /* +0x36 */
	char pad37[0x31];     /* +0x37 */
	int unk_68;           /* +0x68 */
	int unk_6c;           /* +0x6c */
	char pad70[0x88];     /* +0x70 */
} Msg4ad6a0;

extern int g_7728d0;
extern int g_664e10[];
extern int g_664e34[];
extern char gm_EntitySlotTable[];
extern int gm_GameTime;
extern int gm_GameTimeHour;
extern int gm_GameTimeSliceDword;
extern short gm_GameTimeTailWord;

int __cdecl amt_FindOfficeSlotByType(int id, int* out);
char* __cdecl amt_GetOfficeOverlord(int kind);
float __cdecl amt_ScoreOfficeCandidate(unsigned char* a1, unsigned short* a2, int a3, int a4);
void __cdecl cm_RequestChangeBits(int a1, int a2, int a3, int a4, int a5);
int __cdecl amt_SendOfficeCommand(unsigned char a1, char* a2, char* a3, int a4, int a5);
void __cdecl cm_SendCopyEntityData(char* msg);
void __cdecl amt_SendSpecialOfficeSlot(int a1);

/* Rates every listed entity against the office record, then hands the highest
 * scoring owner to the office and notifies the other guild masters. */
/* ADDRESS: GOLDTL 0x004ad6a0 */
/* ADDRESS: GOLDDE 0x0049b9e0 */
void __cdecl amt_AssignSpecialOffices(void)
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
	int selectedOwnerId;
	float highestScore;

	if ((unsigned int) g_7728d0 >= 3) {
		return;
	}
	id = g_664e10[g_7728d0];
	mask = g_664e34[g_7728d0];
	if (amt_FindOfficeSlotByType(id, info) == 0) {
		return;
	}
	memset(hits, 0, sizeof(hits));
	count = 0;
	rec = gm_EntitySlotTable;
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
	obj = amt_GetOfficeOverlord(id);
	if (obj == 0) {
		for (i = 0; i < count; i++) {
			if (hits[i].p == 0) {
				goto end;
			}
			cm_RequestChangeBits(*(int*) (hits[i].p + 4), 0x1cc, 4, 0, mask);
		}
		amt_SendSpecialOfficeSlot(-1);
		return;
	}
	best = 0;
	highestScore = -1.0;
	for (i = 0; i < count; i++) {
		hits[i].f = amt_ScoreOfficeCandidate((unsigned char*) hits[i].p,
		    (unsigned short*) obj, id, 1);
	}
	for (i = 0; i < count; i++) {
		if (hits[i].f > highestScore) {
			highestScore = hits[i].f;
			best = hits[i].p;
		}
	}
	if (best != 0) {
		amt_SendOfficeCommand((unsigned char) info[0], best, 0, 1, 0xff);
		if (best[2] == 6 || best[2] == 7 || best[2] == 5) {
			msg.timestamp.a = gm_GameTime;
			msg.timestamp.b = gm_GameTimeHour;
			selectedOwnerId = *(int*) (best + 4);
			msg.timestamp.c = gm_GameTimeSliceDword;
			msg.timestamp.d = gm_GameTimeTailWord;
			msg.type = 0xa5;
			msg.id = selectedOwnerId;
			msg.unk_c = -1;
			msg.flag = 1;
			msg.unk_6c = id;
			msg.unk_68 = selectedOwnerId;
			cm_SendCopyEntityData((char*) &msg);
			for (rec = gm_EntitySlotTable + 2; (int) rec < (int) gm_EntitySlotTable + 0x65402; rec += 0x21c) {
				if (*(unsigned short*) (rec - 2) != 0xffff && rec - 2 != best &&
				    (*rec == 6 || *rec == 7)) {
					msg.id = *(int*) (rec + 2);
					cm_SendCopyEntityData((char*) &msg);
				}
			}
		}
	}
end:
	amt_SendSpecialOfficeSlot(-1);
}
