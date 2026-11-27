void __cdecl d3_ChangeObjectTransparency(char* a, char* e, int v);

/* ADDRESS: GOLDTL 0x0043a540 */
char __cdecl d3_SetObjectColorCallback(char* a, int* v)
{
	unsigned int i;

	if (*(char**) (a + 0x1ec) != 0) {
		for (i = 0; i < *(unsigned char*) (*(char**) (a + 0x1ec) + 0x163c); i++) {
			d3_ChangeObjectTransparency(a, *(char**) (a + 0x1ec) + i * 0x4a4 + 0xf4, *v);
		}
	}
	return 1;
}
