extern int g_6a23b8;
extern int g_6a23bc;
extern char g_6a23c0;
extern char g_6a23b0[];
extern int ls_SaveVersion;
extern char gm_TownTable[];
extern char gm_PlayerCount;
extern char gm_GameTime[];
#include "Develop/DieGildeAddOn/game/game_player.h"
extern unsigned char gm_ActiveTownIndex;
#include "Develop/DieGildeAddOn/game/entity_record.h"
extern char ls_SaveSlotIndex;
extern char gm_DifficultyLevel[];
extern char g_7e2480[];
extern char g_7f3ac4[];
extern unsigned short ls_SavePreviewPixels[];
extern char* d2_VisitedBuilding;
extern char* d2_InteriorBuilding;
extern char* sv_SelectedBuilding;

char* __cdecl m_alloc(int, char*);
void __cdecl m_FreeTracked(void*);
unsigned int __cdecl vfs_fwrite(void*, int, int, void*);
void __cdecl gfx_UnpackPixelRgb(unsigned int, char*, char*, char*);
int __cdecl gm_CalcPersonWealth(unsigned short);
int __cdecl gm_AmountToUnits(int, unsigned char);

/* ADDRESS: GOLDTL 0x0051e490 */
/* ADDRESS: GOLDDE 0x00507760 */
int __cdecl ls_WriteSaveHeader(void* outputStream, int a1)
{
	char hdr[0x10];
	char name[0x20];
	char zq[4];
	char b0;
	char b1;
	char b2;
	char b3;
	unsigned int v11;
	unsigned int pair[2];

	unsigned int v22;
	unsigned int tmp;
	char v14;
	char v15;
	char* buf;
	char* base;
	char* t;
	char* p;
	char* s;
	unsigned int r;
	int i;
	int j;
	int n;

	*(int*) hdr = g_6a23b8;
	*(int*) (hdr + 9) = 0;
	*(short*) (hdr + 0xd) = 0;
	*(int*) (hdr + 4) = g_6a23bc;
	hdr[8] = g_6a23c0;
	hdr[0xf] = 0;
	b0 = b1 = b2 = b3 = 0;
	zq[0] = 0;
	zq[1] = 0;
	zq[2] = 0;
	zq[3] = 0;
	tmp = -1;
	i = 0;
	buf = m_alloc(0xe100, g_6a23b0);
	v11 = 0x1005a;
	ls_SaveVersion = 0x1005a;
	r = vfs_fwrite(&v11, 4, 1, outputStream);
	if (r <= 0) {
		goto fail;
	}
	r = vfs_fwrite(&a1, 1, 1, outputStream);
	if (r <= 0) {
		goto fail;
	}
	base = gm_TownTable + gm_ActiveTownIndex * 0x2f4;
	p = name;
	t = base;
	while ((*p++ = *t++) != 0) {
	}
	pair[0] = *(unsigned int*) (base + 0x40);
	pair[1] = *(unsigned int*) (base + 0x44);
	v14 = *(char*) (base + 0x48);
	v15 = gm_PlayerCount;
	if (vfs_fwrite(name, 0x20, 1, outputStream) <= 0) {
		goto fail;
	}
	if (vfs_fwrite(pair, 8, 1, outputStream) <= 0) {
		goto fail;
	}
	if (vfs_fwrite(&v14, 1, 1, outputStream) <= 0) {
		goto fail;
	}
	if (vfs_fwrite(&v15, 1, 1, outputStream) <= 0) {
		goto fail;
	}
	if (vfs_fwrite(gm_GameTime, 0xe, 1, outputStream) <= 0) {
		goto fail;
	}
	if (gm_LocalPlayerSlot != 0xffff) {
		n = gm_LocalPlayerSlot;
		p = (char*)&((ENTITY_RECORD*)gm_EntitySlotTable)[n];
		if (vfs_fwrite(&((ENTITY_RECORD*)gm_EntitySlotTable)[gm_LocalPlayerSlot].unk_02c[4], 0x10, 1, outputStream) <= 0) {
			goto fail;
		}
		if (vfs_fwrite(&((ENTITY_RECORD*)gm_EntitySlotTable)[gm_LocalPlayerSlot].unk_02c[0x14], 0x10, 1, outputStream) <= 0) {
			goto fail;
		}
		if (vfs_fwrite(&((ENTITY_RECORD*)gm_EntitySlotTable)[gm_LocalPlayerSlot].unk_00c, 1, 1, outputStream) <= 0) {
			goto fail;
		}
		if (vfs_fwrite(&((ENTITY_RECORD*)gm_EntitySlotTable)[gm_LocalPlayerSlot].unk_052[2], 4, 1, outputStream) <= 0) {
			goto fail;
		}
		if (vfs_fwrite(&((ENTITY_RECORD*)gm_EntitySlotTable)[gm_LocalPlayerSlot].unk_164, 1, 1, outputStream) <= 0) {
			goto fail;
		}
		if (vfs_fwrite(&((ENTITY_RECORD*)gm_EntitySlotTable)[gm_LocalPlayerSlot].unk_165[1], 1, 1, outputStream) <= 0) {
			goto fail;
		}
		if (vfs_fwrite(&((ENTITY_RECORD*)gm_EntitySlotTable)[gm_LocalPlayerSlot].unk_00d, 1, 1, outputStream) <= 0) {
			goto fail;
		}
		tmp = gm_AmountToUnits(gm_CalcPersonWealth(gm_LocalPlayerSlot), gm_ActiveTownIndex);
		if (vfs_fwrite(&tmp, 4, 1, outputStream) <= 0) {
			goto fail;
		}
		s = &((ENTITY_RECORD*)gm_EntitySlotTable)[gm_LocalPlayerSlot].gender;
	} else {
		/* Native prologue initializes all four default bytes. */
		if (vfs_fwrite(hdr, 0x10, 1, outputStream) <= 0) {
			return 0;
		}
		if (vfs_fwrite(&b1, 1, 1, outputStream) <= 0) {
			return 0;
		}
		if (vfs_fwrite(&b3, 1, 1, outputStream) <= 0) {
			return 0;
		}
		if (vfs_fwrite(&b0, 1, 1, outputStream) <= 0) {
			return 0;
		}
		if (vfs_fwrite(zq, 4, 1, outputStream) <= 0) {
			return 0;
		}
		s = &b2;
	}
	if (vfs_fwrite(s, 1, 1, outputStream) <= 0) {
fail:
		return 0;
	}
	if (vfs_fwrite(&ls_SaveSlotIndex, 1, 1, outputStream) <= 0) {
		return 0;
	}
	v22 = -1;
	if (d2_VisitedBuilding != 0) {
		v22 = *(unsigned int*) (d2_VisitedBuilding + 1);
	} else if (d2_InteriorBuilding != 0) {
		v22 = *(unsigned int*) (d2_InteriorBuilding + 1);
	}
	vfs_fwrite(&v22, 4, 1, outputStream);
	if (sv_SelectedBuilding != 0) {
		v22 = *(unsigned int*) (sv_SelectedBuilding + 2);
	} else {
		v22 = -1;
	}
	vfs_fwrite(&v22, 4, 1, outputStream);
	for (n = 0; n < 8; n++) {
		vfs_fwrite(g_7f3ac4 + n * 8, 4, 1, outputStream);
	}
	tmp = 0x78;
	do {
		p = buf + i * 3 + 1;
		j = 0xa0;
		do {
			gfx_UnpackPixelRgb((unsigned int) ls_SavePreviewPixels[i], p - 1, p, p + 1);
			i = i + 1;
			p = p + 3;
			j = j - 1;
		} while (j != 0);
		tmp = tmp - 1;
	} while (tmp != 0);
	r = vfs_fwrite(buf, 0xe100, 1, outputStream);
	if (r <= 0) {
		return 0;
	}
	if (buf != 0) {
		m_FreeTracked(buf);
	}
	vfs_fwrite(gm_DifficultyLevel, 4, 1, outputStream);
	vfs_fwrite(g_7e2480, 0x60, 1, outputStream);
	return 1;
}
