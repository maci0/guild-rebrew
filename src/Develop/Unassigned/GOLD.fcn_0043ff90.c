#include "Develop/Units/m_alloc/m_alloc.h"

void __cdecl d3_ReleaseSceneResourceRef(void*);
void __cdecl d3_ResetFloorTileCache(void);

#define SLOT(p, off) (*(void**) ((char*) (p) + (off)))

/* ADDRESS: GOLD 0x0043ff90 */
void __cdecl d3_DestroyFloor(char* scene)
{
	int i;
	int j;
	char* rec;
	char* row;
	void** q;

	row = scene + 0x30;
	for (i = 0; i < 8; i++) {
		q = (void**) row;
		for (j = 0; j < 3; j++) {
			if (*q != 0) {
				m_FreeTracked(*q);
				*q = 0;
			}
			q += 8;
		}
		row += 4;
	}
	rec = scene + 0x108;
	for (i = 0; i < 8; i++) {
		for (j = 0; j < 8; j++) {
			m_FreeTracked(SLOT(rec, -0x10));
			SLOT(rec, -0x10) = 0;
			m_FreeTracked(SLOT(rec, 0));
			SLOT(rec, 0) = 0;
			m_FreeTracked(SLOT(rec, 8));
			SLOT(rec, 8) = 0;
			m_FreeTracked(SLOT(rec, 0x14));
			SLOT(rec, 0x14) = 0;
			if (*(unsigned char*) (rec + 0x38)) {
				m_FreeTracked(SLOT(rec, 0xc));
				SLOT(rec, 0xc) = 0;
				m_FreeTracked(SLOT(rec, -0xc));
				SLOT(rec, -0xc) = 0;
				m_FreeTracked(SLOT(rec, 4));
				SLOT(rec, 4) = 0;
			}
			rec += 0x64;
		}
	}
	if (SLOT(scene, 0x10) != 0) {
		m_FreeTracked(SLOT(scene, 0x10));
		SLOT(scene, 0x10) = 0;
	}
	if (SLOT(scene, 0x14) != 0) {
		m_FreeTracked(SLOT(scene, 0x14));
		SLOT(scene, 0x14) = 0;
	}
	if (SLOT(scene, 0x18) != 0) {
		m_FreeTracked(SLOT(scene, 0x18));
		SLOT(scene, 0x18) = 0;
	}
	if (SLOT(scene, 0x1c) != 0) {
		m_FreeTracked(SLOT(scene, 0x1c));
		SLOT(scene, 0x1c) = 0;
	}
	if (SLOT(scene, 0x20) != 0) {
		m_FreeTracked(SLOT(scene, 0x20));
		SLOT(scene, 0x20) = 0;
	}
	if (SLOT(scene, 0x19e0) != 0) {
		for (i = 0; i < *(unsigned char*) (scene + 0x1c6d); i++) {
			d3_ReleaseSceneResourceRef(*(void**) ((char*) SLOT(scene, 0x19e0) + i * 0x158));
		}
		m_FreeTracked(SLOT(scene, 0x19e0));
		SLOT(scene, 0x19e0) = 0;
	}
	for (i = 0; i < 3; i++) {
		if (SLOT(scene, 0x24 + i * 4) != 0) {
			m_FreeTracked(SLOT(scene, 0x24 + i * 4));
			SLOT(scene, 0x24 + i * 4) = 0;
		}
	}
	d3_ResetFloorTileCache();
	m_FreeTracked(scene);
}
