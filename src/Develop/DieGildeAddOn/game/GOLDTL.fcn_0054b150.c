#include "client_types.h"
#include "client_actions.h"

#pragma pack(push, 1)
typedef struct {
	int x00;
	unsigned short x04;
	int x06;
	int x0a;
} SIM_CLOCK;
#pragma pack(pop)

extern pos14_7f4c00 gm_GameTime;

char* __cdecl gm_LookupEntityRecordById(int a1);
int __cdecl cm_SendSetHE(char a1, unsigned char* e);
void __cdecl gm_AddTime(SIM_CLOCK* clock, int arg2, int arg3, int arg4);
void __cdecl cm_RequestCopyEntityData(int a1, int a2, int a3, int a4);
int __cdecl io_FormatTextBuffer(char* dst, int id, ...);
int __cdecl he_PostEntityMessage(int id, int arg, char* text1, unsigned char flags, int value, char* text2);
void __cdecl gm_TryRecordCrime(int a, int b, int c, int d, int e);

/* ADDRESS: GOLDTL 0x0054b150 */
void __cdecl fcn_0054b150(char* entity)
{
	char buf[0x200];
	char* firstEntity;
	char* secondEntity;
	char* p;
	int v4;

	firstEntity = gm_LookupEntityRecordById(*(int*) (entity + 0xac));
	secondEntity = gm_LookupEntityRecordById(*(int*) (entity + 0xb0));
	*(int*) (entity + 0x84) = -1;
	if ((entity[0x78] & 2) == 0) {
		return;
	}
	if (firstEntity == 0 || secondEntity == 0) {
		*(pos14_7f4c00*) (entity + 0x52) = gm_GameTime;
		cm_SendSetHE(-1, (unsigned char*) entity);
	}
	*(pos14_7f4c00*) (entity + 0x52) = gm_GameTime;
	gm_AddTime((SIM_CLOCK*) (entity + 0x52), 0x30, 0, 0);
	cm_SendSetHE(0, (unsigned char*) entity);
	cm_RequestCopyEntityData(*(int*) (secondEntity + 4), *(int*) (firstEntity + 4), -0x14, 1);
	if (firstEntity[2] == 6 || firstEntity[2] == 7) {
		io_FormatTextBuffer(buf, 0x175a, *(unsigned short*) secondEntity, *(unsigned short*) secondEntity);
		he_PostEntityMessage(*(int*) (firstEntity + 4), -1, buf, 0, 0x5fb, (char*) 0x6b5c60);
	}
	v4 = -1;
	p = *(char**) (secondEntity + 0x170);
	if (p != 0) {
		v4 = *(int*) (p + 1);
	}
	else {
		p = *(char**) (firstEntity + 0x170);
		if (p != 0) {
			v4 = *(int*) (p + 1);
		}
	}
	gm_TryRecordCrime(0x13, 1, *(int*) (entity + 0xb0), *(int*) (entity + 0xac), v4);
}
