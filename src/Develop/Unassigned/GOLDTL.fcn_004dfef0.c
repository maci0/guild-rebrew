/* fcn_004dfef0 — register the name and clear the pending flag. */

void __cdecl fcn_00508cf0(int, int);

/* ADDRESS: GOLDTL 0x004dfef0 */
void __cdecl fcn_004dfef0(int name)
{
	fcn_00508cf0(name, 0x9afe00);
	*(int*) 0x68bfc8 = name;
	*(int*) 0x772f60 = 0;
}
