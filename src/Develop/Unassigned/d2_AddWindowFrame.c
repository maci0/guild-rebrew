


int __cdecl d2_AddElementToWindow(int, int, int, int);
void __cdecl d2_ReorderControlStack(int);

void __cdecl d2_AddWindowFrame(int layer, int id)
{
	d2_ReorderControlStack(d2_AddElementToWindow(0, 0, id, layer));
	d2_ReorderControlStack(d2_AddElementToWindow(0, 0x1a2, id + 1, layer));
	d2_ReorderControlStack(d2_AddElementToWindow(0, 0x78, id + 2, layer));
	d2_ReorderControlStack(d2_AddElementToWindow(0x243, 0x78, id + 3, layer));
}
