extern char g_6b7e98[];
extern char g_676b64[];


int __cdecl fcn_0041dd90(void* p);
void __cdecl evt_LogScriptError(void* vm, int line, char* file);

/* ADDRESS: GOLDTL 0x00410380 */
/* ADDRESS: GOLDDE 0x0040f180 */
int __cdecl SetEmitterPlane(void** pp, int* normalX, int* normalY, int* normalZ, int* distance)
{
	void* obj;
	float scaledX;
	float scaledY;
	float scaledZ;

	obj = *pp;
	if (!fcn_0041dd90(obj)) {
		evt_LogScriptError(*(void**) &g_6b7e98,
			*(int*) ((char*) *(void**) &g_6b7e98 + 0x118), (char*) &g_676b64);
		return 0;
	}
	scaledY = (float) *normalY * 0.01f;
	scaledZ = (float) *normalZ * 0.01f;
	scaledX = (float) *normalX * 0.01f;
	*(float*) ((char*) obj + 0xa4) = scaledX;
	*(float*) ((char*) obj + 0xa8) = scaledY;
	*(float*) ((char*) obj + 0xac) = scaledZ;
	*(float*) ((char*) obj + 0xb0) = (float) *distance;
	return 0;
}
