/* The callee is thiscall (self in ecx, one stack argument, ret 4). MSVC 6 rejects
 * __thiscall in C mode; self is still in ecx from the load below, so a one-argument
 * __stdcall declaration pushes the same stack argument. */
extern int __stdcall fcn_005fc024(int flags);

/* ADDRESS: GOLDTL 0x005fc0f4 */
int __stdcall fcn_005fc0f4(int* self)
{
	self[0xc] -= 1;
	if (self[0xc] != 0) {
		return self[0xc];
	}
	fcn_005fc024(1);
	return 0;
}
