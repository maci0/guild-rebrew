


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

extern Rec2d_9a3800 cm_CrimeRecords[512];
extern Pair_99f800 cm_CrimeEvidenceLinks[0x800];

int __cdecl cm_UpdateStraftatState(int a, int b, unsigned int st, int flag)
{
	int cnt;
	int i;
	int j;
	int id;

	cnt = 0;
	if (flag) {
		for (i = 0; i < 0x800; i++) {
			if (((Pair*)cm_CrimeEvidenceLinks)[i].a == a) {
				id = ((Pair*)cm_CrimeEvidenceLinks)[i].b;
				for (j = 0; j < 512; j++) {
					if (cm_CrimeRecords[j].id == id) {
						if (cm_CrimeRecords[j].x25 == 1 && cm_CrimeRecords[j].x16 == b) {
							cm_CrimeRecords[j].x25 = st;
							cnt++;
						}
						break;
					}
				}
			}
		}
		return cnt;
	}
	for (j = 0; j < 512; j++) {
		if (cm_CrimeRecords[j].x25 == st) {
			cm_CrimeRecords[j].x25 = 1;
			cnt++;
		}
	}
	return cnt;
}
