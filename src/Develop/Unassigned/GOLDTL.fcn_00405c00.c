

extern char g_1043370[];
char __cdecl fcn_0045b990(int rec, int key, int* a, int* b, int* c);
int __cdecl ch_MarkGridDiamond(int a, int b, unsigned char id, int x, int y);

int __cdecl ch_MarkGridDiamondAtPos(int key, unsigned char id, int x, int y)
{
	int a;
	int b;
	int c;
	int rec;

	rec = ((int*)g_1043370)[id * 247];
	if (rec != 0 && fcn_0045b990(rec, key, &a, &b, &c)) {
		return ch_MarkGridDiamond(a, b, id, x, y);
	}
	return -1;
}
