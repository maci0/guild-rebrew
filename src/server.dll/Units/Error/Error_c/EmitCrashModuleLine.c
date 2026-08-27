/* EmitCrashModuleLine — crash-log module line emitter (0x10002fc0). */

// CFLAGS: /O2 /Gd
// FUNCTION: SERVER 0x10002FC0
// EmitCrashModuleLine
// SIZE: 376
// NOTE: semantically complete reconstruction (verified statement-by-statement
// against the target disasm).  Byte-exact so far: the module-search loop
// (offsets 0x00-0x3e, incl. the hoisted st[2] load, unsigned jb/jbe bounds and
// the lea [edi+ebp+0x10] stride), both return epilogues (xor al,al / mov al,1),
// frame size 0x1c, and the GetDebugRecordByIndex call setup (mod kept in edx).
// Remaining deltas (0x3f onward, 39 structural instructions, 183/376 byte
// match) are a single MSVC6 register-allocation cascade, same class as
// ValidateAndAssignOffice (docs/msvc6-allocator.md):
//  - found block: the tbuf byte temps land in CL instead of AL (a0-moffs form
//    missing), so the first dword temp takes EAX (a1) instead of ECX;
//  - the extra=0 store is hoisted to the top of the found block and `extra` is
//    homed in the dead arg slot [esp+0x30]; the reference keeps it at
//    [esp+0x14] immediately before the first branch;
//  - frame slots: ours = written@0x10, sp@0x18, linebuf coalesced into
//    tbuf@0x1c, extra@arg slot; reference = linebuf@0x10, extra@0x14,
//    written@0x18, tbuf@0x1c, sp spilled as a word to the arg slot;
//  - tail: linebuf word/byte stores are emitted right after their loads (ref:
//    deferred into the `if (extra)` branch shadow); sp stored as a dword (ref:
//    word).
// NOT steerable from C: 70+ formulations (declaration orders, statement
// orders, types incl. volatile/register, struct overlays, loop forms, tail
// reorders, dependency-forcing expressions) all compile byte-identical, and
// the GA (50 generations) found no register-allocation gains.

#include <string.h>
#include <windows.h>

char* __cdecl GetDebugRecordByIndex(char* arg1, unsigned int arg2);

unsigned char __cdecl EmitCrashModuleLine(int* st)
{
	int* mod;
	int* entry;
	int count;
	int idx;
	int addr;
	int* rec;
	char linebuf[4];
	char* extra;
	unsigned int written;
	char tbuf[0x10];
	char flag;
	unsigned short sp;
	int st4;

	mod = (int*) *st;
	entry = (int*) ((char*) mod + mod[3] + 0x10);
	count = mod[2];
	idx = 0;
	while ((unsigned int) idx < (unsigned int) count) {
		addr = st[2];
		if ((unsigned int) addr >= (unsigned int) entry[1] && (unsigned int) addr <= (unsigned int) entry[2]) {
			goto found;
		}
		idx++;
		entry = (int*) ((char*) entry + entry[0] + 0x10);
	}
	return 0;
found:
	*(unsigned char*) (tbuf + 4) = *(unsigned char*) 0x10027338;
	*(unsigned int*) (tbuf + 0) = *(unsigned int*) 0x10027334;
	*(unsigned char*) (tbuf + 0xc) = *(unsigned char*) 0x10027330;
	st4 = st[4];
	*(unsigned int*) (tbuf + 8) = *(unsigned int*) 0x1002732c;
	flag = *(char*) 0x1003461c;
	extra = 0;
	if (st4 == 0) {
		st[4] = entry[1];
	} else if (st4 == st[3]) {
		st[4] = entry[1];
		st[6]++;
	} else {
		extra = tbuf;
		if ((unsigned int) st[5] > 0 && (unsigned int) st[6] <= 1) {
			extra = tbuf + 8;
			st[4] = entry[1];
			st[5]--;
		} else {
			if (flag == 0) {
				return 0;
			}
		}
	}

	rec = (int*) GetDebugRecordByIndex((char*) mod, (unsigned int) entry[3]);
	*(unsigned short*) (linebuf + 0) = *(unsigned short*) 0x10027314;
	*(unsigned char*) (linebuf + 2) = *(unsigned char*) 0x10027316;
	sp = *(unsigned short*) 0x10027328;
	if (extra != 0) {
		WriteFile((HANDLE) st[1], extra, 4, (LPDWORD) &written, 0);
	}
	WriteFile((HANDLE) st[1], (char*) entry + 0x10, entry[0] - 1, (LPDWORD) &written, 0);
	if (rec != 0) {
		WriteFile((HANDLE) st[1], (char*) &sp, 1, (LPDWORD) &written, 0);
		WriteFile((HANDLE) st[1], (char*) rec + 4, rec[0] - 1, (LPDWORD) &written, 0);
	}
	WriteFile((HANDLE) st[1], linebuf, 2, (LPDWORD) &written, 0);
	return 1;
}
