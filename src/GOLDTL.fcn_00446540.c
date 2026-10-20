#include <ctype.h>
#include <string.h>

/* SIZE 0xc */
typedef struct Vec3 {
	float x;
	float y;
	float z;
} Vec3;

/* SIZE 0x18; two corner vectors per pair record. */
typedef struct Pair {
	Vec3 a;
	Vec3 b;
} Pair;

/* SIZE 0x38; per-item record inside the model data block. */
typedef struct ModelItem {
	Vec3 a;
	Vec3 b;
	Vec3 c;
	int i24;
	int i28;
	int i2c;
	int i30;
	int i34;
} ModelItem;

/* SIZE 0x1a4; model data block. */
typedef struct ModelData {
	ModelItem items[7];
	int i198;
	int i19c;
} ModelData;

/* SIZE 0x410; draw model name and count. */
typedef struct Model {
	char pad0[0x40c];
	char* name;
	char pad410[0x163c - 0x410];
	unsigned char count;
} Model;

typedef struct Node Node;

struct Node {
	char name[0x4c];
	Vec3 pos;
	char pad58[4];
	Vec3 v5c;
	int i68;
	char pad6c[0x18];
	Vec3 v84;
	Vec3 v90;
	Pair pairs[10];
	char pad18c[0x48];
	void* event;
	char pad1d8[0x10];
	ModelData* data;
	Model* model;
	char pad1f0[4];
	Node* next;
	char pad1f8[8];
	Node* child;
	int i204;
	char pad208[0xc];
	char flags;
	char b215;
	char b216;
	char pad217;
	int type;
	int kind;
	int i220;
};

void __cdecl fcn_00401210(int, unsigned char);
void __cdecl fcn_00401230(int, char*);
void __cdecl fcn_00401260(int, int);
void __cdecl fcn_004012f0(int, float*);
void __cdecl fcn_00401360(int, int);
void __cdecl fcn_0041d9e0(const char*);
void __cdecl fcn_0043b740(int, void*);

/* ADDRESS: GOLDTL 0x00446540 */
void __cdecl fcn_00446540(int stream, Node* n)
{
	char buf[0x100];
	char* p;
	char* str;
	int kind;
	int i;
	Node* p2;

	fcn_00401210(stream, (unsigned char) n->flags >> 7);
	if (n->flags >= 0)
		goto tail;
	kind = n->type;
	if (n->type == 1)
		kind = n->kind;
	if (n->type == 1 && n->name[0] == '!')
		str = n->name + 1;
	else
		str = n->name;
	fcn_00401230(stream, str);
	fcn_00401360(stream, n->i204);
	fcn_00401360(stream, n->i220);
	fcn_00401360(stream, kind);
	fcn_00401210(stream, n->type == 1);
	switch (kind) {
	case 0:
		fcn_00401210(stream, ((unsigned char) n->flags >> 6) & 1);
		fcn_00401260(stream, n->i68);
		fcn_004012f0(stream, &n->pos.x);
		fcn_004012f0(stream, &n->v5c.x);
		fcn_004012f0(stream, &n->v90.x);
		break;
	case 1:
	case 4:
		fcn_00401210(stream, ((unsigned char) n->flags >> 5) & 1);
		fcn_00401210(stream, 1);
		fcn_00401210(stream, (unsigned char) n->b215 & 1);
		fcn_00401210(stream, (unsigned char) n->b216 & 3);
		fcn_00401210(stream, ((unsigned char) n->b216 >> 2) & 1);
		fcn_00401210(stream, ((unsigned char) n->b216 >> 3) & 1);
		fcn_00401210(stream, ((unsigned char) n->b216 >> 4) & 1);
		fcn_00401360(stream, 0);
		if (n->model != 0) {
			fcn_00401360(stream, n->model->count);
			if (n->model->count != 0) {
				strcpy(buf, n->model->name);
				p = strrchr(buf, '_');
				if (p != 0 && strlen(p) == 2 && isdigit(p[1]))
					p[0] = 0;
				fcn_00401230(stream, buf);
			}
		} else {
			fcn_00401360(stream, 0);
		}
		break;
	case 2:
	case 3:
		fcn_004012f0(stream, &n->pos.x);
		fcn_004012f0(stream, &n->v84.x);
		fcn_00401210(stream, ((unsigned char) n->flags >> 6) & 1);
		if (n->flags & 0x40) {
			fcn_004012f0(stream, &n->v5c.x);
			fcn_004012f0(stream, &n->v90.x);
		}
		for (i = 0; i < 10; i++) {
			fcn_004012f0(stream, &n->pairs[i].a.x);
			fcn_004012f0(stream, &n->pairs[i].b.x);
		}
		break;
	case 5:
	case 6:
	case 7:
	case 8:
		fcn_00401210(stream, 1);
		fcn_00401210(stream, ((unsigned char) n->b215 >> 2) & 1);
		fcn_00401260(stream, *(int*) &n->v90);
		fcn_00401260(stream, *(int*) &n->v90.y);
		fcn_00401260(stream, *(int*) &n->v90.z);
		fcn_004012f0(stream, &n->v5c.x);
		fcn_004012f0(stream, &n->pos.x);
		fcn_004012f0(stream, &n->v84.x);
		fcn_00401260(stream, n->data->i198);
		fcn_00401360(stream, n->data->i19c);
		for (i = 0; i < 0x188; i += 0x38) {
			fcn_00401260(stream, *(int*) ((char*) n->data + i + 0x28));
			fcn_00401260(stream, *(int*) ((char*) n->data + i + 0x24));
			fcn_00401260(stream, *(int*) ((char*) n->data + i + 0x2c));
			fcn_004012f0(stream, (float*) ((char*) n->data + i + 0x18));
			fcn_004012f0(stream, (float*) ((char*) n->data + i));
			fcn_004012f0(stream, (float*) ((char*) n->data + i + 0xc));
			fcn_00401260(stream, *(int*) ((char*) n->data + i + 0x30));
			fcn_00401360(stream, *(int*) ((char*) n->data + i + 0x34));
		}
		break;
	default:
		fcn_0041d9e0("unknown object type");
		break;
	}
tail:
	for (p2 = n->child; p2 != 0 && p2->flags >= 0; p2 = p2->next)
		;
	fcn_00401210(stream, p2 != 0);
	if (p2 != 0)
		fcn_00446540(stream, p2);
	for (p2 = n->next; p2 != 0; p2 = p2->next) {
		if ((p2->flags & 1) == 0 && p2->flags < 0)
			break;
	}
	fcn_00401210(stream, p2 != 0);
	if (p2 != 0)
		fcn_00446540(stream, p2);
	fcn_0043b740(stream, n->event);
}
