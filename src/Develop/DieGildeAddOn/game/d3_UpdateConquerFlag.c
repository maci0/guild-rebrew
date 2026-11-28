extern int g_772f08;
extern char* d3_CombatFlagObjects[];
extern char str_empty[];

char* __cdecl d3_FindSceneObject(char*, int, char*, char*);
char* __cdecl gm_LookupEntityRecordIn32SlotTable(int);
void __cdecl io_FormatTextBuffer(char*, int, int);
void __cdecl d2_ShowStatusBanner(char*);
void __cdecl d3_DestroyObject(int);
void __cdecl d3_TransformPoint(char*, float*, float*);
char* __cdecl d3_CreateSceneModelObject(int, float*, float*, char*);
void __cdecl d3_ApplyObjectAnimation(char*, char*, int);
char __cdecl SelectTextureSet(void*, void*, unsigned char, char);
int __cdecl fcn_0064d41a(char*, char*, ...);

/* ADDRESS: GOLDTL 0x004d87f0 */
/* ADDRESS: GOLDDE 0x004c54e0 */
void __cdecl d3_UpdateConquerFlag(int* orderRecord)
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
	if (orderRecord[1] == 0) {
		return;
	}
	info = d3_FindSceneObject(0, 0x40, 0, (char*) orderRecord + 0x10);
	if (orderRecord[0] != -1) {
		ent = gm_LookupEntityRecordIn32SlotTable(orderRecord[0]);
		*(unsigned char*) (*(int*) (ent + 0x184) + 0x8d) |= 4;
		io_FormatTextBuffer(buf, 0x11b8, *(unsigned short*) ent);
		d2_ShowStatusBanner(buf);
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
			d3_TransformPoint(info, (float*) (info + 0x4c), position);
			obj = d3_CreateSceneModelObject(0, position, rotation, "ub_FLUCHTFLAGGE");
			d3_CombatFlagObjects[g_772f08] = d3_CreateSceneModelObject(0, position, rotation, str_empty);
			d3_ApplyObjectAnimation(obj, "sonstiges/anim_FLUCHTFLAGGE.baf", 1);
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
