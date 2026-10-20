#include <string.h>

#include "client_types.h"
#include "client_actions.h"

extern int g_7f4c00;
extern unsigned char g_773d75;
extern int g_aed32c;
extern float g_665ee8;

extern char* __cdecl gm_ResolveParentEntity(void* record);
extern int __cdecl gm_RandomMod(int range);
extern void __cdecl fcn_00500bb0(void* clock, int arg2, int arg3, int arg4);
extern float __cdecl fcn_0050b980(int id, int pct);
extern void __cdecl fcn_004c5150(int a1, int a2, char a3, int a4);
extern void __cdecl fcn_004c5530(int block);
extern void* __cdecl fcn_004be320(int a, int b);
extern void* __cdecl gm_SearchTable67(int value);
extern int __cdecl fcn_004be340(int a);
extern void __cdecl fcn_004c4510(void* record, unsigned int value);
extern void __cdecl fcn_004c4700(int a, int b, int offset, void* value);
extern unsigned int __cdecl fcn_004c53a0(void);
extern void* __cdecl fcn_0050d570(void* record);
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
	unsigned char p88[0x1a];
	unsigned char fa2;
	unsigned char p_a3[0x55];
} TIME_JOB;
#pragma pack(pop)

/* ADDRESS: GOLDTL 0x005705a0 */
void __cdecl fcn_005705a0(int a0, char* rec)
{
	TIME_JOB job;
	char* entity;
	char* entry;
	char* found;
	int steps[7];
	int age;
	int next;
	int threshold;
	int value;
	unsigned char previous;

	if (*(int*) (rec + 0x24) != 0)
		return;
	entity = gm_ResolveParentEntity(rec);
	age = (unsigned char) rec[0x12];
	if ((unsigned int) age < (gm_RandomMod(0x20) & 0xffff) + 0x28) {
		memset(&job, 0, sizeof(job));
		job.f08 = *(unsigned int*) (entity + 4);
		job.f0c = *(unsigned int*) (entity + 4);
		job.a28 = g_7f4c00;
		job.b2c = g_7f4c04;
		job.c30 = g_7f4c08;
		job.d34 = g_7f4c0c;
		job.f04 = 0x10;
		job.e36 = 1;
		fcn_00500bb0(&job.a28, 0, 0, 10);
		job.f58 = *(unsigned int*) (rec + 2);
		job.f5c = 100 - age;
		job.f64 = 5;
		job.f84 = 0;
		value = (int) (fcn_0050b980(*(unsigned short*) rec, 100) * g_665ee8
			* (float) (100 - age));
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
			steps[1] = 0x0c;
			steps[2] = 8;
			steps[3] = 4;
			steps[4] = 2;
			steps[5] = 0;
			next = steps[(unsigned char) rec[0x31] + 1];
			rec[0x32] = (char) (previous + 1);
			if ((unsigned int) (unsigned char) (previous + 1) < (unsigned int) next)
				return;
			rec[0x32] = 0;
		}
		if (fcn_00529710(rec, entry) != 0
			&& (fcn_00505340(entry) == 0
				|| *(int*) (rec + 6) == *(int*) ((char*) *(void**) 0x7749f0 + 1))) {
			next = fcn_004be340(*(unsigned int*) (rec + 0x29));
			steps[0] = *(int*) (rec + 0x2d) + 1;
			if (next <= steps[0])
				steps[0] = 0;
			fcn_004c4510(rec, *(unsigned int*) (rec + 2));
			fcn_004c4700(4, 1, (int) (rec + 0x2d) - g_aed32c, steps);
			*(unsigned int*) (a0 + 0x84) = fcn_004c53a0();
			return;
		}
		found = (char*) fcn_0050d570(rec);
		if (found != 0) {
			memset(&job, 0, sizeof(job));
			job.f08 = *(unsigned int*) (entity + 4);
			job.f04 = 0x0f;
			job.f0c = -1;
			job.a28 = g_7f4c00;
			job.b2c = g_7f4c04;
			job.c30 = g_7f4c08;
			job.d34 = g_7f4c0c;
			job.e36 = 2;
			job.f58 = *(unsigned int*) (rec + 2);
			job.f5c = *(unsigned int*) (found + 1);
			job.f60 = *(unsigned int*) (entry + 1);
			job.fa2 = 1;
			fcn_004c5530((int) &job);
		}
	}
}
