

extern unsigned char* g_90e094;
extern unsigned char* g_868050;

void* __cdecl fcn_004f18d0(int a, unsigned char* rec, void* prev, void* filter, int mask);
int __cdecl fcn_004f17f0(void);

int __cdecl fcn_004f4650(int a, unsigned char** out1, void** out2)
{
	unsigned char* rec;
	void* r;
	int i;

	*out1 = 0;
	*out2 = 0;
	rec = g_90e094;
	for (i = 0; i < 256; i++, rec += 0xa9) {
		if (rec[0] != 0 && g_868050[rec[0] * 0x24d] == 0x1d) {
			r = fcn_004f18d0(a, rec, 0, (void*) fcn_004f17f0, 0xff);
			if (r != 0) {
				*out1 = rec;
				*out2 = r;
				return 1;
			}
		}
	}
	return 0;
}
