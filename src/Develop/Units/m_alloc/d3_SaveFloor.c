// SIZE 0x60
typedef struct {
	char pad0[0x54];
	unsigned char f54;
	char pad55[9];
	unsigned char f5e;
	char pad5f[1];
} FLOOR_MODEL_HDR;

// SIZE 0x158
typedef struct {
	FLOOR_MODEL_HDR* model;
	int pad4;
	char b8;
	char b9;
	unsigned char flags;
	char padb;
	int c;
	int d;
	int e;
	int v18[4];
	int v28[4];
	char pad38[0x154 - 0x38];
	int f154;
} FLOOR_PART_REC;

extern char g_6b5c60[];

void* __cdecl m_alloc(int size, const char* tag);
void __cdecl m_FreeTracked(void* p);
void __cdecl vfs_WriteByte(void* s, char v);
void __cdecl vfs_WriteCString(void* s, void* str);
void __cdecl vfs_WriteInt32(void* s, int v);
void __cdecl vfs_WriteVec3(void* s, void* v);
void __cdecl vfs_WriteVec4(void* s, int* v);
void __cdecl vfs_WriteInt(void* s, int v);
void __cdecl vfs_WriteArray(void* s, int a, int b, void* data);

#define PART(i) ((*(FLOOR_PART_REC**) (o + 0x7da0))[i])


/* ADDRESS: GOLDTL 0x004469e0 */
void __cdecl d3_SaveFloor(void* s, char* o)
{
	void* buf;
	int i;

	vfs_WriteCString(s, o + 0x7da4);
	if (o[0x7da4] != 0) {
		vfs_WriteInt(s, *(int*) o);
		vfs_WriteArray(s, *(int*) o, *(int*) o, *(void**) (o + 0x10));
		buf = m_alloc(*(int*) o * *(int*) o * 4, "!d3:LOfs");
		vfs_WriteArray(s, *(int*) o * 4, *(int*) o, buf);
		m_FreeTracked(buf);
		vfs_WriteByte(s, *(int*) (o + 0x18) != 0);
		if (*(int*) (o + 0x18) != 0) {
			vfs_WriteInt(s, *(unsigned char*) (o + 0x8035));
			if (*(unsigned char*) (o + 0x8035) > 0) {
				vfs_WriteArray(s, *(int*) o, *(int*) o, *(void**) (o + 0x18));
			}
			for (i = 0; i < *(unsigned char*) (o + 0x8035); i++) {
				if (PART(i).model != 0) {
					vfs_WriteCString(s, PART(i).model);
					vfs_WriteByte(s, 0);
					vfs_WriteByte(s, PART(i).model->f5e & 0xf);
					vfs_WriteByte(s, PART(i).model->f54 & 1);
				} else {
					vfs_WriteCString(s, g_6b5c60);
					vfs_WriteByte(s, 0);
					vfs_WriteByte(s, 0);
					vfs_WriteByte(s, 0);
				}
				vfs_WriteByte(s, PART(i).b8);
				vfs_WriteByte(s, PART(i).b9);
				vfs_WriteByte(s, PART(i).flags & 1);
				vfs_WriteByte(s, (PART(i).flags >> 1) & 1);
				vfs_WriteInt32(s, PART(i).e);
				vfs_WriteInt32(s, PART(i).c);
				vfs_WriteInt32(s, PART(i).d);
				vfs_WriteVec4(s, PART(i).v18);
				vfs_WriteVec4(s, PART(i).v28);
				vfs_WriteInt(s, PART(i).f154);
			}
		}
	} else {
		vfs_WriteByte(s, 0);
	}
	vfs_WriteCString(s, o + 0x7de4);
	if (o[0x7de4] != 0) {
		vfs_WriteArray(s, *(int*) o, *(int*) o, *(void**) (o + 0x14));
	}
	for (i = 0; i < 8; i++) {
		vfs_WriteCString(s, o + 0x7e24 + i * 0x40);
	}
	vfs_WriteInt32(s, *(int*) (o + 0x60));
	vfs_WriteInt32(s, *(int*) (o + 0x84));
	vfs_WriteVec3(s, o + 0x50);
}
