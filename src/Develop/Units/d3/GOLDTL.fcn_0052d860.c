int __cdecl _strcmpi(const char*, const char*);
void __cdecl fcn_00455350(char*, float*, float*);
int __cdecl fcn_00442910(void*, void*, void*, const char*);
void __cdecl fcn_00451900(float*, float*);
void __cdecl fcn_004458a0(void*, void*, void*);
char __cdecl SelectTextureSet(void*, int, unsigned char, char);
int __cdecl fcn_00412f10(void*, const char*, int);

/* ADDRESS: GOLDTL 0x0052d860 */
char __cdecl fcn_0052d860(char* e, char* o)
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
	fcn_00455350(e, (float*) (e + 0x4c), (float*) name);
	obj = (void*) fcn_00442910(*(void**) (o + 0x61), name, rot, "sp_WIMPEL");
	rot[0] = 0;
	rot[1] = 3.14159274f;
	rot[2] = 0;
	fcn_00451900(rot, m);
	fcn_004458a0(obj, name, m);
	if (*(unsigned short*) (o + 0x27) != 0xffff) {
		SelectTextureSet(obj, *(int*) ((char*) obj + 0x1cc),
		    (unsigned char) (*(char*) (*(unsigned short*) (o + 0x27) * 0x21c + 0x7f4cf4) + 0x66), 1);
		*(int*) ((char*) obj + 0x220) = 4;
	}
	fcn_00412f10(obj, "sonstiges\\sp_WIMPEL.baf", 1);
	*((unsigned char*) obj + 0x216) = (unsigned char) ((*((unsigned char*) obj + 0x216) & 0xfd) | 0x11);
	*((unsigned char*) obj + 0x214) &= 0x7f;
	return 1;
}
