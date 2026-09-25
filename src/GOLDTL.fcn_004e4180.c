void __cdecl fcn_004e4e90(char*);
int __cdecl gm_ResolveEntityById(void** dynamic, void** existing, void** static_ptr, int entity_id);
void __cdecl fcn_004e4230(void*, int);
void __cdecl fcn_004e4730(char*);
void __cdecl fcn_004e4c90(int);
void __cdecl fcn_004c54c0(int, int, int, int);
void __cdecl fcn_004e48b0(void);
void __cdecl fcn_004e4910(void);
void __cdecl fcn_004e4eb0(void);

// FUNCTION: GOLD 0x004e2860
// SIZE: 165
// FUNCTION: GOLDTL 0x004e4180
// SIZE: 165

void __cdecl fcn_004e4180(int* m)
{
	void* dyn;
	int fallback;
	int i;

	fallback = 0;
	fcn_004e4e90(0);
	gm_ResolveEntityById(&dyn, 0, 0, m[5]);
	if (dyn != 0) {
		fcn_004e4230(dyn, 0x17);
	} else {
		fallback = 1;
		fcn_004e4730("ob_SALON.ed3");
	}
	fcn_004e4c90(5);
	for (i = 0; i < 4; i++) {
		if (m[14 + i] != -1) {
			fcn_004c54c0(m[13], m[14 + i], 0xa, 1);
			fcn_004c54c0(m[14 + i], m[13], 0xa, 1);
		}
	}
	if (fallback) {
		fcn_004e48b0();
		fcn_004e4910();
	}
	fcn_004e4eb0();
}
