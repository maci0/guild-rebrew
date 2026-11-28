


extern int d3_ActiveScene;

void __cdecl d3_VisitSceneObjects(int, int, int, int, int);
char __cdecl d3_RemoveObjectFromCellTree(char*, char*);

/* ADDRESS: GOLDDE 0x0044a960 */
void __cdecl d3_RemoveSubTreeFromCellTree(int node, int* cellTree)
{
	if (cellTree == 0) {
		return;
	}
	if (node == 0) {
		return;
	}
	d3_VisitSceneObjects(d3_ActiveScene, node, cellTree[0x44 / 4] | 0x280, (int) d3_RemoveObjectFromCellTree, (int) cellTree);
}
