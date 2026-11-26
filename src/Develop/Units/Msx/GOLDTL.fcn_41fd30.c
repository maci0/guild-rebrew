

int __cdecl msx_SetMasterVolume(int, int);

void __cdecl fcn_004c3140(void* a)
{
	if (*(int*) 0x6b71a8 != 0) {
		((void (__stdcall*)(int)) *(void**) 0x662074)(0x14cc5a0);
		msx_SetMasterVolume(*(int*) 0x6b71a8, (int) a);
		*(int*) 0x678164 = (int) a;
		((void (__stdcall*)(int)) *(void**) 0x662070)(0x14cc5a0);
	}
}
