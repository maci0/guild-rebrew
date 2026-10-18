#ifndef D2_GUI_H
#define D2_GUI_H

typedef struct D2_BILD_GROESSE {
    char pad00[0x50];
    short breite;
    short hoehe;
} D2_BILD_GROESSE;

#ifdef REBREW_GOLD
#include "../../../gold_gui.h"
typedef GuiEnt D2_GUI_ITEM;
extern GuiEnt* g_00f8f080;
extern short g_00fb9070;
extern short g_00fb9072;
#else
typedef struct D2_GUI_ITEM {
    int id;
    char pad04[4];
    int f08;
    char* data;
    int x;
    int y;
    int w;
    int f16;
    int kind;
    char pad24[4];
    int f1e;
    int f20;
    int f22;
    int f24;
    char pad38[0x88 - 0x38];
    int bild_offset;
    char pad8c[0x2f4 - 0x8c];
} D2_GUI_ITEM;
extern char* g_1015ea0;
extern int g_1040490;
extern int g_1040494;
#endif

extern char* g_772500;
extern int g_772568;

/* Inferred argument-slot view; complete backing allocation and owner unknown. */
/* ADDRESS: GOLD 0x00fa6038 */
/* ADDRESS: GOLDTL 0x0102d158 */
extern char d2_BildArgument2[];

void* __cdecl fcn_00466190(int bild);
void __cdecl fcn_00469960(int bild);
void __cdecl fcn_00469900(int bild);
void __cdecl d2_SetElementImage(int element, int bild);

#endif
