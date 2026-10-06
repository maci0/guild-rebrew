// FUNCTION: GOLDTL 0x00402a00

extern char g_675328[];
void __cdecl fcn_00442d50(void* p, int on);
void __cdecl fcn_00442c00(void* p, int on);
void __cdecl fcn_004033e0(char* e);
void __cdecl fcn_0041d9e0(char* msg);

void __cdecl fcn_00402a00(char* e, int on)
{
	if (e != 0 && *(void**) (e + 0x34) != 0) {
		fcn_00442d50(*(void**) (e + 0x34), on);
		if (*(void**) (e + 0x64) != 0) {
			fcn_00442c00(*(void**) (e + 0x64), on);
		}
		if (*(void***) (e + 0x124) != 0) {
			fcn_00442d50(**(void***) (e + 0x124), on);
		}
		if (*(void**) (e + 0x22c) != 0) {
			fcn_00442c00(*(void**) (e + 0x22c), on);
		}
		if (on) {
			*(short*) (e + 0x8c) &= ~0x20;
		} else {
			*(short*) (e + 0x8c) |= 0x20;
		}
		fcn_004033e0(e);
		return;
	}
	fcn_0041d9e0(g_675328);
}
