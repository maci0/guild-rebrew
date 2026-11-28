


int __cdecl gm_GetLawEntry(int, void*);
void __cdecl io_FormatTextBuffer(void*, int, ...);

/* ADDRESS: GOLDDE 0x004e11b0 */
int __cdecl gm_FormatLawName(void* buf, int a2)
{
	unsigned char local[0x24];
	unsigned char a;
	unsigned char b;
	int formatId;
	int r = 1;

	if (!gm_GetLawEntry(a2, local)) {
		return 0;
	}
	a = local[0];
	b = local[1];
	formatId = a * 5 + 0x13fd;
	switch (b) {
	case 0:
		io_FormatTextBuffer(buf, formatId + 1, formatId, *(int*) (local + 0x18));
		break;
	case 1:
		io_FormatTextBuffer(buf, formatId + 1, formatId, *(int*) (local + 0x18) + 0x13dd);
		break;
	case 2:
		io_FormatTextBuffer(buf, formatId + 1, formatId, *(int*) (local + 0x18) + 0x13e6);
		break;
	case 3:
		io_FormatTextBuffer(buf, formatId + 1, formatId, *(int*) (local + 0x18) + 0x13ec);
		break;
	default:
		r = 0;
		break;
	}
	return r;
}
