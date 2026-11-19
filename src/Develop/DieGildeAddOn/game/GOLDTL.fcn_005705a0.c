#include <string.h>

#include "client_types.h"
#include "client_actions.h"

extern int gm_GameTime;
extern unsigned char g_773d75;
extern int g_aed32c;
extern float g_665ee8;

extern char* __cdecl gm_ResolveParentEntity(void* record);
extern int __cdecl gm_RandomMod(int range);
extern void __cdecl fcn_00500bb0(void* clock, int arg2, int arg3, int arg4);
extern float __cdecl eval_ObjektPreis2Credits(int id, int pct);
extern void __cdecl fcn_004c5150(int a1, int a2, char a3, int a4);
extern void __cdecl fcn_004c5530(int block);
extern void* __cdecl fcn_004be320(int a, int b);
extern void* __cdecl gm_SearchTable67(int value);
extern int __cdecl fcn_004be340(int a);
extern void __cdecl fcn_004c4510(void* record, unsigned int value);
extern void __cdecl fcn_004c4700(int a, int b, int offset, void* value);
extern unsigned int __cdecl fcn_004c53a0(void);
extern void* __cdecl gm_EntityAccumulate(void* record);
extern int __cdecl fcn_00529710(void* record, void* entry);
extern int __cdecl fcn_00505340(void* entry);

#pragma pack(push, 1)
typedef struct {
	unsigned char p00[4];
	unsigned char f04;
	unsigned char p05[3];
	int f08;
	int f0c;
	unsigned char p10[0x18];
	int a28;
	int b2c;
	int c30;
	unsigned short d34;
	unsigned char e36;
	unsigned char p37[0x21];
	int f58;
	int f5c;
	int f60;
	int f64;
	unsigned char p68[0x1c];
	int f84;
	unsigned char p88[0x16];
	unsigned char f9e;
	unsigned char p_9f[0x59];
} TIME_JOB;
#pragma pack(pop)

extern char g_774964;
extern void* g_7749f0;
extern int __cdecl fcn_004c4450(int);
extern void __cdecl fcn_00546190(char*);
extern void* __cdecl gm_StartFilteredEntitySearch(int, ...);
extern unsigned short* __cdecl gm_NextEntityQueryMatch(void);
extern char* __cdecl fcn_00502cd0(int, int, int, int, int);
void __cdecl fcn_005705a0(int a0, char* rec);

/* Timed action 0xA6 (route supervisor) FINISH: once the linked record is gone or the
 * phase is 0, walks every matching cart and hands it to fcn_005705a0, then reschedules. */
/* ADDRESS: GOLDTL 0x00570870 */
void __cdecl fcn_00570870(char* h)
{
	char* e;
	int phase;

	if (!g_774964)
		return;
	if (*(int*) (h + 0x84) != -1 && !fcn_004c4450(*(int*) (h + 0x84)))
		return;
	phase = *(int*) (h + 0x70);
	*(int*) (h + 0x84) = -1;
	if (phase >= -2) {
		if (phase >= 0) {
			if (phase == 0) {
				g_7749f0 = gm_StartFilteredEntitySearch(1, 0, 0x44);
				e = fcn_00502cd0(0, 2, 7, 4, 0x1d);
				if (e) {
					do {
						if (*(int*) (e + 0x29) && !(e[0x20] & 1) && !(e[0x13] & 0x20) && e[0x33])
							fcn_005705a0((int) h, e);
						e = (char*) gm_NextEntityQueryMatch();
					} while (e);
				}
				*(pos14_7f4c00*) (h + 0x52) = *(pos14_7f4c00*) &gm_GameTime;
				fcn_00500bb0(h + 0x52, 0, 0xf, 0);
			}
		} else {
			fcn_00546190(h);
		}
	}
}

/* ADDRESS: GOLDTL 0x005705a0 */
void __cdecl fcn_005705a0(int a0, char* rec)
{
	TIME_JOB job;
	char* entity;
	char* entry;
	char* found;
	int steps[5];
	int age;
	int next;
	int threshold;
	int value;
	unsigned char previous;
	float price;

	if (*(int*) (rec + 0x24) != 0)
		return;
	entity = gm_ResolveParentEntity(rec);
	threshold = (gm_RandomMod(0x20) & 0xffff) + 0x28;
	age = (unsigned char) rec[0x12];
	if (age < threshold) {
		unsigned int eid;
		memset(&job, 0, sizeof(job));
		eid = *(unsigned int*) (entity + 4);
		job.f08 = eid;
		job.f0c = eid;
		job.a28 = gm_GameTime;
		job.b2c = g_7f4c04;
		job.f04 = 0x10;
		job.e36 = 1;
		job.c30 = g_7f4c08;
		job.d34 = g_7f4c0c;
		fcn_00500bb0(&job.a28, 0, 0, 10);
		job.f58 = *(unsigned int*) (rec + 2);
		job.f64 = 5;
		job.f84 = 0;
		job.f5c = 100 - (unsigned char) rec[0x12];
		price = eval_ObjektPreis2Credits(*(unsigned short*) rec, 100) * g_665ee8;
		value = (int) (price * (float) (100 - (unsigned char) rec[0x12]));
		fcn_004c5150(-1, *(unsigned int*) (entity + 4), (char) g_773d75, value);
		fcn_004c5530((int) &job);
		return;
	}
	entry = (char*) fcn_004be320(*(unsigned int*) (rec + 0x29),
		*(unsigned int*) (rec + 0x2d));
	if (entry != 0)
		entry = (char*) gm_SearchTable67(*(unsigned int*) (entry + 4));
	if (entry != 0) {
		if (*(int*) (rec + 0x2d) == 0) {
			previous = (unsigned char) rec[0x32];
			steps[0] = 0x0c;
			steps[1] = 8;
			steps[2] = 4;
			steps[3] = 2;
			steps[4] = 0;
			next = steps[(unsigned char) rec[0x31]];
			rec[0x32] = (char) (previous + 1);
			if ((int) (unsigned char) (previous + 1) < next)
				return;
			rec[0x32] = 0;
		}
		if (fcn_00529710(rec, entry) != 0
			&& (fcn_00505340(entry) == 0
				|| *(int*) (rec + 6) == *(int*) ((char*) *(void**) 0x7749f0 + 1))) {
			int next_idx;
			next = fcn_004be340(*(unsigned int*) (rec + 0x29));
			next_idx = *(int*) (rec + 0x2d) + 1;
			if (next_idx >= next)
				next_idx = 0;
			fcn_004c4510(rec, *(unsigned int*) (rec + 2));
			fcn_004c4700(4, 1, (int) (rec + 0x2d) - g_aed32c, &next_idx);
			*(unsigned int*) (a0 + 0x84) = fcn_004c53a0();
			return;
		}
		found = (char*) gm_EntityAccumulate(rec);
		if (found != 0) {
			memset(&job, 0, sizeof(job));
			job.f9e = 1;
			job.f08 = *(unsigned int*) (entity + 4);
			job.f04 = 0x0f;
			job.f0c = -1;
			job.a28 = gm_GameTime;
			job.b2c = g_7f4c04;
			job.c30 = g_7f4c08;
			job.d34 = g_7f4c0c;
			job.e36 = 2;
			job.f58 = *(unsigned int*) (rec + 2);
			job.f5c = *(unsigned int*) (found + 1);
			job.f60 = *(unsigned int*) (entry + 1);
			fcn_004c5530((int) &job);
		}
	}
}
