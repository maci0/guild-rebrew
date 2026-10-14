extern char* g_5fb5b0;
extern int g_fc52f0;
extern int g_fc28f4;
extern int g_fb98f4;
extern int g_fb9598;
extern char g_fc2700[];

char __cdecl fcn_004378c0(int, unsigned int);

/* ADDRESS: GOLD 0x00438d40 */

/* Walks a scene subtree and calls cb(node, ctx) for every node whose type
 * matches the flags; stops and returns 0 when cb returns 0. */
char __cdecl fcn_00438d40(char* scene, char* node, unsigned int flags, char (__cdecl* cb)(char*, void*), void* ctx)
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
			if (*(char**) (node + 0x1fc) != 0 && (ok & 0x80) == 0) {
				ok = fcn_00438d40(scene, *(char**) (node + 0x1fc), flags & ~0x200, cb, ctx);
			}
			if (!ok) {
				return 0;
			}
			if (flags & 0x200) {
				break;
			}
			node = *(char**) (node + 0x1f0);
			if (node == 0) {
				break;
			}
		} while (!(node[0x210] & 1));
	} else {
		if (scene == g_5fb5b0) {
			*(int*) (scene + 0x80) = g_fc52f0;
			*(int*) (scene + 0x84) = g_fc28f4;
			*(int*) (scene + 0xa4) = g_fb98f4;
			*(int*) (scene + 0xa8) = g_fb9598;
		}
		for (n = *(char**) (scene + 0x80); n != 0 && n != g_fc2700; n = *(char**) (n + 0x1f0)) {
			if (!fcn_00438d40(scene, n, flags, cb, ctx)) {
				return 0;
			}
		}
	}
	return 1;
}
