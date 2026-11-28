

extern int d3_ActiveScene;

void __cdecl d3_UnlinkFromRenderList(char*);
void __cdecl d3_ReleaseTexture(int);
void __cdecl m_FreeTracked(void*);

void __cdecl d3_FreeMeshObject(char* o)
{
	char* owner;

	owner = *(char**) (o + 0x2f4);
	if (owner == ((char*)d3_ActiveScene)) {
		*(char**) (*(char**) (o + 0x314) + 0x318) = *(char**) (o + 0x318);
		*(char**) (*(char**) (o + 0x318) + 0x314) = *(char**) (o + 0x314);
		if (o == *(char**) (owner + 0xa4)) {
			*(char**) (owner + 0xa4) = *(char**) (o + 0x314);
		}
		if (o == *(char**) (owner + 0xa8)) {
			*(char**) (owner + 0xa8) = *(char**) (o + 0x314);
		}
	} else {
		d3_UnlinkFromRenderList(o);
	}
	if (*(int*) (o + 0xdc) != 0) {
		d3_ReleaseTexture(*(int*) (o + 0xdc));
	}
	m_FreeTracked(*(void**) (o + 0x28));
	*(void**) (o + 0x28) = 0;
	m_FreeTracked(*(void**) (o + 0x2c));
	*(void**) (o + 0x2c) = 0;
	m_FreeTracked(*(void**) (o + 0x30));
	*(void**) (o + 0x30) = 0;
	m_FreeTracked(o);
}
