/* EmitCrashModuleLine — crash-log module line emitter (0x10002fc0). */

// CFLAGS: /O2 /Gd
// FUNCTION: SERVER 0x10002FC0
// EmitCrashModuleLine
// SIZE: 358
// NOTE: semantically complete reconstruction.  Loop (module search), both
// return epilogues (xor al,al / mov al,1), tbuf register roles (AL/ECX),
// frame size (0x1c) and the WriteFile sequence (extra / module name / ' '
// space byte / debug record / CRLF) now match the reference.  Remaining
// deltas are the MSVC6 register-allocation cascade documented in
// docs/msvc6-allocator.md (ValidateAndAssignOffice class): the tbuf byte
// loads land in CL instead of AL, `extra` stays in ebp (reference spills it
// to [esp+0x14] and keeps `rec` in ebp), so the space byte (`sp`) spills to
// extra's slot as a dword instead of the arg slot as a word.  20+ C
// formulations (declaration orders, statement orders, types incl. volatile/
// register, extra-in-branch defs, flag-first, st4 local) did not steer it.

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
	sp = *(unsigned short*) 0x10027328;
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
	if (extra != 0) {
		WriteFile((HANDLE) st[1], extra, 4, (LPDWORD) &written, 0);
	}
	WriteFile((HANDLE) st[1], (char*) entry + 0x10, entry[0] - 1, (LPDWORD) &written, 0);
	WriteFile((HANDLE) st[1], (char*) &sp, 1, (LPDWORD) &written, 0);
	WriteFile((HANDLE) st[1], (char*) rec + 4, rec[0] - 1, (LPDWORD) &written, 0);
	WriteFile((HANDLE) st[1], linebuf, 2, (LPDWORD) &written, 0);
	return 1;
}
