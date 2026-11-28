typedef struct D3_SCENE_OBJ
{
	char pad000[0x1f4];
	struct D3_SCENE_OBJ* next;
	struct D3_SCENE_OBJ* prev;
	struct D3_SCENE_CTX* scene;
} D3_SCENE_OBJ;
// SIZE 0x200

typedef struct D3_SCENE_CTX
{
	char pad00[0x80];
	D3_SCENE_OBJ* head;
	D3_SCENE_OBJ* tail;
	char pad88[0xa4 - 0x88];
	void* fa4;
	void* fa8;
} D3_SCENE_CTX;
// SIZE 0xac

typedef struct
{
	D3_SCENE_CTX* from;
	D3_SCENE_CTX* to;
} D3_SCENE_MOVE_CTX;
// SIZE 0x8

extern int d3_ActiveScene;
#include "Develop/DieGildeAddOn/game/game_data.h"
extern char g_1043060;

void __cdecl d3_VisitSceneObjects(D3_SCENE_CTX* s, D3_SCENE_OBJ* o, int mask, void* fn, void* ctx);
void __cdecl d3_TransferObjectSceneCallback(void);
void __cdecl d3_InitSceneLevel(D3_SCENE_CTX* s);

/* ADDRESS: GOLDTL 0x00443900 */
/* ADDRESS: GOLDDE 0x0043bd50 */
char __cdecl d3_MoveObjectToScene(D3_SCENE_OBJ* o, D3_SCENE_CTX* from, D3_SCENE_CTX* to)
{
	D3_SCENE_OBJ* p;
	D3_SCENE_MOVE_CTX ctx;

	if (o == 0 || from == 0 || to == 0 || o->scene != 0) {
		return 0;
	}
	if (from == to) {
		return 1;
	}
	if (from == ((D3_SCENE_CTX*)d3_ActiveScene)) {
		from->head = (*(D3_SCENE_OBJ**)&d3_ObjectListHead);
		from->tail = (*(D3_SCENE_OBJ**)&g_1042538);
		from->fa4 = (*(void**)&d3_SceneRenderListHead);
		from->fa8 = (*(void**)&g_1040958);
	}
	for (p = from->head; p != &(*(D3_SCENE_OBJ*)d3_SceneObjectSentinel); p = p->next) {
		if (p == o) {
			break;
		}
	}
	if (p != o) {
		return 0;
	}
	if (o->prev == &(*(D3_SCENE_OBJ*)&g_1043060)) {
		from->head = o->next;
	} else {
		o->prev->next = o->next;
	}
	if (o->next == &(*(D3_SCENE_OBJ*)d3_SceneObjectSentinel)) {
		from->tail = o->prev;
	} else {
		o->next->prev = o->prev;
	}
	if (from == ((D3_SCENE_CTX*)d3_ActiveScene)) {
		(*(D3_SCENE_OBJ**)&d3_ObjectListHead) = from->head;
		(*(D3_SCENE_OBJ**)&g_1042538) = from->tail;
		(*(void**)&d3_SceneRenderListHead) = from->fa4;
		(*(void**)&g_1040958) = from->fa8;
	}
	ctx.from = from;
	ctx.to = to;
	d3_VisitSceneObjects(from, o, 0x3ff, (void*) d3_TransferObjectSceneCallback, &ctx);
	if (to == ((D3_SCENE_CTX*)d3_ActiveScene)) {
		to->head = (*(D3_SCENE_OBJ**)&d3_ObjectListHead);
		to->tail = (*(D3_SCENE_OBJ**)&g_1042538);
		to->fa4 = (*(void**)&d3_SceneRenderListHead);
		to->fa8 = (*(void**)&g_1040958);
	} else if (to->head == 0) {
		d3_InitSceneLevel(to);
	}
	o->next = &(*(D3_SCENE_OBJ*)d3_SceneObjectSentinel);
	p = to->tail;
	p->next = o;
	o->prev = p;
	to->tail = o;
	if (to == ((D3_SCENE_CTX*)d3_ActiveScene)) {
		(*(D3_SCENE_OBJ**)&d3_ObjectListHead) = to->head;
		(*(D3_SCENE_OBJ**)&g_1042538) = to->tail;
		(*(void**)&d3_SceneRenderListHead) = to->fa4;
		(*(void**)&g_1040958) = to->fa8;
	}
	return 1;
}
