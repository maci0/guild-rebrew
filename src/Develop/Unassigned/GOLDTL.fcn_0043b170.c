extern int g_67a370;
extern char g_1042340[];
extern unsigned int g_1052c50;
extern int g_6b7fac;
extern int g_6b8010;
extern int g_6b8014;
extern int g_6b86d4;
extern char g_6b8018;

void __cdecl fcn_0045ccf0(unsigned int now);
char __cdecl fcn_004379a0(char* scene, char* node, unsigned int flags, char (__cdecl* cb)(char*, void*), void* ctx);
char __cdecl fcn_00432480(char* node, void* ctx);
void __cdecl fcn_0043ad10(int mode);


typedef struct {
	char* node;
	char pad[0x3d8];
} Entry_1043340;
// SIZE 0x3dc

/* Flushes cached timing and walks the scene tree, then refreshes both
 * frame-rate counters. Re-entrant calls only run the trailing mode hook. */
/* ADDRESS: GOLDTL 0x0043b170 */
void __cdecl fcn_0043b170(unsigned int flags, char force, unsigned int mode, char deep)
{
	if (g_6b86d4 < 0) {
		g_6b86d4 = 0;
	}
	if (!g_6b8018 || g_6b86d4 != 0 || !g_6b8014) {
		return;
	}
	g_6b86d4 = 1;
	if (force) {
		unsigned int now;
		unsigned int elapsed;
		unsigned int frames;
		unsigned int scale;
		int i;
		Entry_1043340* entry;
		char* node;

		now = g_6b7fac;
		fcn_0045ccf0(now);
		flags |= 0x181;
		fcn_004379a0((char*) g_67a370, 0, flags, fcn_00432480, (void*) now);
		if (deep) {
			i = 0;
			entry = (Entry_1043340*) 0x1043340;
			do {
				if (i != g_6b8010) {
					node = entry->node;
					if (node != 0 && node != g_1042340) {
						do {
							fcn_004379a0((char*) g_67a370, node, flags, fcn_00432480, (void*) (now | 0x80000000));
							node = *(char**) (node + 0x1f4);
						} while (node != g_1042340);
					}
				}
				entry++;
				i++;
			} while ((int) entry < (int) 0x1052a40);
		}
		scale = g_1052c50;
		frames = ++*(unsigned int*) 0x6b8070;
		elapsed = now - *(unsigned int*) 0x6b806c;
		if (elapsed > 60 && elapsed > 0) {
			*(unsigned int*) 0x6b8070 = 0;
			*(unsigned int*) 0x6b806c = now;
			*(unsigned int*) 0x6b8048 = frames * 1000 / (elapsed * scale);
		}
		frames = ++*(unsigned int*) 0x6b8078;
		elapsed = now - *(unsigned int*) 0x6b8074;
		if (elapsed > 10 && elapsed > 0) {
			*(unsigned int*) 0x6b8078 = 0;
			*(unsigned int*) 0x6b8074 = now;
			*(unsigned int*) 0x6b804c = frames * 1000 / (elapsed * scale);
		}
	}
	fcn_0043ad10(mode);
	g_6b86d4--;
}
