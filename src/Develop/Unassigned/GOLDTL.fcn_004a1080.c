char* __cdecl gm_LookupEntityRecordById(int a1);
void __cdecl fcn_004c5530(int a1);
void __cdecl fcn_004c5420(int a1, int a2, int a3, int a4, int a5);

/* ADDRESS: GOLDTL 0x004a1080 */
int __cdecl fcn_004a1080(char* a0, char* a1, char* a2)
{
	char buf[0xf8];
	char* e;

	if (*(unsigned char*) a1 == 7 && *(unsigned char*) a2 == 0x0e) {
		e = gm_LookupEntityRecordById(0);
		if (e != 0) {
			*(unsigned char*) (buf + 0x36) = 0x12;
			*(unsigned char*) (buf + 0x04) = 0x5f;
			*(int*) (buf + 0x08) = *(int*) (e + 4);
			*(int*) (buf + 0x58) = *(int*) (a0 + 4);
			*(unsigned char*) (buf + 0x64) = *(unsigned char*) (a2 + 4);
			*(int*) (buf + 0x0c) = -1;
			*(unsigned char*) (buf + 0x65) = *(unsigned char*) (a2 + 0x10);
			*(int*) (buf + 0x60) = *(int*) (a1 + 0x10);
			fcn_004c5530((int) buf);
			fcn_004c5420(*(int*) (e + 4), 0x1c8, 4, 0x10000, 0);
			return 0x3b;
		}
	}
	return 0;
}
