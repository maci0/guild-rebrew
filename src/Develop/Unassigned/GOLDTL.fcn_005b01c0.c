


int __cdecl d2_AddElementToWindow(int, int, int, int);
void __cdecl fcn_0046f4c0(int);

void __cdecl d2_AddWindowFrame(int layer, int id)
{
	fcn_0046f4c0(d2_AddElementToWindow(0, 0, id, layer));
	fcn_0046f4c0(d2_AddElementToWindow(0, 0x1a2, id + 1, layer));
	fcn_0046f4c0(d2_AddElementToWindow(0, 0x78, id + 2, layer));
	fcn_0046f4c0(d2_AddElementToWindow(0x243, 0x78, id + 3, layer));
}
