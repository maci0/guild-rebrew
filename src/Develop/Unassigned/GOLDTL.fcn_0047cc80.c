int __cdecl fcn_0047cc40(int, int, int, void*, int, float);
void __cdecl fcn_0047b9a0(int, unsigned char, unsigned char, unsigned char);


/* ADDRESS: GOLDTL 0x0047cc80 */
int __cdecl fcn_0047cc80(int a1, int a2, int a3, void* s, int idx, float scale, int tint)
{
	int r;

	r = fcn_0047cc40(a1, a2, a3, s, idx, scale);
	if (tint != 0)
		fcn_0047b9a0(r, 0xff, 0xff, 0xff);
	return 1;
}
