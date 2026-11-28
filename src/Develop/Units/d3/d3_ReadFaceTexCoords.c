


// SIZE 0x38
typedef struct Face {
	float uv[3][2];
	int idx[3];
	int rest[5];
} Face;

int __cdecl vfs_ReadDword(void* stream, void* dst);

/* ADDRESS: GOLDDE 0x00443b10 */
void __cdecl d3_ReadFaceTexCoords(void* r, char* o)
{
	float t;
	int i;

	for (i = 0; i < 3; i++) {
		vfs_ReadDword(r, &(*(Face**) (o + 0x20))[*(int*) (o + 0x18)].uv[i][0]);
	}
	for (i = 0; i < 3; i++) {
		vfs_ReadDword(r, &(*(Face**) (o + 0x20))[*(int*) (o + 0x18)].uv[i][1]);
	}
	for (i = 0; i < 3; i++) {
		vfs_ReadDword(r, &t);
	}
}
