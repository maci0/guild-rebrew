/* The stored 54-byte extent continues past this body into the cold path of
 * the enclosing CRT allocator at 0x0064e1d0; this definition is the 9-byte
 * "__unlock(9)" helper only. */
void __cdecl __unlock(int);

/* ADDRESS: GOLDTL 0x0064e1c7 */
void __cdecl fcn_0064e1c7(void)
{
	__unlock(9);
}
