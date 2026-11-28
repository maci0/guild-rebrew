extern int d3_TextureBank;
extern char* g_1040958;
extern int d3_ActiveScene;
extern volatile int gm_GameTicks;
extern char g_1040640[];
int __cdecl d3_LoadOrReuseTexture(char* name, int flags, int a3, int a4);
void __cdecl d3_LoadTextureSurfaceTl(int h);
void* __cdecl m_alloc(unsigned int size, const char* tag);
void __cdecl d3_InitSceneObject(char* o);

/* ADDRESS: GOLDTL 0x004524e0 */
/* ADDRESS: GOLDDE 0x00447d90 */
char* __cdecl d3_CreateParticleSystem(unsigned int entryCount, char* assetName, int a2, float a3, int a4, int a5)
{
	char* s;
	int stamp;
	int assetHandle;
	int i;

	s = 0;
	if (a3 > 0.0 && entryCount > 0) {
		assetHandle = d3_LoadOrReuseTexture(assetName, a2, 0, 0);
		if (assetHandle != 0) {
			d3_LoadTextureSurfaceTl(assetHandle);
			s = m_alloc(0x31c, "d3_par:ParticleSystem");
			*(int*) (s + 0xdc) = assetHandle;
			i = (assetHandle - d3_TextureBank) / 0x70;
			*(int*) (s + 0xd8) = entryCount;
			*(float*) (s + 0xe4) = a3;
			*(int*) (s + 0xe0) = i;
			*(int*) (s + 0x310) = a5;
			*(char**) (s + 0x28) = m_alloc(*(unsigned int*) (s + 0xd8) * 0x54, "d3_par:Particles");
			*(char**) (s + 0x2c) = m_alloc(*(unsigned int*) (s + 0xd8) * 4, "d3_par:TexIndices");
			*(char**) (s + 0x30) = m_alloc(*(unsigned int*) (s + 0xd8) * 4, "d3_par:PartIndices");
			*(int*) (s + 0) = 0;
			*(int*) (s + 4) = 0;
			*(int*) (s + 8) = 0;
			*(int*) (s + 0xc) = 0;
			*(int*) (s + 0x10) = 0;
			*(int*) (s + 0x14) = 0;
			*(int*) (s + 0x18) = 0;
			*(int*) (s + 0x1c) = 0;
			*(int*) (s + 0x24) = 0;
			*(int*) (s + 0x20) = 0;
			stamp = gm_GameTicks;
			for (i = 0; i < *(int*) (s + 0xd8); i++) {
		
				*(int*) (*(char**) (s + 0x28) + i * 0x54 + 0x38) = 0;
				*(int*) (*(char**) (s + 0x28) + i * 0x54 + 0x3c) = 0;
				*(int*) (*(char**) (s + 0x28) + i * 0x54 + 0x40) = 0;
				*(int*) (*(char**) (s + 0x28) + i * 0x54 + 0) = 0;
				*(int*) (*(char**) (s + 0x28) + i * 0x54 + 4) = 0;
				*(int*) (*(char**) (s + 0x28) + i * 0x54 + 8) = 0;
				*(int*) (*(char**) (s + 0x28) + i * 0x54 + 0x30) = stamp;
				*(int*) (*(char**) (s + 0x28) + i * 0x54 + 0x48) = *(int*) (s + 0xe4);
				*(unsigned char*) (*(char**) (s + 0x28) + i * 0x54 + 0x51) &= 0xfe;
				*(unsigned char*) (*(char**) (s + 0x28) + i * 0x54 + 0x50) = 0;
				*(int*) (*(char**) (s + 0x28) + i * 0x54 + 0x4c) = -1;
			}
			*(unsigned char*) (s + 0x2ff) |= 2;
			d3_InitSceneObject(s + 0xe8);
			*(int*) (s + 0x2e4) = a4;
			*(int*) (s + 0x2f4) = d3_ActiveScene;
			*(char**) (s + 0x318) = g_1040958;
			*(char**) (s + 0x314) = g_1040640;
			*(char**) (g_1040958 + 0x314) = s;
			g_1040958 = s;
		}
	}
	return s;
}
