extern char str_empty[];
/* fcn_0057f3b0 — on the first pass, tag the filtered entry. */

void* __cdecl gm_StartFilteredEntitySearch(int, int, int);
void __cdecl d2_EnterBuildingObjekt(void*, int, int);

/* ADDRESS: GOLDTL 0x0057f3b0 */
/* ADDRESS: GOLDDE 0x005650b0 */
void __cdecl d2_FocusTutorialBuilding0x0a(int step)
{
	void* entry;

	if (step == 1) {
		entry = gm_StartFilteredEntitySearch(1, 5, 0xa);
		if (entry != 0) {
			d2_EnterBuildingObjekt(entry, -1, (int) &str_empty);
		}
	}
}
