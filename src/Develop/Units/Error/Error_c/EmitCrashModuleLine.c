/* EmitCrashModuleLine — crash-log module line emitter (0x10002fc0). */

// FUNCTION: SERVER 0x10002FC0
// EmitCrashModuleLine
// SIZE: 376

#include <string.h>
#include <windows.h>

extern char g_crash_dump_all_frames;

char* __cdecl GetDebugRecordByIndex(char* arg1, unsigned int arg2);

/* The crash-log strings from 0x10027318 to 0x1002733c.  They follow
 * CrashDumpUnhandledExceptionFilter.c's two separator literals, which that
 * file emits as string COMDATs after its own data, so they are defined in
 * this TU, the next object in the link.  0x10027314 is the "\r\n" literal
 * itself: this TU's copy folds into that file's COMDAT. */
// DATA: SERVER 0x10027318
char g_crashdump_tail[36] = {
	0x5f, 0x5f, 0x63, 0x72, 0x61, 0x73, 0x68, 0x64, 0x75, 0x6d, 0x70, 0x2e,
	0x6c, 0x6f, 0x67, 0x00, 0x20, 0x00, 0x00, 0x00, 0x2d, 0x2d, 0x3e, 0x20,
	0x00, 0x00, 0x00, 0x00, 0x3f, 0x3f, 0x3f, 0x20, 0x00, 0x00, 0x00, 0x00,
};
#define g_crash_newline "\r\n"                        /* REF 0x10027314 */
#define g_crash_space   (g_crashdump_tail + 16) /* REF 0x10027328 */
#define g_crash_arrow   (g_crashdump_tail + 20) /* REF 0x1002732c */
#define g_crash_unknown (g_crashdump_tail + 28) /* REF 0x10027334 */

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
		char unknown[5];
		char arrow[5];

		memcpy(unknown, g_crash_unknown, 5);
		memcpy(arrow, g_crash_arrow, 5);

		st4 = st[4];
		flag = g_crash_dump_all_frames;
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
