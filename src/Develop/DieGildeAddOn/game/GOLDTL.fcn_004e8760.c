


typedef struct {
	unsigned char c0;
	char pad1[3];
	int id;
	unsigned char kind;
	char pad9[7];
	unsigned char f10;
	char pad11[3];
	int f14;
} rec18;
// SIZE 0x18

#include "Develop/DieGildeAddOn/game/aemter.h"
int __cdecl cm_SendSwapOfficeOccupants(char*);

int __cdecl amt_SendSameOfficeCommand(char* x, unsigned char* firstEntity, unsigned char* secondEntity)
{
	char message[0xc];
	rec18 a1;
	rec18 b1;
	rec18 a2;
	rec18 b2;

	if (x == 0 || firstEntity == 0 || secondEntity == 0)
		return -1;
	if (srv_GetEntityOfficeSlot(firstEntity, &a1, &a2) == 0)
		return -1;
	if (srv_GetEntityOfficeSlot(secondEntity, &b1, &b2) == 0)
		return -1;
	if (a1.kind != b1.kind || a1.id != b1.id)
		return -1;
	*(int*) message = *(int*) (x + 4);
	message[4] = a2.c0;
	message[5] = b2.c0;
	*(int*) (message + 6) = 6;
	return cm_SendSwapOfficeOccupants(message);
}
