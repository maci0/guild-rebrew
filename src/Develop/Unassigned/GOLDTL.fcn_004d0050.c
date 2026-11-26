

void __cdecl d2_DestroyForm(int);

void __cdecl fcn_004d0050(void)
{
	if (*(int*) 0x68b7a0 != -1) {
		d2_DestroyForm(*(int*) 0x68b7a0);
		*(int*) 0x68b7a0 = -1;
	}
}
