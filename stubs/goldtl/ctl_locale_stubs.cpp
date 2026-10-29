/* Displaces the two CTLFWR32 globals the reference's C++ code defined. Both the
 * retail and debug CTL archives reference them (library inspect --refs) but no
 * member defines them, so Util.Obj cannot link when the d3dx8 effect members
 * come in. A C++ translation unit is required because the references carry C++
 * mangled names; the values are not recovered yet. */

unsigned long g_lcidLocale = 0;
extern const short g_fSatelliteLocalization = 0;
