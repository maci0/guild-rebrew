/* EmitCrashModuleLine — crash-log module line emitter (0x10002fc0). */

// FUNCTION: SERVER 0x10002FC0
// EmitCrashModuleLine
// SIZE: 376

#include <string.h>
#include <windows.h>

char* __cdecl GetDebugRecordByIndex(char* arg1, unsigned int arg2);

/* This TU's .data string pool copies of "\r\n" and " " (the same text
 * occurs earlier in .rdata, so content-scan binding would resolve to those
 * copies instead of the ones the local-array init reads here). */

// DATA: SERVER 0x10027314
char g_crash_newline[4] = {
    0x0d, 0x0a, 0x00, 0x00,
};

// DATA: SERVER 0x10027328
char g_crash_space[4] = {
    0x20, 0x00, 0x00, 0x00,
};

unsigned char __cdecl EmitCrashModuleLine(int* st)
{
	int* mod;
	int* entry;
	int count;
	int idx;
	int addr;
	int* rec;
	char* extra;
	unsigned int written;
	char flag;
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
	{
		char unknown[5] = "??? ";
		char arrow[5] = "--> ";

		st4 = st[4];
		flag = *(char*) 0x1003461c;
		extra = 0;
		if (st4 == 0) {
			st[4] = entry[1];
		} else if (st4 == st[3]) {
			st[4] = entry[1];
			st[6]++;
		} else {
			extra = unknown;
			if ((unsigned int) st[5] > 0 && (unsigned int) st[6] <= 1) {
				extra = arrow;
				st[4] = entry[1];
				st[5]--;
			} else {
				if (flag == 0) {
					return 0;
				}
			}
		}

		rec = (int*) GetDebugRecordByIndex((char*) mod, (unsigned int) entry[3]);
		{
			char linebuf[3];
			char spbuf[2];

			*(unsigned short*) linebuf = *(const unsigned short*) g_crash_newline;
			linebuf[2] = g_crash_newline[2];
			*(unsigned short*) spbuf = *(const unsigned short*) g_crash_space;

			if (extra != 0) {
				WriteFile((HANDLE) st[1], extra, 4, (LPDWORD) &written, 0);
			}
			WriteFile((HANDLE) st[1], (char*) entry + 0x10, entry[0] - 1, (LPDWORD) &written, 0);
			if (rec != 0) {
				WriteFile((HANDLE) st[1], spbuf, 1, (LPDWORD) &written, 0);
				WriteFile((HANDLE) st[1], (char*) rec + 4, rec[0] - 1, (LPDWORD) &written, 0);
			}
			WriteFile((HANDLE) st[1], linebuf, 2, (LPDWORD) &written, 0);
		}
	}
	return 1;
}
