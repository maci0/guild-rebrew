


extern float flt_0_0;

/* ADDRESS: GOLDDE 0x0044f100 */
void __cdecl d3_SetSkyLayerScrollSpeed(char* skyCtx, char* output, float value)
{
	if (skyCtx != 0 && output != 0) {
		if (value != flt_0_0) {
			*(float*) (output + 8) = value * -0.000001f;
		} else {
			*(int*) (output + 8) = 0;
		}
	}
}
