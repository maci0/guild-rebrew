
// fcn_004de5e0 — fcn_00505ca0(a, 0x92bcc0); [0x60d350]=a; [0x6f0db0]=0.

int __cdecl gm_GenerateShuffledIndices(int, int);

void __cdecl gm_InitShuffledIndexPool(int count)
{
	gm_GenerateShuffledIndices(count, 0x92bcc0);
	*(int*) 0x60d350 = count;
	*(int*) 0x6f0db0 = 0;
}
