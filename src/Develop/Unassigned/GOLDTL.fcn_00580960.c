


extern int* g_665f08;
extern int d2_CurrentElementId;
extern int d2_TutorialActive;
extern int g_100f1dc;

int __cdecl fcn_00580960(void)
{
	int r;

	if (*(int*) ((char*)&d2_TutorialActive) == 0) {
		return -4;
	}
	if (*(int*) ((char*)&g_100f1dc) != -1 && d2_CurrentElementId == g_665f08[19]) {
		r = 1;
	} else {
		r = 0;
	}
	return r;
}
