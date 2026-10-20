typedef void (__stdcall* DESTROY1)(void* obj);
typedef void (__stdcall* DESTROY2)(void* obj, void* slot);
/* ADDRESS: GOLDTL 0x0062ae18 */
int __fastcall fcn_0062ae18(void* self)
{
	char* s;
	void* obj;
	int i;

	s = (char*) self;
	if (*(void**) (s + 4) != 0) {
		if (*(void**) (s + 0x64) != 0) {
			obj = *(void**) (s + 4);
			((DESTROY2) (*(void***) obj)[0xe0 / 4]) (obj, *(void**) (s + 0x64));
			*(void**) (s + 0x64) = 0;
		}
		if (*(void**) (s + 0x68) != 0) {
			obj = *(void**) (s + 4);
			((DESTROY2) (*(void***) obj)[0xe0 / 4]) (obj, *(void**) (s + 0x68));
			*(void**) (s + 0x68) = 0;
		}
	}
	if (*(void**) (s + 0xc) != 0) {
		obj = *(void**) (s + 0xc);
		((DESTROY1) (*(void***) obj)[0x20 / 4]) (obj);
	}
	if (*(int*) (s + 0x50) != 0) {
		for (i = 0; i < 8; i++) {
			obj = *(void**) (s + 0x30);
			if (obj != 0) {
				((DESTROY1) (*(void***) obj)[8 / 4]) (obj);
				*(void**) (s + 0x30) = 0;
			}
			obj = *(void**) (s + 0x10);
			if (obj != 0) {
				((DESTROY1) (*(void***) obj)[8 / 4]) (obj);
				*(void**) (s + 0x10) = 0;
			}
			s += 4;
		}
		s -= 0x20;
	}
	return 0;
}
