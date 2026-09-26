typedef struct fcn_00443900_Obj
{
	char pad000[0x1f4];
	struct fcn_00443900_Obj* next;
	struct fcn_00443900_Obj* prev;
	struct fcn_00443900_Scene* scene;
} fcn_00443900_Obj;
// SIZE 0x200

typedef struct fcn_00443900_Scene
{
	char pad00[0x80];
	fcn_00443900_Obj* head;
	fcn_00443900_Obj* tail;
	char pad88[0xa4 - 0x88];
	void* fa4;
	void* fa8;
} fcn_00443900_Scene;
// SIZE 0xac

typedef struct
{
	fcn_00443900_Scene* from;
	fcn_00443900_Scene* to;
} fcn_00443900_Ctx;
// SIZE 0x8

extern int g_67a370;
extern char* g_1043254;
extern char* g_1042538;
extern char* g_1040c74;
extern char* g_1040958;
extern char g_1042340[];
extern char g_1043060;

void __cdecl fcn_004379a0(fcn_00443900_Scene* s, fcn_00443900_Obj* o, int mask, void* fn, void* ctx);
void __cdecl fcn_004438b0(void);
void __cdecl fcn_00443030(fcn_00443900_Scene* s);

// FUNCTION: GOLDTL 0x443900
// SIZE: 507
char __cdecl fcn_00443900(fcn_00443900_Obj* o, fcn_00443900_Scene* from, fcn_00443900_Scene* to)
{
	fcn_00443900_Obj* p;
	fcn_00443900_Ctx ctx;

	if (o == 0 || from == 0 || to == 0 || o->scene != 0) {
		return 0;
	}
	if (from == to) {
		return 1;
	}
	if (from == ((fcn_00443900_Scene*)g_67a370)) {
		from->head = (*(fcn_00443900_Obj**)&g_1043254);
		from->tail = (*(fcn_00443900_Obj**)&g_1042538);
		from->fa4 = (*(void**)&g_1040c74);
		from->fa8 = (*(void**)&g_1040958);
	}
	for (p = from->head; p != &(*(fcn_00443900_Obj*)g_1042340); p = p->next) {
		if (p == o) {
			break;
		}
	}
	if (p != o) {
		return 0;
	}
	if (o->prev == &(*(fcn_00443900_Obj*)&g_1043060)) {
		from->head = o->next;
	} else {
		o->prev->next = o->next;
	}
	if (o->next == &(*(fcn_00443900_Obj*)g_1042340)) {
		from->tail = o->prev;
	} else {
		o->next->prev = o->prev;
	}
	if (from == ((fcn_00443900_Scene*)g_67a370)) {
		(*(fcn_00443900_Obj**)&g_1043254) = from->head;
		(*(fcn_00443900_Obj**)&g_1042538) = from->tail;
		(*(void**)&g_1040c74) = from->fa4;
		(*(void**)&g_1040958) = from->fa8;
	}
	ctx.from = from;
	ctx.to = to;
	fcn_004379a0(from, o, 0x3ff, (void*) fcn_004438b0, &ctx);
	if (to == ((fcn_00443900_Scene*)g_67a370)) {
		to->head = (*(fcn_00443900_Obj**)&g_1043254);
		to->tail = (*(fcn_00443900_Obj**)&g_1042538);
		to->fa4 = (*(void**)&g_1040c74);
		to->fa8 = (*(void**)&g_1040958);
	} else if (to->head == 0) {
		fcn_00443030(to);
	}
	o->next = &(*(fcn_00443900_Obj*)g_1042340);
	p = to->tail;
	p->next = o;
	o->prev = p;
	to->tail = o;
	if (to == ((fcn_00443900_Scene*)g_67a370)) {
		(*(fcn_00443900_Obj**)&g_1043254) = to->head;
		(*(fcn_00443900_Obj**)&g_1042538) = to->tail;
		(*(void**)&g_1040c74) = to->fa4;
		(*(void**)&g_1040958) = to->fa8;
	}
	return 1;
}
