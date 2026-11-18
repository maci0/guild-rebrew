


extern float g_6628a8;

void __cdecl fcn_00459940(char* a1, char* output, float value)
{
	if (a1 != 0 && output != 0) {
		if (value != g_6628a8) {
			*(float*) (output + 8) = value * -0.000001f;
		} else {
			*(int*) (output + 8) = 0;
		}
	}
}
