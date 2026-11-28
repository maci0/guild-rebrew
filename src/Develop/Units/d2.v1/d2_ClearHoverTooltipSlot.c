extern char d2_HoverTooltipSlots[];
extern char d2_HoverTooltipSlots[];

/* ADDRESS: GOLD 0x0052c4d0 */
/* ADDRESS: GOLDTL 0x00531c00 */
void __cdecl d2_ClearHoverTooltipSlot(int value)
{
	int i;
	int cursor;

	for (i = 0, cursor = (int) d2_HoverTooltipSlots; cursor < (int) d2_HoverTooltipSlots + 0x4300; cursor += 0x10c, i++) {
		if (*(int*) cursor == value) {
			*(int*) ((int) d2_HoverTooltipSlots + i * 268) = 0;
			return;
		}
	}
}
