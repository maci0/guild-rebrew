


extern int* g_665f08;

void __cdecl d2_CloseActionPopup(void*);

int __cdecl d2_CleanupTutorialAction(void)
{
	char* p;

	p = *(char**) ((int) g_665f08 + 0x1c);
	if (p == 0) {
		return -4;
	}
	if (*(int*) (p + 0x74) == 0) {
		return -4;
	}
	d2_CloseActionPopup(p);
	return 0;
}
