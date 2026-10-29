/* Thunk: a tail jump to 0x546190. The twelve 0x90 bytes after it are the
 * reference's alignment fill and sit outside the repaired extent. */

void __cdecl fcn_00546190(void);

/* ADDRESS: GOLDTL 0x0000572760 */
void __cdecl fcn_00572760(void)
{
	fcn_00546190();
}
