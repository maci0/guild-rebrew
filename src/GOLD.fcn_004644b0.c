void __cdecl fcn_00463740(int, int, int);

/* ADDRESS: GOLD 0x004644b0 */
int __cdecl fcn_004644b0(int a, int b)
{
	fcn_00463740(a, b, 0);
	(*(void (__cdecl **)(int, int))(b + 0x24))(*(int *)(b + 0x28), *(int *)(a + 0x28));
	(*(void (__cdecl **)(int, int))(b + 0x24))(*(int *)(b + 0x28), *(int *)(a + 0x24));
	(*(void (__cdecl **)(int, int))(b + 0x24))(*(int *)(b + 0x28), a);
	return 0;
}
