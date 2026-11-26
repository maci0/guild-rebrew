


extern int g_6b6f3c;
void __cdecl fcn_0041bdc0(void);
int __cdecl d3_AllocOctreeNodes(void);
void __cdecl d3_FreeOctreeNodes(void);
int __cdecl fcn_0041bf90(void* dst, int n);
void __cdecl fcn_0041c290(int a);
void __cdecl d3_AssignOctreePalette(int a, int b);
int __cdecl fcn_0041c470(void* dst, void* src, int w, int h, int pitch);
void __cdecl d3_CopyOctreePalette(int a);

int __cdecl d3_QuantizeImageOctree(void* dst, void* src, int w, int h, int mode, int pitch, int fmt)
{
	if (g_6b6f3c == 0) {
		g_6b6f3c = 1;
		fcn_0041bdc0();
	}
	if (!d3_AllocOctreeNodes()) {
		d3_FreeOctreeNodes();
		return 0;
	}
	if (!fcn_0041bf90(dst, w * h)) {
		d3_FreeOctreeNodes();
		return 0;
	}
	fcn_0041c290(mode);
	d3_AssignOctreePalette(0, 0);
	if (!fcn_0041c470(dst, src, w, h, pitch)) {
		d3_FreeOctreeNodes();
		return 0;
	}
	d3_FreeOctreeNodes();
	d3_CopyOctreePalette(fmt);
	return 1;
}
