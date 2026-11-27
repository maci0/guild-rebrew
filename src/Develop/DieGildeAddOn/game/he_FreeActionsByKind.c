/* fcn_00546ce0 — drain the entries selected by the record's first word. */

void* __cdecl he_StartHandlungSearch(int, int, int);
void __cdecl he_CancelInvalidBuildingAction(void*);
void* __cdecl he_fn_Handlung(void);

/* ADDRESS: GOLDTL 0x00546ce0 */
void __cdecl he_FreeActionsByKind(unsigned short* record)
{
	void* entry;

	entry = he_StartHandlungSearch(1, 2, *record);
	while (entry != 0) {
		he_CancelInvalidBuildingAction(entry);
		entry = he_fn_Handlung();
	}
}
