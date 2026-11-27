void __cdecl d2_GetControlValue(int);


/* ADDRESS: GOLDTL 0x004be520 */
void __cdecl d2_PollRadioSlotControl(int* p)
{
	d2_GetControlValue(*p);
}
