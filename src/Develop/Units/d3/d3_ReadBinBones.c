

// SIZE 0x58
typedef struct Bone {
	char name[0x40];
	float a[3];
	float b[3];
} Bone;

int __cdecl fcn_004011f0(void* stream, void* dst);
int __cdecl vfs_ReadByte(void* stream, void* dst);
char* __cdecl vfs_ReadCString(void* stream, char* text);
void __cdecl vfs_ReadVec3(void* stream, void* dst);

void __cdecl d3_ReadBinBones(void* stream, char* obj)
{
	int n;
	char c;
	int i;

	n = 0;
	fcn_004011f0(stream, &n);
	*(int*) (obj + 0x34) = n;
	for (i = 0; i < n; i++) {
		vfs_ReadByte(stream, &c);
		vfs_ReadCString(stream, ((Bone*) (obj + 0x38))[i].name);
		vfs_ReadByte(stream, &c);
		vfs_ReadVec3(stream, ((Bone*) (obj + 0x38))[i].a);
		vfs_ReadByte(stream, &c);
		vfs_ReadVec3(stream, ((Bone*) (obj + 0x38))[i].b);
	}
}
