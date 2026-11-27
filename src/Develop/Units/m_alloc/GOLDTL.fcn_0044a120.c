struct D3_MESH_COM_IFACE;

// SIZE 0xc
struct D3_MESH_COM_VTBL {
	long (__stdcall* QueryInterface)(struct D3_MESH_COM_IFACE*, void*, void**);
	unsigned long (__stdcall* AddRef)(struct D3_MESH_COM_IFACE*);
	unsigned long (__stdcall* Release)(struct D3_MESH_COM_IFACE*);
};

// SIZE 0x4
struct D3_MESH_COM_IFACE {
	struct D3_MESH_COM_VTBL* vtbl;
};

extern unsigned long g_14ce728;

void __cdecl m_FreeTracked(void*);
void __cdecl d3_ReleaseTexture(char*);

/* ADDRESS: GOLDTL 0x0044a120 */
void __cdecl d3_ReleaseAGFMesh(char* e)
{
	char* p;
	int i;

	if (--*(int*) (e + 0x1e0) > 0) {
		return;
	}
	*(int*) (*(int*) (e + 0x1f8) + 0x1fc) = *(int*) (e + 0x1fc);
	*(int*) (*(int*) (e + 0x1fc) + 0x1f8) = *(int*) (e + 0x1f8);
	i = 0;
	if (*(int*) (e + 0x1e4) > 0) {
		do {
			p = *(char**) (*(int*) (e + 0x284) + i * 4);
			if (p != 0) {
				d3_ReleaseTexture(p);
			}
			i++;
		} while (i < *(int*) (e + 0x1e4));
	}
	m_FreeTracked(*(void**) (e + 0x200));
	*(int*) (e + 0x200) = 0;
	m_FreeTracked(*(void**) (e + 0x284));
	*(int*) (e + 0x284) = 0;
	p = *(char**) (e + 0x264);
	if (p != 0) {
		g_14ce728 = (*(struct D3_MESH_COM_IFACE**) &p)->vtbl->Release((struct D3_MESH_COM_IFACE*) p);
		*(int*) (e + 0x264) = 0;
	}
	m_FreeTracked(*(void**) (e + 0x27c));
	*(int*) (e + 0x27c) = 0;
	m_FreeTracked(*(void**) (e + 0x280));
	*(int*) (e + 0x280) = 0;
	m_FreeTracked(*(void**) (e + 0x288));
	*(int*) (e + 0x288) = 0;
	m_FreeTracked(*(void**) (e + 0x28c));
	*(int*) (e + 0x28c) = 0;
	if ((*(unsigned char*) (e + 0x2a1) & 2) != 0) {
		p = *(char**) (e + 0x268);
		if (p != 0) {
			g_14ce728 = (*(struct D3_MESH_COM_IFACE**) &p)->vtbl->Release((struct D3_MESH_COM_IFACE*) p);
			*(int*) (e + 0x268) = 0;
		}
		m_FreeTracked(*(void**) (e + 0x294));
		*(int*) (e + 0x294) = 0;
		m_FreeTracked(*(void**) (e + 0x298));
		*(int*) (e + 0x298) = 0;
		m_FreeTracked(*(void**) (e + 0x29c));
		*(int*) (e + 0x29c) = 0;
	}
	m_FreeTracked(e);
}
