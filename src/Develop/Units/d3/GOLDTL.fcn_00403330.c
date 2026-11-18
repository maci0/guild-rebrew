#include "Develop/Units/d3/d3_object.h"
#include "Develop/DieGildeAddOn/game/ch_motion.h"




extern void* ch_CharacterSlots[];
#include "Develop/DieGildeAddOn/game/game_data.h"
extern int ch_LowPolyMode;
int __cdecl fcn_00413190(int p);
void __cdecl fcn_004432d0(int a, int b);
void __cdecl d3_RemoveObjectAnim(int h);

void __cdecl fcn_00403870(char* e);

void __cdecl fcn_00403330(unsigned char mode)
{
	int saved;
	char** p;
	char* e;

	saved = d3_CurrentContextIndex;
	p = ((char**)ch_CharacterSlots);
	do {
		e = *p;
		if (e != 0) {
			fcn_004432d0(fcn_00413190(*(int*) (e + 0x88)), 1);
			if (mode == 2) {
				if (*(int*) (e + 0x22c) != 0) {
					d3_RemoveObjectAnim(*(int*) (e + 0x22c));
					d3_DestroyObject((D3_OBJECT*) (*(int*) (e + 0x22c)));
					*(int*) (e + 0x22c) = 0;
				}
			} else if ((mode == 0 || mode == 1) && *(int*) (e + 0x22c) == 0) {
				fcn_00403870(e);
				ch_Updatelowpoly(e);
			}
		}
		p++;
	} while ((int) p < (int) (((char**)ch_CharacterSlots) + 0x300));
	ch_LowPolyMode = 2 - mode;
	fcn_004432d0(saved, 1);
}
