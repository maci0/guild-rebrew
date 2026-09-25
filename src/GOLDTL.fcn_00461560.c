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
	void* zalloc;
	void(__cdecl* zfree)(void* opaque, void* p);
	void* opaque;
} ZStream;
// SIZE 0x2c

void __cdecl fcn_004609c0(void* s, ZStream* z);

// FUNCTION: GOLDTL 0x461560
// SIZE: 72
int __cdecl fcn_00461560(ZStream* z)
{
	if (z == 0 || z->state == 0 || z->zfree == 0) {
		return -2;
	}
	if (z->state->blocks != 0) {
		fcn_004609c0(z->state->blocks, z);
	}
	(*z->zfree)(z->opaque, z->state);
	z->state = 0;
	return 0;
}
