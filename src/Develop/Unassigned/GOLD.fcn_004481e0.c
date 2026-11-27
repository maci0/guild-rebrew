#include "client_scene_resources.h"

/* ADDRESS: GOLD 0x004481e0 */
void __cdecl d3_ReleaseSceneResource(SCENE_RESOURCE* resource)
{
	if (resource != 0) {
		fcn_0045fbb0(resource);
	}
}
