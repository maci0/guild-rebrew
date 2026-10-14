


// fcn_0040abd0 — if(!a[0xc]) { fcn_00402480(a[0x14], a[0x30]); fcn_004047a0(a); }.

int __cdecl fcn_00402480(int, int);
int __cdecl fcn_004047a0(void*);

void __cdecl fcn_0040abd0(char* a)
{
	if (*(int*) (a + 0xc) != 0) {
		return;
	}
	fcn_00402480(*(int*) (a + 0x14), *(int*) (a + 0x30));
	fcn_004047a0(a);
}

