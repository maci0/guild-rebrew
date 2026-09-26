// FUNCTION: GOLDTL 0x452420
// SIZE: 188

extern int g_67a370;

void __cdecl fcn_004523a0(char*);
void __cdecl fcn_0045bfb0(int);
void __cdecl fcn_0041ddd0(void*);

void __cdecl fcn_00452420(char* o)
{
	char* owner;

	owner = *(char**) (o + 0x2f4);
	if (owner == ((char*)g_67a370)) {
		*(char**) (*(char**) (o + 0x314) + 0x318) = *(char**) (o + 0x318);
		*(char**) (*(char**) (o + 0x318) + 0x314) = *(char**) (o + 0x314);
		if (o == *(char**) (owner + 0xa4)) {
			*(char**) (owner + 0xa4) = *(char**) (o + 0x314);
		}
		if (o == *(char**) (owner + 0xa8)) {
			*(char**) (owner + 0xa8) = *(char**) (o + 0x314);
		}
	} else {
		fcn_004523a0(o);
	}
	if (*(int*) (o + 0xdc) != 0) {
		fcn_0045bfb0(*(int*) (o + 0xdc));
	}
	fcn_0041ddd0(*(void**) (o + 0x28));
	*(void**) (o + 0x28) = 0;
	fcn_0041ddd0(*(void**) (o + 0x2c));
	*(void**) (o + 0x2c) = 0;
	fcn_0041ddd0(*(void**) (o + 0x30));
	*(void**) (o + 0x30) = 0;
	fcn_0041ddd0(o);
}
