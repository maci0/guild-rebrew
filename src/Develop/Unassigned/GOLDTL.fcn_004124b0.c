

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

typedef int (__stdcall* GetDevData)(void* self, unsigned int cb, DevData* data, unsigned int* n, unsigned int flags);

/* Drain the keyboard device. The loop is a do/while on the HRESULT so
 * the failure path is a jl to the tail and GetDeviceData is emitted
 * once. The volatile byte load is what puts that byte in al. */
void __cdecl fcn_004124b0(void)
{
	DevData ev;
	unsigned int n;
	int one;
	int* dev;
	int hr;
	unsigned int ofs;
	unsigned char cur;
	unsigned char key;
	int stamp;

	*(unsigned char*) 0x14cf950 = 0;
	one = 1;
	do {
		dev = *(int**) 0x14ce90c;
		n = (unsigned int) one;
		hr = ((GetDevData) ((int*) *dev)[10])(dev, 0x14, &ev, &n, 0);
		if (hr < 0) {
			break;
		}
		if (n == 0) {
			break;
		}
		if (ev.data & 0x80) {
			if (*(int*) 0x6b5c90 == 0) {
				ofs = ev.ofs;
				*(unsigned char*) 0x14cf950 = (unsigned char) ofs;
				((unsigned char*) 0x14cf700)[(unsigned char) ofs] = (unsigned char) one;
			}
		} else if (*(int*) 0x6b5c90 == 0) {
			ofs = ev.ofs;
			((unsigned char*) 0x14cf700)[ofs] = 0;
			((unsigned char*) 0x14cf960)[ofs] = (unsigned char) one;
		}
	} while (hr >= 0);
	cur = *(volatile unsigned char*) 0x14cf950;
	if (cur != 0) {
		key = cur;
		stamp = *(int*) 0x6b7fb8;
		*(unsigned char*) 0x6b5cb0 = key;
		stamp = stamp + 9;
		*(int*) 0x6b5c68 = stamp;
	} else {
		stamp = *(int*) 0x6b5c68;
		key = *(unsigned char*) 0x6b5cb0;
	}
	if (key != 0) {
		if (cur == 0 && ((unsigned char*) 0x14cf700)[*(int*) 0x6b5cb0 & 0xff] != 0 && *(unsigned int*) 0x6b7fb8 > (unsigned int) stamp + 5) {
			*(unsigned char*) 0x14cf950 = key;
			*(int*) 0x6b5c68 = *(int*) 0x6b7fb8;
		}
		if (((unsigned char*) 0x14cf700)[*(int*) 0x6b5cb0 & 0xff] == 0) {
			*(unsigned char*) 0x6b5cb0 = 0;
			*(int*) 0x6b5c68 = 0x4e729fff;
		}
	}
}
