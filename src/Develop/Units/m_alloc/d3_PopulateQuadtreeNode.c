extern int d3_ActiveScene;

void __cdecl d3_FreeQuadtreeNode(int* n);
char __cdecl d3_CollectActiveMeshObjects(void* p, int* n);
void __cdecl d3_VisitSceneObjects(int list, int a, int mask, char(__cdecl* fn)(void*, int*), int* arg);
void __cdecl d3_SplitQuadtreeNode(int* n, int a, int b, int c);

/* ADDRESS: GOLDTL 0x004550e0 */
/* ADDRESS: GOLDDE 0x0044a990 */
void __cdecl d3_PopulateQuadtreeNode(int a1, int* n)
{
	int i;

	if (n != 0) {
		for (i = 0; i < 4; i++) {
			d3_FreeQuadtreeNode((int*) n[i]);
		}
		d3_VisitSceneObjects(d3_ActiveScene, a1, n[0x11] | 0x200, d3_CollectActiveMeshObjects, n);
		d3_SplitQuadtreeNode(n, n[0xd], 1, n[0xe]);
	}
}
