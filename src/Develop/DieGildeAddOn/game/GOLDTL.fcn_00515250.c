


// SIZE 0x21c
typedef struct {
	short slot;
	unsigned char type;
	char pad3[9];
	unsigned char faith;
	char padd[0x21c - 0xd];
} Entity;

// SIZE 0x2f4
typedef struct {
	char name[0x2f4];
} Variant;

extern char g_7f4ca0[];
extern char g_868060[];
extern unsigned char g_7747b0;
extern char* gm_RichterKatholisch;
extern char* gm_RichterEvangelisch;
extern char* g_773db4[];

void __cdecl fcn_004432d0(int, int);
void __cdecl fcn_005016c0(void);
void __cdecl fcn_005016f0(int);
#include "Develop/Units/Error/error_message.h"
void __cdecl fcn_00515010(void);
void __cdecl fcn_00510100(void);

void __cdecl init_LocalData(void)
{
	Entity** p;
	int i;
	int n;

	fcn_004432d0(0, 0);
	if ((g_7747b0 & 0x40) == 0) {
		fcn_005016c0();
		for (i = 0; i < 4; i++) {
			if (((Variant*)g_868060)[i].name[0] == 0) {
				break;
			}
			fcn_005016f0(i);
		}
	}
	n = 2;
	for (i = 1; i < 768; i++) {
		if (n == 0) {
			break;
		}
		if (((Entity*)g_7f4ca0)[i].type == 0xc) {
			if (((Entity*)g_7f4ca0)[i].faith == 0) {
				(*(Entity**)&gm_RichterKatholisch) = &((Entity*)g_7f4ca0)[i];
				n--;
			} else if (((Entity*)g_7f4ca0)[i].faith == 1) {
				(*(Entity**)&gm_RichterEvangelisch) = &((Entity*)g_7f4ca0)[i];
				n--;
			}
		}
	}
	p = ((Entity**)g_773db4);
	for (i = 0; i < 768; i++) {
		if (((Entity*)g_7f4ca0)[i].type == 0xb) {
			*p++ = &((Entity*)g_7f4ca0)[i];
		}
	}
	if ((*(Entity**)&gm_RichterKatholisch) == 0) {
		ReportClientMessage("init_LocalData(): gm_RichterKatholisch==NULL");
	}
	if ((*(Entity**)&gm_RichterEvangelisch) == 0) {
		ReportClientMessage("init_LocalData(): gm_RichterEvangelisch==NULL");
	}
	if ((g_7747b0 & 0x44) == 0) {
		fcn_00515010();
	}
	fcn_00510100();
}
