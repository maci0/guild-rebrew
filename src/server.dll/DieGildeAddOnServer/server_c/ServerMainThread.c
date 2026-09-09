// FUNCTION: SERVER 0x100093a0
#include "../../Units/Error/error.h"
#include "../../Units/m_alloc/m_alloc.h"

#include <stdio.h>
#include <string.h>
#include <windows.h>
#include <winsock2.h>
__declspec(dllimport) unsigned int __stdcall timeGetTime(void);
extern void __cdecl srand(unsigned int); /* CRT srand */

/* Command layer (local externs — server.c uses different signatures) */
int __cdecl cm_QueuePlayerCommand(unsigned int* player, unsigned char* data);
int __cdecl cm_ClosePlayerConnection(unsigned int* player_slot);
int __cdecl cm_ProcessCommandQueue(void);
/* Entity lifecycle (local externs) */
/* Network functions (local externs — signatures differ from net.h) */
int __cdecl AcceptConnections(void);
void __cdecl CleanupSockets(void);
int __cdecl ProcessReceiveData(void);
int __cdecl ProcessSendData(void);
int __cdecl SendBroadcastPacket(unsigned char* data, int size);

void __cdecl RecvGameSavegame(void);
int __cdecl srv_Init(void);
int __cdecl AdvanceGameClock(int* clock_state, int a2, int a3, int a4);
void __cdecl sim_SetSyncParams(int target, unsigned char type_id, unsigned int field_6, unsigned int field_10);
extern int g_max_players; /* 0x11764084 */
extern int g_tick_rate;    /* 0x11764088 */

/* ServerMainThread: the main server orchestration loop.
 * PHASE 0: read game.ini config, init logging/sockets/game data.
 * PHASE 1 (Lobby): accept connections until every player has the
 *   0x800 ready flag; announce server info every 3s; handle
 *   disconnects (0x1000) and host disconnect (0x400).
 * PHASE 4 (Data send): stream the savegame to non-host clients in
 *   128-byte chunks (cmd 0x09), total size first (cmd 0x08).
 * PHASE 3 (Data receive): wait for host savegame data (flag 0x08).
 * PHASE 5 (Player allocation): wait for each player's character
 *   entity (flag 0x10).
 * PHASE 6 (Game loop): advance the game clock, broadcast sync
 *   packets (cmd 0x1E/0x20), process the command queue.
 *
 * STATUS: SIZE_MISMATCH, 1162/2434, obj 2433 against a 2434 target.
 *
 * The residual is one layout-pass decision, not missing or wrong code.
 * Under an optimal alignment 584/627 instructions are already identical;
 * `match_count` is a *positional* byte compare (relocation slots masked,
 * rebrew/src/rebrew/core/matching.py:488), so the 1-byte deficit shifts
 * every later byte and scores it as a miss. The 43 instructions that
 * still differ are almost all register-name choices, not wrong code.
 *
 * Root cause, single instruction: at target 0x1000963f the branch into
 * the host-slot block is `jne rel32` (6 bytes) because the block sits out
 * of line, ending in a 5-byte backward `jmp`. MSVC places the same block
 * inline here, so the branch is `jne rel8` (2 bytes) and the block needs
 * only a 2-byte skip: 6+5 against 2+2+2 is exactly the 3-byte deficit.
 * In the 672-byte prefix that is still aligned, the ONLY non-relocation
 * byte differences are that `jne` and three `jmp 0x961`/`jmp 0x95e`
 * displacements, which are themselves consequences of the same 3 bytes.
 *
 * Failed attempts (all compiled and measured, see docs/msvc6-c-shapes.md
 * section 17 for the three earlier placement experiments):
 *   - label moved past the enclosing while-loop with a `goto` bypass,
 *     so the jump crosses a loop boundary: identical bytes, 1122.
 *   - host-slot store rewritten from the scaled array index to a byte
 *     offset (`*(unsigned int*)((char*)base + i*0x264264)`): identical
 *     shift-chain codegen, 1122.
 *   - constant 7 hoisted into a shared `unsigned char` local to reproduce
 *     the target's `mov bl, 7`: still `mov ebx, 7`, and it widened
 *     `sbb al,al`/`and al,bl` to `sbb eax,eax`/`and eax,ebx`. 1122.
 *   - payload_src/payload_dst locals inlined into the `memcpy` call:
 *     1120, worse. Reverted.
 *   - loop rewritten as `do/while` and as `for(;;)` with two breaks:
 *     byte-identical output both times; MSVC canonicalises this loop
 *     regardless of the source shape.
 *   - host-slot search rewritten so the flag store is inline in the loop
 *     body instead of a `goto` target: 776, much worse. The out-of-line
 *     `goto host_slot_found` shape is the one that matches.
 *   - `goto` target moved to just before `cleanup_and_exit` and to just
 *     after the phase-1 log call: identical bytes both times, so source
 *     position does not steer the layout pass.
 *   - payload_src rewritten as `(char*)offset + (unsigned)base` and the
 *     `memcpy` operands reordered three ways: identical bytes each time.
 *   - `+ 1` counter written as a compound assign, through three different
 *     locals, and split into read/add/store: identical bytes each time.
 *
 * What did move it (1122 -> 1162):
 *   - the phase-5 wait loop tests the 0x114ffe20 bound at the TOP and
 *     `phase_complete` at the BOTTOM; the reverse order costs 22 bytes.
 *   - the sync-packet globals 0x1003588c and 0x10035888 must be read at
 *     their point of use, not hoisted into a local.
 *   - 0x10035880 likewise, but 0x10035884 must stay in a local.
 *
 * Remaining delta: 1 byte of object size and 43 instructions that differ
 * only in which register the value lands in (ebx/ecx and eax/edx pairs
 * around the sync counter at 0x10035880). Not reachable by any statement
 * or loop reshaping tried here.
 *
 * 2026-09-08 round 7 re-measured this with an order-based instruction diff
 * that masks branch displacements and relocated operands, so layout shifts
 * cannot hide content differences (.scratch/l7-smt/sdiff.py, capstone on
 * both sides).  578 of the target's 627 instructions already align, leaving
 * 33 hunks, and they are not spread out: TWO of them are the whole story.
 * Both are the same fault, a cold `goto` block that the target keeps out of
 * line and msvc6 places inline here:
 *   - the host-slot block at target 0x1000973a (T[234:243]), reached by
 *     `jne rel32` and ending in a 5-byte backward `jmp`;
 *   - the unsynced-player block at target 0x10009b66 (T[515:516]).
 * The rest are consequences: `mov bl,7` against `mov ebx,7`, `and al,bl`
 * against `and eax,ebx`, the sync-packet store order, and the ebx/ecx and
 * ecx/edx pairs in the tail.
 *
 * Ruled out this round, each compiled and scored against the 1162 baseline:
 * preloading 0x10035880 and 0x10035888 into locals before the packet stores,
 * in both orders (1148 both, object 2430); the 7 constant hoisted into an
 * `unsigned char` local (1162, `mov ebx,7` unchanged); `payload_src` written
 * with the offset first (1162); the tick accumulator split into a named
 * local three ways and the sync counter likewise (1162 each); the
 * phase_complete store hoisted out of the unsynced-player loop into its own
 * labelled block, placed both before `check_transfer_state` (1111, object
 * 1974) and after the pending-sync loop (1162); a trampoline label between
 * `host_slot_found` and `send_start_commands` (1162); the host-slot search
 * inverted to `if ((*p & 0x400) != 0) goto` (766, much worse); and the
 * host-slot store as a byte-offset expression and as an explicit
 * read-or-write pair (1162 each).
 * No change kept; the file is byte-identical to where round 6 left it.
 * Harness: .scratch/l7-smt/ (build.sh, sdiff.py, try.sh).
 *
 * Round 8 added five more, all scored against 1162 and reverted: the
 * unsynced-player test split into nested ifs (1162); the host-slot search
 * as a while loop with a `goto no_host_slot` exit (747); the pending-start
 * loop with its bound test moved into the body (778); `host_flags_word`
 * compared against a zeroed local to chase the target's `cmp eax,ebp`
 * (1162); and `i` reset inside the host-slot block (1162).
 *
 * PROVEN is NOT reachable for this function with the current rebrew prove,
 * and the reason is not the watch list.  Runs attempted: full function with
 * all nine written globals watched (0x10034680, 0x10035880, 0x101deac0,
 * 0x101deaf0, 0x11764084, 0x11764088, 0x11764090, 0x101deae8, 0x101deb00)
 * at --timeout 60, 600 and 900 with --loop-bound 1 and 2; and slices at
 * [0:20], [0:160], [556:690], [1856:2026], [2116:2242], [2360:2388] and
 * [2360:2389].  Every one returns "No terminal states reached".
 * The blocker is angr, not the C: this function makes 55 calls, 9 of them
 * indirect through import thunks (0x1002403c, 0x10024058, 0x1002405c,
 * 0x10024060, 0x10024064, 0x10024154 — GetTickCount, Sleep and friends),
 * which have no resolvable target in the loaded image.  The control cases
 * confirm the pattern: 0x1001bdd0 (123B, no calls) proves in seconds, while
 * 0x100068e0 InitPacketPool (162B, one call plus `rep stos`) fails with the
 * same message despite being 15x smaller.  Mid-function slices additionally
 * have no `ret`, so they can never reach a terminal state, and the two real
 * `ret`s sit at target offsets 2386 and 2431, where the 1-byte size deficit
 * has already desynchronised the compiled offsets ([2400:2434] is rejected
 * outright as out of range for the 2433-byte object).
 * Getting this off SIZE_MISMATCH needs import-thunk stubbing in prove.py,
 * not a source change here.
 *
 * Round 9 (2026-09-09) attacked the two cold blocks directly, with
 * .scratch/smt-a/ as the harness (probe.sh, bskew.py, sdiff.py).  The
 * disassembly re-derivation first: both regions are separable cold tails,
 * not interleaved code.  Each is a single basic block with one predecessor
 * and one successor, physically wedged into an unrelated chain:
 *   - host-slot store, 33 bytes / 10 instructions, target 0x1000973a-0x1000975b
 *     (`mov eax,ecx; shl/add chain; or dword [eax*4+0x101deb00],8;
 *     jmp 0x10009657`), reached only by `jne rel32` from 0x1000963f and
 *     ending in a 5-byte backward jmp to the send_start entry.  It sits
 *     between the phase-5 transfer loop's exit `jmp` (0x10009738) and the
 *     transfer_pending landing (0x1000975b).
 *   - unsynced-player, 7 bytes, target 0x10009b66-0x10009b6c
 *     (`mov edi,1; jmp 0x10009afa`), reached only by `je rel32` from
 *     0x10009a95 (the check-sync loop), sitting between the
 *     `0x11764090 == 0` branch tail (mov [0x101deaf0],ebx; jmp 0x10009b81)
 *     and the else-if head (0x10009b6d).
 *
 * Fresh probes, each compiled and inspected for the two block positions and
 * the loop shapes (all scored against the 1162 baseline unless noted):
 *   - Bisection by deletion: removing the phase-5 transfer content (S1),
 *     the send-start loop (S2), or both (S3) leaves the host store glued
 *     inline at obj+0x2b5 right after the CleanupSockets call.  The code
 *     downstream of the branch site does not steer the placement at all.
 *   - Distance inflation (S5/S6): ~350 bytes of filler pushed the store
 *     past the jne's rel8 range and msvc6 still kept it inline, accepting
 *     a rel32.  Out-of-line placement is not a rel8/rel32 decision.
 *   - Transfer-loop polarity: rewriting the phase-5 search as
 *     `if ((*p & 8) == 0) { advance; continue; } goto transfer_pending;`
 *     flips msvc6 to the target's classic loop shape (test; jne; add; cmp;
 *     jl; jmp), matching the target's instruction sequence exactly, but the
 *     host store still does not land in the target's gap: 772 (E1).  The
 *     positional score is all-or-nothing; no single-region fix helps.
 *   - Same inversion on the compound-condition check-sync loops A/B via a
 *     `||` guard: transfer loop classic, loops A and B unaffected (the
 *     rotation lever works only on the single-condition loop), 772 (G1,
 *     628 insns; loop A inverted alone stayed rotated at 629 insns).
 *   - Both cold bodies moved textually to the end of the function before
 *     cleanup_and_exit (VF): byte-identical 1162.  Source position of the
 *     cold code confirmed irrelevant for the unsynced block too.
 *   - `#pragma optimize("", off)` around the whole function: 847
 *     instructions of unoptimised code, unusable; no pragma letter steers
 *     the layout pass while the optimiser is on.
 *
 * Verdict after rounds 6-9 (every compiled variant measured): both cold
 * blocks are emitted by this msvc6 build adjacent to their source loop's
 * chain, and the original compile deferred them into gaps inside unrelated
 * chains.  No C structure tried (label position, branch polarity, guard
 * form, duplication, cold-tail placement, region size, pragmas)
 * reproduces the deferral.  The remaining 43 instruction-level
 * differences (register-name pairs and store orders around the send-start
 * and sync-packet loops) are allocator fixed points downstream of the
 * same layout decision.  This is a genuine layout-pass artifact, matching
 * docs/msvc6-c-shapes.md section 17; byte-EXACT needs a code-layout lever
 * that does not exist in C89 for this compiler, and PROVEN needs
 * import-thunk stubbing in prove.py. */

int __stdcall ServerMainThread(void* lpThreadParameter)
{
	char* module_path;
	char* ini_tail;
	unsigned int* player_slot;
	unsigned int* transfer_progress;
	unsigned int* payload_src;
	unsigned int* payload_dst;
	unsigned int connected_players;
	unsigned int now_tick;
	unsigned int current_tick;
	unsigned int last_announce_tick;
	unsigned int sync_timer;
	int i;
	int phase_complete;
	unsigned int sent_bytes;
	unsigned int host_flags_word;
	unsigned int total_size;
	unsigned char host_flags;
	unsigned char cmd_buffer_primary[0x99];
	unsigned char cmd_buffer_secondary[0x99];
	unsigned int startup_cfg_words[27];
	char log_buffer[64];

	module_path = (char*) 0x101de9a0;
	GetModuleFileNameA(0, module_path, 0x104);
	ini_tail = strrchr(module_path, 0x5c);
	*(unsigned int*) (ini_tail + 0) = *(unsigned int*) 0x1002993c;
	*(unsigned int*) (ini_tail + 4) = *(unsigned int*) 0x10029940;
	*(unsigned short*) (ini_tail + 8) = *(unsigned short*) 0x10029944;

	g_tick_rate = (int) GetPrivateProfileIntA((char*) 0x1002992c, (char*) 0x10029934, 0x1d6b, module_path);
	g_max_players = 2;
	GetPrivateProfileStringA(
		(char*) 0x100298f8,
		(char*) 0x10029900,
		(char*) 0x1002990c,
		(char*) 0x10029594,
		0x104,
		module_path
	);

	memcpy(startup_cfg_words, lpThreadParameter, 0x6a);

	if (*(unsigned short*) ((char*) startup_cfg_words + 2) == 1) {
		*((unsigned char*) startup_cfg_words + 0x27) = 0;
		*(unsigned int*) 0x11764084 = *(unsigned int*) ((char*) startup_cfg_words + 0x26) & 0xff;
	}
	else if (*(unsigned short*) ((char*) startup_cfg_words + 2) == 4) {
		*((unsigned char*) startup_cfg_words + 0x27) = 0;
		*(unsigned int*) 0x11764084 = *(unsigned int*) ((char*) startup_cfg_words + 0x26) & 0xff;
	}

	srv_Init();
	sprintf(log_buffer, (char*) 0x100298d8, *(int*) 0x11764084);
	LogMessageInternal((char*) 0x100298b0, 0x131, log_buffer, 1);

	srand(timeGetTime());
	last_announce_tick = 0;
	phase_complete = 0;
	while (phase_complete == 0) {
		if (*(int*) 0x10034680 != 0) {
			break;
		}
		connected_players = 0;
		player_slot = (unsigned int*) 0x101deb00;
		do {
			if (*player_slot != 0) {
				connected_players = connected_players + 1;
			}
			player_slot = (unsigned int*) ((char*) player_slot + 0x264264);
		} while ((int) player_slot < 0x114ffe20);

		AcceptConnections();

		if (connected_players == *(unsigned int*) 0x11764084) {
			phase_complete = 1;
			for (player_slot = (unsigned int*) 0x101deb00; (int) player_slot < 0x114ffe20;
				player_slot = (unsigned int*) ((char*) player_slot + 0x264264)) {
				if ((*player_slot != 0) && ((*player_slot & 0x800) == 0)) {
					phase_complete = 0;
					goto lobby_check_announce;
				}
			}
			LogMessageInternal((char*) 0x100298b0, 0x14e, (char*) 0x10029890, 1);
		}

	lobby_check_announce:
		now_tick = timeGetTime();
		if ((3000 < now_tick - last_announce_tick) || phase_complete) {
			*((unsigned char*) startup_cfg_words + 0x27) = (unsigned char) connected_players;
			SendBroadcastPacket((unsigned char*) 0x3039, (int) startup_cfg_words);
			last_announce_tick = timeGetTime();
		}

		if ((unsigned int) ProcessReceiveData() == 0xffffffff) {
			LogMessageInternal((char*) 0x100298b0, 0x15f, (char*) 0x1002986c, 1);
			goto cleanup_and_exit;
		}

		if ((unsigned int) ProcessSendData() == 0xffffffff) {
			LogMessageInternal((char*) 0x100298b0, 0x16a, (char*) 0x1002986c, 1);
			goto cleanup_and_exit;
		}

		player_slot = (unsigned int*) 0x101deb00;
		do {
			if ((*player_slot & 0x1000) != 0) {
				if ((*player_slot & 0x400) != 0) {
					LogMessageInternal((char*) 0x100298b0, 0x176, (char*) 0x10029834, 1);
					goto cleanup_and_exit;
				}
				cm_ClosePlayerConnection(player_slot);
			}
			player_slot = (unsigned int*) ((char*) player_slot + 0x264264);
		} while ((int) player_slot < 0x114ffe20);

		Sleep(0x1e);
	}

	player_slot = (unsigned int*) 0x101deb00;
	do {
		if ((*player_slot & 1) != 0) {
			*player_slot = (*player_slot & 0xfffffdff) | 0x4004;
		}
		player_slot = (unsigned int*) ((char*) player_slot + 0x264264);
	} while ((int) player_slot < 0x114ffe20);

	i = 0;
	player_slot = (unsigned int*) 0x101deb00;
	do {
		if ((*player_slot & 0x400) == 0) {
			player_slot = (unsigned int*) ((char*) player_slot + 0x264264);
			i = i + 1;
			continue;
		}
		goto host_slot_found;
	} while ((int) player_slot < 0x114ffe20);

	CleanupSockets();

send_start_commands:
	Sleep(2000);
	i = 0;
	player_slot = (unsigned int*) 0x101deb00;
	do {
		host_flags_word = *player_slot;
		if (host_flags_word != 0) {
			cmd_buffer_primary[0] = 4;
			cmd_buffer_primary[3] = 0xff;
			*(unsigned int*) (cmd_buffer_primary + 4) = 0xffffffff;
			*(unsigned int*) (cmd_buffer_primary + 0xc) = 0;
			cmd_buffer_primary[0x10] = (unsigned char) ((((host_flags_word & 8) != 0) ? 7 : 0) + 2);
			if (cm_QueuePlayerCommand(player_slot, cmd_buffer_primary) == -1) {
				goto cleanup_and_exit;
			}

			cmd_buffer_primary[0] = 0x20;
			cmd_buffer_primary[3] = 0xff;
			*(unsigned int*) (cmd_buffer_primary + 4) = 0xffffffff;
			*(unsigned int*) (cmd_buffer_primary + 0xc) = 0;
			cmd_buffer_primary[0x10] = 7;
			*(unsigned int*) (cmd_buffer_primary + 0x11) = (unsigned int) i;
			i = i + 1;
			if (cm_QueuePlayerCommand(player_slot, cmd_buffer_primary) == -1) {
				goto cleanup_and_exit;
			}
		}
		player_slot = (unsigned int*) ((char*) player_slot + 0x264264);
	} while ((int) player_slot < 0x114ffe20);

	LogMessageInternal((char*) 0x100298b0, 0x1ca, (char*) 0x10029824, 1);
	phase_complete = 0;
	while (phase_complete == 0) {
		if (*(int*) 0x10034680 != 0) {
			break;
		}

		phase_complete = 1;
		player_slot = (unsigned int*) 0x101deb00;
		do {
			if ((*player_slot & 8) != 0) {
				goto transfer_pending;
			}
			player_slot = (unsigned int*) ((char*) player_slot + 0x264264);
		} while ((int) player_slot < 0x114ffe20);
		goto wait_start_io;

	host_slot_found:
		((unsigned int*) 0x101deb00)[i * 0x99099] |= 8;
		goto send_start_commands;

	transfer_pending:
		phase_complete = 0;

	wait_start_io:
		if ((unsigned int) ProcessReceiveData() == 0xffffffff) {
			LogMessageInternal((char*) 0x100298b0, 0x1df, (char*) 0x1002986c, 1);
			goto cleanup_and_exit;
		}

		if ((unsigned int) ProcessSendData() == 0xffffffff) {
			LogMessageInternal((char*) 0x100298b0, 0x1df, (char*) 0x1002986c, 1);
			goto cleanup_and_exit;
		}

		Sleep(0x1e);
	}

	RecvGameSavegame();
	LogMessageInternal((char*) 0x100298b0, 0x1f9, (char*) 0x1002980c, 1);
	if ((*(unsigned char*) 0x101de464 & 4) == 0) {
		LogMessageInternal((char*) 0x100298b0, 0x1ff, (char*) 0x100297fc, 1);
		do {
			phase_complete = 1;
			player_slot = (unsigned int*) 0x101deb00;
			transfer_progress = (unsigned int*) 0x101deac8;
			do {
				if ((*player_slot & 4) != 0) {
					sent_bytes = *transfer_progress;
					if (sent_bytes == 0xffffffff) {
						total_size = *(unsigned int*) 0x101deac0;
						cmd_buffer_primary[0] = 8;
						cmd_buffer_primary[3] = 0xff;
						*(unsigned int*) (cmd_buffer_primary + 4) = sent_bytes;
						*(unsigned int*) (cmd_buffer_primary + 0xc) = 0;
						*(unsigned int*) (cmd_buffer_primary + 0x10) = total_size;
						if (cm_QueuePlayerCommand(player_slot, cmd_buffer_primary) == -1) {
							goto cleanup_and_exit;
						}
						*transfer_progress = 0;
					}
					else {
						payload_src = (unsigned int*) ((char*) *(void**) 0x101deae8 + sent_bytes);
						payload_dst = (unsigned int*) (cmd_buffer_primary + 0x10);
						cmd_buffer_primary[0] = 9;
						cmd_buffer_primary[3] = 0xff;
						*(unsigned int*) (cmd_buffer_primary + 4) = 0xffffffff;
						*(unsigned int*) (cmd_buffer_primary + 0xc) = 0;
						memcpy(payload_dst, payload_src, 0x80);

						if (cm_QueuePlayerCommand(player_slot, cmd_buffer_primary) != -1) {
							*transfer_progress = *transfer_progress + 0x80;
						}
						else {
							LogMessageInternal((char*) 0x100298b0, 0x228, (char*) 0x100297e4, 1);
						}

						sent_bytes = *transfer_progress;
						if (sent_bytes >= *(unsigned int*) 0x101deac0) {
							*player_slot = *player_slot & 0xfffffffb;
						}
					}

					phase_complete = 0;
				}

				transfer_progress = transfer_progress + 1;
				player_slot = (unsigned int*) ((char*) player_slot + 0x264264);
			} while ((int) transfer_progress < 0x101deae8);

			if ((unsigned int) ProcessReceiveData() == 0xffffffff) {
				LogMessageInternal((char*) 0x100298b0, 0x23a, (char*) 0x1002986c, 1);
				goto cleanup_and_exit;
			}

			if ((unsigned int) ProcessSendData() == 0xffffffff) {
				LogMessageInternal((char*) 0x100298b0, 0x23a, (char*) 0x1002986c, 1);
				goto cleanup_and_exit;
			}

			Sleep(0x1e);
		} while (phase_complete == 0);
	}
	else {
		player_slot = (unsigned int*) 0x101deb00;
		do {
			if ((*player_slot & 4) != 0) {
				*player_slot = *player_slot & 0xfffffffb;
			}
			player_slot = (unsigned int*) ((char*) player_slot + 0x264264);
		} while ((int) player_slot < 0x114ffe20);
	}

	m_FreeTracked(*(void**) 0x101deae8);
	host_flags = *(unsigned char*) 0x101de464;
	*(void**) 0x101deae8 = (void*) 0;
	*(unsigned int*) 0x101deac0 = 0;

	if ((host_flags & 4) == 0) {
		LogMessageInternal((char*) 0x100298b0, 0x262, (char*) 0x100297bc, 1);
		player_slot = (unsigned int*) 0x101deb00;
		do {
			if ((*player_slot & 1) != 0) {
				*player_slot = *player_slot | 0x10;
			}
			player_slot = (unsigned int*) ((char*) player_slot + 0x264264);
		} while ((int) player_slot < 0x114ffe20);

		phase_complete = 0;
		while (phase_complete == 0) {
			phase_complete = 1;
			player_slot = (unsigned int*) 0x101deb00;
			while (phase_complete != 0) {
				if ((int) player_slot >= 0x114ffe20) {
					break;
				}
				if ((*player_slot & 0x10) != 0) {
					phase_complete = 0;
				}
				player_slot = (unsigned int*) ((char*) player_slot + 0x264264);
			}

			if ((unsigned int) ProcessReceiveData() == 0xffffffff) {
				LogMessageInternal((char*) 0x100298b0, 0x278, (char*) 0x1002986c, 1);
				goto cleanup_and_exit;
			}

			if ((unsigned int) ProcessSendData() == 0xffffffff) {
				LogMessageInternal((char*) 0x100298b0, 0x278, (char*) 0x1002986c, 1);
				goto cleanup_and_exit;
			}

			Sleep(0x1e);
		}
	}

	player_slot = (unsigned int*) 0x101deb00;
	do {
		if ((*player_slot & 1) != 0) {
			cmd_buffer_secondary[0] = 4;
			cmd_buffer_secondary[3] = 0xff;
			*(unsigned int*) (cmd_buffer_secondary + 4) = 0xffffffff;
			*(unsigned int*) (cmd_buffer_secondary + 0xc) = 0;
			cmd_buffer_secondary[0x10] = 4;
			if (cm_QueuePlayerCommand(player_slot, cmd_buffer_secondary) == -1) {
				goto cleanup_and_exit;
			}
		}
		player_slot = (unsigned int*) ((char*) player_slot + 0x264264);
	} while ((int) player_slot < 0x114ffe20);

	LogMessageInternal((char*) 0x100298b0, 0x2a8, (char*) 0x100297b0, 1);

	for (;;) {
		if (*(int*) 0x10034680 != 0) {
			*(int*) 0x10034680 = 0;
			return 0;
		}

		Sleep(0x1e);
		current_tick = GetTickCount();
		phase_complete = 0;
		player_slot = (unsigned int*) 0x101deb00;
		do {
			if ((*player_slot != 0) && ((*player_slot & 0x40) != 0)) {
				goto check_sync_all_players;
			}
			player_slot = (unsigned int*) ((char*) player_slot + 0x264264);
		} while ((int) player_slot < 0x114ffe20);
		goto process_pending_sync;

	check_sync_all_players:
		phase_complete = 0;
		player_slot = (unsigned int*) 0x101deb00;
		do {
			if ((*player_slot != 0) && ((*player_slot & 0x40) == 0)) {
				phase_complete = 1;
				goto check_transfer_state;
			}
			player_slot = (unsigned int*) ((char*) player_slot + 0x264264);
		} while ((int) player_slot < 0x114ffe20);

	process_pending_sync:
		player_slot = (unsigned int*) 0x101deb00;
		do {
			if ((*player_slot != 0) && ((*player_slot & 0x40) != 0)) {
				LogMessageInternal((char*) 0x100298b0, 0x2ce, (char*) 0x100297a0, 1);
				*player_slot = *player_slot & 0xffffffbf;
				if (cm_QueuePlayerCommand(player_slot, (unsigned char*) ((char*) player_slot + 0x264154)) == -1) {
					goto cleanup_and_exit;
				}
			}
			player_slot = (unsigned int*) ((char*) player_slot + 0x264264);
		} while ((int) player_slot < 0x114ffe20);

	check_transfer_state:
		if (*(int*) 0x11764090 == 0) {
			if (phase_complete) {
				goto game_loop_network_io;
			}

			*(int*) 0x11764090 = 1;
			phase_complete = 1;
			player_slot = (unsigned int*) 0x101deb00;
			do {
				if ((*player_slot != 0) && ((*player_slot & 0x20) == 0)) {
					phase_complete = 0;
				}
				player_slot = (unsigned int*) ((char*) player_slot + 0x264264);
			} while ((int) player_slot < 0x114ffe20);

			*(int*) 0x11764090 = phase_complete;
			if (!phase_complete) {
				goto game_loop_network_io;
			}

			player_slot = (unsigned int*) 0x101deb00;
			do {
				if (*player_slot != 0) {
					*player_slot = *player_slot & 0xffffffdf;
				}
				player_slot = (unsigned int*) ((char*) player_slot + 0x264264);
			} while ((int) player_slot < 0x114ffe20);
			*(unsigned int*) 0x101deaf0 = current_tick;
		}
		else if (phase_complete || (*(unsigned int*) 0x101deaf0 > current_tick)) {
			goto game_loop_network_io;
		}

		AdvanceGameClock((int*) 0x10035880, 0, 1, 0);
		player_slot = (unsigned int*) 0x101deb00;
		do {
			if (*player_slot != 0) {
				/* The clock struct at 0x10035880 is copied into the packet
				 * at cmd+0x10, so the 0x10035888 word lands at cmd+0x18.
				 * Target writes it as [esp+0x30]; the buffer base is
				 * esp+0x18 after the two argument pushes. */
				sync_timer = *(unsigned int*) 0x10035884;
				*(unsigned int*) (cmd_buffer_primary + 0x14) = sync_timer;
				*(unsigned int*) (cmd_buffer_primary + 0x10) = *(unsigned int*) 0x10035880;
				cmd_buffer_primary[0] = 0x1e;
				cmd_buffer_primary[3] = 0xff;
				*(unsigned int*) (cmd_buffer_primary + 4) = 0xffffffff;
				*(unsigned int*) (cmd_buffer_primary + 0xc) = 0;
				*(unsigned int*) (cmd_buffer_primary + 0x18) = *(unsigned int*) 0x10035888;
				*(unsigned short*) (cmd_buffer_primary + 0x1c) = *(unsigned short*) 0x1003588c;
				if (cm_QueuePlayerCommand(player_slot, cmd_buffer_primary) == -1) {
					goto cleanup_and_exit;
				}
			}
			player_slot = (unsigned int*) ((char*) player_slot + 0x264264);
		} while ((int) player_slot < 0x114ffe20);

		if (*(unsigned short*) 0x10035884 >= 0x17) {
			phase_complete = 1;
			player_slot = (unsigned int*) 0x101deb00;
			do {
				if (*player_slot != 0) {
					cmd_buffer_secondary[0] = 0x20;
					cmd_buffer_secondary[3] = 0xff;
					*(unsigned int*) (cmd_buffer_secondary + 4) = 0xffffffff;
					*(unsigned int*) (cmd_buffer_secondary + 0xc) = 0;
					cmd_buffer_secondary[0x10] = 2;
					if (phase_complete) {
						*(unsigned int*) (cmd_buffer_secondary + 0x11) = 1;
						phase_complete = 0;
					}
					else {
						*(unsigned int*) (cmd_buffer_secondary + 0x11) = 0;
					}
					if (cm_QueuePlayerCommand(player_slot, cmd_buffer_secondary) == -1) {
						goto cleanup_and_exit;
					}
					*(int*) 0x11764090 = 0;
				}
				player_slot = (unsigned int*) ((char*) player_slot + 0x264264);
			} while ((int) player_slot < 0x114ffe20);

			sent_bytes = *(unsigned int*) 0x10035880 + 1;
			*(unsigned int*) 0x10035880 = sent_bytes;
			sim_SetSyncParams(0x10035880, 6, 0, 0);
		}

		*(unsigned int*) 0x101deaf0 += *(unsigned int*) 0x1002c3f0;

	game_loop_network_io:
		if ((unsigned int) ProcessReceiveData() == 0xffffffff) {
			LogMessageInternal((char*) 0x100298b0, 0x348, (char*) 0x1002986c, 1);
			goto cleanup_and_exit;
		}

		if ((unsigned int) ProcessSendData() == 0xffffffff) {
			LogMessageInternal((char*) 0x100298b0, 0x348, (char*) 0x1002986c, 1);
			goto cleanup_and_exit;
		}

		if (cm_ProcessCommandQueue() == -1) {
			goto cleanup_and_exit;
		}
	}

cleanup_and_exit:
	CleanupSockets();
	return 0;
}
