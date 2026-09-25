float __cdecl fcn_0050f980(int, int, int);
int __cdecl fcn_004e99c0(int);
int __cdecl fcn_004e6f10(int);
float __cdecl fcn_004ec340(unsigned char*, int);

// FUNCTION: GOLD 0x4ad3e0
// SIZE: 298
// FUNCTION: GOLDTL 0x4ad500
// SIZE: 298

float __cdecl fcn_004ad500(unsigned char* a1, unsigned short* a2, int a3, int a4)
{
	float d;
	float w;
	float r1;
	float r2;
	float s1;
	float s2;

	d = fcn_0050f980(*(unsigned short*) a1, *a2, 1) * 0.01f;
	if (a4 != 0)
		d = d + d;
	w = (a1[0xd] + 1) * 0.1f;
	w = w + w;
	r1 = (float) fcn_004e99c0(a1[0x166]) / fcn_004e99c0(0x1b);
	r2 = (float) fcn_004e99c0(a1[0x167]) / fcn_004e99c0(0x1b);
	s1 = 0.0f;
	if (a1[0x166] != 0)
		s1 = fcn_004ec340(a1, fcn_004e6f10(a1[0x166]));
	s2 = 0.0f;
	if (a1[0x167] != 0)
		s2 = fcn_004ec340(a1, fcn_004e6f10(a1[0x167]));
	return s1 * r1 + s2 * r2 + w + d;
}
