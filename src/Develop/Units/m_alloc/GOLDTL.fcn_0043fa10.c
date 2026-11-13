#include <string.h>

extern char g_6b5c60[];
extern int g_1041d08;
extern float g_6628cc;
extern int g_6b7fdc;

char* __cdecl m_alloc(int, char*);
void __cdecl fcn_0042f420(int, int, char*);
unsigned char __cdecl fcn_00401590(char*, int*, int*, int);
char __cdecl fcn_00401650(char*, unsigned char*, unsigned char*, int);
void __cdecl fcn_0043f7e0(int*, char*, int);
void __cdecl fcn_0043f6b0(int*);
void __cdecl fcn_0043bcf0(int*);
int __cdecl sprintf(char*, const char*, ...);

/* Load one terrain patch: derive the two file names under boden/, read the
 * height and texture maps, clone or load the water maps and build the patch
 * object the renderer indexes. */
static __inline void copy_43fa10(void* dst, const void* src, int size)
{
	void* d;
	const void* s;
	int n;
	n = size;
	s = src;
	d = dst;
	__asm {
		mov edi, d
		mov esi, s
		mov ebx, n
		lea ecx, [edi+edi*2]
		and ecx, 3
		sub ebx, ecx
		jle short L_copy
		rep movsb
		mov ecx, ebx
		and ebx, 3
		shr ecx, 2
		rep movsd
	L_copy:
		add ecx, ebx
		rep movsb
	}
}

#pragma optimize("y", off)
/* ADDRESS: GOLDTL 0x0043fa10 */
int* __cdecl fcn_0043fa10(char* a0)
{
	char path[256];
	char prefix[256];
	char msg[256];
	int width;
	int height;
	int n;
	int i;
	int count;
	int minv;
	int maxv;
	int value;
	int* v6;
	char* raw;
	void* dst;
	void* src;
	char* name;
	char* slot;
	int* cell;

	v6 = (int*) m_alloc(0x8038, (char*) 0x67a950);
	raw = (char*) v6;
	strcpy(raw + 0x7da4, a0);
	strcpy(raw + 0x7de4, a0 + 0x48);
	*(unsigned char*) (raw + 0x8037) = (*(unsigned char*) (raw + 0x8037) ^ *(unsigned char*) 0x6b8305) & 0xf ^ *(unsigned char*) (raw + 0x8037);
	if (*(int*) (a0 + 0x40) && *(int*) (a0 + 0x9c) > 0) {
		n = *(int*) (a0 + 0x9c);
		*v6 = n;
		dst = m_alloc(n * n, (char*) 0x67a940);
		v6[4] = (int) dst;
		copy_43fa10(dst, *(void**) (a0 + 0x40), *v6 * *v6);
	} else {
		fcn_0042f420(g_1041d08, g_6b7fdc, path);
		strcat(path, "boden/");
		{ int j = 0; do { prefix[j] = path[j]; } while (path[j++]); }
		strcat(path, a0);
		strcat(path, ".bmp");
		if (fcn_00401590(path, &width, &height, 0) && width == height) {
			*v6 = width;
			dst = m_alloc(width * width, (char*) 0x67a940);
			v6[4] = (int) dst;
			fcn_00401650(path, (unsigned char*) dst, 0, 5);
		} else {
			sprintf(msg, "Could not open HeightMap-File %s or HeightMap has wrong size!!!", path);
		}
	}
	n = *v6;
	v6[2] = (n * n - 1) | (n - 1);
	v6[3] = n - 1;
	if (*(int*) (a0 + 0x98) > 0 && *(int*) (a0 + 0xa0)) {
		if (*(int*) (a0 + 0x44) && *(int*) (a0 + 0x9c) > 0) {
			dst = m_alloc(*v6 * *v6, (char*) 0x67a764);
			v6[6] = (int) dst;
			copy_43fa10(dst, *(void**) (a0 + 0x44), *v6 * *v6);
		} else {
			{ int j = 0; do { path[j] = prefix[j]; } while (prefix[j++]); }
			strcat(path, a0);
			strcat(path, "_w.bmp");
			if (fcn_00401590(path, &width, &height, 0) && width == height && width == *v6) {
				dst = m_alloc(*v6 * *v6, (char*) 0x67a764);
				v6[6] = (int) dst;
				fcn_00401650(path, (unsigned char*) dst, 0, 5);
			} else {
				sprintf(msg, "Could not open WaterMap-File %s or WaterMap has wrong size!!!", path);
			}
		}
		*(unsigned char*) (raw + 0x8035) = *(unsigned char*) (a0 + 0x98);
		dst = m_alloc((unsigned int) *(unsigned char*) (raw + 0x8035) * 0x158, (char*) 0x67a88c);
		v6[0x1f68] = (int) dst;
		copy_43fa10(dst, *(void**) (a0 + 0xa0), (unsigned int) *(unsigned char*) (raw + 0x8035) * 0x158);
	}
	if (*(int*) (a0 + 0x88) && *(int*) (a0 + 0x9c) > 0) {
		dst = m_alloc(*v6 * *v6, (char*) 0x67a87c);
		v6[5] = (int) dst;
		copy_43fa10(dst, *(void**) (a0 + 0x88), *v6 * *v6);
	} else {
		{ int j = 0; do { path[j] = prefix[j]; } while (prefix[j++]); }
		strcat(path, a0 + 0x48);
		strcat(path, ".bmp");
		if (fcn_00401590(path, &width, &height, 0) && width == height && width == *v6) {
			dst = m_alloc(*v6 * *v6, (char*) 0x67a87c);
			v6[5] = (int) dst;
			fcn_00401650(path, (unsigned char*) dst, 0, 5);
		} else {
			sprintf(msg, "Could not open Texture-Information-File %s or Texture-Information has wrong size!!!", path);
		}
	}
	if (!v6[5] || !v6[4]) {
		fcn_0043bcf0(v6);
		return 0;
	}
	*(float*) (raw + 0x50) = (float) (-*v6) * *(float*) (a0 + 0x90) * g_6628cc;
	*(float*) (raw + 0x54) = *(float*) (a0 + 0x94) * *(float*) 0x662cac;
	*(float*) (raw + 0x58) = (float) *v6 * *(float*) (a0 + 0x90) * g_6628cc;
	*(float*) (raw + 0x60) = *(float*) (a0 + 0x90);
	*(int*) (raw + 0x64) = 0;
	*(int*) (raw + 0x68) = 0;
	*(int*) (raw + 0x70) = 0;
	*(int*) (raw + 0x74) = 0;
	*(float*) (raw + 0x78) = -*(float*) (a0 + 0x90);
	*(int*) (raw + 0x80) = 0;
	v6[1] = *v6 / 8;
	*(int*) (raw + 0x88) = 0;
	*(float*) (raw + 0x84) = *(float*) (a0 + 0x94);
	*(float*) (raw + 0x8024) = 20.0f;
	*(float*) (raw + 0x8028) = 40.0f;
	*(unsigned char*) (raw + 0x8036) = *(unsigned char*) (raw + 0x8036) & 0xe1;
	slot = raw + 0x7e24;
	name = a0 + 0xa4;
	i = 8;
	do {
		*slot = g_6b5c60[0];
		if (name && *name) {
			fcn_0043f7e0(v6, name, -1);
		}
		slot += 0x40;
		name += 0x40;
		i--;
	} while (i);
	count = *v6 * *v6;
	maxv = 0;
	minv = 0xff;
	i = 0;
	if (count > 0) {
		do {
			value = *(unsigned char*) (v6[5] + i);
			if (maxv <= value) {
				maxv = value;
			}
			if (value <= minv) {
				minv = value;
			}
			i++;
		} while (i < count);
	}
	i = 0;
	if (count > 0) {
		do {
			cell = (int*) (v6[5] + i);
			*(char*) cell = *(char*) cell - (char) minv;
			i++;
		} while (i < *v6 * *v6);
	}
	fcn_0043f6b0(v6);
	return v6;
}
