

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

char* __cdecl fcn_00445600(int, int, int, int);
void __cdecl fcn_00455350(char*, char*, float*);
Figure* __cdecl fcn_00403b90(int, float*);
void __cdecl fcn_00455140(char*, char*, float*);
float __cdecl fcn_00451380(char*, float*);
void __cdecl fcn_00438cb0(Model*, float*);
void __cdecl fcn_004053a0(Figure*, int);
void __cdecl fcn_00438ac0(Model*, int);
void __cdecl fcn_00404a00(Figure*, int, char*);
void __cdecl fcn_005338d0(Model*, int, int);

Figure* __cdecl fcn_0053b090(int res, int kind, int anim)
{
	float box[4];
	char* h;
	Figure* f;

	h = fcn_00445600(0, 0x100, 0, res);
	if (h == 0) {
		return 0;
	}
	fcn_00455350(h, h + 0x4c, box);
	f = fcn_00403b90(kind, box);
	if (f != 0) {
		float pos[3];
		float at[3];

		pos[0] = 0.0f;
		pos[1] = 0.0f;
		pos[2] = 0.0f;
		fcn_00455140(h, ((char*)g_662d40), at);
		pos[1] = fcn_00451380(((char*)g_662d40), at);
		fcn_00438cb0(f->model, pos);
		fcn_004053a0(f, 0);
		f->model->owner = f;
		fcn_00438ac0(f->model, 1);
		fcn_00404a00(f, 1, "bewegung/gehen");
		f->model->x48 = 0;
		f->speed = 0.7f;
		f->target = -1;
		f->active = 1;
		f->state = 4;
		fcn_005338d0(f->model, g_14abee0[anim], 0);
	}
	return f;
}
