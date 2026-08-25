/* m_FreeTracked — debug-heap tracked free (0x10006820). */

// FUNCTION: SERVER 0x10006820
// m_FreeTracked
// SIZE: 192

extern int g_10034638;
extern int g_10034624;
extern int g_10034640;
extern int g_1003462c;
extern int g_10034630;
extern int g_10034634;
extern int g_10034628;
extern void __cdecl LogMessageInternal(char* file, unsigned int line, char* msg, int level);
extern void __cdecl ReportFatalError(char* modulePath, unsigned int lineNumber, char* message);
extern void __cdecl fcn_1001ab81(void* ptr);
extern int g_117640b4;
extern int g_117640b0;
extern int g_117640bc;
extern int g_117640b8;
extern int g_117640c0;
extern int g_117640c4;
extern int g_117640a0;
extern int g_117640a4;

void __cdecl m_FreeTracked(void* ptr)
{
	char* pool;
	int i;
	int count;
	int size;
	int* block;

	if (ptr == 0) {
		return;
	}
	g_10034638--;
	count = g_10034624;
	pool = (char*) g_10034640;
	for (i = 0; i < count; i++) {
		if (*(void**) (pool + 8) == ptr) {
			break;
		}
		pool += 0x10;
	}
	if (i == count) {
		LogMessageInternal("D:\\Develop\\Units\\m_alloc\\m_alloc.c", 0x149, "Memory freed more than once or tried to free invalid pointer", 1);
		return;
	}
	size = *(int*) (pool + 0xc);
	*(int*) (pool + 8) = 0;
	fcn_1001ab81(ptr);
	g_1003462c--;
	block = *(int**) pool;
	block[5]--;
	g_10034628 -= size;
	block = *(int**) pool;
	block[4] -= size;
	if (g_10034628 < 0) {
		ReportFatalError("D:\\Develop\\Units\\m_alloc\\m_alloc.c", 0x17a, "Memory-Underflow Error");
	}
}

/* InitPacketPool — allocates and zeroes the packet pool (0x100068E0).
 * The dest-alignment memset prelude (lea ecx,[edi+edi*2]; ...) is an
 * unreproducible msvc6 expansion (docs/msvc6-allocator.md); a plain
 * memset compiles to the non-aligned rep stosd form. */

// FUNCTION: SERVER 0x100068E0
// InitPacketPool
// SIZE: 176

extern void* __cdecl fcn_1001a7f7(unsigned int size);

void __cdecl InitPacketPool(int n)
{
	g_10034624 = n;
	g_10034628 = 0;
	g_10034630 = 0;
	g_1003462c = 0;
	g_10034634 = 0;
	g_10034640 = (int) fcn_1001a7f7((unsigned int) (n * 16));
	memset((void*) g_10034640, 0, (unsigned int) (n * 16));
	g_117640b4 = 0;
	g_117640b0 = 0;
	g_117640bc = 0;
	g_117640b8 = 0;
	g_117640c0 = 0;
	g_117640c4 = 0;
	g_117640a0 = *(unsigned int*) 0x10028938;
	g_117640a4 = *(unsigned int*) 0x1002893c;
}
