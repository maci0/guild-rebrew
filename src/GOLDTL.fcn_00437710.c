typedef struct {
	unsigned char mirrors : 1;
	unsigned char beautiful : 1;
	unsigned char shadows : 3;
	unsigned char pad05 : 3;
	char pad1[3];
	int fill;
} D3dCfg_437710;
// SIZE 0x8

int __cdecl fcn_004112b0(const char* sub, int mode);
int __cdecl fcn_00411350(int h, const char* name);
int __cdecl fcn_00411390(int h, const char* name, int* out);
int __cdecl fcn_004113d0(int h, const char* name, char* out);
void __cdecl fcn_00411340(int h);
int __cdecl _strcmpi(const char* a, const char* b);

/* ADDRESS: GOLDTL 0x00437710 */

/* Reads the Direct3D display options from the registry over the defaults. */
char __cdecl fcn_00437710(D3dCfg_437710* cfg, const char* key, D3dCfg_437710* def)
{
	int v;
	int n;
	int h;
	char mode[0x100];

	if (cfg != def) {
		n = sizeof(D3dCfg_437710);
		/*
		 * TODO: replace this inline-asm copy with proper C once a spelling is
		 * found; no msvc6 C memset/memcpy form emits the prelude
		 * (docs/msvc6-allocator.md Finding 19).
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
	h = fcn_004112b0(key, 1);
	if (h != -1) {
		v = fcn_00411350(h, "d3d_registry_version");
		if (v != 3) {
			fcn_00411340(h);
		} else {
			if (fcn_00411390(h, "d3d_beautiful", &v) != 0) {
				cfg->beautiful = v;
			}
			if (fcn_004113d0(h, "d3d_fillmode", mode) != 0) {
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
			if (fcn_00411390(h, "d3_mirrors", &v) != 0) {
				cfg->mirrors = v;
			}
			if (fcn_00411390(h, "d3d_shadows", &v) != 0) {
				cfg->shadows = v;
			}
			fcn_00411340(h);
			return 1;
		}
	}
	return 0;
}
