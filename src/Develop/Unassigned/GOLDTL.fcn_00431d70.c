/* ADDRESS: GOLDTL 0x00431d70 */
void __cdecl d3_GetAnimFrameOffset(char* obj, char* data, int idx, int unused, float* out)
{
	out[0] = *(float*) (*(char**) (*(char**) (data + 0x68) + 0x15c) + idx * 0xc0 + 0x2c) + *(float*) (obj + 0x84);
	out[1] = *(float*) (*(char**) (*(char**) (data + 0x68) + 0x15c) + idx * 0xc0 + 0x30) + *(float*) (obj + 0x88);
	out[2] = *(float*) (*(char**) (*(char**) (data + 0x68) + 0x15c) + idx * 0xc0 + 0x34) + *(float*) (obj + 0x8c);
}
