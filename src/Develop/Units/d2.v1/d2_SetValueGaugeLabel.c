extern char d2_Controls[];


void __cdecl fcn_0064d530(int, int, int);

/* ADDRESS: GOLDDE 0x0045c500 */
void __cdecl d2_SetValueGaugeLabel(int slot, int label)
{
	fcn_0064d530(*(int*) &d2_Controls + slot * 0x2f4 + 0xa8, label, 0x3f);
}
