/* CRT band. Not a function entry: 0x0065a7ce is the __except filter block of
 * the SEH routine at 0x0065a686 (that row is EXACT). It has no prologue, reads
 * the enclosing frame at [ebp-0x28], [ebp-0x24], [ebp-0x1c], [ebp-0x20] and
 * [ebp-0x2c], reuses live esi/edi, and is entered by the guarded call at
 * 0x0065a78f. It tests the C++ EH record (0xe06d7363, NumberParameters 3,
 * magic 0x19930520) and calls getptd (0x00652c98) and abnormal_termination
 * (0x0065aa0a). A standalone C function cannot reproduce bytes that depend on
 * the caller's frame. Non-C class (compiler-generated SEH funclet). */
/* ADDRESS: GOLDTL 0x0065a7ce */
int __cdecl fcn_0065a7ce(void)
{
	return 0;
}
