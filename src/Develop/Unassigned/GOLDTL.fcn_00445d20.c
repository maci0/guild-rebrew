void __cdecl d3_InterpolateObjectKeyframe(int a, unsigned int i, float f);

/* ADDRESS: GOLDTL 0x00445d20 */
char __cdecl d3_InterpolateObjectSlotCallback(int obj, float* slotPos)
{
	float x;
	unsigned int i;

	x = *slotPos;
	i = (unsigned int) x;
	d3_InterpolateObjectKeyframe(obj, i, x - i);
	return 1;
}
