extern char gm_EntitySlotTable[];

/* ADDRESS: GOLD 0x004ae030 */
/* ADDRESS: GOLDTL 0x004ae170 */
/* ADDRESS: GOLDDE 0x0049c490 */
int __cdecl gm_IsSlotLivingPerson(int slot)
{
	unsigned char c;
	unsigned char f;

	slot &= 0xffff;
	if (*(unsigned short*) (((unsigned char*)gm_EntitySlotTable) + slot * 540) != 0xffff) {
		c = (((unsigned char*)gm_EntitySlotTable) + 8)[slot * 540];
		if (c > 0) {
			f = (((unsigned char*)gm_EntitySlotTable) + 2)[slot * 540];
			if (f == 6 || f == 7 || f == 5) {
				return 1;
			}
		}
	}
	return 0;
}

/* ADDRESS: GOLD 0x004ae120 */
/* ADDRESS: GOLDTL 0x004ae260 */
/* ADDRESS: GOLDDE 0x0049c580 */
int __cdecl gm_IsSlotActiveBuilding(int slot)
{
	int o;

	o = (slot & 0xffff) * 540;
	if (*(unsigned short*) ((int) gm_EntitySlotTable + o) != 0xffff
	    && *(unsigned char*) ((int) gm_EntitySlotTable + 8 + o) > 0
	    && *(unsigned char*) ((int) gm_EntitySlotTable + 2 + o) == 0) {
		return 1;
	}
	return 0;
}
