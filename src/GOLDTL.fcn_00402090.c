// FUNCTION: GOLDTL 0x00402090

extern char g_67515c[];
char __cdecl fcn_00401590(const char* name, int* width, int* height, int* bpp);
char __cdecl fcn_00401650(const char* name, unsigned char* pixels, unsigned char* pal, int flags);
unsigned char* __cdecl m_alloc(int size, char* tag);
void __cdecl m_FreeTracked(void* p);

/* Averages the palette colour of an 8-bit image, weighted by pixel count. */
char __cdecl fcn_00402090(const char* name, unsigned char* out)
{
	char r;
	int n;
	unsigned char* pix;
	unsigned int hist[0x100];
	unsigned char pal[0x300];
	float sum[3];
	float inv;
	int i;
	int k;

	/* w/h and len/d are block-scoped so their frame slots are reused by pix
	 * and the conversion temporaries, as in the reference frame. */
	r = 0;
	if (out != 0 && name != 0) {
		int w;
		int h;

		if (!fcn_00401590(name, &w, &h, 0)) {
			return 0;
		}
		n = w * h;
	}
	else {
		return 0;
	}
	pix = m_alloc(n, g_67515c);
	if (fcn_00401650(name, pix, pal, 7)) {
		{
			int len;
			unsigned int* d;

			len = 0x400;
			d = hist;
			__asm {
				mov edi, d
				mov ebx, len
				xor eax, eax
				lea ecx, [edi+edi*2]
				and ecx, 3
				sub ebx, ecx
				jle short L1
				rep stosb
				mov ecx, ebx
				and ebx, 3
				shr ecx, 2
				rep stosd
			L1:
				add ecx, ebx
				rep stosb
			}
		}
		for (i = 0; i < n; i++) {
			hist[pix[i]]++;
		}
		inv = 1.0f / (float) n;
		sum[2] = 0;
		sum[1] = 0;
		sum[0] = 0;
		for (i = 0; i < 0x100; i++) {
			for (k = 0; k < 3; k++) {
				sum[k] += (float) pal[i * 3 + k] * (float) hist[i] * inv;
			}
		}
		out[2] = (unsigned char) sum[0];
		out[1] = (unsigned char) sum[1];
		out[0] = (unsigned char) sum[2];
		r = 1;
	}
	m_FreeTracked(pix);
	return r;
}
