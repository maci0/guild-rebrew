/* Thunk: a tail jump to 0x546190. The twelve 0x90 bytes after it are the
 * reference's alignment fill and sit outside the repaired extent. */

void __cdecl fcn_00546190(void);

/* ADDRESS: GOLDTL 0x00005756f0 */
void __cdecl fcn_005756f0(void)
{
	fcn_00546190();
}
