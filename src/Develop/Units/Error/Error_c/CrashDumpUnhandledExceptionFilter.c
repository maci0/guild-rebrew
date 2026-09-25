/* The crash-dump message and exception-name data this file addresses by
 * absolute VA.  Every string below is referenced from the code as a literal
 * address -- `LogMessageInternal((char*) 0x10027104, ...)`, the WriteFile
 * argument table at 0x10027178..0x10027260, `CreateFileA((const char*)
 * 0x10027318, ...)` -- and none of it was defined anywhere, so those reads
 * landed outside the section.  Bytes are generated from the reference. */
// DATA: SERVER 0x10027104
char g_crashdump_data_10027104[568] = {
	0x6e, 0x6f, 0x20, 0x64, 0x62, 0x67, 0x20, 0x66, 0x69, 0x6c, 0x65, 0x00,
	0x62, 0x61, 0x64, 0x20, 0x64, 0x62, 0x67, 0x20, 0x66, 0x69, 0x6c, 0x65,
	0x00, 0x00, 0x00, 0x00, 0x6e, 0x6f, 0x20, 0x6d, 0x65, 0x6d, 0x6f, 0x72,
	0x79, 0x00, 0x00, 0x00, 0x62, 0x61, 0x64, 0x20, 0x28, 0x73, 0x6d, 0x61,
	0x6c, 0x6c, 0x29, 0x20, 0x64, 0x62, 0x67, 0x20, 0x66, 0x69, 0x6c, 0x65,
	0x00, 0x00, 0x00, 0x00, 0x44, 0x3a, 0x5c, 0x44, 0x65, 0x76, 0x65, 0x6c,
	0x6f, 0x70, 0x5c, 0x55, 0x6e, 0x69, 0x74, 0x73, 0x5c, 0x45, 0x72, 0x72,
	0x6f, 0x72, 0x5c, 0x45, 0x72, 0x72, 0x6f, 0x72, 0x2e, 0x63, 0x00, 0x00,
	0x6e, 0x6f, 0x74, 0x20, 0x6f, 0x70, 0x65, 0x6e, 0x20, 0x63, 0x72, 0x61,
	0x73, 0x68, 0x64, 0x75, 0x6d, 0x70, 0x00, 0x00, 0x53, 0x54, 0x41, 0x43,
	0x4b, 0x5f, 0x4f, 0x56, 0x45, 0x52, 0x46, 0x4c, 0x4f, 0x57, 0x00, 0x00,
	0x50, 0x52, 0x49, 0x56, 0x5f, 0x49, 0x4e, 0x53, 0x54, 0x52, 0x55, 0x43,
	0x54, 0x49, 0x4f, 0x4e, 0x00, 0x00, 0x00, 0x00, 0x49, 0x4e, 0x54, 0x5f,
	0x4f, 0x56, 0x45, 0x52, 0x46, 0x4c, 0x4f, 0x57, 0x00, 0x00, 0x00, 0x00,
	0x49, 0x4e, 0x54, 0x5f, 0x44, 0x49, 0x56, 0x49, 0x44, 0x45, 0x5f, 0x42,
	0x59, 0x5f, 0x5a, 0x45, 0x52, 0x4f, 0x00, 0x00, 0x46, 0x4c, 0x54, 0x5f,
	0x55, 0x4e, 0x44, 0x45, 0x52, 0x46, 0x4c, 0x4f, 0x57, 0x00, 0x00, 0x00,
	0x46, 0x4c, 0x54, 0x5f, 0x53, 0x54, 0x41, 0x43, 0x4b, 0x5f, 0x43, 0x48,
	0x45, 0x43, 0x4b, 0x00, 0x46, 0x4c, 0x54, 0x5f, 0x4f, 0x56, 0x45, 0x52,
	0x46, 0x4c, 0x4f, 0x57, 0x00, 0x00, 0x00, 0x00, 0x46, 0x4c, 0x54, 0x5f,
	0x49, 0x4e, 0x56, 0x41, 0x4c, 0x49, 0x44, 0x5f, 0x4f, 0x50, 0x45, 0x52,
	0x41, 0x54, 0x49, 0x4f, 0x4e, 0x00, 0x00, 0x00, 0x46, 0x4c, 0x54, 0x5f,
	0x49, 0x4e, 0x45, 0x58, 0x41, 0x43, 0x54, 0x5f, 0x52, 0x45, 0x53, 0x55,
	0x4c, 0x54, 0x00, 0x00, 0x46, 0x4c, 0x54, 0x5f, 0x44, 0x49, 0x56, 0x49,
	0x44, 0x45, 0x5f, 0x42, 0x59, 0x5f, 0x5a, 0x45, 0x52, 0x4f, 0x00, 0x00,
	0x4e, 0x4f, 0x4e, 0x43, 0x4f, 0x4e, 0x54, 0x49, 0x4e, 0x55, 0x41, 0x42,
	0x4c, 0x45, 0x5f, 0x45, 0x58, 0x43, 0x45, 0x50, 0x54, 0x49, 0x4f, 0x4e,
	0x00, 0x00, 0x00, 0x00, 0x49, 0x4e, 0x56, 0x41, 0x4c, 0x49, 0x44, 0x5f,
	0x44, 0x49, 0x53, 0x50, 0x4f, 0x53, 0x49, 0x54, 0x49, 0x4f, 0x4e, 0x00,
	0x46, 0x4c, 0x54, 0x5f, 0x44, 0x45, 0x4e, 0x4f, 0x52, 0x4d, 0x41, 0x4c,
	0x5f, 0x4f, 0x50, 0x45, 0x52, 0x41, 0x4e, 0x44, 0x00, 0x00, 0x00, 0x00,
	0x41, 0x52, 0x52, 0x41, 0x59, 0x5f, 0x42, 0x4f, 0x55, 0x4e, 0x44, 0x53,
	0x5f, 0x45, 0x58, 0x43, 0x45, 0x45, 0x44, 0x45, 0x44, 0x00, 0x00, 0x00,
	0x49, 0x4c, 0x4c, 0x45, 0x47, 0x41, 0x4c, 0x5f, 0x49, 0x4e, 0x53, 0x54,
	0x52, 0x55, 0x43, 0x54, 0x49, 0x4f, 0x4e, 0x00, 0x49, 0x4e, 0x5f, 0x50,
	0x41, 0x47, 0x45, 0x5f, 0x45, 0x52, 0x52, 0x4f, 0x52, 0x00, 0x00, 0x00,
	0x30, 0x78, 0x25, 0x30, 0x38, 0x58, 0x00, 0x00, 0x57, 0x52, 0x49, 0x54,
	0x45, 0x20, 0x00, 0x00, 0x52, 0x45, 0x41, 0x44, 0x20, 0x00, 0x00, 0x00,
	0x41, 0x43, 0x43, 0x45, 0x53, 0x53, 0x5f, 0x56, 0x49, 0x4f, 0x4c, 0x41,
	0x54, 0x49, 0x4f, 0x4e, 0x20, 0x00, 0x00, 0x00, 0x42, 0x52, 0x45, 0x41,
	0x4b, 0x50, 0x4f, 0x49, 0x4e, 0x54, 0x00, 0x00, 0x53, 0x49, 0x4e, 0x47,
	0x4c, 0x45, 0x5f, 0x53, 0x54, 0x45, 0x50, 0x00, 0x2d, 0x2d, 0x2d, 0x2d,
	0x2d, 0x2d, 0x2d, 0x2d, 0x2d, 0x2d, 0x2d, 0x2d, 0x2d, 0x2d, 0x2d, 0x2d,
	0x2d, 0x2d, 0x2d, 0x2d, 0x2d, 0x2d, 0x2d, 0x2d, 0x0d, 0x0a, 0x00, 0x00,
	0x0d, 0x0a, 0x00, 0x00, 0x5f, 0x5f, 0x63, 0x72, 0x61, 0x73, 0x68, 0x64,
	0x75, 0x6d, 0x70, 0x2e, 0x6c, 0x6f, 0x67, 0x00, 0x20, 0x00, 0x00, 0x00,
	0x2d, 0x2d, 0x3e, 0x20, 0x00, 0x00, 0x00, 0x00, 0x3f, 0x3f, 0x3f, 0x20,
	0x00, 0x00, 0x00, 0x00,
};

// FUNCTION: SERVER 0x10002770
#include <stdio.h>
#include <string.h>
#include <windows.h>
void __cdecl LogMessageInternal(char* module, unsigned int line, char* msg, int severity);
char __cdecl check_memory_protection(unsigned int);
char __cdecl AnalyzeInstruction(int, int, int, int*);
unsigned char __cdecl EmitCrashModuleLine(int*);
int g_crash_callback = 0;

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
 * case 0xc000008e falls into.  group_a_done repeats the frame fill's first
 * statement, the hCrashLog store, and jumps past the frame fill's copy.  It
 * uses no scratch register (hCrashLog is ebp), so the copies compile alike:
 * c2 cross-jumps them into the frame fill and then tail A's newline call
 * into tail B's, as in the reference.  An
 * empty label there collapses into the switch end and the A arms stop
 * merging; a copy that loads into a scratch register (frameInfo[0]) differs
 * between the two sites and stays in tail A.  pStack is stored after the
 * frameInfo zero stores, as in the reference; stored in the join copies it
 * lands before them, and hDbgFile and pDbgBuf (three references each) come
 * out in each other's stack slots.
 *
 * Separator copies (0x100028fb..0x1000294c, instruction-exact).  szLine,
 * space and szSep are initialised locals of an inner block opened after the
 * Esp read.  c2 orders a load through pCtx behind (or ahead of) stores to the
 * outer address-taken locals, which a memcpy or assignment gives, but not
 * behind an initialiser's stores; with no such edge the Esp load drops to its
 * own height and issues after the rep movs, as in the reference.  The Esp
 * read has to stay ahead of the copies: that puts the pCtx load's scratch
 * pick before the szLine pair's, giving eax, ecx, edx.  The two literals
 * duplicate the bytes at 0x10027314 and 0x100272f8.
 *
 * Still open: the scheduling of the frame fill's first two loads. */
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
	int frameInfo[7];
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
		char* pStart;

		/* Find last char */
		path_cursor = szModulePath;
		if (*path_cursor != '\0') {
			while (*path_cursor != '\0') {
				path_cursor++;
			}
			/* Search backwards for '.' */
			pStart = szModulePath;
			while (path_cursor >= pStart) {
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
						hCrashLog = CreateFileA((const char*) 0x10027318, 0x40000000, 0, 0, 4, 0x80, 0);

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
								WriteFile(hCrashLog, (const char*) 0x100272ec, 0xb, &nBytesWritten, 0);
								WriteFile(hCrashLog, szLine, 2, &nBytesWritten, 0);
								goto group_a_done;
							case 0x80000003:
								WriteFile(hCrashLog, (const char*) 0x100272e0, 0xa, &nBytesWritten, 0);
								WriteFile(hCrashLog, szLine, 2, &nBytesWritten, 0);
								goto group_a_done;
							case 0xc0000005:
								/* ACCESS_VIOLATION */
								WriteFile(hCrashLog, (const char*) 0x100272cc, 0x11, &nBytesWritten, 0);
								if (pExceptionPointers->ExceptionRecord->ExceptionInformation[0] == 0) {
									WriteFile(hCrashLog, (const char*) 0x100272c4, 5, &nBytesWritten, 0);
								}
								else {
									WriteFile(hCrashLog, (const char*) 0x100272bc, 6, &nBytesWritten, 0);
								}
								sprintf(szDateBuf, (const char*) 0x100272b4, pExceptionPointers->ExceptionRecord->ExceptionInformation[1]);
								WriteFile(hCrashLog, szDateBuf, strlen(szDateBuf), &nBytesWritten, 0);
								WriteFile(hCrashLog, szLine, 2, &nBytesWritten, 0);
								break;
							case 0xc0000006:
								WriteFile(hCrashLog, (const char*) 0x100272a4, 0xd, &nBytesWritten, 0);
								WriteFile(hCrashLog, szLine, 2, &nBytesWritten, 0);
								break;
							case 0xc000001d:
								WriteFile(hCrashLog, (const char*) 0x10027290, 0x13, &nBytesWritten, 0);
								WriteFile(hCrashLog, szLine, 2, &nBytesWritten, 0);
								break;
							case 0xc000008c:
								WriteFile(hCrashLog, (const char*) 0x10027278, 0x15, &nBytesWritten, 0);
								WriteFile(hCrashLog, szLine, 2, &nBytesWritten, 0);
								goto group_a_done;
							case 0xc000008d:
								WriteFile(hCrashLog, (const char*) 0x10027260, 0x14, &nBytesWritten, 0);
								WriteFile(hCrashLog, szLine, 2, &nBytesWritten, 0);
								goto group_a_done;
							case 0xc0000026:
								WriteFile(hCrashLog, (const char*) 0x1002724c, 0x13, &nBytesWritten, 0);
								WriteFile(hCrashLog, szLine, 2, &nBytesWritten, 0);
								goto group_a_done;
							case 0xc0000025:
								WriteFile(hCrashLog, (const char*) 0x10027230, 0x18, &nBytesWritten, 0);
								WriteFile(hCrashLog, szLine, 2, &nBytesWritten, 0);
								goto group_a_done;
							case 0xc000008e:
								WriteFile(hCrashLog, (const char*) 0x1002721c, 0x12, &nBytesWritten, 0);
								WriteFile(hCrashLog, szLine, 2, &nBytesWritten, 0);
group_a_done:
								frameInfo[1] = (int) hCrashLog;
								goto frame_fill;
							case 0xc000008f:
								WriteFile(hCrashLog, (const char*) 0x10027208, 0x12, &nBytesWritten, 0);
								WriteFile(hCrashLog, szLine, 2, &nBytesWritten, 0);
								break;
							case 0xc0000090:
								WriteFile(hCrashLog, (const char*) 0x100271f0, 0x15, &nBytesWritten, 0);
								WriteFile(hCrashLog, szLine, 2, &nBytesWritten, 0);
								break;
							case 0xc0000091:
								WriteFile(hCrashLog, (const char*) 0x100271e0, 0xc, &nBytesWritten, 0);
								WriteFile(hCrashLog, szLine, 2, &nBytesWritten, 0);
								break;
							case 0xc0000092:
								WriteFile(hCrashLog, (const char*) 0x100271d0, 0xf, &nBytesWritten, 0);
								WriteFile(hCrashLog, szLine, 2, &nBytesWritten, 0);
								break;
							case 0xc0000093:
								WriteFile(hCrashLog, (const char*) 0x100271c0, 0xd, &nBytesWritten, 0);
								WriteFile(hCrashLog, szLine, 2, &nBytesWritten, 0);
								break;
							case 0xc0000094:
								WriteFile(hCrashLog, (const char*) 0x100271ac, 0x12, &nBytesWritten, 0);
								WriteFile(hCrashLog, szLine, 2, &nBytesWritten, 0);
								break;
							case 0xc0000095:
								WriteFile(hCrashLog, (const char*) 0x1002719c, 0xc, &nBytesWritten, 0);
								WriteFile(hCrashLog, szLine, 2, &nBytesWritten, 0);
								break;
							case 0xc0000096:
								WriteFile(hCrashLog, (const char*) 0x10027188, 0x10, &nBytesWritten, 0);
								WriteFile(hCrashLog, szLine, 2, &nBytesWritten, 0);
								break;
							case 0xc00000fd:
								WriteFile(hCrashLog, (const char*) 0x10027178, 0xe, &nBytesWritten, 0);
								WriteFile(hCrashLog, szLine, 2, &nBytesWritten, 0);
								break;
							default:
								goto unknown_exc;
							}

unknown_exc:

							/* Stack walk */
							frameInfo[1] = (int) hCrashLog;
frame_fill:
							frameInfo[0] = (int) pDbgBuf;
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
							LogMessageInternal((char*) 0x10027144, 0x20f, (char*) 0x10027164, 1);
						}
					}
					else {
						LogMessageInternal((char*) 0x10027144, 0x213, (char*) 0x1002712c, 1);
					}
					VirtualFree(pDbgBuf, 0, 0x8000);
				}
				else {
					LogMessageInternal((char*) 0x10027144, 0x218, (char*) 0x10027120, 1);
				}
			}
			else {
				LogMessageInternal((char*) 0x10027144, 0x21b, (char*) 0x10027110, 1);
			}
			CloseHandle(hDbgFile);
		}
		else {
			LogMessageInternal((char*) 0x10027144, 0x220, (char*) 0x10027104, 1);
		}
	}

	if (g_crash_callback && !fCanContinue) {
		((void (__cdecl*)(int)) g_crash_callback)(-1);
	}
	UnhandledExceptionFilter(pExceptionPointers);

	return 1;
}
