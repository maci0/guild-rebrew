#if defined(REBREW_GOLD)
typedef struct DevData16 {
	unsigned int ofs;
	unsigned int data;
	unsigned int time;
	unsigned int seq;
} DevData16;

/* Polls the device through vtable slot 0x28, updates the key tables and then
   runs the key repeat timer.
   DATA TODO: 0x14673cc, 0x1468410, 0x14681c0, 0x1468420, 0x6310c0, 0x6310e0,
   0x631098 and 0x6333d8 have no Gold definition, so raw addresses stay. */
/* ADDRESS: GOLD 0x004112e0 */
void __cdecl io_PollKeyboardInput(void)
{
	DevData16 ev;
	unsigned int n;
	int one;
	int dev;
	int hr;
	unsigned int ofs;
	unsigned char cur;
	unsigned char key;
	int stamp;

	*(unsigned char*) 0x1468410 = 0;
	one = 1;
	do {
		dev = *(int*) 0x14673cc;
		n = (unsigned int) one;
		hr = ((int (__stdcall*) (int, int, DevData16*, unsigned int*, int)) (*(int**) dev)[0x28 / 4])
			(dev, 0x10, &ev, &n, 0);
		if (hr < 0) {
			break;
		}
		if (n == 0) {
			break;
		}
		if (ev.data & 0x80) {
			if (*(int*) 0x6310c0 == 0) {
				ofs = ev.ofs;
				*(unsigned char*) 0x1468410 = (unsigned char) ofs;
				*(unsigned char*) (0x14681c0 + (unsigned char) ofs) = (unsigned char) one;
			}
		} else if (*(int*) 0x6310c0 == 0) {
			ofs = ev.ofs;
			*(unsigned char*) (0x14681c0 + ofs) = 0;
			*(unsigned char*) (0x1468420 + ofs) = (unsigned char) one;
		}
	} while (hr >= 0);
	cur = *(unsigned char*) 0x1468410;
	if (cur != 0) {
		key = cur;
		stamp = *(int*) 0x6333d8;
		*(unsigned char*) 0x6310e0 = key;
		stamp = stamp + 9;
		*(int*) 0x631098 = stamp;
	} else {
		stamp = *(int*) 0x631098;
		key = *(unsigned char*) 0x6310e0;
	}
	if (key != 0) {
		if (cur == 0 && *(unsigned char*) (0x14681c0 + (*(int*) 0x6310e0 & 0xff)) != 0
		    && *(unsigned int*) 0x6333d8 > (unsigned int) stamp + 5) {
			*(unsigned char*) 0x1468410 = key;
			*(int*) 0x631098 = *(int*) 0x6333d8;
		}
		if (*(unsigned char*) (0x14681c0 + (*(int*) 0x6310e0 & 0xff)) == 0) {
			*(unsigned char*) 0x6310e0 = 0;
			*(int*) 0x631098 = 0x4e729fff;
		}
	}
}
#else
extern volatile int g_6b7fb8;
extern char g_14cf950;

typedef struct DevData DevData;

/* DIDEVICEOBJECTDATA, 0x14 bytes. */
// SIZE 0x14
struct DevData {
	unsigned int ofs;
	unsigned int data;
	unsigned int time;
	unsigned int seq;
	unsigned int app;
};

#include "Develop/DieGildeAddOn/game/client_input.h"

/* Drain the keyboard device. The loop is a do/while on the HRESULT so
 * the failure path is a jl to the tail and GetDeviceData is emitted
 * once. */
/* ADDRESS: GOLDTL 0x004124b0 */
void __cdecl io_PollKeyboardInput(void)
{
	DevData ev;
	unsigned int n;
	int one;
	INPUT_DEVICE* dev;
	int hr;
	unsigned int ofs;
	unsigned char cur;
	unsigned char key;
	int stamp;

	g_14cf950 = 0;
	one = 1;
	do {
		dev = g_14ce90c;
		n = (unsigned int) one;
		hr = dev->vtbl->GetDeviceData(dev, 0x14, (LPDIDEVICEOBJECTDATA) &ev, (LPDWORD) &n, 0);
		if (hr < 0) {
			break;
		}
		if (n == 0) {
			break;
		}
		if (ev.data & 0x80) {
			if (*(int*) 0x6b5c90 == 0) {
				ofs = ev.ofs;
				g_14cf950 = (char) ofs;
				((unsigned char*) 0x14cf700)[(unsigned char) ofs] = (unsigned char) one;
			}
		} else if (*(int*) 0x6b5c90 == 0) {
			ofs = ev.ofs;
			((unsigned char*) 0x14cf700)[ofs] = 0;
			((unsigned char*) 0x14cf960)[ofs] = (unsigned char) one;
		}
	} while (hr >= 0);
	cur = (unsigned char) g_14cf950;
	if (cur != 0) {
		key = cur;
		stamp = g_6b7fb8;
		*(unsigned char*) 0x6b5cb0 = key;
		stamp = stamp + 9;
		*(int*) 0x6b5c68 = stamp;
	} else {
		stamp = *(int*) 0x6b5c68;
		key = *(unsigned char*) 0x6b5cb0;
	}
	if (key != 0) {
		if (cur == 0 && ((unsigned char*) 0x14cf700)[*(int*) 0x6b5cb0 & 0xff] != 0 && (unsigned int) g_6b7fb8 > (unsigned int) stamp + 5) {
			g_14cf950 = key;
			*(int*) 0x6b5c68 = g_6b7fb8;
		}
		if (((unsigned char*) 0x14cf700)[*(int*) 0x6b5cb0 & 0xff] == 0) {
			*(unsigned char*) 0x6b5cb0 = 0;
			*(int*) 0x6b5c68 = 0x4e729fff;
		}
	}
}
#endif
