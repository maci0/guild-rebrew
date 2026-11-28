extern char gm_EntityIdField[];
extern char gm_EntityIdField[];

/* ADDRESS: GOLD 0x005414b0 */
/* ADDRESS: GOLDTL 0x00549330 */
/* ADDRESS: GOLDDE 0x0052f870 */
void __cdecl he_SetActionSubject(char* p, int slotId)
{
	*(unsigned short*) (p + 8) = (unsigned short) slotId;
	if (slotId != 0xffff) {
		*(int*) (p + 0xc) = *(int*) (gm_EntityIdField + slotId * 540);
		return;
	}
	*(int*) (p + 0xc) = -1;
}
