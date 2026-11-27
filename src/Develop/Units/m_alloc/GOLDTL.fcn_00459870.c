void* __cdecl m_alloc(unsigned int size, const char* source);
void* __cdecl d3_LoadOrReuseTexture(int a0, unsigned int a1, int a2, int a3);
void __cdecl d3_LoadTextureSurfaceTl(void* a0);

/* ADDRESS: GOLDTL 0x00459870 */
unsigned int* __cdecl d3_CreateSkyLayer(char* a0, unsigned int a1, int a2, unsigned int a3, unsigned int a4, unsigned int a5, unsigned int a6, unsigned int a7)
{
	unsigned int* node;
	int v3;
	int* tail;
	int* nx;

	node = 0;
	if (a0 != 0 && a2 != 0) {
		node = (unsigned int*) m_alloc(0x2c, (const char*) 0x67bcc4);
		if (node != 0) {
			*node = a4;
			node[1] = a5;
			node[2] = 0;
			node[6] = a6;
			node[5] = a7;
			*(char*) ((char*) node + 0x28) = (char) a3;
			*(char*) ((char*) node + 0x29) = (char) a3;
			node[3] = 0x3f800000;
			node[4] = 0;
			node[9] = a3;
			v3 = (int) d3_LoadOrReuseTexture(a2, a3, 0, 0);
			node[7] = v3;
			if (v3 != 0)
				d3_LoadTextureSurfaceTl((void*) v3);
			if (a1 == 0) {
				node[8] = 0;
				tail = (int*) *(int*) (a0 + 0x24);
				if (tail != 0) {
					while ((nx = (int*) *(int*) ((char*) tail + 0x20)) != 0)
						tail = nx;
					*(int**) ((char*) tail + 0x20) = (int*) node;
				} else {
					*(int**) (a0 + 0x24) = (int*) node;
				}
			} else {
				node[8] = *(unsigned int*) (a0 + 0x24);
				*(int**) (a0 + 0x24) = (int*) node;
			}
		}
	}
	return node;
}
