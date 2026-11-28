

extern char tp_ch_PathGrid[];
char __cdecl d3sm_3D2SuperMap(int rec, int key, int* a, int* b, int* c);
int __cdecl ch_MarkGridDiamond(int a, int b, unsigned char id, int x, int y);

int __cdecl ch_MarkGridDiamondAtPos(int key, unsigned char id, int x, int y)
{
	int a;
	int b;
	int c;
	int rec;

	rec = ((int*)tp_ch_PathGrid)[id * 247];
	if (rec != 0 && d3sm_3D2SuperMap(rec, key, &a, &b, &c)) {
		return ch_MarkGridDiamond(a, b, id, x, y);
	}
	return -1;
}
