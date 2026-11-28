


extern double g_665e30;

typedef struct {
	float x;
	int y;
	int z;
} D3_VEC3_BUILD;
// SIZE 0xc

void __cdecl d3_AnimateObjectTransform(char*, char*, D3_VEC3_BUILD*, int, int);

/* ADDRESS: GOLDDE 0x00559d10 */
void __cdecl d3_AnimateBuildStage(char* obj, char* buildAction)
{
	D3_VEC3_BUILD offset;

	offset.x = *(float*) (obj + 0x84) + g_665e30;
	offset.y = *(int*) (obj + 0x88);
	offset.z = *(int*) (obj + 0x8c);
	d3_AnimateObjectTransform(obj, obj + 0x4c, &offset, 0x46, 0x20);
	buildAction[0xd0]--;
}
