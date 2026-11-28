


extern int* d2_TutorialState;

/* ADDRESS: GOLDDE 0x00565a80 */
int __cdecl d2_CheckTutCh3Msg26Node1d0Gate(int* msg)
{
	int* g;
	int r;

	g = d2_TutorialState;
	if (g[14] >= 0 && *msg == 0x26 && msg[3] == 0x1d0) {
		r = 1;
		g[14] = r;
	} else if (*msg == 0x1a || *msg == 0x1c) {
		r = 1;
	} else {
		r = 0;
	}
	return r;
}
