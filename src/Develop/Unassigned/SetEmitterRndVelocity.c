int __cdecl fcn_0041dd90(void*);
void __cdecl evt_LogScriptError(void*, int, char*);

/* ADDRESS: GOLDTL 0x00410310 */
int __cdecl SetEmitterRndVelocity(void** emitter, int* a2, int* a3, int* a4)
{
	char* p;
	float x;
	float y;
	float z;

	p = (char*) *emitter;
	if (!fcn_0041dd90(p)) {
		evt_LogScriptError(*(void**) 0x6b7e98,
			*(int*) ((char*) *(void**) 0x6b7e98 + 0x118),
			(char*) 0x676b38);
		return 0;
	}
	x = (float) *a3 * *(float*) 0x662910;
	y = (float) *a4 * *(float*) 0x662910;
	z = (float) *a2 * *(float*) 0x662910;
	*(float*) (p + 0x8c) = z;
	*(float*) (p + 0x90) = x;
	*(float*) (p + 0x94) = y;
	return 0;
}
