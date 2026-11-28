extern int d3_RenderedFaceCount;
extern int d3_FrameFaceCount;
extern int d3_FrameVertexCount;
extern int d3_RenderedVertexCount;

void __cdecl d3_RenderScene(void*, void*);
void __cdecl d3_UpdateScene(void*, void*, int, int);

#if defined(REBREW_GOLD)
/* ADDRESS: GOLD 0x0043e680 */
void __cdecl d3_RenderFrame(int pass, int overlay, int mode)
{
	d3_RenderScene((void*) pass, (void*) overlay);
	d3_UpdateScene((void*) pass, (void*) overlay, mode, 1);
}
#else
/* ADDRESS: GOLDTL 0x0043b320 */
/* ADDRESS: GOLDDE 0x004340e0 */
void __cdecl d3_RenderFrame(void* a1, void* a2, int a3)
{
	d3_RenderScene(a1, a2);
	d3_RenderedFaceCount = 0;
	d3_FrameFaceCount = 0;
	d3_FrameVertexCount = 0;
	d3_RenderedVertexCount = 0;
	d3_UpdateScene(a1, a2, a3, 1);
}
#endif
