

void __cdecl d3_SetNodeScale(int, void*);

void __cdecl d3_SetNodeScaleXYZ(int a1, int a2, int a3, int a4)
{
	int buf[4];

	buf[0] = a2;
	buf[1] = a3;
	buf[2] = a4;
	d3_SetNodeScale(a1, buf);
}
