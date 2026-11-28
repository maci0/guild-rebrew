extern char g_6ad568[];
void __cdecl d2_DestroyForm(int);

/* ADDRESS: GOLDTL 0x005e6dd0 */
/* ADDRESS: GOLDDE 0x005c8090 */
void __cdecl d2_DestroyCardGameForm(void)
{
	d2_DestroyForm(*(int*) &g_6ad568);
	*(int*) &g_6ad568 = -1;
}
