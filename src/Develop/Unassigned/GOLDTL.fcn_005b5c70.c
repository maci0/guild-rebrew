


#ifdef REBREW_GOLD
#define d2_DestroyElement d2_DestroyGuiElement
#endif
void __cdecl d2_DestroyElement(int);

void __cdecl d2_ClearGauge(int* gauge)
{
	int i;

	if (gauge[7] != -1) {
		d2_DestroyElement(gauge[7]);
		gauge[7] = -1;
	}
	if (gauge[4] != -1) {
		d2_DestroyElement(gauge[4]);
		gauge[4] = -1;
	}
	for (i = 0; i < 6; i++) {
		if (gauge[10 + i] != -1) {
			d2_DestroyElement(gauge[10 + i]);
			gauge[10 + i] = -1;
		}
		if (gauge[16 + i] != -1) {
			d2_DestroyElement(gauge[16 + i]);
			gauge[16 + i] = -1;
		}
	}
}
