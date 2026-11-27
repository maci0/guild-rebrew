
// fcn_0045c9e0 — [0xfb9264]=0; fcn_00438d40([0x5fb5b0], 0, 0x10, 0x45c9b0, 0).

int __cdecl d3_VisitSceneObjectsUntilStopped(int, int, int, int, int);

void __cdecl d3_CollectFlaggedObjects(void)
{
	int self;

	self = *(int*) 0x5fb5b0;
	*(int*) 0xfb9264 = 0;
	d3_VisitSceneObjectsUntilStopped(self, 0, 0x10, 0x45c9b0, 0);
}
