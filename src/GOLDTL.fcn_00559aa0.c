#include "client_actions.h"

/* SIZE 0x10, matches the job record used by callers in this subsystem. */
struct job {
	int house;
	int item;
	unsigned char f8;
	unsigned char flags;
	char pada[6];
};

extern int g_7e4538;
extern int g_7e453c;
extern float g_6628cc;
extern unsigned char* g_868050;
extern unsigned char* g_90e094;

extern void* __cdecl fcn_00508e40(int id);
extern int __cdecl gm_RandomMod(int range);
extern float __cdecl gm_RandomFloat01(void);
extern void __cdecl gm_ResolveEntityById(void** out, int a, int b, int item);
extern int __cdecl fcn_00529670(void* entity, void* record);
extern int __cdecl fcn_004c5420(unsigned int handle, int a, int b, int c, int d);
extern void __cdecl fcn_004c6650(unsigned int handle);
extern void __cdecl fcn_004c5c80(unsigned int handle);
extern void __cdecl fcn_004c5da0(int house, int item, int a, int b, int c, char* name);
extern void* __cdecl gm_StartFilteredEntitySearch(int a, int b, int c);
extern void* __cdecl gm_FindNextFilteredEntity(void);
extern int __cdecl fcn_00567410(char* entity, int count, void** list, int* out, int* flag);
extern void __cdecl gm_SearchTable67(int value);
extern void __cdecl fcn_005599c0(char* entity);

/* ADDRESS: GOLDTL 0x00559aa0 */
void __cdecl fcn_00559aa0(struct job* job)
{
	char* entity;
	char* record;
	char* candidate;
	char* list[32];
	int guard;
	int state;
	int divisor;
	int found;
	int count;
	int i;
	int value;
	unsigned char type;
	signed char slot_byte;
	unsigned int bit_lo;
	unsigned int bit_hi;

	record = 0;
	guard = 0;
	count = 0;
	entity = (char*) fcn_00508e40(job->house);
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
		if (fcn_00529670(entity, record) == 0)
			return;
		candidate = *(char**) (entity + 0x184);
		if (candidate != 0 && *(int*) (candidate + 0x2c) != -1
			&& *(int*) (candidate + 0x30) != -1) {
			found = 1;
			job->flags |= 0x40;
			if ((signed char) job->pada[2] == -1) {
				job->pada[2] = (char) g_7f4c04;
				fcn_004c5420(*(unsigned int*) (entity + 4), 0x1c8, 4, 0, 0x1000);
				return;
			}
			if ((g_7f4c04 & 0xffff) <= (signed char) job->pada[2] + 1)
				return;
			job->flags &= 0xbf;
			fcn_004c5420(*(unsigned int*) (entity + 4), 0x1c8, 4, 0x1000, 0);
			fcn_004c6650(*(unsigned int*) (entity + 4));
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
				fcn_005599c0(entity);
				job->flags |= 0x10;
				return;
			}
		}
	}
	job->flags &= 0xef;
	fcn_004c5c80(*(unsigned int*) (entity + 4));
	if (gm_RandomFloat01() <= g_6628cc) {
		state = (unsigned char) job->pada[0];
		guard = 0x100;
		value = (int) (signed char) ((unsigned char) job->pada[1] + state);
		do {
			candidate = (char*) (g_90e094 + value * 0xa9);
			record = candidate;
			if (*candidate != 0) {
				type = g_868050[(unsigned char) *candidate * 0x24d];
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
			guard--;
			value = (int) (signed char) (state + value);
		} while (guard != 0);
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
				&& fcn_00567410(entity, count, (void**) list, &divisor, &found) != 0)
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
	type = g_868050[(unsigned char) *record * 0x24d];
	if (type != 0x16 && type != 7 && type != 0x0f)
		fcn_004c5da0(job->house, job->item, -1, 0, 1, (char*) 0x6a6038);
	else
		fcn_004c5da0(job->house, job->item, -1, 0, 0, (char*) 0x6a6038);
}
