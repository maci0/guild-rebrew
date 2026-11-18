

extern int d2_TutorialActive;
extern int* g_665f08;

int __cdecl fcn_0057eb80(void)
{
	if (d2_TutorialActive == 0) {
		return 0;
	}
	return *(int*) (((char*)g_665f08) + 0x3c) == 2;
}
