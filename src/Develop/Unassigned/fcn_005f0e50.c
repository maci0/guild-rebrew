/* ADDRESS: GOLDTL 0x005f0e50 */
void __fastcall fcn_005f0e50(void* self, int edx_dummy, int a, unsigned int b)
{
	void* obj;
	void** vt;

	(void) edx_dummy;
	obj = *(void**) ((char*) self + 0x3c);
	vt = *(void***) obj;
	((void (__stdcall*) (void*, int, int, int, int)) vt[0x2c / 4])
	    (obj, 0, 0, a, b | 0x800);
}
