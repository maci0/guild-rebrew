


extern float g_6628a8;

void __cdecl d3_SetSkyLayerScrollSpeed(char* skyCtx, char* output, float value)
{
	if (skyCtx != 0 && output != 0) {
		if (value != g_6628a8) {
			*(float*) (output + 8) = value * -0.000001f;
		} else {
			*(int*) (output + 8) = 0;
		}
	}
}
