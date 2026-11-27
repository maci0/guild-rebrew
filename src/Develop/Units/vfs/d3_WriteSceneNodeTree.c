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
	char pad188[0x10];
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
	unsigned char flags;
	unsigned char b215;
	unsigned char b216;
	char pad217;
	int type;
	int kind;
	int i220;
};

void __cdecl vfs_WriteByte(int, unsigned char);
void __cdecl vfs_WriteCString(int, char*);
void __cdecl vfs_WriteInt32(int, int);
void __cdecl vfs_WriteVec3(int, float*);
void __cdecl vfs_WriteInt(int, int);
void __cdecl ReportClientMessage(const char*);
void __cdecl d3_WriteEventTable(int, void*);

/* ADDRESS: GOLDTL 0x00446540 */
void __cdecl d3_WriteSceneNodeTree(int stream, Node* n)
{
	char buf[0x100];
	char* p;
	int kind;
	int i;
	Node* p2;

	vfs_WriteByte(stream, (unsigned char) n->flags >> 7);
	if (((unsigned char) n->flags >> 7) == 0)
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
	vfs_WriteInt(stream, n->i204);
	vfs_WriteInt(stream, n->i220);
	vfs_WriteInt(stream, kind);
	vfs_WriteByte(stream, n->type == 1);
	switch (kind) {
	case 1:
	case 4:
		vfs_WriteByte(stream, ((unsigned char) n->flags >> 5) & 1);
		vfs_WriteByte(stream, 1);
		vfs_WriteByte(stream, (unsigned char) n->b215 & 1);
		vfs_WriteByte(stream, (unsigned char) n->b216 & 3);
		vfs_WriteByte(stream, ((unsigned char) n->b216 >> 2) & 1);
		vfs_WriteByte(stream, ((unsigned char) n->b216 >> 3) & 1);
		vfs_WriteByte(stream, ((unsigned char) n->b216 >> 4) & 1);
		vfs_WriteInt(stream, 0);
		if (n->model != 0) {
			vfs_WriteInt(stream, n->model->count);
			if (n->model->count > 0) {
				strcpy(buf, n->model->name);
				p = strrchr(buf, '_');
				if (p != 0 && strlen(p) == 2 && isdigit(p[1]))
					p[0] = 0;
				vfs_WriteCString(stream, buf);
			}
		} else {
			vfs_WriteInt(stream, 0);
		}
		/* Native flow continues into the 2/3 body: no break in the original. */
	case 2:
	case 3:
		vfs_WriteVec3(stream, &n->pos.x);
		vfs_WriteVec3(stream, &n->v84.x);
		vfs_WriteByte(stream, ((unsigned char) n->flags >> 6) & 1);
		if (n->flags & 0x40) {
			vfs_WriteVec3(stream, &n->v5c.x);
			vfs_WriteVec3(stream, &n->v90.x);
		}
		for (i = 0; i < 10; i++) {
			vfs_WriteVec3(stream, &n->pairs[i].a.x);
			vfs_WriteVec3(stream, &n->pairs[i].b.x);
		}
		break;
	case 0:
		vfs_WriteByte(stream, ((unsigned char) n->flags >> 6) & 1);
		vfs_WriteInt32(stream, n->i68);
		vfs_WriteVec3(stream, &n->pos.x);
		vfs_WriteVec3(stream, &n->v5c.x);
		vfs_WriteVec3(stream, &n->v90.x);
		break;
	case 5:
	case 6:
	case 7:
	case 8:
		vfs_WriteByte(stream, 1);
		vfs_WriteByte(stream, ((unsigned char) n->b215 >> 2) & 1);
		vfs_WriteInt32(stream, *(int*) &n->v90);
		vfs_WriteInt32(stream, *(int*) &n->v90.y);
		vfs_WriteInt32(stream, *(int*) &n->v90.z);
		vfs_WriteVec3(stream, &n->v5c.x);
		vfs_WriteVec3(stream, &n->pos.x);
		vfs_WriteVec3(stream, &n->v84.x);
		vfs_WriteInt32(stream, n->data->i198);
		vfs_WriteInt(stream, n->data->i19c);
		for (i = 0; i < 0x188; i += 0x38) {
			vfs_WriteInt32(stream, *(int*) ((char*) n->data + i + 0x28));
			vfs_WriteInt32(stream, *(int*) ((char*) n->data + i + 0x24));
			vfs_WriteInt32(stream, *(int*) ((char*) n->data + i + 0x2c));
			vfs_WriteVec3(stream, (float*) ((char*) n->data + i + 0x18));
			vfs_WriteVec3(stream, (float*) ((char*) n->data + i));
			vfs_WriteVec3(stream, (float*) ((char*) n->data + i + 0xc));
			vfs_WriteInt32(stream, *(int*) ((char*) n->data + i + 0x30));
			vfs_WriteInt(stream, *(int*) ((char*) n->data + i + 0x34));
		}
		break;
	default:
		ReportClientMessage("unknown object type");
		break;
	}
tail:
	for (p2 = n->child; p2 != 0 && ((unsigned char) p2->flags >> 7) == 0; p2 = p2->next)
		;
	vfs_WriteByte(stream, p2 != 0);
	if (p2 != 0)
		d3_WriteSceneNodeTree(stream, p2);
	for (p2 = n->next; p2 != 0; p2 = p2->next) {
		if ((p2->flags & 1) == 1)
			continue;
		if (((unsigned char) p2->flags >> 7) != 0)
			break;
	}
	vfs_WriteByte(stream, p2 != 0);
	if (p2 != 0)
		d3_WriteSceneNodeTree(stream, p2);
	d3_WriteEventTable(stream, n->event);
}
