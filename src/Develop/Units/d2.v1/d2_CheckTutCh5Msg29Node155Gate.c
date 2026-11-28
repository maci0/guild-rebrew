


extern int* d2_TutorialState;

int __cdecl d2_CheckTutCh5Msg29Node155Gate(int* msg)
{
	int* g;
	int r;

	g = d2_TutorialState;
	if (g[14] > 0) {
		if (*msg == 0x29 && msg[3] == 0x155) {
			r = 1;
			g[14] = r;
		} else {
			r = 0;
		}
		return r;
	}
	return 1;
}
