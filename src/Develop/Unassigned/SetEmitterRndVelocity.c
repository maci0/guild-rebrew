extern char g_6b7e98[];
extern char g_676b38[];
extern char flt_0_01[];
int __cdecl fcn_0041dd90(void*);
void __cdecl evt_LogScriptError(void*, int, char*);

/* ADDRESS: GOLDTL 0x00410310 */
/* ADDRESS: GOLDDE 0x0040f110 */
int __cdecl SetEmitterRndVelocity(void** emitter, int* a2, int* a3, int* a4)
{
	char* p;
	float x;
	float y;
	float z;

	p = (char*) *emitter;
	if (!fcn_0041dd90(p)) {
		evt_LogScriptError(*(void**) &g_6b7e98,
			*(int*) ((char*) *(void**) &g_6b7e98 + 0x118),
			(char*) &g_676b38);
		return 0;
	}
	x = (float) *a3 * *(float*) &flt_0_01;
	y = (float) *a4 * *(float*) &flt_0_01;
	z = (float) *a2 * *(float*) &flt_0_01;
	*(float*) (p + 0x8c) = z;
	*(float*) (p + 0x90) = x;
	*(float*) (p + 0x94) = y;
	return 0;
}
