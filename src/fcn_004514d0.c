/* fcn_004514d0 — add the fixed offset unless the helper's value is at or below the base. */

float __cdecl fcn_00451380(int, int);

// GLOBAL: GOLDTL 0x6628f8
extern char g_6628f8[];
// GLOBAL: GOLD 0x5eb7d8
extern char g_6628f8[];
// GLOBAL: GOLDTL 0x6628c8
extern char g_6628c8[];
// GLOBAL: GOLD 0x5eb7a8
extern char g_6628c8[];
// FUNCTION: GOLD 0x00453b30
// SIZE: 38
// FUNCTION: GOLDTL 0x4514d0
// SIZE: 38
float __cdecl fcn_004514d0(int a1, int a2)
{
	float value;

	value = fcn_00451380(a1, a2);
	if (value < *(float*) g_6628f8) {
		value = value + *(float*) g_6628c8;
	}
	return value;
}
