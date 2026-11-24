#include <ctype.h>
#include <string.h>

/* SIZE 0xc */
typedef struct Vec3 {
	float x;
	float y;
	float z;
} Vec3;

/* SIZE 0x18 */
typedef struct Pair {
	Vec3 a;
	Vec3 b;
} Pair;

/* SIZE 0x38 */
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

/* SIZE 0x1a4 */
typedef struct ModelData {
	ModelItem items[7];
	char pad188[0x14];
	int i19c;
	int i1a0;
} ModelData;

/* SIZE 0x970 */
typedef struct Model {
	char pad0[0x104];
	char* name;
	char pad108[0x96c - 0x108];
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
	Node* next;
	char pad1f4[8];
	Node* child;
	int i200;
	char pad204[0xc];
	unsigned char flags;
	unsigned char b211;
	unsigned char b212;
	char pad213;
	int i214;
	int type;
	int kind;
	int i220;
};

void __cdecl fcn_004011f0(int, unsigned char);
void __cdecl vfs_WriteCString(int, char*);
void __cdecl vfs_WriteVec3(int, float*);
void __cdecl fcn_00401320(int, int);
void __cdecl ReportClientMessage(const char*);
void __cdecl d3_WriteEventTable(int, void*);

/* ADDRESS: GOLD 0x0044a2c0 */
void __cdecl wr_object(int stream, Node* n)
{
	char buf[0x100];
	char* p;
	int kind;
	int i;
	Node* p2;

	fcn_004011f0(stream, ((unsigned char) n->b211 >> 1) & 1);
	if ((n->b211 & 2) == 0)
		goto tail;
	kind = n->type;
	if (kind == 1) {
		kind = n->kind;
		if (n->name[0] == '!')
			vfs_WriteCString(stream, n->name + 1);
		else
			vfs_WriteCString(stream, n->name);
	} else {
		vfs_WriteCString(stream, n->name);
	}
	fcn_00401320(stream, n->i200);
	fcn_00401320(stream, n->i220);
	fcn_00401320(stream, kind);
	fcn_004011f0(stream, n->type == 1);
	switch (kind) {
	case 1:
	case 4:
		fcn_004011f0(stream, (unsigned char) n->flags >> 7);
		fcn_004011f0(stream, ((unsigned char) n->flags >> 5) & 1);
		fcn_004011f0(stream, ((unsigned char) n->b211 >> 2) & 1);
		fcn_004011f0(stream, ((unsigned char) n->b212 >> 2) & 3);
		fcn_004011f0(stream, ((unsigned char) n->b212 >> 4) & 1);
		fcn_004011f0(stream, ((unsigned char) n->b212 >> 5) & 1);
		fcn_004011f0(stream, ((unsigned char) n->b212 >> 6) & 1);
		fcn_00401320(stream, n->i214);
		if (n->model != 0) {
			fcn_00401320(stream, n->model->count);
			if (n->model->count > 0) {
				strcpy(buf, n->model->name);
				p = strrchr(buf, '_');
				if (p != 0 && strlen(p) == 2 && isdigit(p[1]))
					p[0] = 0;
				vfs_WriteCString(stream, buf);
			}
		} else {
			fcn_00401320(stream, 0);
		}
	case 2:
	case 3:
		vfs_WriteVec3(stream, &n->pos.x);
		vfs_WriteVec3(stream, &n->v84.x);
		fcn_004011f0(stream, (unsigned char) n->b211 & 1);
		if (n->b211 & 1) {
			vfs_WriteVec3(stream, &n->v5c.x);
			vfs_WriteVec3(stream, &n->v90.x);
		}
		for (i = 0; i < 10; i++) {
			vfs_WriteVec3(stream, &n->pairs[i].a.x);
			vfs_WriteVec3(stream, &n->pairs[i].b.x);
		}
		break;
	case 0:
		fcn_004011f0(stream, (unsigned char) n->b211 & 1);
		fcn_00401320(stream, n->i68);
		vfs_WriteVec3(stream, &n->pos.x);
		vfs_WriteVec3(stream, &n->v5c.x);
		vfs_WriteVec3(stream, &n->v90.x);
		break;
	case 5:
	case 6:
	case 7:
	case 8:
		fcn_004011f0(stream, ((unsigned char) n->flags >> 5) & 1);
		fcn_004011f0(stream, ((unsigned char) n->b211 >> 4) & 1);
		fcn_00401320(stream, *(int*) &n->v90.x);
		fcn_00401320(stream, *(int*) &n->v90.y);
		fcn_00401320(stream, *(int*) &n->v90.z);
		vfs_WriteVec3(stream, &n->v5c.x);
		vfs_WriteVec3(stream, &n->pos.x);
		vfs_WriteVec3(stream, &n->v84.x);
		fcn_00401320(stream, n->data->i19c);
		fcn_00401320(stream, n->data->i1a0);
		for (i = 0; i < 7; i++) {
			fcn_00401320(stream, n->data->items[i].i28);
			fcn_00401320(stream, n->data->items[i].i24);
			fcn_00401320(stream, n->data->items[i].i2c);
			vfs_WriteVec3(stream, &n->data->items[i].c.x);
			vfs_WriteVec3(stream, &n->data->items[i].a.x);
			vfs_WriteVec3(stream, &n->data->items[i].b.x);
			fcn_00401320(stream, n->data->items[i].i30);
			fcn_00401320(stream, n->data->items[i].i34);
		}
		break;
	default:
		ReportClientMessage("unknown object type");
		break;
	}
tail:
	for (p2 = n->child; p2 != 0 && (p2->b211 & 2) == 0; p2 = p2->next)
		;
	fcn_004011f0(stream, p2 != 0);
	if (p2 != 0)
		wr_object(stream, p2);
	for (p2 = n->next; p2 != 0; p2 = p2->next) {
		if ((p2->flags & 1) == 1)
			continue;
		if ((p2->b211 & 2) != 0)
			break;
	}
	fcn_004011f0(stream, p2 != 0);
	if (p2 != 0)
		wr_object(stream, p2);
	d3_WriteEventTable(stream, n->event);
}
