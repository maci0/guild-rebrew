/* ADDRESS: GOLDTL 0x005efd86 */
/* Native ABI is __thiscall with no stack arguments (self in ecx, plain ret);
 * MSVC 6 C has no __thiscall and __fastcall decorates the symbol, so this C
 * form carries self in ecx. */
int __fastcall fcn_005efd86(void* self)
{
	return (int) self;
}
