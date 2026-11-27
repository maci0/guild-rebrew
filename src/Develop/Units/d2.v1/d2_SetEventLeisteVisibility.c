

void __cdecl d2_SetFormVisibility(int, int);

void __cdecl d2_SetEventLeisteVisibility(int a1)
{
	if (*(int*) 0x6a476c != -1) {
		d2_SetFormVisibility(*(int*) 0x77e8a0, a1);
	}
}
