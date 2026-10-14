/* fcn_005803f0 — stop, flush and restart the shared output stream. */

void __cdecl fcn_004727a0(int, int);
void __cdecl fcn_00519190(int);
void __cdecl fcn_00471af0(int, int);

/* ADDRESS: GOLDTL 0x005803f0 */
void __cdecl fcn_005803f0(void)
{
	fcn_004727a0(*(int*) (*(int*) 0x665f08 + 0x24), 0);
	fcn_00519190(0x6811b0);
	fcn_00471af0(*(int*) (*(int*) 0x665f08 + 0x24), 0);
}
