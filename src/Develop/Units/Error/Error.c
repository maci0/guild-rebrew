#include <stdio.h>
#include <string.h>
#include <time.h>
#include <windows.h>
#include "rebrew_types.h"
#include "rebrew_globals.h"
char __cdecl check_memory_protection(unsigned int);
char __cdecl AnalyzeInstruction(int, int, int, int*);
char* __cdecl GetDebugRecordByIndex();
extern void (*g_panic_callback)(void);
void __cdecl LogMessageInternal(char* module, unsigned int line, char* msg, int severity);

void __cdecl DispatchLogOutput(const char* text, int output_mask, int severity);

extern unsigned int g_log_mode_flags;
extern int g_owner_window;
extern char g_log_message_buffer[];
#if defined(REBREW_SERVER)
int g_log_level_table[3] = {
    0x01, 0x02, 0x08,
};

char g_log_format_table[96] = {
    0x5f, 0x5f, 0x73, 0x65, 0x72, 0x76, 0x65, 0x72, 0x2e, 0x6c, 0x6f, 0x67,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x67, 0x69, 0x6c, 0x64,
    0x65, 0x5f, 0x73, 0x65, 0x72, 0x76, 0x65, 0x72, 0x2e, 0x6c, 0x6f, 0x67,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x5f, 0x5f, 0x64, 0x62, 0x67, 0x2e, 0x6c, 0x6f,
    0x67, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};

char g_log_newline[2] = { 0x0a, 0x00, };

char g_log_default_name[13] = {
    0x5f, 0x5f, 0x73, 0x65, 0x72, 0x76, 0x65, 0x72, 0x2e, 0x6c, 0x6f, 0x67, 0x00,
};
#endif


extern void (*g_panic_callback)(void);

/* Dispatches a log message to the configured output handlers
 * (file, debugger, etc.). Routes based on severity level.  The client build
 * has 12 severity levels and 12 log-file names; its twin is GOLDTL.Error.c. */

extern void* g_crash_callback;

extern unsigned int g_log_mode_flags;

extern char g_crash_dump_all_frames; /* 0x117660e0 - byte access in this TU */

extern char g_log_message_buffer[];

/* Dispatches a log message to the configured output handlers
 * (file, debugger, etc.). Routes based on severity level. */

/* string referenced by ShutdownLogAndErrorHandler asm (was in the init body) */


/* REF 0x100273ac..0x10027488 — named emit; kill anonymous COMDATs in this TU. */

extern int g_owner_window;
extern void (*g_panic_callback)(void);

extern char g_log_buffer[256];

extern int g_log_file_handle;

void __cdecl DispatchLogOutput(const char* text, int output_mask, int severity);





/* THREE ints, not twelve.  The reference gives this table 12 bytes
 * (0x10027078..0x10027084, where g_log_format_table begins) and DispatchLogOutput
 * only ever indexes [0..2].  The initialiser was written as the twelve BYTES
 * 01 00 00 00 02 00 00 00 08 00 00 00 but spelled `int[12]`, which emits 48
 * bytes -- a 36-byte surplus that pushed every later symbol in the section. */

/* Three 0x20-byte log-file names, not one.  InitializeLogAndErrorHandler walks
 * this table from 0x10027084 in 0x20 steps until 0x100270e4 and DispatchLogOutput
 * indexes it as `g_log_format_table + idx * 32`, and the reference has
 * "__server.log", "gilde_server.log" and "__dbg.log" there.  Declaring only the
 * first 13 bytes left the other two absent from the image entirely. */

/* The log module's own literal pool copies (this TU's .data), used because
 * the same text occurs earlier in .rdata/.data and content-scan binding
 * would resolve to those copies instead of the ones this code targets. */
#if defined(REBREW_SERVER)
void __cdecl DispatchLogOutput(const char* msg, int flags, int level)
{
	char buf[260];
	unsigned int written;
	FILE* stream;
	int idx;

	if (flags & 1) {
		idx = 0;
		while (idx < 3) {
			if (level == g_log_level_table[idx]) {
				goto found;
			}
			idx++;
		}
		goto fallback;

	found:
		sprintf(buf, "%s\\%s", g_log_buffer, g_log_format_table + idx * 32);
		stream = (FILE*) fopen(buf, "at");
		if (stream != 0) {
			goto do_write;
		}

	fallback:
		sprintf(buf, "%s\\%s", g_log_buffer, g_log_default_name);
		stream = (FILE*) fopen(buf, "at");
		if (stream == 0) {
			goto skip;
		}

	do_write:
		fputs(msg, stream);
		fputs(g_log_newline, stream);
		fclose(stream);
	skip:;
	}

	if (flags & 4) {
		OutputDebugStringA(msg);
		OutputDebugStringA(g_log_newline);
	}

	if (flags & 8) {
		WriteConsoleA((HANDLE) g_log_file_handle, msg, strlen(msg), &written, 0);
		WriteConsoleA((HANDLE) g_log_file_handle, g_log_newline, 1, &written, 0);
	}
}
#endif
/* Unhandled exception filter for crash dumps. Creates a
 * minidump file with module info and stack trace when the
 * process crashes. */

#include <stdio.h>
#include <string.h>
#include <windows.h>
void __cdecl LogMessageInternal(char* module, unsigned int line, char* msg, int severity);
char __cdecl check_memory_protection(unsigned int);
char __cdecl AnalyzeInstruction(int, int, int, int*);
unsigned char __cdecl EmitCrashModuleLine(int*);
extern void* g_crash_callback;

/* Crash handler: rewrites the module path to <name>.dbg, loads and decrypts
 * it, appends a dated record to __crashdump.log (exception name, then one
 * line per stack frame via EmitCrashModuleLine) and chains to
 * UnhandledExceptionFilter.  The checks nest as `if (success) { body }
 * else { error }` because the front end creates else-blocks innermost-first,
 * which is the reference's cold-block order.  Every path, the two failures
 * before the hDbgFile region included, reaches the one exit at the end.
 *
 * Cleanup (0x10002d63..0x10002e9b, instruction-exact).  The region's paths
 * share one VirtualFree(pDbgBuf) (success, 0x20f, 0x213) and one
 * CloseHandle(hDbgFile) (all five), as the nesting gives them.  With that
 * join, c2 saves ebx/edi at the region entry (0x1000282c) and pops them
 * after the shared CloseHandle, and a late pass copies the two short blocks
 * into each path, leaving the reference's per-path `pop edi; pop ebx; jmp`.
 * With each path closing its own handles the region has no join before the
 * exit, and all four registers are saved in the prologue.
 *
 * Exception switch (0x10002a02..0x10002c54, instruction-exact).  Every case
 * writes its message and the newline itself: that gives each arm three
 * scratch temporaries, so all arms of one group start on the same register
 * (c2 picks scratch registers round-robin in item order).  msvc6 cross-jumps
 * only into the block that falls through to a jump target, so the reference's
 * two tails need two targets: the B cases `break` to the frame fill, which
 * case 0xc00000fd falls into, and the A cases jump to group_a_done, which
 * case 0xc000008e falls into.  group_a_done is `espVal += 4` and then the
 * same `espVal -= 4` in both arms of `if (nFrames)`.  The net is zero.  A
 * single subtract, or one `goto` to a shared subtract, leaves `add ebx,4` /
 * `sub ebx,4` in the object (2127 bytes).  Identical arms are folded away
 * only after the A tails have cross-jumped into case 0xc000008e's newline,
 * so the tails stay shared and the join itself emits nothing.  An empty
 * label there collapses into the switch end and the A arms stop merging; a
 * copy that loads into a scratch register (frameInfo[0]) differs between the
 * two sites and stays in tail A.  pStack is stored after the
 * frameInfo zero stores, as in the reference; stored in the join copies it
 * lands before them, and hDbgFile and pDbgBuf (three references each) come
 * out in each other's stack slots.
 *
 * Frame fill (0x10002c54).  frameInfo is a local of the inner block: then
 * c2 does not order its stores against the pCtx->Eip load, pDbgBuf's load
 * drops below pCtx's and pCtx loads first, as in the reference.  The default
 * arm breaks rather than jumping to a label ahead of the join: each label
 * leaves a scheduler node in the block that takes a cycle.
 *
 * Separator copies (0x100028fb..0x1000294c, instruction-exact).  szLine,
 * space and szSep are initialised locals of an inner block opened after the
 * Esp read.  c2 orders a load through pCtx behind (or ahead of) stores to the
 * outer address-taken locals, which a memcpy or assignment gives, but not
 * behind an initialiser's stores; with no such edge the Esp load drops to its
 * own height and issues after the rep movs, as in the reference.  The Esp
 * read has to stay ahead of the copies: that puts the pCtx load's scratch
 * pick before the szLine pair's, giving eax, ecx, edx.  The two literals
 * are the reference's strings at 0x10027314 and 0x100272f8.
 *
 * Frame fill stores (0x10002c5c).  frameInfo[0] is written before
 * frameInfo[1].  Both stores have priority 2, so source order is the issue
 * order once the group-A join no longer occupies the first slot: `89 54 24 3c`
 * then `89 6c 24 40`.  The frame is `sub esp,0x280`.  Measured RELOC,
 * 2115/2115, delta 0 (was NEAR_MATCHING 2111/2115).  The joins that do not
 * fold are in msvc6-allocator.md Finding 73. */
int WINAPI CrashDumpUnhandledExceptionFilter(EXCEPTION_POINTERS* pExceptionPointers)
{
	unsigned int nBytesWritten;
	char fCanContinue;
	unsigned int dwDbgFileSize;
	unsigned int dwBytesRead;
	unsigned int* pStack;
	unsigned int espVal;
	unsigned int nFrames;
	CONTEXT* pCtx;
	void* hDbgFile;
	void* pDbgBuf;
	void* hProcess;
	void* hCrashLog;
	unsigned int excCode;
	unsigned int key;
	unsigned int* pDwords;
	char instrType;
	unsigned int szDateLen;
	unsigned int szTimeLen;
	MEMORY_BASIC_INFORMATION mbi;
	char szDateBuf[0x100];
	char szModulePath[0x100];

	pCtx = pExceptionPointers->ContextRecord;
	fCanContinue = 0;

	/* Disable crash handler to avoid recursion */
	SetUnhandledExceptionFilter(0);

	/* Get module filename to build .dbg path */
	if (GetModuleFileNameA(0, szModulePath, 0x100)) {
		char* path_cursor;

		/* Find the terminator.  Unguarded, as in the reference: for an
		 * empty path c2 threads the loop's entry test straight into the
		 * backward search body (the cursor is known to be the start).  The
		 * path is never empty here: GetModuleFileNameA returned its length. */
		path_cursor = szModulePath;
		while (*path_cursor != '\0') {
			path_cursor++;
		}
		/* Search backwards for '.' */
		while (path_cursor >= szModulePath) {
			if (*path_cursor == '.') {
				break;
			}
			path_cursor--;
		}
		if (*path_cursor == '.') {
			path_cursor++;
			*path_cursor = 'd';
			path_cursor++;
			*path_cursor = 'b';
			path_cursor++;
			*path_cursor = 'g';
			*(path_cursor + 1) = '\0';
		}

		/* Open the .dbg file */
		hDbgFile = CreateFileA(szModulePath, 0x80000000, 1, 0, 3, 0x80, 0);
		if (hDbgFile != (void*) -1) {
			/* Read 4-byte dbg file size */
			ReadFile(hDbgFile, &dwDbgFileSize, 4, &dwBytesRead, 0);
			if (dwBytesRead == 4) {
				/* Allocate buffer for dbg content */
				pDbgBuf = VirtualAlloc(0, dwDbgFileSize, 0x1000, 4);
				if (pDbgBuf) {
					/* Read entire dbg file */
					ReadFile(hDbgFile, pDbgBuf, dwDbgFileSize, &dwBytesRead, 0);
					if (dwDbgFileSize == dwBytesRead) {
						/* Open crash log for append */
						hCrashLog = CreateFileA("__crashdump.log", 0x40000000, 0, 0, 4, 0x80, 0);

						/* Decrypt dbg: rotate-XOR each dword.  The counter is dwDbgFileSize
						 * (dead after the size check): the reference keeps it in that
						 * variable's stack slot, reloading it every iteration. */
						key = *(unsigned int*) pDbgBuf;
						pDwords = (unsigned int*) ((char*) pDbgBuf + 0x10);
						for (dwDbgFileSize = 0; dwDbgFileSize < dwBytesRead / 4 - 4; dwDbgFileSize++) {
							key = (key >> 17) | (key << 15);
							*pDwords++ ^= key;
						}

						if (hCrashLog != (void*) -1) {
							/* Write separator line.  pCtx->Esp is read here into its own
							 * variable (ebx until the frame fill, as in the reference); the
							 * `- 4` is applied at the frame fill. */
							hProcess = GetCurrentProcess();
							espVal = pCtx->Esp;
							nFrames = 0x800;
							{
							char szLine[] = "\r\n";
							char space = ' ';
							char szSep[] = "------------------------\r\n";
							int frameInfo[7];
							SetFilePointer(hCrashLog, -1, 0, 2);
							WriteFile(hCrashLog, szSep, 0x1a, &nBytesWritten, 0);

							/* Write date */
							szDateLen = GetDateFormatA(0x400, 2, 0, 0, szDateBuf, 0x100);
							if (szDateLen) {
								WriteFile(hCrashLog, szDateBuf, szDateLen - 1, &nBytesWritten, 0);
								WriteFile(hCrashLog, &space, 1, &nBytesWritten, 0);
							}

							/* Write time */
							szTimeLen = GetTimeFormatA(0x400, 8, 0, 0, szDateBuf, 0x100);
							if (szTimeLen) {
								WriteFile(hCrashLog, szDateBuf, szTimeLen - 1, &nBytesWritten, 0);
								WriteFile(hCrashLog, szLine, 2, &nBytesWritten, 0);
							}

							/* Classify exception */
							excCode = pExceptionPointers->ExceptionRecord->ExceptionCode;

							switch (excCode) {
							case 0x80000004:
								WriteFile(hCrashLog, "SINGLE_STEP", 0xb, &nBytesWritten, 0);
								WriteFile(hCrashLog, szLine, 2, &nBytesWritten, 0);
								goto group_a_done;
							case 0x80000003:
								WriteFile(hCrashLog, "BREAKPOINT", 0xa, &nBytesWritten, 0);
								WriteFile(hCrashLog, szLine, 2, &nBytesWritten, 0);
								goto group_a_done;
							case 0xc0000005:
								/* ACCESS_VIOLATION */
								WriteFile(hCrashLog, "ACCESS_VIOLATION ", 0x11, &nBytesWritten, 0);
								if (pExceptionPointers->ExceptionRecord->ExceptionInformation[0] == 0) {
									WriteFile(hCrashLog, "READ ", 5, &nBytesWritten, 0);
								}
								else {
									WriteFile(hCrashLog, "WRITE ", 6, &nBytesWritten, 0);
								}
								sprintf(szDateBuf, "0x%08X", pExceptionPointers->ExceptionRecord->ExceptionInformation[1]);
								WriteFile(hCrashLog, szDateBuf, strlen(szDateBuf), &nBytesWritten, 0);
								WriteFile(hCrashLog, szLine, 2, &nBytesWritten, 0);
								break;
							case 0xc0000006:
								WriteFile(hCrashLog, "IN_PAGE_ERROR", 0xd, &nBytesWritten, 0);
								WriteFile(hCrashLog, szLine, 2, &nBytesWritten, 0);
								break;
							case 0xc000001d:
								WriteFile(hCrashLog, "ILLEGAL_INSTRUCTION", 0x13, &nBytesWritten, 0);
								WriteFile(hCrashLog, szLine, 2, &nBytesWritten, 0);
								break;
							case 0xc000008c:
								WriteFile(hCrashLog, "ARRAY_BOUNDS_EXCEEDED", 0x15, &nBytesWritten, 0);
								WriteFile(hCrashLog, szLine, 2, &nBytesWritten, 0);
								goto group_a_done;
							case 0xc000008d:
								WriteFile(hCrashLog, "FLT_DENORMAL_OPERAND", 0x14, &nBytesWritten, 0);
								WriteFile(hCrashLog, szLine, 2, &nBytesWritten, 0);
								goto group_a_done;
							case 0xc0000026:
								WriteFile(hCrashLog, "INVALID_DISPOSITION", 0x13, &nBytesWritten, 0);
								WriteFile(hCrashLog, szLine, 2, &nBytesWritten, 0);
								goto group_a_done;
							case 0xc0000025:
								WriteFile(hCrashLog, "NONCONTINUABLE_EXCEPTION", 0x18, &nBytesWritten, 0);
								WriteFile(hCrashLog, szLine, 2, &nBytesWritten, 0);
								goto group_a_done;
							case 0xc000008e:
								WriteFile(hCrashLog, "FLT_DIVIDE_BY_ZERO", 0x12, &nBytesWritten, 0);
								WriteFile(hCrashLog, szLine, 2, &nBytesWritten, 0);
group_a_done:
								espVal += 4;
								if (nFrames)
									espVal -= 4;
								else
									espVal -= 4;
								break;
							case 0xc000008f:
								WriteFile(hCrashLog, "FLT_INEXACT_RESULT", 0x12, &nBytesWritten, 0);
								WriteFile(hCrashLog, szLine, 2, &nBytesWritten, 0);
								break;
							case 0xc0000090:
								WriteFile(hCrashLog, "FLT_INVALID_OPERATION", 0x15, &nBytesWritten, 0);
								WriteFile(hCrashLog, szLine, 2, &nBytesWritten, 0);
								break;
							case 0xc0000091:
								WriteFile(hCrashLog, "FLT_OVERFLOW", 0xc, &nBytesWritten, 0);
								WriteFile(hCrashLog, szLine, 2, &nBytesWritten, 0);
								break;
							case 0xc0000092:
								WriteFile(hCrashLog, "FLT_STACK_CHECK", 0xf, &nBytesWritten, 0);
								WriteFile(hCrashLog, szLine, 2, &nBytesWritten, 0);
								break;
							case 0xc0000093:
								WriteFile(hCrashLog, "FLT_UNDERFLOW", 0xd, &nBytesWritten, 0);
								WriteFile(hCrashLog, szLine, 2, &nBytesWritten, 0);
								break;
							case 0xc0000094:
								WriteFile(hCrashLog, "INT_DIVIDE_BY_ZERO", 0x12, &nBytesWritten, 0);
								WriteFile(hCrashLog, szLine, 2, &nBytesWritten, 0);
								break;
							case 0xc0000095:
								WriteFile(hCrashLog, "INT_OVERFLOW", 0xc, &nBytesWritten, 0);
								WriteFile(hCrashLog, szLine, 2, &nBytesWritten, 0);
								break;
							case 0xc0000096:
								WriteFile(hCrashLog, "PRIV_INSTRUCTION", 0x10, &nBytesWritten, 0);
								WriteFile(hCrashLog, szLine, 2, &nBytesWritten, 0);
								break;
							case 0xc00000fd:
								WriteFile(hCrashLog, "STACK_OVERFLOW", 0xe, &nBytesWritten, 0);
								WriteFile(hCrashLog, szLine, 2, &nBytesWritten, 0);
								break;
							default:
								break;
							}

							/* Stack walk */
							frameInfo[0] = (int) pDbgBuf;
							frameInfo[1] = (int) hCrashLog;
							frameInfo[2] = (int) pCtx->Eip;
							frameInfo[3] = 0;
							frameInfo[4] = 0;
							frameInfo[5] = 0;
							frameInfo[6] = 0;
							pStack = (unsigned int*) (espVal - 4);

							for (;;) {
								VirtualQuery((const void*) frameInfo[2], &mbi, 0x1c);
								instrType = check_memory_protection((unsigned int) mbi.Protect);
								if (!instrType) {
									goto next_frame;
								}
								/* The reference compares the State field ([esp+0x68], offset 0x10), not RegionSize (offset 0x0c) — same constant, wrong field used to skip non-committed frames here. */
								if (mbi.State != 0x1000 /* MEM_COMMIT */) {
									goto next_frame;
								}
								/* Scan back up to 7 bytes for a readable call instruction; when
								 * nothing is readable nInstr ends at 0, as in the reference.  The
								 * reference's `seta al; and al,1; test al,al` needs the `& 1` and
								 * the constant in an else arm: with `instrType = 1` ahead of the
								 * `if` (or no mask) c2 folds the flag into the compare, and a masked
								 * flag that is not a register candidate gets a stack slot. */
								if (frameInfo[2] != (int) pCtx->Eip) {
									int nInstr = 7;
									char* pInstr = szDateBuf;
									for (; nInstr > 0; nInstr--, pInstr++) {
										if (ReadProcessMemory(hProcess, (void*) (frameInfo[2] - nInstr), pInstr, nInstr, 0)) {
											break;
										}
									}
									instrType = ((unsigned char) AnalyzeInstruction((int) &szDateBuf[7], nInstr, frameInfo[2], &frameInfo[3]) > 0) & 1;
								}
								else {
									instrType = 1;
								}
								if (instrType) {
									if (EmitCrashModuleLine(frameInfo)) {
										nFrames--;
									}
								}
next_frame:
								pStack++;
								if ((int) nFrames <= 0) {
									goto done_walk;
								}
								if (!ReadProcessMemory(hProcess, pStack, &frameInfo[2], 4, 0)) {
									break;
								}
							}

done_walk:

							if (g_crash_callback) {
								((void (__cdecl*)(void*)) g_crash_callback)(hCrashLog);
								fCanContinue = 1;
							}
							WriteFile(hCrashLog, &szLine[2], 1, &nBytesWritten, 0);
							CloseHandle(hCrashLog);
							}
						}
						else {
							LogMessageInternal("D:\\Develop\\Units\\Error\\Error.c", 0x20f, "not open crashdump", 1);
						}
					}
					else {
						LogMessageInternal("D:\\Develop\\Units\\Error\\Error.c", 0x213, "bad (small) dbg file", 1);
					}
					VirtualFree(pDbgBuf, 0, 0x8000);
				}
				else {
					LogMessageInternal("D:\\Develop\\Units\\Error\\Error.c", 0x218, "no memory", 1);
				}
			}
			else {
				LogMessageInternal("D:\\Develop\\Units\\Error\\Error.c", 0x21b, "bad dbg file", 1);
			}
			CloseHandle(hDbgFile);
		}
		else {
			LogMessageInternal("D:\\Develop\\Units\\Error\\Error.c", 0x220, "no dbg file", 1);
		}
	}

	if (g_crash_callback && !fCanContinue) {
		((void (__cdecl*)(int)) g_crash_callback)(-1);
	}
	UnhandledExceptionFilter(pExceptionPointers);

	return 1;
}


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

		memcpy(unknown, "??? ", 5);
		memcpy(arrow, "--> ", 5);

		st4 = st[4];
		flag = *(char*) &g_crash_dump_all_frames;
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

			*(unsigned short*) linebuf = *(const unsigned short*) "\r\n";
			linebuf[2] = "\r\n"[2];
			*(unsigned short*) spbuf = *(const unsigned short*) " ";

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

/* The crash-log strings from 0x10027318 to 0x1002733c.  They follow
 * CrashDumpUnhandledExceptionFilter.c's two separator literals, which that
 * file emits as string COMDATs after its own data, so they are defined in
 * this TU, the next object in the link.  0x10027314 is the "\r\n" literal
 * itself: this TU's copy folds into that file's COMDAT. */



/* Variable-length record accessor - walks a record table to find the nth entry */

char* __cdecl GetDebugRecordByIndex(char* arg1, unsigned int arg2)
{
	char* result;

	if (arg2 < *(unsigned int*) (arg1 + 4)) {
		result = arg1 + 0x10;
		if (arg2 <= 0) {
			return result;
		}
		do {
			result = result + *(int*) result + 4;
		} while (--arg2);
		return result;
	}
	return 0;
}

/* Checks if a memory page's protection flags indicate it is
 * readable. Returns 1 if the protection includes read access. */


char __cdecl check_memory_protection(unsigned int protect)
{
	MEMORY_BASIC_INFORMATION mbi;

	VirtualQuery(check_memory_protection, &mbi, 0x1c);

	switch (protect & 0xFF) {
	case 2:
	case 4:
		return mbi.Protect == 2 || mbi.Protect == 4;
	case 0x10:
	case 0x20:
	case 0x40:
	case 0x80:
		return 1;
	}
	return 0;
}

/* Analyzes an x86 instruction at the given address to determine
 * its length and type. Used by the crash dump handler to decode
 * the faulting instruction context. */

char __cdecl AnalyzeInstruction(int arg1, int arg2, int arg3, int* arg4)
{
	*arg4 = 0;
	if (arg2 >= 5 && *(unsigned char *) (arg1 - 5) == 0xe8) {
		*arg4 = *(int *) (arg1 - 4) + arg3;
		return 1;
	}
	if (arg2 >= 3 && *(char *) (arg1 - 3) == -1 && *(unsigned char *) (arg1 - 2) == 0x14) return 2;
	if (arg2 >= 6 && *(char *) (arg1 - 6) == -1 && *(unsigned char *) (arg1 - 5) == 0x15) return 2;
	if (arg2 >= 2 && *(char *) (arg1 - 2) == -1 && *(unsigned char *) (arg1 - 1) < 0x40) return 2;
	if (arg2 >= 2 && *(char *) (arg1 - 2) == -1 && (*(unsigned char *) (arg1 - 1) & 0xf8) == 0xd0) return 2;
	if (arg2 >= 3 && *(char *) (arg1 - 3) == -1 && (*(unsigned char *) (arg1 - 2) & 0xf8) == 0x50) return 2;
	if (arg2 >= 7 && *(char *) (arg1 - 7) == -1 && (*(unsigned char *) (arg1 - 6) & 0xf8) == 0x90) return 2;
	return 0;
}


/* Initializes the logging and error handling subsystem.
 * Opens log files, sets up exception handlers, and configures
 * output severity filters. */


#include <windows.h>
#include "rebrew_types.h"
#include "rebrew_globals.h"

extern void (*g_panic_callback)(void);
extern unsigned int g_log_mode_flags; /* 0x10034618 */
extern int g_owner_window;
#if defined(REBREW_SERVER)
void __cdecl InitializeLogAndErrorHandler(int a, int b, unsigned int c, unsigned int d)
{
	int now;
	char buf[0x104]; /* target frame: now@0, buf@4..0x108, path@0x108 */
	char path[0x100];
	FILE* file;
	char* string_cursor;

	g_panic_callback = (void (*)(void)) a;
	g_log_mode_flags = d;
	g_crash_callback = (void*) b;
	g_owner_window = c;
	g_crash_dump_all_frames = (d >> 4) & 1;
	SetUnhandledExceptionFilter(CrashDumpUnhandledExceptionFilter);
	now = time(0);
	GetWindowTextA((HWND) c, path, 0x100);
	GetModuleFileNameA(0, (char*) &g_log_buffer, 0x104);
	*strrchr((char*) &g_log_buffer, 0x5c) = 0;
	sprintf((char*) &g_log_message_buffer, "* ------------------------------------------------------------ *\n[%s], Date: %s", path, ctime((long*) &now));
	if (g_log_mode_flags & 1) {
		string_cursor = (char*) &g_log_format_table;
		do {
			sprintf(buf, "%s\\%s", (char*) &g_log_buffer, string_cursor);
			file = fopen(buf, "at");
			if (file != 0) {
				fseek(file, 0, 2);
				if (ftell(file) > 0x10000) {
					fclose(file);
					file = fopen(buf, "wt");
					fputs("LogFile has been deleted!\n", file);
				}
				fclose(file);
			}
			string_cursor += 0x20;
		} while ((int) string_cursor < (int) ((char*) &g_log_format_table + 0x60));
	}
	if (g_log_mode_flags & 8) {
		AllocConsole();
		g_log_file_handle = (int) GetStdHandle((DWORD) -0xb);
	}
	string_cursor = (char*) &g_log_level_table;
	do {
		DispatchLogOutput((char*) &g_log_message_buffer, g_log_mode_flags, *(int*) string_cursor);
		string_cursor += 4;
	} while ((int) string_cursor < (int) ((char*) &g_log_level_table + 0xc));
}
#endif
void __cdecl ShutdownLogAndErrorHandler(void)
{
	int i;

	for (i = 0; i < 3; i++) {
		DispatchLogOutput("Error-Handler closed.\n", g_log_mode_flags, g_log_level_table[i]);
	}
	if (g_log_mode_flags & 8) {
		FreeConsole();
		g_log_file_handle = 0;
	}
	g_panic_callback = 0;
	g_owner_window = 0;
	g_log_mode_flags = 0;
}


/* Reports a fatal error with a message, then terminates the
 * process via _exit(). Does not return. */


__declspec(noreturn) void __cdecl exit(int);

void __cdecl ReportFatalError(char* modulePath, unsigned int lineNumber, char* message)
{
	unsigned int flags;
	int dialogResult;

	if (g_panic_callback == 0) {
		MessageBoxA((HWND) 0, "ERROR-Handler has not been started...", "Error!", 0x30);
		return;
	}
	flags = g_log_mode_flags;
	if (flags == 0) {
		return;
	}
	if ((flags & 0xf) != 0) {
		sprintf(g_log_message_buffer, "FATAL ERROR (%s:%lu):\n%s\n", modulePath, lineNumber, message);
		flags = g_log_mode_flags;
	}
	if ((flags & 0xd) != 0) {
		DispatchLogOutput(g_log_message_buffer, flags, 1);
		flags = g_log_mode_flags;
	}
	if ((flags & 2) == 0) {
		return;
	}
	dialogResult = MessageBoxA((HWND) g_owner_window, g_log_message_buffer, "Fatal Error! Abort Program?", 0x124);
	if (dialogResult != 6) {
		return;
	}
	g_panic_callback();
	exit(0xf);
}

/* Reports a non-fatal error with its source location; the dialog has no
 * abort choice.  Client-only code (TL 0x41d950, unreferenced there and
 * absent from Europa1400Gold.exe): the server calls it nowhere, so
 * /OPT:REF discards it.  Its storage is this TU's. */

void __cdecl ReportError(char* modulePath, unsigned int lineNumber, char* message)
{
	if (g_panic_callback == 0) {
		MessageBoxA((HWND) 0, "ERROR-Handler has not been started...", "Error!", 0x10030);
		return;
	}
	if (g_log_mode_flags == 0) {
		return;
	}
	if (g_log_mode_flags & 0xf) {
		sprintf(g_log_message_buffer, "ERROR (%s:%lu):\n%s\n", modulePath, lineNumber, message);
	}
	if (g_log_mode_flags & 0xd) {
		DispatchLogOutput(g_log_message_buffer, g_log_mode_flags, 1);
	}
	if (g_log_mode_flags & 2) {
		MessageBoxA((HWND) g_owner_window, g_log_message_buffer, "Error!", 0x10030);
	}
}

/* Reports a non-fatal message through the logging system.
 * Dispatches to DispatchLogOutput with default severity. */


void __cdecl ReportMessage(char* msg)
{
	if (!g_panic_callback) {
		MessageBoxA(0, "ERROR-Handler has not been started...", "Error!", 0x10030);
		return;
	}
	if (!g_log_mode_flags) {
		return;
	}
	if (g_log_mode_flags & 0x0d) {
		sprintf(g_log_message_buffer, "MESSAGE: %s\n", msg);
		DispatchLogOutput(g_log_message_buffer, g_log_mode_flags, 1);
	}
	if (g_log_mode_flags & 2) {
		MessageBoxA(0, msg, "Message:", 0x1030);
	}
}

/* Core logging function: formats and dispatches a log message
 * with source module path, line number, message text, and
 * severity level (1=error, 8=info, etc.). */


void __cdecl LogMessageInternal(char* module, unsigned int line, char* msg, int severity)
{
	unsigned char flags;

	if (*(int*) &g_panic_callback == 0) {
		MessageBoxA(0, "ERROR-Handler has not been started...", "Error!", 0x10030);
		return;
	}
	flags = *(unsigned char*) &g_log_mode_flags;
	if (flags & 1) {
		if (flags & 0x20) {
			sprintf((char*) &g_log_message_buffer, "Time:%8lu\tModule '%s':\tLine:%lu:\t%s", timeGetTime(), module, line, msg);
		} else {
			sprintf((char*) &g_log_message_buffer, "tModule '%s':\tLine:%lu:\t%s", module, line, msg);
		}
		DispatchLogOutput((char*) &g_log_message_buffer, *(int*) &g_log_mode_flags, severity);
	}
}

/* Writes a message to the log outputs as it is, without a source location.
 * Client-only code (TL 0x41daf0, unreferenced there and absent from
 * Europa1400Gold.exe), discarded by /OPT:REF like ReportError. */

void __cdecl LogMessage(char* msg)
{
	if (g_panic_callback == 0) {
		MessageBoxA(0, "ERROR-Handler has not been started...", "Error!", 0x10030);
		return;
	}
	if (g_log_mode_flags & 1) {
		DispatchLogOutput(msg, g_log_mode_flags, 1);
	}
}
unsigned char _dpad_10027084[96];
unsigned char _dpad_10034348[712];
unsigned char _dpad_117640e0[8192];
unsigned char _dpad_11766100[260];
unsigned char _dpad_6777bc[348] = {
    0x00, 0x00, 0x80, 0x3f, 0x00, 0x00, 0x80, 0x3f, 0x00, 0x00, 0x80, 0x3f, 0x64, 0x64, 0x3a, 0x4d,
    0x6f, 0x64, 0x65, 0x49, 0x6e, 0x66, 0x6f, 0x00, 0x64, 0x64, 0x3a, 0x41, 0x64, 0x61, 0x70, 0x74,
    0x65, 0x72, 0x49, 0x6e, 0x66, 0x6f, 0x00, 0x00, 0x64, 0x38, 0x5f, 0x72, 0x65, 0x73, 0x6f, 0x75,
    0x72, 0x63, 0x65, 0x2e, 0x64, 0x6c, 0x6c, 0x00, 0x64, 0x38, 0x5f, 0x4d, 0x6f, 0x64, 0x65, 0x00,
    0x64, 0x38, 0x5f, 0x47, 0x75, 0x69, 0x64, 0x00, 0x64, 0x38, 0x5f, 0x76, 0x65, 0x73, 0x61, 0x00,
    0x25, 0x73, 0x20, 0x28, 0x25, 0x73, 0x20, 0x25, 0x69, 0x2e, 0x25, 0x69, 0x2e, 0x25, 0x69, 0x2e,
    0x25, 0x69, 0x29, 0x00, 0x25, 0x69, 0x20, 0x78, 0x20, 0x25, 0x69, 0x20, 0x78, 0x20, 0x25, 0x69,
    0x20, 0x28, 0x25, 0x73, 0x29, 0x00, 0x00, 0x00, 0x25, 0x30, 0x38, 0x78, 0x2d, 0x25, 0x30, 0x34,
    0x78, 0x2d, 0x25, 0x30, 0x34, 0x78, 0x2d, 0x25, 0x30, 0x32, 0x78, 0x25, 0x30, 0x32, 0x78, 0x25,
    0x30, 0x32, 0x78, 0x25, 0x30, 0x32, 0x78, 0x25, 0x30, 0x32, 0x78, 0x25, 0x30, 0x32, 0x78, 0x25,
    0x30, 0x32, 0x78, 0x25, 0x30, 0x32, 0x78, 0x00, 0x25, 0x75, 0x78, 0x25, 0x75, 0x78, 0x25, 0x75,
    0x78, 0x25, 0x75, 0x00, 0x4d, 0x69, 0x73, 0x73, 0x69, 0x6e, 0x67, 0x20, 0x64, 0x64, 0x5f, 0x45,
    0x6e, 0x64, 0x4c, 0x69, 0x6e, 0x65, 0x73, 0x21, 0x00, 0x00, 0x00, 0x00, 0x54, 0x6f, 0x6f, 0x20,
    0x6d, 0x61, 0x6e, 0x79, 0x20, 0x6c, 0x69, 0x6e, 0x65, 0x73, 0x20, 0x69, 0x6e, 0x20, 0x64, 0x64,
    0x5f, 0x4c, 0x69, 0x6e, 0x65, 0x28, 0x29, 0x3a, 0x20, 0x49, 0x6e, 0x63, 0x72, 0x65, 0x61, 0x73,
    0x65, 0x20, 0x64, 0x64, 0x5f, 0x4d, 0x41, 0x58, 0x5f, 0x4c, 0x49, 0x4e, 0x45, 0x53, 0x20, 0x69,
    0x6e, 0x20, 0x64, 0x38, 0x5f, 0x76, 0x65, 0x73, 0x61, 0x2e, 0x63, 0x21, 0x00, 0x00, 0x00, 0x00,
    0x64, 0x64, 0x5f, 0x4c, 0x69, 0x6e, 0x65, 0x20, 0x63, 0x61, 0x6c, 0x6c, 0x65, 0x64, 0x20, 0x77,
    0x2f, 0x6f, 0x20, 0x64, 0x64, 0x5f, 0x42, 0x65, 0x67, 0x69, 0x6e, 0x4c, 0x69, 0x6e, 0x65, 0x73,
    0x21, 0x00, 0x00, 0x00, 0x64, 0x64, 0x5f, 0x45, 0x6e, 0x64, 0x4c, 0x69, 0x6e, 0x65, 0x73, 0x20,
    0x63, 0x61, 0x6c, 0x6c, 0x65, 0x64, 0x20, 0x77, 0x2f, 0x6f, 0x20, 0x64, 0x64, 0x5f, 0x42, 0x65,
    0x67, 0x69, 0x6e, 0x4c, 0x69, 0x6e, 0x65, 0x73, 0x21, 0x00, 0x00, 0x00,
};
unsigned char _dpad_677948[384] = {
    0x5f, 0x65, 0x72, 0x72, 0x6f, 0x72, 0x2e, 0x6c, 0x6f, 0x67, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x5f, 0x61, 0x69, 0x2e, 0x6c, 0x6f, 0x67, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x5f, 0x73, 0x69, 0x6d, 0x2e, 0x6c, 0x6f, 0x67, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x5f, 0x64, 0x62, 0x67, 0x2e, 0x6c, 0x6f, 0x67, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x5f, 0x73, 0x63, 0x72, 0x69, 0x70, 0x74, 0x2e, 0x6c, 0x6f, 0x67, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x5f, 0x63, 0x75, 0x74, 0x73, 0x63, 0x65, 0x6e, 0x65, 0x2e, 0x6c, 0x6f, 0x67, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x5f, 0x6d, 0x65, 0x69, 0x73, 0x74, 0x65, 0x72, 0x2e, 0x6c, 0x6f, 0x67, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x5f, 0x64, 0x33, 0x2e, 0x6c, 0x6f, 0x67, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x5f, 0x73, 0x74, 0x61, 0x74, 0x73, 0x2e, 0x6c, 0x6f, 0x67, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x5f, 0x6d, 0x73, 0x78, 0x2e, 0x6c, 0x6f, 0x67, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x5f, 0x5f, 0x5f, 0x74, 0x72, 0x61, 0x63, 0x6b, 0x65, 0x72, 0x2e, 0x6c, 0x6f, 0x67, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x5f, 0x6d, 0x65, 0x69, 0x73, 0x74, 0x65, 0x72, 0x32, 0x2e, 0x6c, 0x6f, 0x67, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};
