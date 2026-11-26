extern char* lpGebaeudePROT;
extern char g_7f4ca0[];
#include "Develop/DieGildeAddOn/game/entity_record.h"
int __cdecl gm_GetBuildingTechEffect(unsigned char* p, int a, int b);
char* __cdecl fcn_0050dc90(int arg1);
char* __cdecl gm_LookupEntityRecordById(int id);
float __cdecl fcn_004ff040(char* e);
float __cdecl fcn_0050fdb0(int k, int n, int* ids);
#include "Develop/DieGildeAddOn/game/building_prototype.h"
/* ADDRESS: GOLDTL 0x00510260 */
float __cdecl fcn_00510260(unsigned char* buildingData, int countArg, int idsAddress)
{
	float a;
	float f;
	float sum;
	float avg;
	float bonus;
	int count;
	int i;
	char* typePrototype;
	char* e;
	char* ent;
	int* arr;

	arr = (int*) idsAddress;
	i = 0;
	avg = 0.0f;
	count = 0;
	sum = 0.0f;
	bonus = 0.0f;
	typePrototype = (char*)&((BUILDING_PROTOTYPE*)lpGebaeudePROT)[(int) *buildingData];
	a = gm_GetBuildingTechEffect(buildingData, 1, 1) * 0.01 + 1.0;
	e = fcn_0050dc90((int) buildingData);
	if (e == 0) {
		e = (char*)&((ENTITY_RECORD*)0x7f4ca0)[(int) *(unsigned short*) (buildingData + 0x27)];
	}
	if (*(unsigned char*) (e + 2) == 6 || *(unsigned char*) (e + 2) == 7) {
		f = (float) (*(unsigned char*) (e + 0x81) * 0.000992063492063492);
	} else {
		f = 0.0f;
	}
	a = a + f;
	if (countArg > 0) {
		do {
			if (arr[i] != -1) {
				ent = gm_LookupEntityRecordById(arr[i]);
				if (ent != 0) {
					sum = (float) (fcn_004ff040(ent) + sum);
					if (*(char*) (typePrototype + 0x22f) == *(char*) (ent + 0x165)) {
						bonus = (float) (bonus + 0.3);
					}
					count++;
				}
			}
			i++;
		} while (i < countArg);
	}
	if (count != 0) {
		avg = sum * (1.0f / count);
		bonus = (1.0f / count) * bonus;
	}
	f = (float) (fcn_0050fdb0(*(unsigned short*) (buildingData + 0x27), countArg, idsAddress) - 0.5);
	f = (float) (f * 0.25);
	if (*(unsigned short*) (buildingData + 0x5a) & 0x1000) {
		a = a + 0.1f;
	}
	f = (float) (f + a + (*(int*) (buildingData + 0x41) - 2) * 0.1);
	return (bonus + avg) * f;
}
