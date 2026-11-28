extern char* g_1041d00;
extern char* g_6b86ec;
extern char* g_6b86e0;
extern char* d3_DirectionalLightList;
extern char* d3_SceneLightListHead;
extern int g_6b86f8;
extern int g_6b86f0;
extern int g_6b86f4;
extern float d3_UnitAxisVectors[3];

unsigned char __cdecl d3_UpdateSceneObjectLodAndBounds(char* o);
void __cdecl d3_TransformDirectionToRef(char* o, char* a, float* v, char* m);
void __cdecl d3_TransformPointToRef(char* o, char* a, char* v, char* m);

/* ADDRESS: GOLDTL 0x00450d40 */
char __cdecl d3_ClassifySceneLightNode(char* node, char* cam)
{
	if (*(int*) (node + 0x218) == 4) {
		if (!(d3_UpdateSceneObjectLodAndBounds(node) & 0x40)) {
			*(char**) (node + 0x1f0) = g_6b86ec;
			g_6b86ec = node;
			return 1;
		}
		*(char**) (node + 0x1f0) = g_1041d00;
		g_1041d00 = node;
		return 1;
	}
	if (*(int*) (node + 0x218) == 8) {
		if ((node[0x215] & 1) && *(float*) (node + 0x94) > 0.0f && g_6b86f8 < 4) {
			*(char**) (node + 0x1f0) = g_6b86e0;
			g_6b86e0 = node;
			g_6b86f8++;
		}
		return 1;
	}
	if (*(int*) (node + 0x218) == 7) {
		if (*(float*) (node + 0x94) > 0.0f && !(node[0x215] & 4)) {
			d3_TransformDirectionToRef(node, cam, d3_UnitAxisVectors, node + 0x1d8);
			*(char**) (node + 0x1f0) = d3_DirectionalLightList;
			d3_DirectionalLightList = node;
			g_6b86f0++;
		}
		return 1;
	}
	if (*(float*) (node + 0x94) > 0.0f) {
		d3_TransformPointToRef(node, cam, node + 0x4c, node + 0x1d8);
		*(char**) (node + 0x1f0) = d3_SceneLightListHead;
		d3_SceneLightListHead = node;
		g_6b86f4++;
	}
	return 1;
}
