
// FUNCTION: GOLD 0x50d730
// SIZE: 179
// FUNCTION: GOLDTL 0x510bd0
// SIZE: 179

void __cdecl fcn_00510bd0(char* o)
{
	int i;

	if (*(int*) (o + 0x218) == 6) {
		for (i = 0; i < 7; i++) {
			if (*(float*) (*(char**) (o + 0x1e8) + i * 0x38 + 0x20) == 0.0f) {
				*(float*) (*(char**) (o + 0x1e8) + i * 0x38 + 0x20) =
				    (*(float*) (*(char**) (o + 0x1e8) + i * 0x38 + 0x1c) +
				     *(float*) (*(char**) (o + 0x1e8) + i * 0x38 + 0x18)) *
				    0.05f;
				*(float*) (*(char**) (o + 0x1e8) + i * 0x38 + 0x1c) = *(float*) (*(char**) (o + 0x1e8) + i * 0x38 + 0x1c) * 0.8f;
				*(float*) (*(char**) (o + 0x1e8) + i * 0x38 + 0x24) = *(float*) (*(char**) (o + 0x1e8) + i * 0x38 + 0x24) * 0.5f;
			}
		}
		if (*(float*) (o + 0x64) == 0.0f) {
			*(float*) (o + 0x64) = (*(float*) (o + 0x5c) + *(float*) (o + 0x60)) * 0.05f;
			*(float*) (o + 0x60) = *(float*) (o + 0x60) * 0.8f;
			*(float*) (o + 0x94) = *(float*) (o + 0x94) * 0.5f;
		}
	}
}
