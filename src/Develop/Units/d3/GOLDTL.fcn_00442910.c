

typedef struct MODEL_SUBMESH_INFO {
	char pad0[0x1e4];
	unsigned int count;
} MODEL_SUBMESH_INFO;

typedef struct MODEL_LOD_SLOT {
	MODEL_SUBMESH_INFO* inner;
	int** tex;
	char pad8[0x4a4 - 8];
} MODEL_LOD_SLOT;
// SIZE 0x4a4

typedef struct MODEL_LOD_SET {
	char pad0[0x40c];
	MODEL_LOD_SLOT slots[3];
	char pad11f8[0x163c - 0x11f8];
	unsigned char count;
} MODEL_LOD_SET;

typedef struct MODEL_SCENE_OBJ {
	char pad0[0x1ec];
	MODEL_LOD_SET* ov;
} MODEL_SCENE_OBJ;

MODEL_SCENE_OBJ* __cdecl d3_SpawnObject(int kind, int id);
void __cdecl d3_AttachSceneNode(MODEL_SCENE_OBJ* parent, MODEL_SCENE_OBJ* o);
int __cdecl d3_FindCachedModel(int id);
void __cdecl d3_LoadModel(int a, int b);
void __cdecl d3_AttachCachedModelParts(MODEL_SCENE_OBJ* o, int z, int id);
void __cdecl fcn_0045ce90(int* t);
void __cdecl d3_SetNodePosition(MODEL_SCENE_OBJ* o, int a);
void __cdecl d3_SetObjectRotation(MODEL_SCENE_OBJ* o, int a);
void __cdecl fcn_00439aa0(MODEL_SCENE_OBJ* o);
void __cdecl d3_DisposeObject(MODEL_SCENE_OBJ* o);

MODEL_SCENE_OBJ* __cdecl fcn_00442910(MODEL_SCENE_OBJ* parent, int a, int b, int id)
{
	MODEL_SCENE_OBJ* o;
	MODEL_LOD_SET* ov;
	int** t;
	unsigned int n;
	unsigned int i;

	o = d3_SpawnObject(4, id);
	if (o == 0) {
		return 0;
	}
	if (parent != 0) {
		d3_AttachSceneNode(parent, o);
	}
	if (d3_FindCachedModel(id) == 0) {
		d3_LoadModel(id, id);
	}
	d3_AttachCachedModelParts(o, 0, id);
	ov = o->ov;
	if (ov != 0 && ov->slots[0].inner != 0) {
		for (i = 0; i < ov->count; i++) {
			if (ov->slots[i].inner != 0) {
				n = ov->slots[i].inner->count;
				t = ov->slots[i].tex;
				for (; n > 0; n--) {
					if (*t != 0) {
						fcn_0045ce90(*t);
					}
					t++;
				}
			}
			ov = o->ov;
		}
		d3_SetNodePosition(o, a);
		d3_SetObjectRotation(o, b);
		if (parent == 0) {
			fcn_00439aa0(o);
		}
		return o;
	}
	d3_DisposeObject(o);
	return 0;
}
