struct z_stream_461190 {
	char pad0[0x24];
	void (__cdecl * zfree)(void*, void*);
	void* opaque;
};

/* ADDRESS: GOLDTL 0x00461190 */
void __cdecl fcn_00461190(void* codes, struct z_stream_461190* z)
{
	(*z->zfree)(z->opaque, codes);
}
