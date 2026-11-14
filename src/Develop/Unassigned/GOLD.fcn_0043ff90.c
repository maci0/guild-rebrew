#include "Develop/Units/m_alloc/m_alloc.h"

void __cdecl fcn_0045fbb0(void*);
void __cdecl fcn_0043f990(void);

#define SLOT(p, off) (*(void**) ((char*) (p) + (off)))

/* ADDRESS: GOLD 0x0043ff90 */
void __cdecl fcn_0043ff90(char* scene)
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
	rec = scene + 0xf8;
	for (i = 0; i < 8; i++) {
		for (j = 0; j < 8; j++) {
			m_FreeTracked(SLOT(rec, 0));
			SLOT(rec, 0) = 0;
			m_FreeTracked(SLOT(rec, 0x10));
			SLOT(rec, 0x10) = 0;
			m_FreeTracked(SLOT(rec, 0x18));
			SLOT(rec, 0x18) = 0;
			m_FreeTracked(SLOT(rec, 0x24));
			SLOT(rec, 0x24) = 0;
			if (*(unsigned char*) (rec + 0x48)) {
				m_FreeTracked(SLOT(rec, 0x1c));
				SLOT(rec, 0x1c) = 0;
				m_FreeTracked(SLOT(rec, 4));
				SLOT(rec, 4) = 0;
				m_FreeTracked(SLOT(rec, 0x14));
				SLOT(rec, 0x14) = 0;
			}
			rec += 0x64;
		}
	}
	for (i = 0x10; i <= 0x20; i += 4) {
		if (SLOT(scene, i) != 0) {
			m_FreeTracked(SLOT(scene, i));
			SLOT(scene, i) = 0;
		}
	}
	if (SLOT(scene, 0x19e0) != 0) {
		for (i = 0; i < *(unsigned char*) (scene + 0x1c6d); i++) {
			fcn_0045fbb0(*(void**) ((char*) SLOT(scene, 0x19e0) + i * 0x158));
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
	fcn_0043f990();
	m_FreeTracked(scene);
}
