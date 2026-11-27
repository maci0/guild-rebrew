

void __cdecl d2_DestroyForm(int);

void __cdecl d2_DestroyHudForm(void)
{
	if (*(int*) 0x68b7a0 != -1) {
		d2_DestroyForm(*(int*) 0x68b7a0);
		*(int*) 0x68b7a0 = -1;
	}
}
