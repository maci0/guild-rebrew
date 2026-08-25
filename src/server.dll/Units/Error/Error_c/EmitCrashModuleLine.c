/* EmitCrashModuleLine — crash-log module line emitter (0x10002fc0). */

// CFLAGS: /O2 /Gd
// FUNCTION: SERVER 0x10002FC0
// EmitCrashModuleLine
// SIZE: 384

#include <string.h>
#include <windows.h>

char* __cdecl GetDebugRecordByIndex(char* arg1, unsigned int arg2);

unsigned int __cdecl EmitCrashModuleLine(int* st)
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

	mod = (int*) *st;
	count = mod[2];
	entry = (int*) ((char*) mod + mod[3] + 0x10);
	idx = 0;
	addr = st[2];
	while ((unsigned int) idx < (unsigned int) count) {
		if ((unsigned int) addr >= (unsigned int) entry[1] && (unsigned int) addr <= (unsigned int) entry[2]) {
			break;
		}
		idx++;
		entry = (int*) ((char*) entry + entry[0] + 0x10);
	}
	if ((unsigned int) idx >= (unsigned int) count) {
		return 0;
	}

	*(unsigned int*) (tbuf + 0) = *(unsigned int*) 0x10027334;
	*(unsigned char*) (tbuf + 4) = *(unsigned char*) 0x10027338;
	*(unsigned int*) (tbuf + 8) = *(unsigned int*) 0x1002732c;
	*(unsigned char*) (tbuf + 0xc) = *(unsigned char*) 0x10027330;
	flag = *(char*) 0x1003461c;
	extra = 0;
	if (st[4] == 0) {
		st[4] = entry[1];
	} else if (st[4] == st[3]) {
		st[4] = entry[1];
		st[6]++;
	} else {
		extra = tbuf;
		if (st[5] != 0 && st[6] <= 1) {
			extra = tbuf + 8;
			st[5]--;
			st[4] = entry[1];
		} else {
			if (flag == 0) {
				return 0;
			}
		}
	}

	rec = (int*) GetDebugRecordByIndex((char*) mod, (unsigned int) entry[3]);
	*(unsigned short*) (linebuf + 0) = *(unsigned short*) 0x10027314;
	*(unsigned char*) (linebuf + 2) = *(unsigned char*) 0x10027316;
	*(unsigned short*) (linebuf + 0x20) = *(unsigned short*) 0x10027328;
	if (extra != 0) {
		WriteFile((HANDLE) st[1], extra, 4, (LPDWORD) &written, 0);
	}
	WriteFile((HANDLE) st[1], (char*) entry + 0x10, entry[0] - 1, (LPDWORD) &written, 0);
	if (rec != 0) {
		WriteFile((HANDLE) st[1], (char*) (linebuf + 0x28), 1, (LPDWORD) &written, 0);
		WriteFile((HANDLE) st[1], (char*) rec + 4, rec[0] - 1, (LPDWORD) &written, 0);
	}
	WriteFile((HANDLE) st[1], (char*) &written, 2, (LPDWORD) &written, 0);
	return 1;
}
