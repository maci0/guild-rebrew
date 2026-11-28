


// SIZE 0x10
struct job {
	int house;
	int item;
	unsigned char f8;
	unsigned char flags;
	char pada[6];
};

#include "Develop/client_types.h"
extern pos14_7f4c00 gm_GameTime;

int __cdecl cm_GetCommandStatus(int);
void __cdecl gm_AddTime(pos14_7f4c00*, int, int, int);
int __cdecl he_ReturnPoliticianFromJob(struct job*);
void __cdecl gm_SimulatePoliticians(struct job*);
int __cdecl he_TryDispatchNpcAction(struct job*, int, int);
int __cdecl cm_SendSetHE(int, char*);
void __cdecl he_FreeAction(char*);

void __cdecl he_RunPoliticians(char* u)
{
	int n;
	int i;

	if (*(int*) (u + 0x70) != -1 && *(int*) (u + 0x70) != -2) {
		if (u[0x78] & 4) {
			return;
		}
		if (*(int*) (u + 0x84) != -1 && cm_GetCommandStatus(*(int*) (u + 0x84)) == 0) {
			return;
		}
		*(pos14_7f4c00*) (u + 0x52) = gm_GameTime;
		gm_AddTime((pos14_7f4c00*) (u + 0x52), 0, 5, 0);
		n = 0;
		*(int*) (u + 0x84) = -1;
		if (*(unsigned short*) (u + 0x56) >= 0x11) {
			for (i = 0; i < 10; i++) {
				if (he_ReturnPoliticianFromJob(&((struct job*) (u + 0xac))[i]) == 2) {
					n++;
				}
			}
			if (n == 0) {
				*(unsigned short*) (u + 0x56) = (unsigned short) n;
				(*(int*) (u + 0x52))++;
			}
			cm_SendSetHE(0, u);
			return;
		}
		for (i = 0; i < 10; i++) {
			if (((struct job*) (u + 0xac))[i].flags & 4) {
				he_ReturnPoliticianFromJob(&((struct job*) (u + 0xac))[i]);
			} else {
				gm_SimulatePoliticians(&((struct job*) (u + 0xac))[i]);
			}
			if (((struct job*) (u + 0xac))[i].flags & 1) {
				n++;
			}
		}
		for (i = 0; i < 10; i++) {
			*(int*) (u + 0x84) = he_TryDispatchNpcAction(&((struct job*) (u + 0xac))[i], n, 0);
			if (*(int*) (u + 0x84) != -1) {
				*(pos14_7f4c00*) (u + 0x52) = gm_GameTime;
				gm_AddTime((pos14_7f4c00*) (u + 0x52), 0, 1, 0);
				break;
			}
		}
		cm_SendSetHE(0, u);
	} else {
		he_FreeAction(u);
	}
}
