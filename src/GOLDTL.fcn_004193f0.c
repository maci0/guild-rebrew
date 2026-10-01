void __cdecl fcn_00418fb0(char* src);
void __cdecl fcn_004190d0(char* src);
void __cdecl fcn_00423670(char* obj, int a, int b);

/* Sound-pan request filled for fcn_00418fb0. */
// SIZE 0x54
typedef struct PanReq {
	char pad[0x34];
	void* emitter;
	void* label;
	int gap3c;
	int mode;
	int flag;
	float level;
	char tail[8];
} PanReq;

// FUNCTION: GOLDTL 0x4193f0
// SIZE: 144

int __cdecl fcn_004193f0(char* obj, void* label, int mode, float amount)
{
	PanReq req;
	float scaled;

	if (obj == 0 || label == 0) {
		return 0;
	}
	scaled = (float) (amount * *(double*) 0x662b40);
	req.label = label;
	req.flag = 1;
	req.emitter = obj;
	*(int*) (obj + 0xc) = 1;
	*(int*) (obj + 0x14) = 0;
	req.mode = mode;
	req.level = scaled;
	fcn_00418fb0((char*) &req);
	fcn_004190d0((char*) &req);
	if (*(int*) (obj + 0x24) == 0) {
		return 0;
	}
	fcn_00423670(obj, 0, 0);
	return 1;
}
