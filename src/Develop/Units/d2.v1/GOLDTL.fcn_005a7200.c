void __cdecl fcn_005338a0(void);
int __cdecl fcn_005373e0(void* p, int n);
char* __cdecl fcn_005338d0(char* name, int id, int len);
void __cdecl fcn_005cf560(char* obj);
void __cdecl fcn_005a7190(char* obj);
void __cdecl fcn_005a59d0(char* obj);
void __cdecl fcn_005a4490(char* obj);
void __cdecl fcn_005a6880(char* obj);
void __cdecl fcn_005a4e00(char* obj);

/* ADDRESS: GOLDTL 0x005a7200 */
void __cdecl fcn_005a7200(char* a0)
{
	char* s1;
	char* s2;
	char* s3;
	char* s4;
	char* obj;

	s3 = 0;
	s4 = 0;
	fcn_005338a0();
	if (!fcn_005373e0((void*) 0x5a7200, 0x67fff)) {
		return;
	}
	do {
		s1 = fcn_005338d0((char*) 0x6aad78, *(int*) 0x14ab6f0, 0x10);
		s2 = fcn_005338d0((char*) 0x6aad68, *(int*) 0x14ab640, 0x10);
		if (*(int*) 0x7746d8 & 0x200) {
			s3 = fcn_005338d0((char*) 0x6aad50, *(int*) 0x14a7d28, 0x16);
			s4 = fcn_005338d0((char*) 0x6aad30, *(int*) 0x14ad1b0, 0x16);
		}
		obj = *(char**) 0x7746a0;
		if (obj) {
			if (obj == s3) {
				fcn_005cf560(a0);
				obj = *(char**) 0x7746a0;
			} else if (obj == s4) {
				fcn_005a7190(a0);
				obj = *(char**) 0x7746a0;
			}
			if (obj) {
				if (*(unsigned short*) (a0 + 0x27) == *(unsigned short*) 0x774970) {
					if (obj == s1) {
						fcn_005a6880(a0);
					} else if (obj == s2) {
						fcn_005a4e00(a0);
					}
				} else {
					if (obj == s1) {
						fcn_005a59d0(a0);
					} else if (obj == s2) {
						fcn_005a4490(a0);
					}
				}
			}
		}
	} while (fcn_005373e0((void*) 0x5a7200, 0x67fff));
}
