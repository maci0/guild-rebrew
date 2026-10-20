extern int g_6b7fdc;
extern char* g_6b85c0[];

char* __cdecl fcn_00449ac0(char*, char*);
void* __cdecl fcn_0042ff50(const char*, const char*, void*);
int __cdecl fcn_004011f0(void*, void*);
void* __cdecl m_alloc(unsigned int, const char*);
void __cdecl m_FreeTracked(void*);
char* __cdecl fcn_004011a0(void*, char*);
void __cdecl CloseVfsStream(void*);

/* ADDRESS: GOLDTL 0x0044b340 */
void __cdecl fcn_0044b340(char* name, char** tex, int* width, int* height)
{
	void* f;
	int w;
	int h;
	int y;
	int x;

	if (name != 0) {
		f = fcn_00449ac0(name, ".TXS");
		if (f != 0) {
			f = fcn_0042ff50(f, "rb", g_6b7fdc);
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
						for (y = 0; y < *width; y++) {
							for (x = 0; x < *height; x++) {
								fcn_004011a0(f, *tex + (y * *height + x) * 0x40);
							}
						}
					}
				}
				CloseVfsStream(f);
			}
		}
	}
}
