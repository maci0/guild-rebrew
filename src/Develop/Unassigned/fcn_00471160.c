extern int g_772560;

int __cdecl d2_LoadForm(int a0, int a1, char* a2);

/* ADDRESS: GOLDTL 0x00471160 */
int __cdecl fcn_00471160(int a0, int a1, char* resource)
{
	g_772560 = 1;
	return d2_LoadForm(a0, a1, resource);
}
