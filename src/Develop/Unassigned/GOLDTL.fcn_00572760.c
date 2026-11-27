/* Thunk: a tail jump to 0x546190. The twelve 0x90 bytes after it are the
 * reference's alignment fill and sit outside the repaired extent. */

void __cdecl he_FreeAction(void);

/* ADDRESS: GOLDTL 0x0000572760 */
void __cdecl he_FreeActionThunk(void)
{
	he_FreeAction();
}
