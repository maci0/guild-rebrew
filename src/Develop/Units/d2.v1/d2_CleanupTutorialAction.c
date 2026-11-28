


extern int* d2_TutorialState;

void __cdecl d2_CloseActionPopup(void*);

/* ADDRESS: GOLDDE 0x00565e50 */
int __cdecl d2_CleanupTutorialAction(void)
{
	char* p;

	p = *(char**) ((int) d2_TutorialState + 0x1c);
	if (p == 0) {
		return -4;
	}
	if (*(int*) (p + 0x74) == 0) {
		return -4;
	}
	d2_CloseActionPopup(p);
	return 0;
}
