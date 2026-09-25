// FUNCTION: GOLDTL 0x0041ddd0
// SIZE: 117

// SIZE 0x18
typedef struct {
	char pad0[0x10];
	int bytes;
	int count;
} Pool;

// SIZE 0x10
typedef struct {
	Pool* pool;
	int pad4;
	void* ptr;
	int size;
} Slot;

extern int g_6b6f78;
extern int g_6b6f64;
extern Slot* g_6b6f80;
extern int g_6b6f6c;
extern int g_6b6f68;
void __cdecl fcn_0064dfda(void* p);

void __cdecl fcn_0041ddd0(void* p)
{
	Slot* s;
	int i;
	int size;

	if (p == 0) {
		return;
	}
	s = g_6b6f80;
	g_6b6f78--;
	for (i = 0; i < g_6b6f64; i++) {
		if (s->ptr == p) {
			break;
		}
		s++;
	}
	if (i == g_6b6f64) {
		return;
	}
	size = s->size;
	s->ptr = 0;
	fcn_0064dfda(p);
	g_6b6f6c--;
	s->pool->count--;
	g_6b6f68 -= size;
	s->pool->bytes -= size;
}
