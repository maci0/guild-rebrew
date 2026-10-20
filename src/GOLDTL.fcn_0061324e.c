/* Reads the Direct3D "DisableMMX" DWORD and caches the resulting state in
 * 0x006ad808 (-1 unknown, 0 MMX usable, 1 MMX disabled).  The registry result
 * decides first; the driver probe 0x00613229 is only asked while the state is
 * still unknown. */
#include <windows.h>
#include <mmintrin.h>

extern int __cdecl fcn_00613229(void);

#pragma optimize("y", off)

/* ADDRESS: GOLDTL 0x0061324e */
int __cdecl fcn_0061324e(void)
{
    HKEY hkey;
    DWORD size;
    DWORD type;
    DWORD data;
    int zero;

    zero = 0;
    if (RegOpenKeyA(HKEY_LOCAL_MACHINE, "Software\\Microsoft\\Direct3D",
                    &hkey) == 0) {
        size = 4;
        if (RegQueryValueExA(hkey, "DisableMMX", zero, &type, (LPBYTE)&data,
                             &size) == 0
            && type == REG_DWORD && data != zero) {
            RegCloseKey(hkey);
            *(int *)0x006ad808 = zero;
            return zero;
        }
        RegCloseKey(hkey);
    }
    if (*(int *)0x006ad808 < zero) {
        *(int *)0x006ad808 = zero;
        if (fcn_00613229() != zero) {
            _mm_empty();
            *(int *)0x006ad808 = 1;
        }
    }
    return *(int *)0x006ad808;
}
