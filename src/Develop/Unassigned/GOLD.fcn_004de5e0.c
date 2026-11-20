
// fcn_004de5e0 — fcn_00505ca0(a, 0x92bcc0); [0x60d350]=a; [0x6f0db0]=0.

int __cdecl gm_GenerateShuffledIndices(int, int);

void __cdecl fcn_004de5e0(int a)
{
	gm_GenerateShuffledIndices(a, 0x92bcc0);
	*(int*) 0x60d350 = a;
	*(int*) 0x6f0db0 = 0;
}
