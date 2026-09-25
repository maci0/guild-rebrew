// FUNCTION: GOLD 0x51adb0
// SIZE: 624
// FUNCTION: GOLDTL 0x0051fd50
// SIZE: 615

// SIZE 0x3d6
typedef struct {
	char pad0[0x3d5];
	unsigned char hidden;
} Model;

// SIZE 0x219
typedef struct {
	char pad0[0x4c];
	char pos[0x10];
	char pad5c[0x28];
	char rot[0xc];
	char pad90[0x188];
	unsigned char state;
} Body;

// SIZE 0x6c
typedef struct Link {
	char pad0[0x68];
	char* name;
} Link;

// SIZE 0x1a0
typedef struct {
	int id;
	char pad4[4];
	char name[0x20];
	char pad28[4];
	int x2c;
	int x30;
	Body* body;
	char pad38[0x2c];
	char* title;
	char pad68[8];
	Link* home;
	Link* work;
	char pad78[0x10];
	Model* model;
	unsigned short flags;
	char pad8e[0xa2];
	char x130[0x40];
	char x170[0x30];
} Figure;

unsigned int __cdecl fcn_00430910(void*, int, int, void*);

int __cdecl fcn_0051fd50(Figure* o, int value, void* f)
{
	float pos[3];
	float rot[4];

	if (fcn_00430910(o, 4, 1, f) <= 0) {
		return 0;
	}
	if (fcn_00430910(o->name, 0x20, 1, f) <= 0) {
		return 0;
	}
	if (fcn_00430910(&o->x2c, 4, 1, f) <= 0) {
		return 0;
	}
	if (fcn_00430910(&o->x30, 4, 1, f) <= 0) {
		return 0;
	}
	if (fcn_00430910(&o->flags, 2, 1, f) <= 0) {
		return 0;
	}
	if (fcn_00430910(o->x170, 0x30, 1, f) <= 0) {
		return 0;
	}
	if (fcn_00430910(o->x130, 0x40, 1, f) <= 0) {
		return 0;
	}
	if (o->model != 0 && o->model->hidden == 0) {
		if (fcn_00430910(o->body->pos, 0x10, 1, f) <= 0) {
			return 0;
		}
		if (fcn_00430910(o->body->rot, 0xc, 1, f) <= 0) {
			return 0;
		}
	} else {
		pos[0] = 0.0f;
		pos[1] = 0.0f;
		pos[2] = 0.0f;
		rot[0] = 0.0f;
		rot[1] = 0.0f;
		rot[2] = 0.0f;
		rot[3] = 0.0f;
		if (fcn_00430910(pos, 0x10, 1, f) <= 0) {
			return 0;
		}
		if (fcn_00430910(rot, 0xc, 1, f) <= 0) {
			return 0;
		}
	}
	if (fcn_00430910(&o->body->state, 1, 1, f) <= 0) {
		return 0;
	}
	if (fcn_00430910(&value, 4, 1, f) <= 0) {
		return 0;
	}
	if (o->title != 0) {
		if (fcn_00430910(o->title, 0x40, 1, f) <= 0) {
			return 0;
		}
	} else {
		char empty[0x40] = "";

		if (fcn_00430910(empty, 0x40, 1, f) <= 0) {
			return 0;
		}
	}
	if (o->work != 0 && o->work != o->home && o->work->name != 0) {
		if (fcn_00430910(o->work->name, 1, 0x40, f) != 0x40) {
			return 0;
		}
	} else {
		char none[0x40] = "";

		if (fcn_00430910(none, 1, 0x40, f) != 0x40) {
			return 0;
		}
	}
	return 1;
}
