#include <stdlib.h>
#include <string.h>

/* Display mode record enumerated for one adapter. */
typedef struct {
	unsigned int width;
	unsigned int height;
	unsigned int refresh;
	unsigned int format;
} MODE8;

typedef int (__stdcall* ADAPTERCOUNTFN)(void*);
typedef int (__stdcall* ADAPTERIDENTFN)(void*, unsigned int, unsigned int, void*);
typedef int (__stdcall* MODECOUNTFN)(void*, unsigned int);
typedef int (__stdcall* ENUMMODEFN)(void*, unsigned int, unsigned int, void*);
typedef int (__stdcall* DISPLAYMODEFN)(void*, unsigned int, void*);
typedef int (__stdcall* CHECKTYPEFN)(void*, unsigned int, unsigned int,
	unsigned int, unsigned int, int);
typedef int (__stdcall* CHECKFORMATFN)(void*, unsigned int, unsigned int,
	unsigned int, unsigned int, unsigned int, unsigned int);
typedef int (__stdcall* CHECKDSMATCHFN)(void*, unsigned int, unsigned int,
	unsigned int, unsigned int, unsigned int);
typedef int (__stdcall* GETCAPSFN)(void*, unsigned int, unsigned int, void*);

extern void* __stdcall Direct3DCreate8(unsigned int version);
extern void __cdecl fcn_0041a2c0(int index);
extern void* __cdecl m_alloc(unsigned int size, const char* tag);
extern int __cdecl fcn_0041a8d0(const void* a, const void* b);

#define D3D (*(int*) 0x6b5ddc)
#define ADAPTERS (*(int*) 0x6b5dd0)
#define ADAPTERCOUNT (*(unsigned int*) 0x6b5de8)
#define VTBL(off) (*(int*) (*(int*) D3D + (off)))
#define MODES ((int*) (*(int*) (ADAPTERS + offset + 0x504)))
#define MODECOUNT (*(unsigned int*) (ADAPTERS + offset + 0x500))
#define MODEAT(k) ((unsigned int*) ((char*) MODES + (k) * 0x10))

/* ADDRESS: GOLDTL 0x0041a380 */
int __cdecl fcn_0041a380(unsigned int minWidth, unsigned int minHeight, unsigned char windowed)
{
	MODE8 cur;
	unsigned char reliable;
	unsigned int i;
	unsigned int offset;
	unsigned int m;
	unsigned int i2;
	unsigned int j;
	unsigned int fmt;
	int r;

	if (D3D == 0) {
		r = (int) Direct3DCreate8(0xdc);
		D3D = r;
		if (r == 0)
			return (int) ADAPTERCOUNT;
	}
	while (ADAPTERCOUNT > 0)
		fcn_0041a2c0(0);
	ADAPTERCOUNT = (unsigned int) ((ADAPTERCOUNTFN) VTBL(0x10))((void*) D3D);
	ADAPTERS = (int) m_alloc(ADAPTERCOUNT * 0x508, "dd:AdapterInfo");
	offset = 0;
	for (i = 0; i < ADAPTERCOUNT; i++) {
		((ADAPTERIDENTFN) VTBL(0x14))((void*) D3D, i, 2,
			(void*) (ADAPTERS + offset));
		((GETCAPSFN) VTBL(0x34))((void*) D3D, i, 1,
			(void*) (ADAPTERS + offset + 0x42c));
		((DISPLAYMODEFN) VTBL(0x20))((void*) D3D, i, &cur);
		reliable = (unsigned char) (~(*(unsigned int*) (ADAPTERS + offset + 0x450) >> 15) & 1);
		MODECOUNT = (unsigned int) ((MODECOUNTFN) VTBL(0x18))((void*) D3D, i);
		*(int*) (ADAPTERS + offset + 0x504) = (int) m_alloc(MODECOUNT * 0x10, "dd:ModeInfo");
		m = 0;
		while (m < MODECOUNT) {
			((ENUMMODEFN) VTBL(0x1c))((void*) D3D, i, m,
				(void*) MODEAT(m));
			m++;
		}
		for (i2 = 0; i2 < MODECOUNT; i2++) {
			for (j = i2 + 1; j < MODECOUNT; j++) {
				if (MODEAT(i2)[3] == MODEAT(j)[3]
				    && MODEAT(i2)[0] == MODEAT(j)[0]
				    && MODEAT(i2)[1] == MODEAT(j)[1]) {
					--MODECOUNT;
					memmove((void*) MODEAT(j), (void*) (MODEAT(j) + 4),
						(MODECOUNT - j) * 0x10);
					j--;
				}
			}
			fmt = MODEAT(i2)[3];
			if (MODEAT(i2)[0] < minWidth || MODEAT(i2)[1] < minHeight
			    || ((CHECKTYPEFN) VTBL(0x24))((void*) D3D, i, 1, fmt, fmt,
				windowed) < 0
			    || (windowed && fmt != cur.format)) {
				--MODECOUNT;
				memmove((void*) MODEAT(i2), (void*) (MODEAT(i2) + 4),
					(MODECOUNT - i2) * 0x10);
				i2--;
				continue;
			}
			MODEAT(i2)[2] = 0;
			if (reliable) {
				if (((CHECKFORMATFN) VTBL(0x28))((void*) D3D, i, 1, fmt,
					2, 1, 0x47) >= 0
				    && ((CHECKDSMATCHFN) VTBL(0x30))((void*) D3D, i, 1,
					fmt, fmt, 0x47) >= 0) {
					MODEAT(i2)[2] = 0x47;
				} else if (((CHECKFORMATFN) VTBL(0x28))((void*) D3D, i, 1,
					fmt, 2, 1, 0x4d) >= 0
				    && ((CHECKDSMATCHFN) VTBL(0x30))((void*) D3D, i, 1,
					fmt, fmt, 0x4d) >= 0) {
					MODEAT(i2)[2] = 0x4d;
				} else if (((CHECKFORMATFN) VTBL(0x28))((void*) D3D, i, 1,
					fmt, 2, 1, 0x50) >= 0
				    || ((CHECKDSMATCHFN) VTBL(0x30))((void*) D3D, i, 1,
					fmt, fmt, 0x50) < 0) {
					MODEAT(i2)[2] = 0x50;
				} else {
					--MODECOUNT;
					memmove((void*) MODEAT(i2),
						(void*) (MODEAT(i2) + 4),
						(MODECOUNT - i2) * 0x10);
					i2--;
					continue;
				}
			}
		}
		qsort((void*) MODES, MODECOUNT, 0x10, fcn_0041a8d0);
		offset += 0x508;
	}
	for (i = 0, offset = 0; i < ADAPTERCOUNT; i++, offset += 0x508) {
		if (!((!windowed
			|| (*(unsigned int*) (ADAPTERS + offset + 0x438) & 0x80000))
		    && *(unsigned int*) (ADAPTERS + offset + 0x500) != 0)) {
			fcn_0041a2c0(i);
			i--;
			offset -= 0x508;
		}
	}
	return (int) ADAPTERCOUNT;
}
