void __fastcall fcn_006194de(void* self);

/* ADDRESS: GOLDTL 0x00619504 */
/* Native ABI is thiscall: the base constructor takes no stack arguments and
 * `this` stays in ecx afterwards, which C89 cannot express (MSVC 6 rejects
 * __thiscall in C mode). The inventory SIZE 0x32 also spans the following
 * destructor at 0x61951a; this body covers the 22-byte constructor only. */
int __fastcall fcn_00619504(void* self)
{
	fcn_006194de(self);
	*(int*) ((char*) self + 0x10) = 0;
	*(int*) ((char*) self + 0x14) = 0;
	*(int*) self = 0x66770c;
	return (int) self;
}
