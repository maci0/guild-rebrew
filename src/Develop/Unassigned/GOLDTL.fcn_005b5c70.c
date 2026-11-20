


#ifdef REBREW_GOLD
#define d2_DestroyElement fcn_0046e700
#endif
void __cdecl d2_DestroyElement(int);

void __cdecl fcn_005b5c70(int* o)
{
	int i;

	if (o[7] != -1) {
		d2_DestroyElement(o[7]);
		o[7] = -1;
	}
	if (o[4] != -1) {
		d2_DestroyElement(o[4]);
		o[4] = -1;
	}
	for (i = 0; i < 6; i++) {
		if (o[10 + i] != -1) {
			d2_DestroyElement(o[10 + i]);
			o[10 + i] = -1;
		}
		if (o[16 + i] != -1) {
			d2_DestroyElement(o[16 + i]);
			o[16 + i] = -1;
		}
	}
}
