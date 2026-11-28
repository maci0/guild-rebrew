#include "Develop/Units/d3/client_scene_resources.h"

#include "Develop/DieGildeAddOn/game/game_data.h"
void __cdecl d3_UnlinkEffect(char*);
void __cdecl m_FreeTracked(void*);

/* ADDRESS: GOLD 0x00455750 */
void __cdecl d3_DestroyEffect(char* object)
{
	char* owner;

	owner = *(char**) (object + 0x2f0);
	if (owner == g_5fb5b0) {
		*(char**) (*(char**) (object + 0x314) + 0x318) = *(char**) (object + 0x318);
		*(char**) (*(char**) (object + 0x318) + 0x314) = *(char**) (object + 0x314);
		if (object == *(char**) (owner + 0xa4))
			*(char**) (owner + 0xa4) = *(char**) (object + 0x314);
		if (object == *(char**) (owner + 0xa8))
			*(char**) (owner + 0xa8) = *(char**) (object + 0x314);
	} else {
		d3_UnlinkEffect(object);
	}
	if (*(SCENE_RESOURCE**) (object + 0xd4) != 0)
		d3_ReleaseSceneResourceRef(*(SCENE_RESOURCE**) (object + 0xd4));
	m_FreeTracked(*(void**) (object + 0x28));
	*(void**) (object + 0x28) = 0;
	m_FreeTracked(*(void**) (object + 0xdc));
	*(void**) (object + 0xdc) = 0;
	m_FreeTracked(*(void**) (object + 0xe0));
	*(void**) (object + 0xe0) = 0;
	m_FreeTracked(object);
}
