

// SIZE 0x208
typedef struct {
	char pad0[0x48];
	int x48;
	char pad4c[0x204 - 0x4c];
	struct Figure* owner;
} Model;

// SIZE 0x241
typedef struct Figure {
	char pad0[0x2c];
	int active;
	char pad30[4];
	Model* model;
	char pad38[0x1a0 - 0x38];
	float speed;
	char pad1a4[0x23c - 0x1a4];
	int target;
	unsigned char state;
} Figure;

extern float d3_UnitAxisVectors[3];
extern int g_14abee0[];

char* __cdecl d3_FindSceneObject(char*, int, char*, char*);
void __cdecl d3_TransformPoint(char*, float*, float*);
#include "Develop/DieGildeAddOn/game/ch_motion.h"
void __cdecl d3_TransformDirection(char*, char*, float*);
float __cdecl d3_SignedPlanarAngle(char*, float*);
void __cdecl d3_SetObjectRotation(Model*, float*);
#include "Develop/DieGildeAddOn/game/ch_ground.h"
void __cdecl d3_InvalidateSubTreeFlags(Model*, int);
void __cdecl ch_PreloadCharacterMotions(Figure*, int, char*);
void __cdecl RegisterStatusText(Model*, int, int);

/* ADDRESS: GOLDDE 0x00522890 */
Figure* __cdecl ch_CreateCharacterAtSceneObject(char* res, char* kind, int anim)
{
	float box[4];
	char* h;
	Figure* f;

	h = d3_FindSceneObject(0, 0x100, 0, res);
	if (h == 0) {
		return 0;
	}
	d3_TransformPoint(h, (float*) (h + 0x4c), box);
	f = (Figure*) ch_CreateAtPosition(kind, box);
	if (f != 0) {
		float pos[3];
		float at[3];

		pos[0] = 0.0f;
		pos[1] = 0.0f;
		pos[2] = 0.0f;
		d3_TransformDirection(h, ((char*)d3_UnitAxisVectors), at);
		pos[1] = d3_SignedPlanarAngle(((char*)d3_UnitAxisVectors), at);
		d3_SetObjectRotation(f->model, pos);
		ch_PlaceOnGround(f, 0);
		f->model->owner = f;
		d3_InvalidateSubTreeFlags(f->model, 1);
		ch_PreloadCharacterMotions(f, 1, "bewegung/gehen");
		f->model->x48 = 0;
		f->speed = 0.7f;
		f->target = -1;
		f->active = 1;
		f->state = 4;
		RegisterStatusText(f->model, g_14abee0[anim], 0);
	}
	return f;
}
