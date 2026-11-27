
/* ADDRESS: GOLDTL 0x0047a280 */
void __cdecl d2_OffsetAnimationSlot(unsigned short firstDelta, unsigned short secondDelta, int index)
{
	*(unsigned short*) (index * 20 + 0x100e7ae) += firstDelta;
	*(unsigned short*) (index * 20 + 0x100e7b0) += secondDelta;
}
