

extern int g_6b7fac;

void __cdecl fcn_00435710(char* o, float a, float b, unsigned int t0, unsigned int t1)
{
	unsigned int now = (*(unsigned int*)&g_6b7fac);
	float f;

	if (o == 0 || *(int*) (o + 0x68) == 0 || t0 > t1) {
		return;
	}
	*(float*) (o + 0x44) = a;
	*(float*) (o + 0x48) = b;
	*(unsigned int*) (o + 0x34) = t0;
	*(unsigned int*) (o + 0x38) = t1;
	if (now < t1) {
		if (now < t0) {
			f = 0.0f;
		} else {
			f = (float) (now - t0) / (t1 - t0);
		}
		*(float*) (o + 0x40) = (b - a) * f + a;
	} else {
		*(float*) (o + 0x40) = b;
	}
}
