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
unsigned char __cdecl fcn_004754b0(void* a0, void* a1, int a3)
{
	BITMAPINFOHEADER hdr;
	unsigned char v10[4];
	void* f;
	int v9;
	int v12;
	int n;
	int last;
	int i;
	void* q;

	f = (void*) fcn_0064e2f9(a0, 0x6750e8);
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
				if (v10[0]) {
					memset((char*) a1 + hdr.biWidth * v9 + v12, v10[1], v10[0]);
					v12 += v10[0];
				}
				else {
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
							fcn_0064ebe4((char*) a1 + hdr.biWidth * v9 + v12, v10[1] + 1, 1, f);
						}
						else {
							fcn_0064ebe4((char*) a1 + hdr.biWidth * v9 + v12, v10[1], 1, f);
						}
						v12 += v10[1];
						break;
					}
				}
			}
		}
		else {
			fcn_0064ebe4(a1, hdr.biHeight, hdr.biWidth, f);
		}
		fcn_0064e1fd(f);
		if ((a3 & 0xff) && hdr.biHeight > 0) {
			q = m_alloc(hdr.biWidth, 0x67d924);
			n = hdr.biHeight / 2;
			last = hdr.biHeight - 1;
			i = 0;
			while (i < n) {
				memcpy(q, (char*) a1 + hdr.biWidth * i, hdr.biWidth);
				memcpy((char*) a1 + hdr.biWidth * i, (char*) a1 + hdr.biWidth * last, hdr.biWidth);
				memcpy((char*) a1 + hdr.biWidth * last, q, hdr.biWidth);
				i++;
				last--;
			}
			m_FreeTracked(q);
		}
		return 1;
	}
	return 0;
}
