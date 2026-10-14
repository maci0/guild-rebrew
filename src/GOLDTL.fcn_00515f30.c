/* fcn_00515f30 — tail-call the notifier when the record is present. */

int __cdecl fcn_0064f170(int, int, int);
void __cdecl fcn_00418f90(int);

/* ADDRESS: GOLDTL 0x00515f30 */
void __cdecl fcn_00515f30(int a1)
{
	if (fcn_0064f170(a1, 0x6a1f7c, 4) != 0) {
		return;
	}
	if (*(int*) (a1 + 0x210) == 0) {
		return;
	}
	fcn_00418f90(*(int*) (a1 + 0x210));
}
