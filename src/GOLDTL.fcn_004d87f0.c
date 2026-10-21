extern int g_772f08;
extern char* g_9b9e40[];
extern char g_6b5c60[];

char* __cdecl fcn_00445600(char*, int, char*, char*);
char* __cdecl fcn_004cef30(int);
void __cdecl fcn_0051af00(char*, int, int);
void __cdecl fcn_00533a40(char*);
void __cdecl d3_DestroyObject(int);
void __cdecl fcn_00455350(char*, float*, float*);
char* __cdecl fcn_00442910(int, float*, float*, char*);
void __cdecl fcn_00412f10(char*, char*, int);
char __cdecl SelectTextureSet(void*, void*, unsigned char, char);
int __cdecl fcn_0064d41a(char*, char*, ...);

/* ADDRESS: GOLDTL 0x004d87f0 */
void __cdecl fcn_004d87f0(int* a0)
{
	char buf[0x100];
	float rotation[3];
	float position[4];
	char* info;
	char* ent;
	char* obj;
	int* mode;
	unsigned char lod;

	ent = 0;
	if (a0[1] == 0) {
		return;
	}
	info = fcn_00445600(0, 0x40, 0, (char*) a0 + 0x10);
	if (a0[0] != -1) {
		ent = fcn_004cef30(a0[0]);
		*(unsigned char*) (*(int*) (ent + 0x184) + 0x8d) |= 4;
		fcn_0051af00(buf, 0x11b8, *(unsigned short*) ent);
		fcn_00533a40(buf);
	}
	if (*(char**) (info + 0x204) != ent) {
		if (*(int*) (info + 0x208) != 0) {
			d3_DestroyObject(*(int*) (info + 0x208));
			*(int*) (info + 0x208) = 0;
		}
		if (ent != 0) {
			rotation[0] = 0.0f;
			rotation[1] = 0.0f;
			rotation[2] = 0.0f;
			fcn_00455350(info, (float*) (info + 0x4c), position);
			obj = fcn_00442910(0, position, rotation, "ub_FLUCHTFLAGGE");
			g_9b9e40[g_772f08] = fcn_00442910(0, position, rotation, g_6b5c60);
			fcn_00412f10(obj, "sonstiges/anim_FLUCHTFLAGGE.baf", 1);
			mode = *(int**) (ent + 0x16c);
			if (mode != 0 && *(int*) ((char*) mode + 0x54) != 0) {
				if (*(char*) ((char*) mode + 2) == 5 || *(char*) ((char*) mode + 2) == 6 ||
				    *(char*) ((char*) mode + 2) == 7) {
					lod = *(unsigned char*) ((char*) mode + 0x54) + 0x67;
					if (lod != 0) {
						SelectTextureSet(obj, *(void**) (obj + 0x1cc), lod, 1);
					}
				}
			}
			fcn_0064d41a(obj, "CONQUER_FLAG");
			*(int*) (obj + 0x204) = 0;
			*(int*) (obj + 0x220) = 4;
			*(int*) (obj + 0x224) = 1;
			*(unsigned char*) (obj + 0x216) =
				(*(unsigned char*) (obj + 0x216) & 0xfd) | 0x11;
			*(int*) (info + 0x208) = (int) obj;
			*(int*) (info + 0x204) = (int) ent;
			return;
		}
		*(int*) (info + 0x208) = 0;
	}
	*(int*) (info + 0x204) = (int) ent;
}
