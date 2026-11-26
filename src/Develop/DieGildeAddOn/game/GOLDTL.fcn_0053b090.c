

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

extern float g_662d40[3];
extern int g_14abee0[];

char* __cdecl fcn_00445600(char*, int, char*, char*);
void __cdecl d3_TransformPoint(char*, float*, float*);
#include "Develop/DieGildeAddOn/game/ch_motion.h"
void __cdecl fcn_00455140(char*, char*, float*);
float __cdecl fcn_00451380(char*, float*);
void __cdecl d3_SetObjectRotation(Model*, float*);
#include "Develop/DieGildeAddOn/game/ch_ground.h"
void __cdecl d3_InvalidateSubTreeFlags(Model*, int);
void __cdecl ch_PreloadCharacterMotions(Figure*, int, char*);
void __cdecl RegisterStatusText(Model*, int, int);

Figure* __cdecl ch_CreateCharacterAtSceneObject(char* res, char* kind, int anim)
{
	float box[4];
	char* h;
	Figure* f;

	h = fcn_00445600(0, 0x100, 0, res);
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
		fcn_00455140(h, ((char*)g_662d40), at);
		pos[1] = fcn_00451380(((char*)g_662d40), at);
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
