#include "d3_floor.h"

/* Native expects valid coordinates and distinct low-byte region values. */
void __cdecl d3_FillWaterRegion(unsigned char* regionen, int breite,
    int x, int y, int alte_region, int neue_region)
{
    regionen[y * breite + x] = (unsigned char) neue_region;
    if (x + 1 < breite && regionen[y * breite + x + 1] == (unsigned char) alte_region) {
        d3_FillWaterRegion(regionen, breite, x + 1, y, alte_region, neue_region);
    }
    if (x - 1 >= 0 && regionen[y * breite + x - 1] == (unsigned char) alte_region) {
        d3_FillWaterRegion(regionen, breite, x - 1, y, alte_region, neue_region);
    }
    if (y + 1 < breite && regionen[(y + 1) * breite + x] == (unsigned char) alte_region) {
        d3_FillWaterRegion(regionen, breite, x, y + 1, alte_region, neue_region);
    }
    if (y - 1 >= 0 && regionen[(y - 1) * breite + x] == (unsigned char) alte_region) {
        d3_FillWaterRegion(regionen, breite, x, y - 1, alte_region, neue_region);
    }
}
