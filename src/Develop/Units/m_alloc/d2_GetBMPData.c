#include <windows.h>
#include <string.h>
#include <stdlib.h>
int __cdecl fcn_0064e2f9(void*, int);
int __cdecl fcn_0064e48f(void*, int, int);
int __cdecl fcn_0064ebe4(void*, int, int, void*);
int __cdecl fcn_0064e1fd(void*);
void* __cdecl m_alloc(int, int);
void __cdecl m_FreeTracked(void*);

/* ADDRESS: GOLDTL 0x004754b0 */
unsigned char __cdecl d2_GetBMPData(void* path, void* pixels, unsigned char a3)
{
	BITMAPINFOHEADER hdr;
	unsigned char v10[2];
	void* f;
	int v9;
	int v12;

	f = (void*) fcn_0064e2f9(path, 0x6750e8);
	if (f) {
		fcn_0064e48f(f, 0xe, 0);
		fcn_0064ebe4(&hdr, 1, 0x28, f);
		if (!hdr.biClrUsed) {
			hdr.biClrUsed = 0x100;
		}
		fcn_0064e48f(f, hdr.biClrUsed * 4 + 0x36, 0);
		if (hdr.biCompression == 1) {
			v12 = 0;
			v9 = 0;
			while (v9 < abs(hdr.biHeight)) {
				fcn_0064ebe4(v10, 1, 2, f);
				if (!v10[0]) {
					switch (v10[1]) {
					case 0:
						v12 = 0;
						v9++;
						break;
					case 1:
						v9 = hdr.biHeight;
						break;
					case 2:
						fcn_0064ebe4(v10, 1, 2, f);
						v12 += v10[0];
						v9 += v10[1];
						break;
					default:
						if ((v10[1] & 1) == 1) {
							fcn_0064ebe4((char*) pixels + hdr.biWidth * v9 + v12, v10[1] + 1, 1, f);
						}
						else {
							fcn_0064ebe4((char*) pixels + hdr.biWidth * v9 + v12, v10[1], 1, f);
						}
						v12 += v10[1];
						break;
					}
				}
				else {
					memset((char*) pixels + hdr.biWidth * v9 + v12, v10[1], v10[0]);
					v12 += v10[0];
				}
			}
		}
		else {
			fcn_0064ebe4(pixels, hdr.biHeight, hdr.biWidth, f);
		}
		fcn_0064e1fd(f);
		if (a3 && hdr.biHeight > 0) {
			void* q;
			int i;
			int n;
			int last;
			q = m_alloc(hdr.biWidth, 0x67d924);
			i = 0;
			n = hdr.biHeight / 2;
			if (i < n) {
				last = hdr.biHeight - 1;
				for (; i < n; i++, last--) {
					memcpy(q, (char*) pixels + hdr.biWidth * i, hdr.biWidth);
					memcpy((char*) pixels + hdr.biWidth * i, (char*) pixels + hdr.biWidth * last, hdr.biWidth);
					memcpy((char*) pixels + hdr.biWidth * last, q, hdr.biWidth);
				}
			}
			m_FreeTracked(q);
		}
		return 1;
	}
	return 0;
}
