


#include "Develop/client_types.h"
#pragma pack(push, 1)
typedef Rec2d_9a3800 Rec2d;
// SIZE 0x2d
#pragma pack(pop)

typedef struct
{
	int a;
	int b;
} Pair;
// SIZE 0x8

extern int cm_LastCrimeId;
extern Rec2d_9a3800 cm_CrimeRecords[512];
extern Pair_99f800 cm_CrimeEvidenceLinks[0x800];

void __cdecl cm_InitCrimeRecords(void)
{
	int i;

	cm_LastCrimeId = 0;
	for (i = 0; i < 512; i++) {
		cm_CrimeRecords[i].x16 = -1;
		cm_CrimeRecords[i].x12 = -1;
		cm_CrimeRecords[i].id = -1;
		cm_CrimeRecords[i].x25 = 0;
	}
	for (i = 0; i < 0x800; i++) {
		((Pair*)cm_CrimeEvidenceLinks)[i].a = -1;
		((Pair*)cm_CrimeEvidenceLinks)[i].b = -1;
	}
}
