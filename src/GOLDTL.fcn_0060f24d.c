/* ADDRESS: GOLDTL 0x0060f24d */
/* Native ABI is thiscall (self in ecx); MSVC 6 C has no __thiscall, so the
 * C form takes self as an ordinary first parameter. The native body is the
 * free-list splice: walk the 16-bit successor table at self+0xc4 from index
 * a1 until a2 (splice the node out) or back to a1, mark self+0x138[a2] used,
 * drop one reference from the block at self+0x128 indexed by a3, and bump
 * the self+0xe0 counter. */
int __cdecl fcn_0060f24d(void* self, unsigned short a1, unsigned short a2, unsigned short a3)
{
	unsigned short* map;
	unsigned short cur;
	unsigned short prev;
	unsigned short next;

	if (a2 == 0xffff) {
		return 0;
	}
	map = *(unsigned short**) ((char*) self + 0xc4);
	cur = map[a1];
	prev = a1;
	while (cur != a2) {
		if (cur == a1) {
			break;
		}
		prev = cur;
		cur = map[cur];
	}
	if (cur == a2) {
		next = map[cur];
		map[prev] = next;
		map[cur] = cur;
	}
	*(*(char**) ((char*) self + 0x138) + a2) = 1;
	--*(int*) (*(char**) ((char*) self + 0x128) + (a3 + a3 * 4) * 4 + 0x10);
	--*(int*) ((char*) self + 0xe0);
	return 0;
}
