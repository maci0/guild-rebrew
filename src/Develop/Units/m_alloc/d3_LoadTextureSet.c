extern int vfs_RootDir;
extern char g_6b85c0[];

char* __cdecl d3_AppendVfsAssetPath(char*, char*);
void* __cdecl vfs_Tfopen(const char*, const char*, void*);
int __cdecl fcn_004011f0(void*, void*);
void* __cdecl m_alloc(unsigned int, const char*);
void __cdecl m_FreeTracked(void*);
char* __cdecl vfs_ReadCString(void*, char*);
void __cdecl CloseVfsStream(void*);

/* ADDRESS: GOLDTL 0x0044b340 */
void __cdecl d3_LoadTextureSet(char* name, char** tex, int* width, int* height)
{
	void* f;
	int w;
	int h;



	if (name != 0) {
		f = d3_AppendVfsAssetPath(name, ".TXS");
		if (f != 0) {
			f = vfs_Tfopen(f, "rb", vfs_RootDir);
			if (f != 0) {
				fcn_004011f0(f, &w);
				if (w == 0x23f209ae) {
					fcn_004011f0(f, &w);
					fcn_004011f0(f, &h);
					if (w > 0 && h > 0) {
						if (*tex != 0) {
							m_FreeTracked(*tex);
							*tex = 0;
						}
						*tex = (char*) m_alloc(w * h * 0x40, "d3_io:LoadtextureSet");
						*width = w;
						*height = h;
						for (w = 0; w < *width; w++) {
							for (h = 0; h < *height; h++) {
								vfs_ReadCString(f, *tex + (w * *height + h) * 0x40);
							}
						}
					}
				}
				CloseVfsStream(f);
			}
		}
	}
}
