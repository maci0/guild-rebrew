#include <stddef.h>

/* Inferred private access view. The native allocation continues past laenge.
   Only the pointer at +8 and the count at +0x14 are accessed. */
typedef struct DATEN_LAENGE_VIEW {
    unsigned char unbekannt_0[8];
    unsigned char *daten;
    unsigned char unbekannt_1[8];
    int laenge;
} DATEN_LAENGE_VIEW;

typedef char DATEN_LAENGE_VIEW_DATEN[(offsetof(DATEN_LAENGE_VIEW, daten) == 8) ? 1 : -1];
typedef char DATEN_LAENGE_VIEW_LAENGE[(offsetof(DATEN_LAENGE_VIEW, laenge) == 0x14) ? 1 : -1];

/* ADDRESS: GOLD 0x00461e60 */
void __cdecl fcn_00461e60(DATEN_LAENGE_VIEW *view, unsigned int wert)
{
    view->daten[view->laenge] = (unsigned char)(wert >> 8);
    view->laenge = view->laenge + 1;
    view->daten[view->laenge] = (unsigned char)wert;
    view->laenge = view->laenge + 1;
}
