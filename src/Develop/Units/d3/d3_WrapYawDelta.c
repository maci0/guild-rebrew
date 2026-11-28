/* fcn_004514d0 — add the fixed offset unless the helper's value is at or below the base. */

float __cdecl d3_SignedPlanarAngle(int, int);

extern char d3_NegPi[];
extern char d3_NegPi[];
extern char d3_TwoPi[];
extern char d3_TwoPi[];
/* ADDRESS: GOLD 0x00453b30 */
/* ADDRESS: GOLDTL 0x004514d0 */
float __cdecl d3_WrapYawDelta(int left, int right)
{
	float value;

	value = d3_SignedPlanarAngle(left, right);
	if (value < *(float*) d3_NegPi) {
		value = value + *(float*) d3_TwoPi;
	}
	return value;
}
