
/* ADDRESS: GOLDTL 0x00533880 */
void __cdecl d3_ClearSceneObjectCache(void)
{
	int a;

	for (a = 0x7e46c0; a < 0x7e5fc0; a += 0xc8) {
		*(int*) a = 0;
	}
}
