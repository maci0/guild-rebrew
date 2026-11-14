#include <stdlib.h>
#include <string.h>
#include "Develop/Units/d3/d3_d3d.h"
#include "client_scene_resources.h"

unsigned char __cdecl fcn_004611a0(SCENE_RESOURCE*, unsigned char);
void __cdecl fcn_004205c0(void*, void*, void*, void*);
void __cdecl fcn_00420140(void*, void*);
void* __cdecl m_alloc(int, const char*);
void __cdecl m_FreeTracked(void*);

/* ADDRESS: GOLD 0x00416980 */
void __cdecl fcn_00416980(void)
{
	unsigned int descriptor[31];
	char palette[4096];
	SCENE_RESOURCE* texture;
	void* surface;
	void* palette_object;
	unsigned int* mip;
	float* temporary;
	float* current;
	float* above;
	float* below;
	char* q;
	int n;
	int level;
	int size;
	int area;
	int i;
	int pass;
	int row;
	int column;
	int samples;
	double sum;
	double maximum;
	float minimum;
	float negative_minimum;
	float scale;
	float value;
	texture = fcn_004605b0("snow_256_ns", 0, 0, 0);
	palette_object = 0;
	if (texture != 0) {
		fcn_004611a0(texture, 1);
		fcn_00460e40(texture, 0);
		surface = texture->com60;
		if (surface == 0) {
			goto release_texture;
		}
		q = (char*) descriptor;
		n = sizeof(descriptor);
		__asm {
			mov edi, q
			mov ebx, n
			xor eax, eax
			lea ecx, [edi+edi*2]
			and ecx, 3
			sub ebx, ecx
			jle clear_tail
			rep stosb
			mov ecx, ebx
			and ebx, 3
			shr ecx, 2
			rep stosd
		clear_tail:
			add ecx, ebx
			rep stosb
		}
		descriptor[0] = 124;
		surface = texture->com60;
		d3d_LastResult = ((int (__stdcall*)(void*, void*, void*, int, void*)) (*(int**) surface)[25])
			(surface, 0, descriptor, 0x11, 0);
		if (d3d_LastResult != 0) {
			fcn_00418e90("D:\\develop\\Units\\d3_tools\\d3_tools.c", 0xea5,
				"snow_tex->surf->lpVtbl->Lock(snow_tex->surf, 0, &snow_ddsd, DDLOCK_WAIT|DDLOCK_READONLY, NULL)");
			if (d3d_LastResult != 0) {
				goto release_texture;
			}
		}
		if (descriptor[19] & 0x20) {
			surface = texture->com60;
			d3d_LastResult = ((int (__stdcall*)(void*, void**)) (*(int**) surface)[20])(surface, &palette_object);
			if (d3d_LastResult != 0) {
				fcn_00418e90("D:\\develop\\Units\\d3_tools\\d3_tools.c", 0xeae,
					"snow_tex->surf->lpVtbl->GetPalette(snow_tex->surf, &lppal)");
				if (d3d_LastResult != 0) {
					surface = texture->com60;
					d3d_LastResult = ((int (__stdcall*)(void*, void*)) (*(int**) surface)[32])(surface, 0);
					if (d3d_LastResult != 0) {
						fcn_00418e90("D:\\develop\\Units\\d3_tools\\d3_tools.c", 0xeb2,
							"snow_tex->surf->lpVtbl->Unlock(snow_tex->surf, NULL)");
					}
					goto release_texture;
				}
			}
			d3d_LastResult = ((int (__stdcall*)(void*, int, int, int, void*)) (*(int**) palette_object)[4])
				(palette_object, 0, 0, 256, palette);
			if (d3d_LastResult != 0) {
				fcn_00418e90("D:\\develop\\Units\\d3_tools\\d3_tools.c", 0xeb8,
					"lppal->lpVtbl->GetEntries(lppal, 0, 0, 256, pal)");
			}
		}
		goto source_ready;
	}
	goto allocate_source;
release_texture:
	fcn_0045fbb0(texture);
	texture = 0;
allocate_source:
	descriptor[0] = 124;
	descriptor[3] = 256;
	descriptor[2] = 256;
	descriptor[18] = 32;
	descriptor[19] = 32;
	descriptor[20] = 0;
	descriptor[21] = 0;
	descriptor[22] = 0;
	descriptor[23] = 0;
	descriptor[24] = 0;
	descriptor[25] = 0;
	descriptor[4] = 256;
	descriptor[9] = (unsigned int) m_alloc(65536, "d3t:snow_ddsd");
	if (descriptor[9] == 0) { return; }
source_ready:
	mip = (unsigned int*) 0x14665a0;
	mip[0] = 124;
	mip[3] = 256;
	mip[2] = 256;
	mip[18] = 32;
	mip[19] = 32;
	mip[20] = 0;
	mip[21] = 8;
	mip[22] = 0;
	mip[23] = 0;
	mip[24] = 0;
	mip[25] = 0;
	mip[4] = 256;
	mip[9] = (unsigned int) m_alloc(65536, "d3t:SnowMipMap8");
	if (mip[9] == 0) { return; }
	fcn_004205c0(mip, palette, descriptor, palette);
	for (level = 0, mip = (unsigned int*) 0x14661c0; (int) mip < 0x14665a0; level++, mip += 31) {
		size = 1 << level;
		mip[0] = 124;
		mip[3] = size;
		mip[2] = size;
		memcpy(mip + 18, (void*) 0x14665e8, 32);
		mip[4] = size;
		mip[9] = (unsigned int) m_alloc(size * size, "d3t:SnowMipMap8");
		if (mip[9] == 0) { return; }
		fcn_00420140(mip, (unsigned int*) 0x14665a0);
	}
	mip = (unsigned int*) 0x1466e80;
	mip[0] = 124;
	mip[3] = 256;
	mip[2] = 256;
	memcpy(mip + 18, (void*) 0xfe79ec, 32);
	mip[4] = 512;
	mip[9] = (unsigned int) m_alloc(131072, "d3t:SnowMipMap16");
	if (mip[9] == 0) { return; }
	fcn_004205c0(mip, palette, descriptor, palette);
	for (level = 0, mip = (unsigned int*) 0x1466aa0; (int) mip < 0x1466e80; level++, mip += 31) {
		size = 1 << level;
		mip[0] = 124;
		mip[3] = size;
		mip[2] = size;
		memcpy(mip + 18, (void*) 0x1466ec8, 32);
		mip[4] = size * 2;
		mip[9] = (unsigned int) m_alloc(size * size * 2, "d3t:SnowMipMap16");
		if (mip[9] == 0) { return; }
		fcn_00420140(mip, (unsigned int*) 0x1466e80);
	}
	mip = (unsigned int*) 0x14672e0;
	mip[0] = 124;
	mip[3] = 256;
	mip[2] = 256;
	mip[18] = 32;
	mip[19] = 64;
	mip[20] = 0;
	mip[21] = 32;
	mip[22] = 0xff0000;
	mip[23] = 0xff00;
	mip[24] = 0xff;
	mip[25] = 0;
	mip[4] = 1024;
	mip[9] = (unsigned int) m_alloc(262144, "d3t:SnowMipMap32");
	if (mip[9] == 0) { return; }
	fcn_004205c0(mip, palette, descriptor, palette);
	for (level = 0, mip = (unsigned int*) 0x1466f00; (int) mip < 0x14672e0; level++, mip += 31) {
		size = 1 << level;
		mip[0] = 124;
		mip[3] = size;
		mip[2] = size;
		memcpy(mip + 18, (void*) 0x1467328, 32);
		mip[4] = size * 4;
		mip[9] = (unsigned int) m_alloc(size * size * 4, "d3t:SnowMipMap32");
		if (mip[9] == 0) { return; }
		fcn_00420140(mip, (unsigned int*) 0x14672e0);
	}
	if (texture != 0) {
		surface = texture->com60;
		d3d_LastResult = ((int (__stdcall*)(void*, void*)) (*(int**) surface)[32])(surface, 0);
		if (d3d_LastResult != 0) {
			fcn_00418e90("D:\\develop\\Units\\d3_tools\\d3_tools.c", 0xf36,
				"snow_tex->surf->lpVtbl->Unlock(snow_tex->surf, NULL)");
		}
		fcn_0045fbb0(texture);
	} else {
		m_FreeTracked((void*) descriptor[9]);
		descriptor[9] = 0;
	}
	temporary = (float*) m_alloc(262144, "d3t:SnowDitherTemp");
	if (temporary == 0) { return; }
	for (level = 0, mip = (unsigned int*) 0x1466640; (int) mip < 0x1466a9c; level++, mip += 31) {
		size = 1 << level;
		area = size * size;
		for (i = 0; i < area; i++) { temporary[i] = (float) (rand() & 255); }
		for (pass = 4; pass != 0; pass--) {
			current = temporary;
			above = temporary - size;
			below = temporary + size;
			for (row = 0; row < size; row++) {
				for (column = 0; column < size; column++) {
					sum = *current;
					samples = 1;
					if (column > 0) { sum += current[-1]; samples = 2; }
					if (column < size - 1) { sum += current[1]; samples++; }
					if (row > 0) { sum += *above; samples++; }
					if (row < size - 1) { sum += *below; samples++; }
					*current++ = (float) (sum / samples);
					above++;
					below++;
				}
			}
		}
		minimum = 1.0e35f;
		maximum = -1.0e35f;
		for (i = 0; i < area; i++) {
			if (temporary[i] < minimum) { minimum = temporary[i]; }
			if (maximum < temporary[i]) { maximum = temporary[i]; }
		}
		negative_minimum = -minimum;
		scale = (float) (255.0f / (maximum - minimum));
		for (i = 0; i < area; i++) {
			value = (float) (((double) negative_minimum + temporary[i]) * scale);
			if (0.0f > value) { value = 0.0f; }
			else if (!(value < 255.0f)) { value = 255.0f; }
			else if (!(0.0f <= value)) { value = 0.0f; }
			temporary[i] = value;
		}
		mip[0] = 124;
		mip[3] = size;
		mip[2] = size;
		mip[18] = 32;
		mip[21] = 8;
		mip[4] = size;
		mip[9] = (unsigned int) m_alloc(area, "d3t:SnowDither");
		if (mip[9] == 0) { return; }
		for (i = 0; i < area; i++) { ((unsigned char*) mip[9])[i] = (unsigned char) temporary[i]; }
	}
	m_FreeTracked(temporary);
}
