/* Inferred name: the independent TL method-start callback at 0x4959f0.
 * command.c owns the separate cm_MarkAndReturn dispatch handler. */

/* ADDRESS: GOLDDE 0x004844a0 */
int __cdecl cm_TestCommandResult(int cmd, int dummy, char* result)
{
	if (cmd != 0) {
		return 0;
	}
	return result == (char*) 0x0;
}
