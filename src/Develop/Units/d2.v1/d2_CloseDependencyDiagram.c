extern char g_7f4c10[];


void __cdecl d2_DestroyForm(int);

/* ADDRESS: GOLDDE 0x004fa640 */
void __cdecl d2_CloseDependencyDiagram(void)
{
	d2_DestroyForm(*(int*) &g_7f4c10);
}
