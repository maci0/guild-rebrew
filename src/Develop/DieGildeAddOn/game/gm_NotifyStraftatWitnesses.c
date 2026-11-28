extern char str_empty[];
extern char gm_EntityIdField[];


unsigned char* __cdecl gm_LookupEntityRecordById(int);
void __cdecl io_FormatTextBuffer(void*, int, ...);
void __cdecl he_PostEntityMessage(int, int, void*, int, int, void*);

void __cdecl gm_NotifyStraftatWitnesses(int straftatId, int excludedId, int mask)
{
	char buf[0x200];
	unsigned char* p;
	int i;
	char* e;

	p = 0;
	for (i = 0x9a3816; i < 0x9a9216; i += 0x2d) {
		if (*(int*) (i - 0x16) == straftatId) {
			p = gm_LookupEntityRecordById(*(int*) i);
			if (p != 0) {
				io_FormatTextBuffer(buf, 0x1747, *(unsigned short*) p);
			}
		}
	}
	if (p == 0) {
		return;
	}
	for (e = gm_EntityIdField; (int) e < (int) (gm_EntityIdField + 0x65400); e += 0x21c) {
		if ((*(char*) (e - 2) == 6 || *(char*) (e - 2) == 7)
		    && *(int*) e != excludedId
		    && (*(int*) (e + 0x1e4) & mask) == 0) {
			for (i = 0; i < 0x800; i++) {
				if (*(int*) (0x99f800 + i * 8) == *(int*) e
				    && *(int*) (0x99f804 + i * 8) == straftatId) {
					he_PostEntityMessage(*(int*) e, -1, buf, 0, 0x5ec, str_empty);
					*(int*) (0x7f4e88 + i * 540) &= mask;
					break;
				}
			}
		}
	}
}
