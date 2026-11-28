


// SIZE 0xc
#include "Develop/client_types.h"
typedef Slot_779d00 Slot;

extern Slot_779d00 main_CameraBookmarks[];
extern char io_LastKeyScancode;
extern char io_ShiftKeyDown[];
extern char str_empty[];

void __cdecl d2_PruneBookmarkSlots(void);
int __cdecl gm_SearchTable67(int);
char* __cdecl gm_FindRecordById(int);
void __cdecl d2_EnterBuildingObjekt(int, int, char*);

void __cdecl d2_FocusBookmarkSlot(void)
{
	int i;
	int x;
	char* r;

	if (io_LastKeyScancode != 0 && (*(char*)io_ShiftKeyDown) == 0) {
		for (i = 0; i < 11; i++) {
			if ((char) main_CameraBookmarks[i].a == io_LastKeyScancode && (*(char*)io_ShiftKeyDown) == 0) {
				d2_PruneBookmarkSlots();
				if (main_CameraBookmarks[i].b != -1) {
					x = gm_SearchTable67(main_CameraBookmarks[i].b);
					r = gm_FindRecordById(main_CameraBookmarks[i].c);
					if (r != 0) {
						d2_EnterBuildingObjekt(x, *(int*) (r + 2), str_empty);
						return;
					}
					d2_EnterBuildingObjekt(x, -1, str_empty);
					return;
				}
			}
		}
	}
}
