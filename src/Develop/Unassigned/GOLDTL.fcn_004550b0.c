


extern int g_67a370;

void __cdecl d3_VisitSceneObjects(int, int, int, int, int);
char __cdecl d3_RemoveObjectFromCellTree(char*, char*);

void __cdecl fcn_004550b0(int a1, int* a2)
{
	if (a2 == 0) {
		return;
	}
	if (a1 == 0) {
		return;
	}
	d3_VisitSceneObjects(g_67a370, a1, a2[0x44 / 4] | 0x280, (int) d3_RemoveObjectFromCellTree, (int) a2);
}
