void __cdecl d2_GetControlValue(int);


/* ADDRESS: GOLDTL 0x004be520 */
/* ADDRESS: GOLDDE 0x004ac0a0 */
void __cdecl d2_PollRadioSlotControl(int* p)
{
	d2_GetControlValue(*p);
}
