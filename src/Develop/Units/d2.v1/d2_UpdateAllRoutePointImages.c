extern char d2_RadioSlots[];


void __cdecl d2_UpdateRoutePointImage(void*);

/* ADDRESS: GOLDDE 0x004ad790 */
void __cdecl d2_UpdateAllRoutePointImages(void)
{
	int a;

	for (a = (int) &d2_RadioSlots; a < ((int) &d2_RadioSlots + 0x40); a += 8) {
		if (*(int*) a != -1) {
			d2_UpdateRoutePointImage((void*) a);
		}
	}
}
