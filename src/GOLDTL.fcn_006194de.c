typedef struct Obj6194de {
	void* vt;  /* 0x0 */
	int f4;    /* 0x4 */
	int f8;    /* 0x8 */
	int fc;    /* 0xc */
} Obj6194de;

/* ADDRESS: GOLDTL 0x006194de */
/* Native ABI is thiscall with no stack arguments (self in ecx, plain ret);
 * MSVC 6 C has no __thiscall and __fastcall decorates the symbol, so this C
 * form takes self as an ordinary first parameter. */
Obj6194de* __cdecl fcn_006194de(Obj6194de* self)
{
	self->fc = 0;
	self->f8 = 0;
	self->vt = (void*) 0x6676d4;
	self->f4 = 1;
	return self;
}
