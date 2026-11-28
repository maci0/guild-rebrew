#include "Develop/DieGildeAddOn/game/client_actions.h"

/* SIZE 0x10, matches the job record used by callers in this subsystem. */
struct job {
	int house;
	int item;
	unsigned char f8;
	unsigned char flags;
	char pada[6];
};

/* lpGebaeudePROT row (0x24d bytes); only the leading type byte is read here. */
typedef struct {
	unsigned char type;
	char pad1[0x24c];
} GebProt_559aa0;

extern int g_7e4538;
extern int g_7e453c;
extern float g_6628cc;
extern unsigned char* lpGebaeudePROT;
extern unsigned char* lpGebaeudeINST;

extern void* __cdecl gm_LookupEntityRecordById(int id);
extern int __cdecl gm_RandomMod(unsigned short range);
extern double __cdecl gm_RandomFloat01(void);
extern void __cdecl gm_ResolveEntityById(void** out, int a, int b, int item);
extern int __cdecl gm_IsEntityAtBuilding(void* entity, void* record);
extern int __cdecl cm_RequestChangeBits(unsigned int handle, int a, int b, int c, int d);
extern void __cdecl cm_RequestCancelEntityEvent(unsigned int handle);
extern void __cdecl cm_SendCancelCharacterActions(unsigned int handle);
extern void __cdecl ch_StartMovement(int house, int item, int a, int b, int c, char* name);
extern void* __cdecl gm_StartFilteredEntitySearch(int a, int b, int c);
extern void* __cdecl gm_FindNextFilteredEntity(void);
extern int __cdecl he_PickNearestWirtshaus(char* entity, int count, void** list, int* out, int* flag);
extern void __cdecl gm_SearchTable67(int value);
extern void __cdecl ch_PlayRandomGesture(char* entity);

/* ADDRESS: GOLDTL 0x00559aa0 */
void __cdecl gm_SimulatePoliticians(struct job* job)
{
	char* entity;
	char* record;
	char* candidate;
	char* list[32];
	int divisor;
	int found;
	int count;
	int value;
	unsigned char type;
	unsigned int bit_lo;
	unsigned int bit_hi;

	record = 0;
	entity = (char*) gm_LookupEntityRecordById(job->house);
	if (entity == 0) {
		job->house = -1;
		job->item = -1;
		job->f8 = 0;
		job->flags = 0;
		job->pada[0] = 0;
		job->pada[1] = 0;
		job->pada[2] = (char) 0xff;
		return;
	}
	gm_ResolveEntityById((void**) &record, 0, 0, job->item);
	found = 0;
	if (record != 0) {
		divisor = (gm_RandomMod(6) & 0xffff) + 2 + (g_7e453c != 0)
			+ (g_7e4538 != 0 ? 2 : 0);
		if (gm_IsEntityAtBuilding(entity, record) == 0)
			return;
		candidate = *(char**) (entity + 0x184);
		if (candidate != 0 && *(int*) (candidate + 0x2c) != -1
			&& *(int*) (candidate + 0x30) != -1) {
			found = 1;
			job->flags |= 0x40;
			if (job->pada[2] == 0xff) { /* never true (signed char vs 0xff), as in the original; do not "fix" */
				job->pada[2] = (char) g_7f4c04;
				cm_RequestChangeBits(*(unsigned int*) (entity + 4), 0x1c8, 4, 0, 0x1000);
				return;
			}
			if ((g_7f4c04 & 0xffff) <= (signed char) job->pada[2] + 1)
				return;
			job->flags &= 0xbf;
			cm_RequestChangeBits(*(unsigned int*) (entity + 4), 0x1c8, 4, 0x1000, 0);
			cm_RequestCancelEntityEvent(*(unsigned int*) (entity + 4));
			job->pada[2] = (char) 0xff;
		}
		type = job->f8;
		if (10 - (int) type < divisor) {
			job->flags |= 4;
			return;
		}
		if ((job->flags & 0x10) == 0) {
			divisor = divisor / 2 + 1;
			if ((int) (type + 2) % divisor == 0 && found == 0) {
				job->f8 = (unsigned char) (type + 1);
				ch_PlayRandomGesture(entity);
				job->flags |= 0x10;
				return;
			}
		}
	}
	job->flags &= 0xef;
	cm_SendCancelCharacterActions(*(unsigned int*) (entity + 4));
	if (!(gm_RandomFloat01() > g_6628cc)) {
		divisor = (unsigned char) job->pada[0];
		found = 0x100;
		value = ((unsigned char) job->pada[1] + divisor) % 0x100;
		do {
			candidate = (char*) (lpGebaeudeINST + value * 0xa9);
			record = candidate;
			if (*candidate != 0) {
				type = ((GebProt_559aa0*) lpGebaeudePROT)[(unsigned char) *candidate].type;
				bit_lo = 0;
				bit_hi = 0;
				if (type > 0x1f) {
					bit_hi = 1 << ((type - 0x20) & 0x1f);
				} else {
					bit_lo = 1 << (type & 0x1f);
				}
				if (*(int*) (candidate + 0x61) != 0) {
					if ((bit_lo & 0xa7f4c3a0) != 0 || (bit_hi & 1) != 0)
						break;
				}
				candidate = 0;
				record = 0;
			}
			found--;
			value = (divisor + value) % 0x100;
		} while (found != 0);
	} else {
		candidate = (char*) gm_StartFilteredEntitySearch(1, 5, 0x16);
		count = 0;
		if (candidate != 0) {
			do {
				if (count >= 0x20)
					break;
				if (*(unsigned short*) (candidate + 0x27) != 0xffff
					&& *(int*) (candidate + 0x61) != 0) {
					list[count] = candidate;
					count++;
				}
				candidate = (char*) gm_FindNextFilteredEntity();
			} while (candidate != 0);
			if (count != 0
				&& he_PickNearestWirtshaus(entity, count, (void**) list, &divisor, &found) != 0)
				gm_SearchTable67(divisor);
		}
	}
	if (record == 0) {
		job->flags |= 4;
		return;
	}
	job->pada[1] = (char) value;
	job->item = *(int*) (record + 1);
	job->f8 = (unsigned char) (job->f8 + 1);
	type = ((GebProt_559aa0*) lpGebaeudePROT)[(unsigned char) *record].type;
	if (type != 0x16 && type != 7 && type != 0x0f)
		ch_StartMovement(job->house, job->item, -1, 0, 1, (char*) 0x6a6038);
	else
		ch_StartMovement(job->house, job->item, -1, 0, 0, (char*) 0x6a6038);
}
