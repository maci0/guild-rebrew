extern int g_14b52fc;



void* __cdecl he_HasActiveAction0x99(int);
void __cdecl d2_ShowModalMessageBox(int, int);

int __cdecl he_HasNoActiveAssassinAction(void* entry)
{
	void* match;

	match = he_HasActiveAction0x99(*(int*) ((char*) entry + 1));
	if (match != 0) {
		d2_ShowModalMessageBox(g_14b52fc, 0);
	}
	return match == 0;
}
