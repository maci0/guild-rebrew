#include <windows.h>
#include <stdio.h>
#include <string.h>

char __cdecl check_memory_protection(unsigned int);
char __cdecl AnalyzeInstruction(int, int, int, int*);
unsigned char __cdecl EmitCrashModuleLine(int*);

extern void (*g_crash_callback)(void);

/* Crash handler: rewrites the module path to <name>.dbg, loads and decrypts
 * it, appends a dated record to __crashdump.log (exception name, then one
 * line per stack frame via EmitCrashModuleLine) and chains to
 * UnhandledExceptionFilter.  This build has no LogMessageInternal error arms,
 * so every failure path shares the single VirtualFree(pDbgBuf) and
 * CloseHandle(hDbgFile) tail. */

int __stdcall fcn_0041cbc0(EXCEPTION_POINTERS* pExceptionPointers)
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
					}
					VirtualFree(pDbgBuf, 0, 0x8000);
				}
			}
			CloseHandle(hDbgFile);
		}
	}

	if (g_crash_callback && !fCanContinue) {
		((void (__cdecl*)(int)) g_crash_callback)(-1);
	}
	UnhandledExceptionFilter(pExceptionPointers);

	return 1;
}
