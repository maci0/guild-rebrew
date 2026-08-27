/* m_FreeTracked — debug-heap tracked free (0x10006820). */

// FUNCTION: SERVER 0x10006820
// m_FreeTracked
// SIZE: 188

extern int g_alloc_counter;          /* 0x10034638 */
extern int g_array_count;            /* 0x10034624 */
extern int g_stat1;                  /* 0x10034628 */
extern int g_stat2;                  /* 0x1003462c */
extern int g_stat3;                  /* 0x10034630 */
extern int g_stat4;                  /* 0x10034634 */
extern void* g_array_ptr;            /* 0x10034640 */
extern int g_alloc_root_count;       /* 0x117640b4 */
extern int g_alloc_root_size_total;  /* 0x117640b0 */
extern int g_alloc_root_count_max;   /* 0x117640bc */
extern int g_alloc_root_size_max;    /* 0x117640b8 */
extern int g_alloc_root_field_20;    /* 0x117640c0 */
extern int g_list_head;              /* 0x117640c4 */
extern int g_alloc_root_name;        /* 0x117640a0 */
extern int g_alloc_root_name_4;      /* 0x117640a4 */
extern int g_default_group_name;     /* 0x10028938 */
extern int g_default_group_name_4;   /* 0x1002893c */
extern void __cdecl LogMessageInternal(char* file, unsigned int line, char* msg, int level);
extern void __cdecl ReportFatalError(char* modulePath, unsigned int lineNumber, char* message);
extern void __cdecl fcn_1001ab81(void* ptr);
extern void* __cdecl fcn_1001a7f7(unsigned int size);

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
	g_alloc_counter--;
	count = g_array_count;
	pool = (char*) g_array_ptr;
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
	g_stat2--;
	block = *(int**) pool;
	block[5]--;
	g_stat1 -= size;
	block = *(int**) pool;
	block[4] -= size;
	if (g_stat1 < 0) {
		ReportFatalError("D:\\Develop\\Units\\m_alloc\\m_alloc.c", 0x17a, "Memory-Underflow Error");
	}
}

/* InitPacketPool — allocates and zeroes the packet pool (0x100068E0).
 * Target 162 bytes; compiled 143. The 19-byte delta is the target's
 * dest-alignment memset prelude (lea ecx,[edi+edi*2]; and ecx,3; sub
 * ebx,ecx; jle; rep stosb; ...; rep stosd; ...; rep stosb) — an
 * unreproducible msvc6 expansion on this toolchain: msvc6 SP6 always
 * materializes runtime counts fresh into ecx and emits the plain
 * dword+tail form (docs/msvc6-allocator.md, "m_PoolAlloc /
 * InitBuildingTypeTable" section). Probed 2026-08-27 for this exact
 * body: 15 C formulations (locals, unsigned/volatile/memory-resident
 * counts, dest-copy, reordered statements) x /O2 /Gd /Oy- plus an
 * /O1 /Ox /O2 /G5 /G6 /GB /Oi /Og- flag sweep — zero prelude hits.
 * Everything else matches: prologue, malloc call, the six zero stores,
 * and the tail (g_alloc_root_name/_4 assignments hoisted above the
 * zero stores, per the target's scheduling). */

// FUNCTION: SERVER 0x100068E0
// InitPacketPool
// SIZE: 162

void __cdecl InitPacketPool(int n)
{
	g_array_count = n;
	g_stat1 = 0;
	g_stat3 = 0;
	g_stat2 = 0;
	g_stat4 = 0;
	g_array_ptr = fcn_1001a7f7((unsigned int) (n * 16));
	memset(g_array_ptr, 0, (unsigned int) (n * 16));
	g_alloc_root_name = g_default_group_name;
	g_alloc_root_name_4 = g_default_group_name_4;
	g_alloc_root_count = 0;
	g_alloc_root_size_total = 0;
	g_alloc_root_count_max = 0;
	g_alloc_root_size_max = 0;
	g_alloc_root_field_20 = 0;
	g_list_head = 0;
}
