/* fcn_004514d0 — add the fixed offset unless the helper's value is at or below the base. */

float __cdecl fcn_00451380(int, int);

/* ADDRESS: GOLDTL 0x006628f8 */
extern char g_6628f8[];
/* ADDRESS: GOLD 0x005eb7d8 */
extern char g_6628f8[];
/* ADDRESS: GOLDTL 0x006628c8 */
extern char g_6628c8[];
/* ADDRESS: GOLD 0x005eb7a8 */
extern char g_6628c8[];
/* ADDRESS: GOLD 0x00453b30 */
/* ADDRESS: GOLDTL 0x004514d0 */
float __cdecl fcn_004514d0(int a1, int a2)
{
	float value;

	value = fcn_00451380(a1, a2);
	if (value < *(float*) g_6628f8) {
		value = value + *(float*) g_6628c8;
	}
	return value;
}
