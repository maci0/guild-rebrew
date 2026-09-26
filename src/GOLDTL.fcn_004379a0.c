extern int g_67a370;
extern char* g_1043254;
extern char* g_1042538;
extern char* g_1040c74;
extern char* g_1040958;
extern char g_1042340[];

char __cdecl fcn_004378c0(int, unsigned int);

// FUNCTION: GOLDTL 0x4379a0
// SIZE: 288

/* Walks a scene subtree and calls cb(node, ctx) for every node whose type
 * matches the flags; stops and returns 0 when cb returns 0. */
char __cdecl fcn_004379a0(char* scene, char* node, unsigned int flags, char (__cdecl* cb)(char*, void*), void* ctx)
{
	char* n;
	char ok;

	if (flags == 0) {
		return 0;
	}
	if (node != 0) {
		do {
			ok = 1;
			if (fcn_004378c0(*(int*) (node + 0x218), flags)) {
				ok = cb(node, ctx);
				if (!ok) {
					return 0;
				}
			}
			if (*(char**) (node + 0x200) != 0 && (ok & 0x80) == 0) {
				ok = fcn_004379a0(scene, *(char**) (node + 0x200), flags & ~0x200, cb, ctx);
			}
			if (!ok) {
				return 0;
			}
			if (flags & 0x200) {
				break;
			}
			node = *(char**) (node + 0x1f4);
			if (node == 0) {
				break;
			}
		} while (!(node[0x214] & 1));
	} else {
		if (scene == ((char*)g_67a370)) {
			*(int*) (scene + 0x80) = (*(int*)&g_1043254);
			*(int*) (scene + 0x84) = (*(int*)&g_1042538);
			*(int*) (scene + 0xa4) = (*(int*)&g_1040c74);
			*(int*) (scene + 0xa8) = (*(int*)&g_1040958);
		}
		for (n = *(char**) (scene + 0x80); n != 0 && n != g_1042340; n = *(char**) (n + 0x1f4)) {
			if (!fcn_004379a0(scene, n, flags, cb, ctx)) {
				return 0;
			}
		}
	}
	return 1;
}
