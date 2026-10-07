// FUNCTION: GOLD 0x519c20
// FUNCTION: GOLDTL 0x0051ebc0

extern unsigned short* g_868054;

unsigned int __cdecl fcn_00430910(void* p, int size, int n, void* file);

int __cdecl fcn_0051ebc0(void* file)
{
	int count;
	int i;
	unsigned char* rec;

	count = 0;
	for (i = 0; i < 0x5008; i++) {
		if (*(short*) (((unsigned char*)g_868054) + i * 0x43) != 0) {
			count++;
		}
	}
	if (fcn_00430910(&count, 4, 1, file) <= 0)
		return 0;
	for (i = 0; i < 0x5008; i++) {
		rec = ((unsigned char*)g_868054) + i * 0x43;
		if (*(short*) rec != 0) {
			if (fcn_00430910(rec, 2, 1, file) <= 0)
				return 0;
			if (fcn_00430910(rec + 2, 4, 1, file) <= 0)
				return 0;
			if (fcn_00430910(rec + 6, 4, 1, file) <= 0)
				return 0;
			if (fcn_00430910(rec + 0xa, 4, 1, file) <= 0)
				return 0;
			if (fcn_00430910(rec + 0xe, 4, 1, file) <= 0)
				return 0;
			if (fcn_00430910(rec + 0x12, 1, 1, file) <= 0)
				return 0;
			if (fcn_00430910(rec + 0x13, 1, 1, file) <= 0)
				return 0;
			rec += 0x1c;
			if (fcn_00430910(rec, 0x1f, 1, file) <= 0)
				return 0;
		}
	}
	return 1;
}
