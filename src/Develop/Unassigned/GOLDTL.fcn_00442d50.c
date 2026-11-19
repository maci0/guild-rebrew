extern int g_67a370;

char __cdecl fcn_00442cb0(void* p, int arg);
void __cdecl d3_VisitSceneObjects(int list, int a, int mask, char(__cdecl* fn)(void*, int), int arg);

/* ADDRESS: GOLDTL 0x00442d50 */
char __cdecl d3_SetSubtreeVisible(int a, unsigned char b)
{
	if (a != 0) {
		d3_VisitSceneObjects(g_67a370, a, 0x3ff, fcn_00442cb0, b);
		return 1;
	}
	return 0;
}
