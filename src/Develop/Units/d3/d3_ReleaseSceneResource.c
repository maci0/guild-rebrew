#include "Develop/Units/d3/client_scene_resources.h"

/* ADDRESS: GOLD 0x004481e0 */
void __cdecl d3_ReleaseSceneResource(SCENE_RESOURCE* resource)
{
	if (resource != 0) {
		d3_ReleaseSceneResourceRef(resource);
	}
}
