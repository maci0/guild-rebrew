extern char g_7f4cf4[];
int __cdecl _strcmpi(const char*, const char*);
void __cdecl d3_TransformPoint(char*, float*, float*);
int __cdecl d3_CreateSceneModelObject(void*, void*, void*, const char*);
void __cdecl d3_BuildEulerRotationMatrix(float*, float*);
void __cdecl d3_ApplyWorldTransformToObject(void*, void*, void*);
char __cdecl SelectTextureSet(void*, int, unsigned char, char);
int __cdecl d3_ApplyObjectAnimation(void*, const char*, int);

/* ADDRESS: GOLDTL 0x0052d860 */
/* ADDRESS: GOLDDE 0x005161f0 */
char __cdecl d3_CreatePennantAtFlagDummy(char* e, char* o)
{
	float rot[3];
	char name[16];
	float m[16];
	void* obj;

	if (_strcmpi(e, "dummy_FAHNE") != 0) {
		return 1;
	}
	rot[0] = 0;
	rot[1] = 0;
	rot[2] = 0;
	d3_TransformPoint(e, (float*) (e + 0x4c), (float*) name);
	obj = (void*) d3_CreateSceneModelObject(*(void**) (o + 0x61), name, rot, "sp_WIMPEL");
	rot[0] = 0;
	rot[1] = 3.14159274f;
	rot[2] = 0;
	d3_BuildEulerRotationMatrix(rot, m);
	d3_ApplyWorldTransformToObject(obj, name, m);
	if (*(unsigned short*) (o + 0x27) != 0xffff) {
		SelectTextureSet(obj, *(int*) ((char*) obj + 0x1cc),
		    (unsigned char) (*(char*) (*(unsigned short*) (o + 0x27) * 0x21c + (int) &g_7f4cf4) + 0x66), 1);
		*(int*) ((char*) obj + 0x220) = 4;
	}
	d3_ApplyObjectAnimation(obj, "sonstiges\\sp_WIMPEL.baf", 1);
	*((unsigned char*) obj + 0x216) = (unsigned char) ((*((unsigned char*) obj + 0x216) & 0xfd) | 0x11);
	*((unsigned char*) obj + 0x214) &= 0x7f;
	return 1;
}
