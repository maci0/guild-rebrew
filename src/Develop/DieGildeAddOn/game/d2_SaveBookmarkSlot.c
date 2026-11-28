


typedef struct
{
	int x0;
	int x4;
	int x8;
} Tip;
// SIZE 0xc

extern char* d2_VisitedBuilding;
extern unsigned char* d2_InteriorBuilding;
extern char* sv_SelectedBuilding;
extern char* d2_SelectedBuilding;
extern char* gm_MarketEntity;
#include "Develop/client_types.h"
extern Slot_779d00 main_CameraBookmarks[];
extern char s_6a9b3c[];
extern char s_6a9b30[];

char* __cdecl gm_QueryEntities(int, int, int, int, int);
void __cdecl io_FormatTextBuffer(void*, int, ...);
void __cdecl d2_ShowStatusBanner(char*);

/* ADDRESS: GOLDDE 0x00577a50 */
void __cdecl d2_SaveBookmarkSlot(int index)
{
	char buf[0x100];
	char* e;
	char* t;

	t = 0;
	e = d2_VisitedBuilding;
	if (e != 0) {
		if (sv_SelectedBuilding != 0) {
			t = sv_SelectedBuilding;
		}
	} else {
		e = ((char*)d2_InteriorBuilding);
		if (e != 0) {
			t = sv_SelectedBuilding;
			if (t == 0) {
				t = gm_QueryEntities(*(int*) (e + 0x5d), 2, 6, 0, 0xfd);
			}
		} else {
			e = d2_SelectedBuilding;
			if (e == 0) {
				e = gm_MarketEntity;
			}
		}
	}
	if (t != 0) {
		((Tip*)main_CameraBookmarks)[index].x4 = *(int*) (e + 1);
		((Tip*)main_CameraBookmarks)[index].x8 = *(int*) (t + 2);
	} else {
		((Tip*)main_CameraBookmarks)[index].x4 = *(int*) (e + 1);
		((Tip*)main_CameraBookmarks)[index].x8 = -1;
	}
	if (t != 0 && *(unsigned short*) t != 0xfd) {
		io_FormatTextBuffer(buf, (int) s_6a9b30, index + 0x205e, e, *(unsigned short*) t * 2 + 0x9a8);
	} else {
		io_FormatTextBuffer(buf, (int) s_6a9b3c, index + 0x205e, e);
	}
	d2_ShowStatusBanner(buf);
}
