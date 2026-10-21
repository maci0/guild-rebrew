/* Reconstruction of GOLDTL 0x0060c32e.
 * Native ABI is thiscall: self in ecx, two stack arguments, ret 8. MSVC 6 C
 * rejects __thiscall, so __fastcall plus a dead second parameter keeps self
 * in ecx and both arguments on the stack. Byte twin of 0x0060a93d; only the
 * renderer hook differs (0x0060a93d calls 0x005f587f). */
#include <stdlib.h>

typedef struct SkinObj60c32e {
	void* vt;
	char pad04[0x2c];
	unsigned count;
} SkinObj60c32e;

typedef struct SkinVt60c32e {
	void* pad00[20];
	int (__stdcall* m50)(void*, void*, void*);
} SkinVt60c32e;

typedef struct Skin60c32e {
	char pad0[0xc];
	int stride;
	int* widths;
	int* rows_int;
	float* rows_float;
	SkinObj60c32e* source;
	char pad20[0xc];
	unsigned char flags;
} Skin60c32e;

int __cdecl fcn_005f63e5(void);

/* The native body keeps an EBP frame under the locked profile. */
#pragma optimize("y", off)

/* ADDRESS: GOLDTL 0x0060c32e */
int __fastcall fcn_0060c32e(Skin60c32e* self, int unused, unsigned a1, int a2)
{
	unsigned i;
	unsigned j;
	int k;
	int hr;
	int loaded;
	int* buf;
	float sum;
	double scale;
	float* base;

	(void) unused;
	if ((self->flags & 4) == 0) {
		hr = fcn_005f63e5();
		if (hr != 0)
			return hr;
	}
	if (self->source->count <= 0)
		return 0;
	buf = 0;
	loaded = 0;
	for (i = 0; i < (unsigned) self->source->count; i++) {
		if ((unsigned) self->widths[i] <= a1)
			continue;
		k = (int) i;
		if (loaded) {
			k = buf[i];
		} else if (a2 != 0) {
			buf = malloc(self->source->count * 4);
			if (buf == 0)
				return (int) 0x8007000e;
			hr = ((SkinVt60c32e*) self->source->vt)->m50(self->source, (void*) a2, buf);
			if (hr != 0) {
				free(buf);
				return hr;
			}
			loaded = 1;
			k = buf[i];
		}
		base = self->rows_float + self->stride * k;
		sum = 0.0f;
		j = 0;
		while (j < a1) {
			sum = sum + base[j];
			j++;
		}
		scale = 1.0 / sum;
		j = 0;
		while (j < a1) {
			base[j] = (float) (base[j] * scale);
			j++;
		}
		while (j < (unsigned) self->widths[k]) {
			base[j] = 0.0f;
			j++;
		}
	}
	if (!loaded)
		return 0;
	i = 0;
	while (i < (unsigned) self->source->count) {
		if (buf[i] != (int) i && self->widths[i] != 0) {
			k = buf[i];
			j = 0;
			while (j < (unsigned) self->widths[i]) {
				self->rows_int[self->stride * k + (int) j] = self->rows_int[self->stride * (int) i + (int) j];
				self->rows_float[self->stride * k + (int) j] = self->rows_float[self->stride * (int) i + (int) j];
				j++;
			}
		}
		i++;
	}
	free(buf);
	return 0;
}
