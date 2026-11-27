
// fcn_0043d690 — if(a) fcn_00438d40([0x5fb5b0], a, 0x240, 0x43d630, b).

int __cdecl d3_VisitSceneObjectsUntilStopped(int, int, int, int, int);

void __cdecl d3_VisitObjectAttachments(int a, int b)
{
	if (a != 0) {
		d3_VisitSceneObjectsUntilStopped(*(int*) 0x5fb5b0, a, 0x240, 0x43d630, b);
	}
}
