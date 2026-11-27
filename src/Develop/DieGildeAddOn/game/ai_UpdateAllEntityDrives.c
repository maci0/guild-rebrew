// for slots: if([p]!=0xffff) ai_UpdateEntityDrives(p).

void __cdecl ai_UpdateEntityDrives(int);

#if defined(REBREW_GOLD)
/* ADDRESS: GOLD 0x0047da70 */
void __cdecl ai_UpdateAllEntityDrives(void)
{
	int p;
	for (p = 0x770b80; p < 0x7d5f80; p += 0x21c) {
		if (*(unsigned short*) p != 0xffff) {
			ai_UpdateEntityDrives(p);
		}
	}
}
#else
/* ADDRESS: GOLDTL 0x0047cf30 */
void __cdecl ai_UpdateAllEntityDrives(void)
{
	int p;
	for (p = 0x7f4ca0; p < 0x85a0a0; p += 0x21c) {
		if (*(unsigned short*) p != 0xffff) {
			ai_UpdateEntityDrives(p);
		}
	}
}
#endif
