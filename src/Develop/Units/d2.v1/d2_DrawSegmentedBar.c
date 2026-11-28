extern char* d2_FileObjTable;
extern int d2_CurrentWindowId;



void __cdecl d2_AddElementToWindow(int, int, int, int);

void __cdecl d2_DrawSegmentedBar(int x0, int y, int len, int t)
{
	int w;
	int n;
	int rem;
	int i;

	w = *(short*) (d2_FileObjTable + t * 0x54 + 0x50) + 2;
	n = (int) (len * 0.04761905f);
	rem = n % 2;
	n /= 2;
	for (i = 0; i < n; i++) {
		d2_AddElementToWindow(x0 + i * w, y, t, d2_CurrentWindowId);
	}
	if (rem != 0) {
		d2_AddElementToWindow(x0 + i * w, y, t + 1, d2_CurrentWindowId);
	}
}
