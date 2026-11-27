#include "client_data.h"

char* __cdecl gm_LookupEntityRecordById(int);
int __cdecl gm_AddTime(char*, int, int, int);
int __cdecl cm_SendSetHE(int, char*);
void __cdecl cm_SendLogAction(char*);
void __cdecl cm_SendTraceEnd(char*);
int __cdecl cm_RequestChangeBits(int, int, int, int, int);
void __cdecl cm_RequestCopyEntityData(int, int, int, int);

/* ADDRESS: GOLDTL 0x00556a20 */
void __cdecl he_StartAllocGeliebte(char* action)
{
	char* target;
	char* owner;
	int* clockPtr;

	target = gm_LookupEntityRecordById(*(int*) (action + 0xb0));
	owner = gm_LookupEntityRecordById(*(int*) (action + 0xac));
	if (*(unsigned char*) (action + 0x78) & 4) {
		return;
	}
	clockPtr = (int*) (action + 0x52);
	*(pos14_7f4c00*) clockPtr = gm_GameTime;



	gm_AddTime((char*) clockPtr, 0, 1, 0);
	if (target == 0) {
		*(int*) (action + 0x84) = cm_SendSetHE(-1, action);
		return;
	}
	if (*(int*) (target + 0x1c8) & 0x800000) {
		*(int*) (action + 0x84) = cm_SendSetHE(-1, action);
		return;
	}
	cm_SendLogAction("Alloc_Geliebte");
	cm_RequestChangeBits(*(int*) (target + 4), 0x1c8, 4, 0x800000, 0);
	cm_RequestCopyEntityData(*(int*) (owner + 4),
	    *(int*) (target + 4), 0x32, 1);
	cm_SendTraceEnd("Alloc_Geliebte AI");
	*(int*) (action + 0xb4) = 0;
	*(int*) (action + 0xb8) = 2;
	*(int*) (action + 0xbc) = -1;
	*(int*) (action + 0x84) = cm_SendSetHE(2, action);
}
