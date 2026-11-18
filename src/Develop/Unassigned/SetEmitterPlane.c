extern float g_662910;

int __cdecl fcn_0041dd90(void* p);
void __cdecl fcn_00425bf0(void* vm, int line, char* file);

/* ADDRESS: GOLDTL 0x00410380 */
int __cdecl SetEmitterPlane(void** pp, int* normalX, int* normalY, int* normalZ, int* distance)
{
	void* obj;
	float scaledX;
	float scaledY;
	float scaledZ;

	obj = *pp;
	if (!fcn_0041dd90(obj)) {
		fcn_00425bf0(*(void**) 0x6b7e98,
			*(int*) ((char*) *(void**) 0x6b7e98 + 0x118), (char*) 0x676b64);
		return 0;
	}
	scaledY = (float) *normalY * g_662910;
	scaledZ = (float) *normalZ * g_662910;
	scaledX = (float) *normalX * g_662910;
	*(float*) ((char*) obj + 0xa4) = scaledX;
	*(float*) ((char*) obj + 0xa8) = scaledY;
	*(float*) ((char*) obj + 0xac) = scaledZ;
	*(float*) ((char*) obj + 0xb0) = (float) *distance;
	return 0;
}
