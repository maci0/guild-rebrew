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

int __cdecl fcn_004112b0(const char* sub, int mode);
int __cdecl fcn_00411350(int h, const char* name);
int __cdecl fcn_00411390(int h, const char* name, int* out);
int __cdecl fcn_004113d0(int h, const char* name, char* out);
int __cdecl fcn_00411490(int h, const char* name, float* out);
void __cdecl fcn_00411340(int h);
int __cdecl fcn_0065f220(const char* a, const char* b);

extern int g_67ac90;

/* ADDRESS: GOLDTL 0x0044c940 */

/* Reads the Direct3D screen and window options from the registry over the
 * defaults. */
char __cdecl fcn_0044c940(D3dRegCfg_44c940* cfg, const char* key, D3dRegCfg_44c940* def)
{
	int v;
	int n;
	int h;
	char mode[0x100];

	if (cfg != def) {
		n = sizeof(D3dRegCfg_44c940);
		/* align-up block copy: no msvc6 C spelling emits it
		 * (docs/codegen-walls.md 6b) */
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
		v = fcn_00411350(h, "d3_registry_version");
		if (v != 3) {
			fcn_00411340(h);
		} else {
			fcn_00411390(h, "d3_screen_res_x", &cfg->res_x);
			fcn_00411390(h, "d3_screen_res_y", &cfg->res_y);
			fcn_00411390(h, "d3_screen_res_depth", &cfg->res_depth);
			if (fcn_00411390(h, "d3d_windowed", &v) != 0) {
				cfg->windowed = v;
			}
			if (fcn_00411390(h, "d3d_use_triple", &v) != 0) {
				cfg->use_triple = v;
			}
			fcn_00411390(h, "d3_max_polys", &cfg->max_polys);
			fcn_00411390(h, "d3_max_textures", &cfg->max_textures);
			fcn_00411390(h, "d3d_max_mipmaps", &cfg->max_mipmaps);
			fcn_00411390(h, "d3d_floortex_divider", &cfg->floortex_divider);
			fcn_00411390(h, "d3d_z_buffer_depth", &cfg->z_buffer_depth);
			fcn_00411390(h, "d3d_static_texture_fourcc", &cfg->static_tex_fourcc);
			if (fcn_004113d0(h, "d3io_LODMode", mode) != 0) {
				if (fcn_0065f220(mode, "d3io_LOD_SWITCH") == 0) {
					g_67ac90 = 1;
				} else if (fcn_0065f220(mode, "d3io_LOD_LOW") == 0) {
					g_67ac90 = 2;
				} else if (fcn_0065f220(mode, "d3io_LOD_HIGH") == 0) {
					g_67ac90 = 4;
				}
			}
			fcn_00411490(h, "d3_window_width", &cfg->window_width);
			fcn_00411490(h, "d3_window_height", &cfg->window_height);
			fcn_00411490(h, "d3_window_x_offset", &cfg->window_x_offset);
			fcn_00411490(h, "d3_window_y_offset", &cfg->window_y_offset);
			fcn_00411490(h, "d3_window_near_z", &cfg->window_near_z);
			fcn_00411490(h, "d3_window_far_z", &cfg->window_far_z);
			fcn_00411490(h, "d3_window_viewdistance", &cfg->viewdistance);
			cfg->viewdistance = 0.0015625f * ((float) (unsigned int) cfg->res_x * 512.0f);
			fcn_00411340(h);
			return 1;
		}
	}
	return 0;
}
