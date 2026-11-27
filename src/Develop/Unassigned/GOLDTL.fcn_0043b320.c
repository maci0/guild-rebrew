extern int g_1042a08;
extern int g_10432a8;
extern int g_1042a04;
extern int d3_RenderedVertexCount;


void __cdecl fcn_0043ad20(void*, void*);
void __cdecl d3_UpdateScene(void*, void*, int, int);

void __cdecl d3_RenderFrame(void* a1, void* a2, int a3)
{
	fcn_0043ad20(a1, a2);
	g_1042a08 = 0;
	g_10432a8 = 0;
	g_1042a04 = 0;
	d3_RenderedVertexCount = 0;
	d3_UpdateScene(a1, a2, a3, 1);
}
