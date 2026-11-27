char* __cdecl d3_SelectObjectLod(char* object);
void __cdecl d3_UpdateObjectLodMesh(void* obj);
void __cdecl d3_TransformPointToView(char* object, char* camera, float* position, float* out);

/* ADDRESS: GOLD 0x00452ee0 */
void __cdecl d3_UpdateObjectLodAndLighting(char* o)
{
	float len;
	char* rec;
	char* vt;

	len = 0.0f;
	if (*(int*) (o + 0x1cc) == 0) {
		*(char**) (o + 0x1cc) = d3_SelectObjectLod(o);
		if (*(int*) (o + 0x1cc) == 0) {
			return;
		}
	}
	d3_TransformPointToView(o, *(char**) 0xfc2dec, (float*) (o + 0x4c), (float*) (o + 0x1d8));
	rec = *(char**) (o + 0x1cc);
	vt = *(char**) (rec + 0x10);
	if (vt != 0) {
		len = ((float (__cdecl*)(char*, char*)) *(void**) (vt + 0x1f8))(o, rec);
	}
	*(float*) (o + 0x1e4) = len * len;
	if (o[0x210] & 4) {
		d3_UpdateObjectLodMesh(o);
	}
	if (o[0x210] & 0x20) {
		rec = *(char**) (o + 0x1cc);
		vt = *(char**) (rec + 0x10);
		if (vt != 0) {
			((void (__cdecl*)(char*, char*)) *(void**) (vt + 0x1ec))(o, rec);
		}
	}
}
