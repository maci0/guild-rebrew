/* CRT band. Not an application function: this address is an inner entry of the
 * stock CRT _realloc. The only reference is _realloc's own SEH filter at
 * 0x00650097; the 11 callable bytes are
 *   push 9; call _unlock (0x652be6); pop ecx; xor edi,edi; ret
 * and the stored 86-byte extent continues into _realloc's SEH epilogue
 * (0x6500cd..0x650117), where edi is the surrounding routine's zero value.
 * The trailing xor edi,edi; ret is compiler-generated funclet code, so C89
 * cannot express the bytes. Non-C class. See docs/data-ownership.md,
 * "The stock _realloc candidate". */
extern int __cdecl _unlock(int locknum);

/* ADDRESS: GOLDTL 0x006500c2 */
int __cdecl fcn_006500c2(void)
{
	_unlock(9);
	return 0;
}
