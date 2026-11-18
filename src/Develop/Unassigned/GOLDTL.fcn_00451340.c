
/* ADDRESS: GOLDTL 0x00451340 */
void __cdecl fcn_00451340(float* start, float* end, float t, float* out)
{
	out[0] = (end[0] - start[0]) * t + start[0];
	out[1] = (end[1] - start[1]) * t + start[1];
	out[2] = (end[2] - start[2]) * t + start[2];
}
