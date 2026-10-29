


#ifdef REBREW_GOLD
#define fcn_0046b2b0 fcn_0046e700
#endif
void __cdecl fcn_0046b2b0(int);

void __cdecl fcn_005b5c70(int* o)
{
	int i;

	if (o[7] != -1) {
		fcn_0046b2b0(o[7]);
		o[7] = -1;
	}
	if (o[4] != -1) {
		fcn_0046b2b0(o[4]);
		o[4] = -1;
	}
	for (i = 0; i < 6; i++) {
		if (o[10 + i] != -1) {
			fcn_0046b2b0(o[10 + i]);
			o[10 + i] = -1;
		}
		if (o[16 + i] != -1) {
			fcn_0046b2b0(o[16 + i]);
			o[16 + i] = -1;
		}
	}
}
