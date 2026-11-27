

void __cdecl d3_RenderScene(int, int);
void __cdecl d3_UpdateScene(int, int, int, int);

void __cdecl d3_RenderFrame(int pass, int overlay, int mode)
{
	d3_RenderScene(pass, overlay);
	d3_UpdateScene(pass, overlay, mode, 1);
}
