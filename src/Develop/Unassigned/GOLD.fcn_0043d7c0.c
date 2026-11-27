void* __cdecl d3_SelectObjectLod(void*);
int __cdecl fcn_00458d90(void*, int, int, void*);
extern int d3_ActiveCamera;

void __cdecl d3_UpdateObjectLodMesh(void *obj)
{
	void *r;
	char buf1[0x40];
	typedef int (__cdecl *method_t)(void*, void*, void*);

	r = d3_SelectObjectLod(obj);
	if (r != 0) {
		if ((int)r != *(int *)((char*)obj + 0x1cc))
			*(int *)((char*)obj + 0x1cc) = (int)r;
		fcn_00458d90(obj,
		              (*(unsigned char *)((char*)obj + 0x210) & 0x80) ? 0 : d3_ActiveCamera,
		              0, buf1);
		((method_t)(*(void **)(*(char **)((char*)r + 0x10) + 0x1f0)))(
			obj, r, buf1);
		*(unsigned char *)((char*)obj + 0x210) |= 4;
	}
}
