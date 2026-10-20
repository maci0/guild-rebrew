#include <string.h>

extern char g_14ce86c;
extern char g_67d91c;
extern char g_67d91d;
extern void* g_6b5de0;

void* __cdecl fcn_0041db70(int size, char* tag);
void __cdecl fcn_0041ddd0(void* p);
void __cdecl fcn_004760c0(void* o, void* desc);
int __cdecl fcn_00610011(void* device, int width, int height, int kind, int arg, int format);

/* Texture wrapper: copies the source descriptor, derives the surface format,
 * rounds the size up to the power of two the device needs and allocates.
 * The descriptor filled by the resource callback is an inferred view. */
/* ADDRESS: GOLDTL 0x004770a0 */
int __cdecl fcn_004770a0(int* src, int flags)
{
	typedef struct TexDesc {
		int format;
		char pad[0xc];
		int width;
		int height;
	} TexDesc;

	int* tex;
	void* device;
	int width;
	int height;
	int format;
	int state;
	int rw;
	int rh;
	int n;
	int* cb;
	int* target;
	int ext;
	TexDesc desc;

	tex = (int*) fcn_0041db70(0x5c, (char*) 0x67d944);
	if (tex == 0) {
		return 0;
	}
	memcpy(tex, src, 0x5c);
	tex[0x14] = 1;
	tex[0] = flags;
	if (flags & 4) {
		tex[0x10] = 1;
	}
	format = tex[10];
	if (flags & 1) {
		*(char*) &tex[5] = 0;
		format = g_14ce86c;
	} else {
		if (*(char*) &tex[5] == 0x10) {
			format = 0x17;
		} else if (*(char*) &tex[5] == 0x18 || *(char*) &tex[5] == 0x20) {
			format = 0x15;
			*(char*) &tex[5] = 0x20;
		}
	}
	if (*(char*) &tex[5] == 0) {
		if (format != 0x17 && format != 0x19) {
			*(char*) &tex[5] = 0x20;
		} else {
			*(char*) &tex[5] = 0x10;
		}
	}
	width = tex[1];
	height = tex[2];
	rw = width;
	rh = height;
	if (g_67d91c != 0) {
		n = 0;
		do {
			if (rw <= 0) {
				break;
			}
			rw >>= 1;
			n++;
		} while (n < 0x18);
		rw = 1 << (n - 1);
		if (rw < width) {
			rw *= 2;
		}
		n = 0;
		do {
			if (rh <= 0) {
				break;
			}
			rh >>= 1;
			n++;
		} while (n < 0x18);
		rh = 1 << (n - 1);
		if (rh < height) {
			rh *= 2;
		}
	}
	if (g_67d91d != 0 || (flags & 0x10) != 0) {
		if (rw <= rh) {
			rw = rh;
		}
		rh = rw;
	}
	if (tex[0x10] != 0) {
		cb = (int*) tex[9];
		if (cb != 0) {
			(*(int (__cdecl**) (void*, TexDesc*)) (*cb + 0x20))(cb, &desc);
			tex[2] = desc.height;
			tex[1] = desc.width;
			if (desc.format == 0x16) {
				*(char*) &tex[5] = 0x20;
			} else if (desc.format == 0x17) {
				*(char*) &tex[5] = 0x10;
			}
			tex[7] = 0;
			tex[0x14] = 0;
		}
		if (tex[0x10] != 0) {
			goto done;
		}
	}
	state = 0;
	if (flags & 0x10) {
		state = 1;
		target = 0;
	} else if (flags & 0x20) {
		device = g_6b5de0;
		(*(void (__cdecl**) (void*, int, int, int, int*)) (*(int*) device + 0x6c))(device, rw, rh,
			format, &tex[9]);
		goto created;
	} else {
		state = 0;
		target = (int*) 1;
	}
	ext = state;
	fcn_00610011(g_6b5de0, rw, rh, 1, (int) &target, ext);
created:
	if (target != 0) {
		tex[8] = (int) target;
		if ((*(int (__cdecl**) (void*, int, int*)) (*target + 0x3c))(target, 0, &tex[9]) != 0) {
			fcn_0041ddd0(tex);
			return 0;
		}
	}
	ext = format;
	fcn_004760c0(tex, &ext);
	tex[0x13] = ext + 0x5c;
done:
	tex[4] = 0;
	tex[0xb] = 0;
	tex[0xc] = 0;
	tex[0xd] = src[1];
	tex[0xe] = src[2];
	return (int) tex;
}
