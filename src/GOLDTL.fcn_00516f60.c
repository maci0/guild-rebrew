// FUNCTION: GOLDTL 0x00516f60
// SIZE: 561

// SIZE 0x230
typedef struct Obj {
	char pad0[0x2c];
	int owner;
	char pad30[4];
	struct Obj* body;
	char pad38[0x50];
	int model;
	char pad8c[0x140];
	int visible;
	char pad1d0[0x5c];
	struct Obj* rider;
} Obj;

// SIZE 0x21c
typedef struct {
	char pad0[0x184];
	Obj* obj;
	char pad188[0x94];
} Entity;

// SIZE 0xa4
typedef struct {
	char pad0[0x88];
	float zoom;
	char pos[0x14];
	int angle;
} View;

// SIZE 0x8c
typedef struct {
	char pad0[0x84];
	char pos[4];
	int angle;
} Camera;

typedef void (__cdecl* Notify)(void*, int, void*, int);

// SIZE 0x218
typedef struct {
	char pad0[0x210];
	Notify notify;
	char arg[4];
} Hook;

// SIZE 0x3cc
typedef struct {
	char pad0[0x3c8];
	Hook* hook;
} Scene;

extern char g_7f4c00;
extern Entity g_7f4ca0[768];
extern int g_6b8010;
extern Camera* g_6b8014;
extern unsigned short g_774970;
extern char g_773dd4;
extern Scene* g_67a370;
extern int g_6b8300;
extern int g_77666c;
extern char g_6b8061;
extern int g_6791c8;
extern float g_67a964;
extern char g_6b859b;

int __cdecl fcn_00500e20(char*);
View* __cdecl fcn_00509570(Entity*);
void __cdecl fcn_00438b40(Camera*, char*);
void __cdecl fcn_0052ac60(float);
void __cdecl fcn_00438cb0(Camera*, char*);
int __cdecl fcn_00413190(int);
void __cdecl fcn_00402aa0(Obj*);
void __cdecl fcn_00402a00(Obj*, int);
void __cdecl fcn_004fdcf0(Entity*);
void __cdecl fcn_00437ac0(Scene*, int, int, void (__cdecl*)(void));
void __cdecl fcn_00516550(void);
void __cdecl fcn_005165b0(void);
void __cdecl fcn_00516be0(void);
void __cdecl fcn_00516040(void);
void __cdecl fcn_00516de0(int, int);
void __cdecl fcn_0052a960(char*);
void __cdecl fcn_00443230(int);

void __cdecl fcn_00516f60(void)
{
	int mode;
	View* v;
	int i;

	mode = fcn_00500e20(&g_7f4c00);
	if (g_6b8010 != 0) {
		return;
	}
	v = fcn_00509570(&g_7f4ca0[g_774970]);
	if (v != 0 && v->zoom != -1.0f) {
		fcn_00438b40(g_6b8014, v->pos);
		fcn_0052ac60(v->zoom);
		g_6b8014->angle = v->angle;
		fcn_00438cb0(g_6b8014, g_6b8014->pos);
	} else {
		fcn_0052ac60(0.33f);
	}
	for (i = 0; i < 768; i++) {
		if (g_7f4ca0[i].obj != 0 && fcn_00413190(g_7f4ca0[i].obj->model) == 0 && g_7f4ca0[i].obj->owner == -1) {
			if (g_7f4ca0[i].obj->body->visible == 0
				|| (g_7f4ca0[i].obj->rider != 0 && g_7f4ca0[i].obj->rider->visible == 0)) {
				fcn_00402aa0(g_7f4ca0[i].obj);
			}
			fcn_00402a00(g_7f4ca0[i].obj, 1);
			fcn_004fdcf0(&g_7f4ca0[i]);
		}
	}
	if (mode == 1) {
		g_773dd4 = 1;
	} else if (mode == 0) {
		g_773dd4 = 0;
	} else if (mode == 2) {
		g_773dd4 = 2;
	} else if (mode == 3) {
		g_773dd4 = 3;
	}
	fcn_00437ac0(g_67a370, 0, 0xe0, fcn_00516550);
	fcn_00437ac0(g_67a370, 0, 0xc0, fcn_005165b0);
	fcn_00516be0();
	if (g_67a370 != 0 && g_67a370->hook != 0 && g_67a370->hook->notify != 0) {
		g_67a370->hook->notify(g_67a370, 4, g_67a370->hook->arg, 0);
	}
	fcn_00516040();
	fcn_00516de0(g_6b8300, 0);
	g_6b8061 = 1;
	g_6791c8 = 0;
	g_67a964 = 1.0f - (unsigned char) g_77666c * 0.01f;
	fcn_0052a960(&g_7f4c00);
	if (g_6b859b != 0) {
		fcn_00443230(0);
	} else {
		fcn_00443230(1);
	}
}
