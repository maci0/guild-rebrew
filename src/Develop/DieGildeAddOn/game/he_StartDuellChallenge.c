#include "Develop/client_types.h"
#pragma pack(push, 1)







// SIZE 0xe
#pragma pack(pop)


extern pos14_7f4c00 gm_GameTime;
extern char g_6a5af4[];
extern char g_6a5ae0[];

char* __cdecl gm_LookupEntityRecordById(int id);
void __cdecl gm_AddTime(pos14_7f4c00* s, int a2, int a3, int a4);
void __cdecl io_FormatTextBuffer(char*, int, ...);
void __cdecl he_PostEntityMessage(int, int, char*, int, int, char*);
void __cdecl gm_TryRecordCrime(int a, int b, int c, int d, int e);
void __cdecl cm_RequestCopyEntityData(int a1, int a2, int a3, int a4);
int __cdecl gs_CollectEvidenceForTarget(int id, int* out, unsigned short k);
void __cdecl gm_GenerateShuffledIndices(int n, int* out);
void __cdecl cm_RequestClearEvidenceLink(int a1, int a2, int a3);
int __cdecl gm_IncrementMissionActionCount(char* a1, int kind);
void __cdecl cm_RequestChangeBits(int a1, int a2, int a3, int a4, int a5);
void __cdecl cm_RequestModifyHealth(int a1, int a2);
int __cdecl cm_SendSetHE(int a1, char* e);

/* ADDRESS: GOLDTL 0x0054ee10 */
/* ADDRESS: GOLDDE 0x005352b0 */
void __cdecl he_StartDuellChallenge(char* t)
{
	int impactValue;
	int pick[16];
	int ids[32];
	char buf[0x100];
	char* firstEntity;
	char* secondEntity;
	int id;
	int n;
	int i;

	*(pos14_7f4c00*) (t + 0x52) = (*(pos14_7f4c00*)&gm_GameTime);
	*(int*) (t + 0x70) = 2;
	if ((t[0x78] & 2) == 0)
		return;
	firstEntity = gm_LookupEntityRecordById(*(int*) (t + 0xac));
	secondEntity = gm_LookupEntityRecordById(*(int*) (t + 0xb0));
	if (firstEntity == 0 || (*(int*) (firstEntity + 0x1c8) & 0x100) || secondEntity == 0 || (*(int*) (secondEntity + 0x1c8) & 0x200)) {
		*(pos14_7f4c00*) (t + 0x52) = (*(pos14_7f4c00*)&gm_GameTime);
		gm_AddTime((pos14_7f4c00*) (t + 0x52), 0, 2, 0);
		*(int*) (t + 0x84) = cm_SendSetHE(-1, t);
		return;
	}
	if (*(int*) (t + 0xb4) != 0) {
		gm_AddTime((pos14_7f4c00*) (t + 0x52), 0x18, 0, 0);
		*(int*) (t + 0x58) = 0;
		if (secondEntity[2] == 6 || secondEntity[2] == 7) {
			io_FormatTextBuffer(buf, 0x1e18, *(unsigned short*) firstEntity);
			he_PostEntityMessage(*(int*) (secondEntity + 4), -1, buf, 0, 0x5fb, g_6a5af4);
		}
		impactValue = -4;
	} else {
		gm_AddTime((pos14_7f4c00*) (t + 0x52), 0x60, 0, 0);
		*(int*) (t + 0x58) = 0;
		impactValue = -2;
		if (secondEntity[2] == 6 || secondEntity[2] == 7) {
			io_FormatTextBuffer(buf, 0x1d5b, *(unsigned short*) firstEntity, *(unsigned short*) firstEntity);
			he_PostEntityMessage(*(int*) (secondEntity + 4), -1, buf, 0, 0x5fb, g_6a5ae0);
		}
		id = -1;
		if (*(char**) (firstEntity + 0x170) != 0)
			id = *(int*) (*(char**) (firstEntity + 0x170) + 1);
		else if (*(char**) (secondEntity + 0x170) != 0)
			id = *(int*) (*(char**) (secondEntity + 0x170) + 1);
		gm_TryRecordCrime(0x16, 1, *(int*) (firstEntity + 4), *(int*) (secondEntity + 4), id);
		cm_RequestCopyEntityData(*(int*) (firstEntity + 4), *(int*) (secondEntity + 4), 0x34, 1);
		n = gs_CollectEvidenceForTarget(*(int*) (secondEntity + 4), ids, *(unsigned short*) firstEntity);
		gm_GenerateShuffledIndices(n < 0x10 ? n : 0x10, pick);
		for (i = 0; i < 3; i++, n--) {
			if (n == 0)
				break;
			cm_RequestClearEvidenceLink(ids[pick[i]], *(int*) (firstEntity + 4), 0);
		}
		if (firstEntity[2] == 6)
			gm_IncrementMissionActionCount(firstEntity, 0xb);
	}
	cm_RequestChangeBits(*(int*) (firstEntity + 4), 0x1c8, 4, 0x100, 0);
	cm_RequestChangeBits(*(int*) (secondEntity + 4), 0x1c8, 4, 0x200, 0);
	cm_RequestModifyHealth(*(int*) (firstEntity + 4), impactValue);
}
