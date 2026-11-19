

int __cdecl msx_StopSample(int);

void __cdecl fcn_004224f0(int* p)
{
	if (*(int*) 0x6b7d7c != 0 && p != 0) {
		msx_StopSample(p[0]);
		p[2] = 0;
		p[9] = 0x7f;
		p[10] = 0x3f;
	}
}
