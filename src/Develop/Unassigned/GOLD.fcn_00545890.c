


// fcn_00545890 — if([a+0x70]!=-2) fcn_004bb6c0(a+0xac); fcn_0053e450(a).

int __cdecl fcn_004bb6c0(void*);
int __cdecl fcn_0053e450(int);

void __cdecl fcn_00545890(char* a)
{
	if (*(int*) (a + 0x70) != -2) {
		fcn_004bb6c0(a + 0xac);
	}
	fcn_0053e450((int) a);
}

