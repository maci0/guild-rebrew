
// fcn_00452e00 — fcn_00438e60([0x5fb5b0],0,4,0x451e70); fcn_00438e60([0x5fb5b0],0,4,0x451f00).

int __cdecl d3_VisitSceneNodes(int, int, int, int);

void __cdecl d3_UpdateSceneOverlayObjects(void)
{
	d3_VisitSceneNodes(*(int*) 0x5fb5b0, 0, 4, 0x451e70);
	d3_VisitSceneNodes(*(int*) 0x5fb5b0, 0, 4, 0x451f00);
}
