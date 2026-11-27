extern char g_7f4ca4[];
extern char g_7f4ca4[];

/* ADDRESS: GOLD 0x005414b0 */
/* ADDRESS: GOLDTL 0x00549330 */
void __cdecl he_SetActionSubject(char* p, int slotId)
{
	*(unsigned short*) (p + 8) = (unsigned short) slotId;
	if (slotId != 0xffff) {
		*(int*) (p + 0xc) = *(int*) (g_7f4ca4 + slotId * 540);
		return;
	}
	*(int*) (p + 0xc) = -1;
}
