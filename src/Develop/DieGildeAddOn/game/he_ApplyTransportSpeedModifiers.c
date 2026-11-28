extern int d3_SnowEffect;
extern int d3_RainEffect;


/* ADDRESS: GOLD 0x00555510 */
/* ADDRESS: GOLDTL 0x0055d6e0 */
void __cdecl he_ApplyTransportSpeedModifiers(char* a, char* b)
{
	char* d;

	d = *(char**) (b + 0x3b);
	if (((int*)d3_SnowEffect) != 0 && *((int*)d3_SnowEffect) > 0x64) {
		*(float*) (d + 0x1a0) = (float)(*(float*) (a + 0xc0) * 0.7);
	} else if (((int*)d3_RainEffect) != 0 && *((int*)d3_RainEffect) > 0xc8) {
		*(float*) (d + 0x1a0) = (float)(*(float*) (a + 0xc0) * 0.8);
	} else {
		*(float*) (d + 0x1a0) = *(float*) (a + 0xc0);
	}
	if (a[0xf1] == 2) {
		*(float*) (d + 0x1a0) = (float)(*(float*) (d + 0x1a0) * 0.8);
	}
}
