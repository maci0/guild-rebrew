

/* Client counterpart of srv_RecvGame: waits until the downloaded savegame
 * (g_fb5740, g_aed328 bytes) is complete, then loads it from memory. */

#include "client_types.h"

// SIZE 0x21c
struct house {
	unsigned short id;
	unsigned char state;
	char pad3[0x219];
};

extern char* g_fb5740;
extern unsigned int g_aed328;
extern unsigned int g_1005820;
extern int g_6a23ac;
extern int g_699364;
extern int g_699368;
extern int g_7749d0;
extern pos14_7f4c00 g_7f4c00;
extern pos14_7f4c00 g_7e1f70;
extern unsigned char g_773d75;
extern char* g_773da8;
extern int g_773d68;
extern int g_773d6c;
extern int g_773d70;
extern int g_773d7c;
extern int g_773d38;
extern int g_100dc00;
extern char g_7f4ca0[];

void __cdecl fcn_005356e0(void);
void __cdecl fcn_00535960(void);
#include "Develop/Units/vfs/vfs.h"
void __cdecl m_FreeTracked(char*);

#include "Develop/DieGildeAddOn/loadsave/loadsave.h"


int __cdecl fcn_00522510(void* stream);


int __cdecl fcn_00524040(void* stream);
int __cdecl fcn_004ec520(void* stream, int version);
#include "client_scene_loader.h"
int __cdecl fcn_00525670(void);

int __cdecl fcn_00525b40(void)
{
	int hdr[0x3f];

	void* f;
	int i;

	while (g_fb5740 == 0 || g_1005820 < g_aed328) {
		fcn_005356e0();
		fcn_00535960();
	}
	f = vfs_OpenStream((unsigned char*) g_fb5740, g_aed328, "rb");
	if (f == 0) {
		m_FreeTracked(g_fb5740);
		g_fb5740 = 0;
		return 0;
	}
	g_773da8 = 0;
	ls_LoadSavegameHeader(f, (char*) hdr);
	if (!(hdr[1] & 2) || hdr[0] > 0x1005a) {
		CloseVfsStream(f);
		m_FreeTracked(g_fb5740);
		g_fb5740 = 0;
		return 0;
	}
	if (ls_ReadVfsDataChecked(&g_699364, 4, 1, f) == 0
	    || ls_ReadVfsDataChecked(&g_7749d0, 4, 1, f) == 0
	    || ls_ReadVfsDataChecked(&g_7f4c00, 0xe, 1, f) == 0
	    || ls_ReadVfsDataChecked(&g_773d75, 1, 1, f) == 0
	    || ls_ReadVfsDataChecked(&g_773da8, 4, 1, f) == 0
	    || ls_ReadVfsDataChecked(&g_773d68, 4, 1, f) == 0
	    || ls_ReadVfsDataChecked(&g_773d6c, 4, 1, f) == 0
	    || ls_ReadVfsDataChecked(&g_773d70, 4, 1, f) == 0) {
		CloseVfsStream(f);
		m_FreeTracked(g_fb5740);
		g_fb5740 = 0;
		return 0;
	}
	g_7e1f70 = g_7f4c00;
	ls_ReadVfsDataChecked(&g_773d7c, 4, 1, f);
	ls_ReadVfsDataChecked(&g_100dc00, 0x18, 1, f);
	if (g_6a23ac >= 0x10030) {
		ls_ReadVfsDataChecked(&g_699368, 4, 1, f);
	}
	if (g_6a23ac >= 0x1003d) {
		ls_ReadVfsDataChecked(&g_773d38, 4, 1, f);
	} else {
		g_773d38 = 1000000;
	}
	if (ls_LoadExistingEntities(f) == 0) {
		CloseVfsStream(f);
		m_FreeTracked(g_fb5740);
		g_fb5740 = 0;
		return 0;
	}
	if (fcn_00522510(f) == 0) {
		CloseVfsStream(f);
		m_FreeTracked(g_fb5740);
		g_fb5740 = 0;
		return 0;
	}
	if (ls_LoadDynamicEntities(f) == 0) {
		CloseVfsStream(f);
		m_FreeTracked(g_fb5740);
		g_fb5740 = 0;
		return 0;
	}
	if (ls_LoadEntities(f) == 0) {
		CloseVfsStream(f);
		m_FreeTracked(g_fb5740);
		g_fb5740 = 0;
		return 0;
	}
	for (i = 0; i < 768; i++) {
		if (((struct house*)g_7f4ca0)[i].id != 0xffff && ((struct house*)g_7f4ca0)[i].state == 6) {
			((struct house*)g_7f4ca0)[i].state = 5;
		}
	}
	if (fcn_00524040(f) == 0) {
		CloseVfsStream(f);
		m_FreeTracked(g_fb5740);
		g_fb5740 = 0;
		return 0;
	}
	if (g_6a23ac >= 0x10045 && fcn_004ec520(f, g_6a23ac) == 0) {
		CloseVfsStream(f);
		m_FreeTracked(g_fb5740);
		g_fb5740 = 0;
		return 0;
	}
	if (!(hdr[1] & 4) && fcn_005222a0(f) == 0) {
		CloseVfsStream(f);
		m_FreeTracked(g_fb5740);
		g_fb5740 = 0;
		return 0;
	}
	if (fcn_00525670() == 0) {
		CloseVfsStream(f);
		m_FreeTracked(g_fb5740);
		g_fb5740 = 0;
		return 0;
	}
	CloseVfsStream(f);
	m_FreeTracked(g_fb5740);
	g_fb5740 = 0;
	return 1;
}
