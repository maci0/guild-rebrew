#include <string.h>

extern int gm_GameTime;
extern int gm_GameTimeHour;
extern int gm_GameTimeSliceDword;
extern short gm_GameTimeTailWord;
extern int gm_TargetPersonTypeMask;
extern int g_66601c;

int __cdecl gm_LookupEntityRecordById(unsigned int);
unsigned short __cdecl gm_RandomMod(unsigned short);
void __cdecl cm_SendCopyEntityData(void*);
void __cdecl cm_RequestModifyHealth(int, int);
void __cdecl io_FormatTextBuffer(char*, int);
int __cdecl d2_OpenTargetPicker(void*, char*, int, void*);
int __cdecl d2_ShowDuelChallengeDialog(unsigned char*);
/* Two dialog outcomes: the shop path builds a 0xf8-byte request record from
 * the owner id and four random-range globals; the quest path fills a
 * five-dword descriptor and looks up the record for id 0x1d66. */
/* ADDRESS: GOLDTL 0x005d6030 */
int __cdecl gm_RunDuelChallengeAction(char* actor, char* request)
{
	unsigned char rec[0xf8];
	unsigned int init[20];
	char name[64];
	unsigned short owner;
	int found;
	unsigned short id;
	int ret;

	ret = 2;
	if (*(unsigned char*) (actor + 2) != 6 && *(unsigned char*) (actor + 2) != 7) {
		found = gm_LookupEntityRecordById(*(unsigned int*) (request + 0x214));
		if (found == 0) {
			return 0x60;
		}
		owner = gm_RandomMod(9);
		owner += 0x1d76;
		id = gm_RandomMod(9);
		id += 0x1d6d;
		memset(rec, 0, sizeof(rec));
		*(int*) (rec + 8) = *(int*) (actor + 4);
		*(int*) (rec + 0xc) = *(int*) (actor + 4);
		*(int*) (rec + 0x58) = *(int*) (actor + 4);
		*(int*) (rec + 0x28) = gm_GameTime;
		*(int*) (rec + 0x30) = gm_GameTimeSliceDword;
		*(int*) (rec + 0x2c) = gm_GameTimeHour;
		*(unsigned short*) (rec + 0x60) = id;
		*(char*) (rec + 4) = 0x47;
		*(char*) (rec + 0x36) = 2;
		*(unsigned short*) (rec + 0x34) = gm_GameTimeTailWord;
		*(unsigned short*) (rec + 0x62) = owner;
		*(int*) (rec + 0x5c) = *(int*) (found + 4);
		cm_SendCopyEntityData(rec);
		cm_RequestModifyHealth(*(int*) (actor + 4), -2);
		return 0x10;
	}
	memset(init, 0, sizeof(init));
	init[1] = 0x400;
	init[2] = gm_TargetPersonTypeMask;
	init[3] = g_66601c;
	init[4] = 6;
	io_FormatTextBuffer(name, 0x1d66);
	found = d2_OpenTargetPicker(init, name, 0, (void*) d2_ShowDuelChallengeDialog);
	if (found != 0 && (*(unsigned int*) (found + 0x1c8) & 0x400) != 0) {
		ret = 0x81;
	}
	return ret;
}
