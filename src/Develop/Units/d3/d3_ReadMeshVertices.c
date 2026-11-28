


// SIZE 0x18
typedef struct Vert {
	float x;
	float y;
	float z;
	float rest[3];
} Vert;

int __cdecl vfs_ReadDword(void* stream, void* dst);

void __cdecl d3_ReadMeshVertices(void* r, char* o)
{
	int i;

	for (i = 0; i < *(int*) (o + 0x24); i++) {
		vfs_ReadDword(r, &(*(Vert**) (o + 0x30))[*(int*) (o + 0x28)].x);
		vfs_ReadDword(r, &(*(Vert**) (o + 0x30))[*(int*) (o + 0x28)].y);
		vfs_ReadDword(r, &(*(Vert**) (o + 0x30))[*(int*) (o + 0x28)].z);
		(*(int*) (o + 0x28))++;
	}
}
