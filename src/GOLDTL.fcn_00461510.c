typedef struct ZState {
	int mode;
	int sub[2];
	int nowrap;
	int wbits;
	void* blocks;
} ZState;
// SIZE 0x18

typedef struct ZStream {
	void* next_in;
	unsigned int avail_in;
	unsigned long total_in;
	void* next_out;
	unsigned int avail_out;
	unsigned long total_out;
	char* msg;
	ZState* state;
} ZStream;
// SIZE 0x20

void __cdecl fcn_0045fc50(void* s, ZStream* z, unsigned long* c);

// FUNCTION: GOLDTL 0x461510
// SIZE: 66
int __cdecl fcn_00461510(ZStream* z)
{
	if (z == 0 || z->state == 0) {
		return -2;
	}
	z->total_in = z->total_out = 0;
	z->msg = 0;
	z->state->mode = z->state->nowrap ? 7 : 0;
	fcn_0045fc50(z->state->blocks, z, 0);
	return 0;
}
