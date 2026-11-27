
// fcn_004bf410 — clear slot a: free + reset.

void __cdecl d2_DestroyGuiElement(int);

void __cdecl d2_ClearRouteMarkerSlot(int index)
{
	d2_DestroyGuiElement(*(int*) (0xf812a0 + index * 8));
	*(int*) (0xf812a0 + index * 8) = 0xffffffff;
	*(int*) (0xf812a4 + index * 8) = 0;
}
