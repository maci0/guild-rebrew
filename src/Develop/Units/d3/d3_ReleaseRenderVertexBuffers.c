

typedef struct {
	int (*f0)(void);
	int (*f1)(void);
	int (__stdcall* release)(void*);
} D3_VBUF_VTBL;
// SIZE 0xc

/* ADDRESS: GOLDDE 0x00416440 */
void __cdecl d3_ReleaseRenderVertexBuffers(void)
{
	void** p;

	p = (void**) *(int*) 0x6b5cb4;
	if (p != 0) {
		*(int*) 0x14ce728 = ((D3_VBUF_VTBL*) p[0])->release(p);
		*(int*) 0x6b5cb4 = 0;
	}
	p = (void**) *(int*) 0x6b5cb8;
	if (p != 0) {
		*(int*) 0x14ce728 = ((D3_VBUF_VTBL*) p[0])->release(p);
		*(int*) 0x6b5cb8 = 0;
	}
}
