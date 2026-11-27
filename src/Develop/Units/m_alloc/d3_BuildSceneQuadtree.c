


// SIZE 0x8
typedef struct Link {
	char* e;
	struct Link* next;
} Link;

extern char g_6b89a0[];
extern int g_67a370;

void* __cdecl m_PoolAlloc(void*, int, int);
void __cdecl m_pool_free(void*, void*);
void __cdecl d3_VisitSceneObjects(int, int, int, void*, void*);
char __cdecl d3_CollectActiveMeshObjects(char*, char*);
void __cdecl d3_SplitQuadtreeNode(char*, int, int, int);

char* __cdecl d3_BuildSceneQuadtree(int node, int mask, int split_limit, int max_depth)
{
	char* ctx;
	Link* l;

	ctx = (char*) m_PoolAlloc(g_6b89a0, 0x48, 0x40);
	*(int*) (ctx + 0x44) = mask;
	*(int*) (ctx + 0x34) = split_limit;
	*(int*) (ctx + 0x38) = max_depth;
	d3_VisitSceneObjects(g_67a370, node, mask, d3_CollectActiveMeshObjects, ctx);
	d3_SplitQuadtreeNode(ctx, split_limit, 1, max_depth);
	if (*(int*) (ctx + 0x30) == 0) {
		m_pool_free(g_6b89a0, ctx);
		return 0;
	}
	for (l = *(Link**) (ctx + 0x3c); l != 0; l = l->next) {
		*(int*) (*(char**) (l->e + 0x1ec) + 0xb0) = -1;
	}
	return ctx;
}
