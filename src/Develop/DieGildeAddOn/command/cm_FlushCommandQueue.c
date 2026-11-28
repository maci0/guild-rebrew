


#pragma pack(1)
typedef struct node99 {
	char f0;
	char f1;
	char f2;
	char f3;
	int f4;
	int f8;
	int fc;
	unsigned short f10;
	char data[0x7f];
	struct node99* prev;
	struct node99* next;
} node99;
// SIZE 0x99
#pragma pack()

#include "Develop/DieGildeAddOn/game/game_data.h"
extern unsigned char* g_14cbca8;

int __cdecl cm_EnqueueCommand(node99*);
void __cdecl nt_FlushSend(void);

int __cdecl cm_FlushCommandQueue(void)
{
	if ((*(node99**)&g_1005760) == 0)
		return 0;
	if (nt_ClientSocket == -1) {
		while (1) {
			if (cm_EnqueueCommand((*(node99**)&g_1005760)) != 0)
				break;
			(*(node99**)&g_1005760) = (*(node99**)&g_1005760)->next;
			if ((*(node99**)&g_1005760) == 0)
				return 0;
			(*(node99**)&g_1005760)->prev = 0;
		}
		return 1;
	}
	do {
		if ((*(node99**)&g_14cbca8) != 0) {
			nt_FlushSend();
			if ((*(node99**)&g_14cbca8) != 0)
				return 0;
		}
		(*(node99**)&g_14cbca8) = (*(node99**)&g_1005760);
		(*(node99**)&g_1005760) = (*(node99**)&g_1005760)->next;
		if ((*(node99**)&g_1005760) != 0)
			(*(node99**)&g_1005760)->prev = 0;
		nt_FlushSend();
	} while ((*(node99**)&g_1005760) != 0);
	return 0;
}
