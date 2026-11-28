


void __cdecl d2_SetElementEnabled(int, int);

/* ADDRESS: GOLDDE 0x005add80 */
void __cdecl d2_EnableDialogItems(int count, char* items)
{
	int* ctrl_id;

	if (count > 0) {
		ctrl_id = (int*) (items + 8);
		do {
			d2_SetElementEnabled(*ctrl_id, 1);
			ctrl_id = (int*) ((char*) ctrl_id + 0x38);
		} while (--count);
	}
}
