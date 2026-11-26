void __cdecl d2_DestroyForm(int);

/* ADDRESS: GOLDTL 0x005e6dd0 */
void __cdecl fcn_005e6dd0(void)
{
	d2_DestroyForm(*(int*) 0x6ad568);
	*(int*) 0x6ad568 = -1;
}
