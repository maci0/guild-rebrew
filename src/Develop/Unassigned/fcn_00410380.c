extern float g_662910;

int __cdecl fcn_0041dd90(void* p);
void __cdecl fcn_00425bf0(void* vm, int line, char* file);

/* ADDRESS: GOLDTL 0x00410380 */
int __cdecl fcn_00410380(void** pp, int* a1, int* a2, int* a3, int* a4)
{
	void* obj;
	float v1;
	float v2;
	float v3;

	obj = *pp;
	if (!fcn_0041dd90(obj)) {
		fcn_00425bf0(*(void**) 0x6b7e98,
			*(int*) ((char*) *(void**) 0x6b7e98 + 0x118), (char*) 0x676b64);
		return 0;
	}
	v2 = (float) *a2 * g_662910;
	v3 = (float) *a3 * g_662910;
	v1 = (float) *a1 * g_662910;
	*(float*) ((char*) obj + 0xa4) = v1;
	*(float*) ((char*) obj + 0xa8) = v2;
	*(float*) ((char*) obj + 0xac) = v3;
	*(float*) ((char*) obj + 0xb0) = (float) *a4;
	return 0;
}
