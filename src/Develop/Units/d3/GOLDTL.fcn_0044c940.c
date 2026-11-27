typedef struct {
	int res_x;              /* 0x00 */
	int res_y;              /* 0x04 */
	int res_depth;          /* 0x08 */
	int use_triple;         /* 0x0c */
	int windowed;           /* 0x10 */
	int max_polys;          /* 0x14 */
	int max_textures;       /* 0x18 */
	int max_mipmaps;        /* 0x1c */
	int z_buffer_depth;     /* 0x20 */
	int static_tex_fourcc;  /* 0x24 */
	int pad28;              /* 0x28 */
	int floortex_divider;   /* 0x2c */
	int pad30[3];           /* 0x30 */
	float window_width;     /* 0x3c */
	float window_height;    /* 0x40 */
	float window_x_offset;  /* 0x44 */
	float window_y_offset;  /* 0x48 */
	float window_near_z;    /* 0x4c */
	float window_far_z;     /* 0x50 */
	float viewdistance;     /* 0x54 */
} D3dRegCfg_44c940;
// SIZE 0x58

int __cdecl io_OpenRegistryKey(const char* sub, int mode);
int __cdecl io_ReadRegistryDword(int h, const char* name);
int __cdecl io_TryReadRegistryDword(int h, const char* name, int* out);
int __cdecl io_ReadRegistryString(int h, const char* name, char* out);
int __cdecl io_TryReadRegistryFloat(int h, const char* name, float* out);
void __cdecl io_CloseRegistryKey(int h);
int __cdecl fcn_0065f220(const char* a, const char* b);

#include "Develop/DieGildeAddOn/game/game_data.h"


/* Reads the Direct3D screen and window options from the registry over the
 * defaults. */
/* ADDRESS: GOLDTL 0x0044c940 */
char __cdecl d3_ReadRegistryConfig(D3dRegCfg_44c940* cfg, const char* key, D3dRegCfg_44c940* def)
{
	int v;
	int n;
	int h;
	char mode[0x100];

	if (cfg != def) {
		n = sizeof(D3dRegCfg_44c940);
		/* align-up block copy: recorded C probes did not emit it
		 * (archived docs/codegen-walls.md 6b) */
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
		v = io_ReadRegistryDword(h, "d3_registry_version");
		if (v != 3) {
			io_CloseRegistryKey(h);
		} else {
			io_TryReadRegistryDword(h, "d3_screen_res_x", &cfg->res_x);
			io_TryReadRegistryDword(h, "d3_screen_res_y", &cfg->res_y);
			io_TryReadRegistryDword(h, "d3_screen_res_depth", &cfg->res_depth);
			if (io_TryReadRegistryDword(h, "d3d_windowed", &v) != 0) {
				cfg->windowed = v;
			}
			if (io_TryReadRegistryDword(h, "d3d_use_triple", &v) != 0) {
				cfg->use_triple = v;
			}
			io_TryReadRegistryDword(h, "d3_max_polys", &cfg->max_polys);
			io_TryReadRegistryDword(h, "d3_max_textures", &cfg->max_textures);
			io_TryReadRegistryDword(h, "d3d_max_mipmaps", &cfg->max_mipmaps);
			io_TryReadRegistryDword(h, "d3d_floortex_divider", &cfg->floortex_divider);
			io_TryReadRegistryDword(h, "d3d_z_buffer_depth", &cfg->z_buffer_depth);
			io_TryReadRegistryDword(h, "d3d_static_texture_fourcc", &cfg->static_tex_fourcc);
			if (io_ReadRegistryString(h, "d3io_LODMode", mode) != 0) {
				if (fcn_0065f220(mode, "d3io_LOD_SWITCH") == 0) {
					d3_LODMode = 1;
				} else if (fcn_0065f220(mode, "d3io_LOD_LOW") == 0) {
					d3_LODMode = 2;
				} else if (fcn_0065f220(mode, "d3io_LOD_HIGH") == 0) {
					d3_LODMode = 4;
				}
			}
			io_TryReadRegistryFloat(h, "d3_window_width", &cfg->window_width);
			io_TryReadRegistryFloat(h, "d3_window_height", &cfg->window_height);
			io_TryReadRegistryFloat(h, "d3_window_x_offset", &cfg->window_x_offset);
			io_TryReadRegistryFloat(h, "d3_window_y_offset", &cfg->window_y_offset);
			io_TryReadRegistryFloat(h, "d3_window_near_z", &cfg->window_near_z);
			io_TryReadRegistryFloat(h, "d3_window_far_z", &cfg->window_far_z);
			io_TryReadRegistryFloat(h, "d3_window_viewdistance", &cfg->viewdistance);
			cfg->viewdistance = 0.0015625f * ((float) (unsigned int) cfg->res_x * 512.0f);
			io_CloseRegistryKey(h);
			return 1;
		}
	}
	return 0;
}
