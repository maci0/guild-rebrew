extern int d3_ActiveScene;

char __cdecl d3_SetSubObjectVisibleCallback(void* p, int arg);
void __cdecl d3_VisitSceneObjects(int list, int a, int mask, char(__cdecl* fn)(void*, int), int arg);

/* ADDRESS: GOLDTL 0x00442d50 */
/* ADDRESS: GOLDDE 0x0043b1a0 */
char __cdecl d3_SetSubtreeVisible(int a, unsigned char b)
{
	if (a != 0) {
		d3_VisitSceneObjects(d3_ActiveScene, a, 0x3ff, d3_SetSubObjectVisibleCallback, b);
		return 1;
	}
	return 0;
}
