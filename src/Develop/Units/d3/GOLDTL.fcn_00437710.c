typedef struct {
	unsigned char mirrors : 1;
	unsigned char beautiful : 1;
	unsigned char shadows : 3;
	unsigned char pad05 : 3;
	char pad1[3];
	int fill;
} D3_DISPLAY_CONFIG;
// SIZE 0x8

int __cdecl io_OpenRegistryKey(const char* sub, int mode);
int __cdecl io_ReadRegistryDword(int h, const char* name);
int __cdecl io_TryReadRegistryDword(int h, const char* name, int* out);
int __cdecl io_ReadRegistryString(int h, const char* name, char* out);
void __cdecl io_CloseRegistryKey(int h);
int __cdecl _strcmpi(const char* a, const char* b);


/* Reads the Direct3D display options from the registry over the defaults. */
/* ADDRESS: GOLDTL 0x00437710 */
char __cdecl d3_LoadDisplayConfigFromRegistry(D3_DISPLAY_CONFIG* cfg, const char* key, D3_DISPLAY_CONFIG* def)
{
	int v;
	int n;
	int h;
	char mode[0x100];

	if (cfg != def) {
		n = sizeof(D3_DISPLAY_CONFIG);
		/*
		 * TODO: replace this inline-asm copy with proper C once a spelling is
		 * found; recorded C fill/copy probes did not emit the prelude
		 * (archived docs/msvc6-allocator.md Finding 19).
		 */
		__asm {
			mov edi, cfg
			mov esi, def
			mov ebx, n
			lea ecx, [edi+edi*2]
			and ecx, 3
			sub ebx, ecx
			jle short L1
			rep movsb
			mov ecx, ebx
			and ebx, 3
			shr ecx, 2
			rep movsd
		L1:
			add ecx, ebx
			rep movsb
		}
	}
	h = io_OpenRegistryKey(key, 1);
	if (h != -1) {
		v = io_ReadRegistryDword(h, "d3d_registry_version");
		if (v != 3) {
			io_CloseRegistryKey(h);
		} else {
			if (io_TryReadRegistryDword(h, "d3d_beautiful", &v) != 0) {
				cfg->beautiful = v;
			}
			if (io_ReadRegistryString(h, "d3d_fillmode", mode) != 0) {
				if (_strcmpi(mode, "D3DFILL_POINT") == 0) {
					cfg->fill = 1;
				} else if (_strcmpi(mode, "D3DFILL_WIREFRAME") == 0) {
					cfg->fill = 2;
				} else if (_strcmpi(mode, "D3DFILL_SOLID") == 0) {
					cfg->fill = 3;
				} else {
					cfg->fill = 3;
				}
			}
			if (io_TryReadRegistryDword(h, "d3_mirrors", &v) != 0) {
				cfg->mirrors = v;
			}
			if (io_TryReadRegistryDword(h, "d3d_shadows", &v) != 0) {
				cfg->shadows = v;
			}
			io_CloseRegistryKey(h);
			return 1;
		}
	}
	return 0;
}
