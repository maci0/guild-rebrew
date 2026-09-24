/* cm_ProcessCommandQueue - Master Command Router (0x1000aac0).
 *
 * Byte-exact at the link (639/639 masked, obj 639).  Load-bearing shapes:
 *   - The head is the natural `if (held == 0) { if (type == 5) held = pkt; }
 *     else if (type == 6) { ... held = 0; }`, followed by
 *     `if (held != 0) ok = 0; if (!ok) goto advance;`.  The separate `ok`
 *     test is what keeps the reference's join `test ebx,ebx; je unlink;
 *     jmp advance` alive with arm 6 in the fallthrough slot:
 *       1. c2 lays blocks out in reverse postorder of a DFS that visits a
 *          conditional block's taken target before its fallthrough
 *          (c2 0x10703558 builds the postorder, 0x107351b7 relinks).  The
 *          `ok` test gives arm 6 a successor of its own, so the join is
 *          listed after arm 6 and preceded by an unconditional jmp.
 *       2. The jump optimiser (c2 0x10705507, run from 0x107053c9) turns
 *          `jcc L1; jmp L2; L1:` into `jncc L2` when the jmp block holds
 *          only the jmp.  The dead `ok = 0` store keeps the join's
 *          `goto advance` block non-empty through every run of it, so the
 *          join keeps `je unlink; jmp advance`; the store is deleted later.
 *       3. The late pass c2 0x10724a49 moves a block that is not fallen
 *          into, up to its first unconditional jmp, behind the jmp that
 *          targets it: the join lands after arm 5's `mov ebx,esi`.
 *     Without the `ok` test the join falls into unlink and the move drags
 *     unlink along (204/639 masked); with a `goto advance` in place of `ok = 0`
 *     the join polarity flips to `jne advance; jmp unlink` (obj 640).
 *   - `nextp` keeps &pkt[0x95] in a register across the unlink (the
 *     target's `lea eax,[esi+0x95]`); reading `next` before taking `nextp`
 *     orders the [esp+0x10] store.
 *   - The volatile `type` read pins the byte load ahead of `test ebx,ebx`
 *     instead of folding it into each `cmp byte ptr [esi],imm`.
 *   - `t2` caches the type byte for the range check (one `mov al,[esi]`
 *     feeding `cmp al,0x6a` and `cmp al,0x20`).
 *   - The range check as `< 0x6a` with the log call in the `else`, and the
 *     dispatch result tested `== 0` with the queued path trailing, put both
 *     cold blocks out of line.
 *   - The broadcast loop is a do/while with both skips in one condition
 *     (no pre-test guard); `i = 0` is written before `slot = g_connections`.
 *   - The connection flag is tested through the `g_connections[...]`
 *     subscript, which emits `test byte ptr [reg*4 + g_connections],1`.
 * `g_connections` is declared `unsigned int[]` so the 0x264264 stride indexes
 * as 0x99099 entries and emits the target's scale-4 `[reg*4 + g_connections]`. */


// FUNCTION: SERVER 0x1000aac0

#include <string.h>
#include "rebrew_types.h"
#include "rebrew_globals.h"

#include "../server_internal.h"

extern handler_func g_dispatch_table[]; /* 0x1002c3f8 */
int __cdecl ahm_ProcessEntityChain(char* cmd_payload);
int __cdecl cm_QueuePlayerCommand(unsigned int* player, unsigned char* data);
extern void __cdecl LogMessageInternal(char* file, unsigned int line, char* msg, int level);

int __cdecl cm_ProcessCommandQueue(void* a)
{
	char* tab;
	char* pkt;
	char* held;
	char* next;
	char* slot;
	char** nextp;
	int i;
	int ok;
	unsigned char type;
	unsigned char t2;

	(void) a;
	for (tab = (char*) 0x10442cf0; (int) tab < 0x11764010; tab += 0x264264) {
		pkt = *(char**) tab;
		held = 0;
		while (pkt != 0) {
			next = *(char**) (pkt + 0x95);
			nextp = (char**) (pkt + 0x95);
			type = *(volatile unsigned char*) pkt;
			ok = 1;
			if (held == 0) {
				if (type == 5) {
					held = pkt;
				}
			} else if (type == 6) {
				if (ahm_ProcessEntityChain(held) == 0) {
					ok = 0;
				}
				nextp = (char**) (held + 0x95);
				next = *nextp;
				pkt = held;
				held = 0;
			}
			if (held != 0) {
				ok = 0;
			}
			if (!ok) {
				goto advance;
			}
			/* Unlink pkt from the incoming queue head and push it onto the freelist. */
			if (pkt == *(char**) tab) {
				*(char**) tab = next;
			} else {
				*(char**) (*(char**) (pkt + 0x91) + 0x95) = *nextp;
				*(char**) (*nextp + 0x91) = *(char**) (pkt + 0x91);
			}
			*(char**) (pkt + 0x91) = 0;
			*nextp = *(char**) (tab + 8);
			*(char**) (tab + 8) = pkt;

			t2 = *(unsigned char*) pkt;
			if (t2 < 0x6a) {
				if (t2 == 0x20 && *(unsigned char*) (pkt + 0x10) == 0xe) {
					slot = (char*) &((unsigned int*) g_connections)[(unsigned int) *(unsigned char*) (pkt + 3) * 0x99099];
					if ((*(unsigned char*) slot & 0x40) != 0) {
						LogMessageInternal("D:\\Develop\\DieGildeAddOnServer\\server.c", 0x72e, "Multisync!!!", 1);
					}
				}
				if (g_dispatch_table[*(unsigned char*) pkt](pkt, 0) == 0) {
				if (*(unsigned char*) pkt == 0x20 && *(unsigned char*) (pkt + 0x10) == 0xe) {
					slot = (char*) g_connections + (unsigned int) *(unsigned char*) (pkt + 3) * 0x264264;
					memcpy((char*) 0x10442c54 + (unsigned int) *(unsigned char*) (pkt + 3) * 0x264264, pkt, 0x99);
					goto advance;
				}
				t2 = ((unsigned char*) g_connections)[(unsigned int) *(unsigned char*) (pkt + 3) * 0x264264];
				slot = (char*) g_connections + (unsigned int) *(unsigned char*) (pkt + 3) * 0x264264;
				if ((t2 & 1) != 0) {
					if (cm_QueuePlayerCommand((unsigned int*) slot, (unsigned char*) pkt) == -1) {
						return -1;
					}
				}
				*(int*) (pkt + 4) = -1;
				i = 0;
				slot = (char*) g_connections;
				do {
					if (i != (int) *(unsigned char*) (pkt + 3) &&
					    (*(unsigned char*) slot & 1) != 0) {
						if (cm_QueuePlayerCommand((unsigned int*) slot, (unsigned char*) pkt) == -1) {
							return -1;
						}
					}
					slot += 0x264264;
					i++;
				} while ((int) slot < 0x114ffe20);
				goto advance;
				}
			queued:
				if ((*(unsigned char*) &((unsigned int*) g_connections)[(unsigned int) *(unsigned char*) (pkt + 3) * 0x99099] & 1) != 0) {
					*(unsigned char*) pkt = 2;
					slot = (char*) &((unsigned int*) g_connections)[(unsigned int) *(unsigned char*) (pkt + 3) * 0x99099];
					if (cm_QueuePlayerCommand((unsigned int*) slot, (unsigned char*) pkt) == -1) {
						return -1;
					}
				}
			} else {
				LogMessageInternal("D:\\Develop\\DieGildeAddOnServer\\server.c", 0x756, "Command-Type out of Range!\n", 1);
			}
		advance:
			pkt = next;
		}
	}
	return 0;
}


// GLOBAL: SERVER 0x1002c3f8
extern handler_func g_dispatch_table[]; /* 0x1002c3f8 */
handler_func g_dispatch_table[106] = {
    0x1000d2e0, 0x1000d330, 0x1000d340, 0x1000d2e0, 0x1000d330, 0x1000d2e0, 0x1000d2e0, 0x1000d2e0, 0x1000d330, 0x1000d330, 0x1000d350, 0x1000d460, 0x1000d570, 0x1000d6e0, 0x1000d730, 0x1000d7f0,
    0x1000d8a0, 0x1000d930, 0x1000e140, 0x1000e530, 0x1000e690, 0x1000e750, 0x1000e7d0, 0x1000e8d0, 0x1000e9c0, 0x1000eaa0, 0x1000eb70, 0x1000ec00, 0x1000ef90, 0x1000f3a0, 0x1000f3a0, 0x1000f3a0,
    0x1000efb0, 0x1000f030, 0x1000f080, 0x1000f3a0, 0x1000f3a0, 0x1000f3a0, 0x1000f3a0, 0x1000f0a0, 0x1000f3a0, 0x1000f3a0, 0x1000f3a0, 0x1000f0d0, 0x1000f1a0, 0x1000f2f0, 0x1000f3a0, 0x1000f3a0,
    0x1000f3a0, 0x1000f3a0, 0x1000f3a0, 0x1000f3a0, 0x1000f3a0, 0x1000f3a0, 0x1000f3a0, 0x1000f3a0, 0x1000f3b0, 0x1000f480, 0x1000f590, 0x1000f680, 0x1000f3a0, 0x1000f730, 0x1000f3a0, 0x1000f3a0,
    0x1000f3a0, 0x1000f3a0, 0x1000f3a0, 0x1000f3a0, 0x1000f940, 0x1000f960, 0x1000f3a0, 0x1000f3a0, 0x1000f3a0, 0x1000f980, 0x1000fad0, 0x1000fbd0, 0x1000fb30, 0x1000fbd0, 0x1000fbd0, 0x1000fbd0,
    0x1000fbf0, 0x1000fbf0, 0x1000fbf0, 0x1000fc10, 0x1000fd50, 0x1000fbf0, 0x1000ff10, 0x1000ff30, 0x1000f3a0, 0x1000ff60, 0x1000ffc0, 0x10010010, 0x10010080, 0x100100a0, 0x10010140, 0x1000f3a0,
    0x10010260, 0x100102f0, 0x10010310, 0x10010350, 0x10010390, 0x1000f3a0, 0x1000f3a0, 0x1000f3a0, 0x1000f3a0, 0x1000f3a0,
};
