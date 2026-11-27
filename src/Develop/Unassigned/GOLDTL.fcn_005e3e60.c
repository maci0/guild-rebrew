

#include "Develop/DieGildeAddOn/game/game_data.h"

int __cdecl d2_LockSurface(char*);
void __cdecl d2_UnlockSurface(char*);

void __cdecl ls_DrawSavePreview(int x0, int y0, char* surf)
{
	int n;
	int x;
	int y;

	n = 0;
	if (d2_LockSurface(surf) != 0) {
		for (y = 0; y < 120; y++) {
			for (x = 0; x < 160; x++) {
				(*(unsigned short**) (surf + 0x1c))[*(int*) (surf + 0x10) * (y + y0) + x + x0] =
				    ls_SavePreviewPixels[n];
				n++;
			}
		}
		d2_UnlockSurface(surf);
	}
}
