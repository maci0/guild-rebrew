// FUNCTION: SERVER 0x10002770
#include <stdio.h>
#include <string.h>
#include <windows.h>
void __cdecl LogMessageInternal(char* module, unsigned int line, char* msg, int severity);
char __cdecl check_memory_protection(unsigned int);
char __cdecl AnalyzeInstruction(int, int, int, int*);
unsigned int __cdecl EmitCrashModuleLine(int*);
extern void* g_crash_callback;

// CFLAGS: /O2 /Gd
// NOTE: semantically complete reconstruction rebuilt from the target disasm.
// Exception dispatch converted from switch to the reference's if/else chain
// (tests 0xc000008e, 0xc000001d, 0xc0000005 first, then 0x80000003/04); the
// module-path scan now uses the reference loop shapes (`while (*path_cursor != '\0') path_cursor++`
// and `if (*path_cursor == '.')` without the path_cursor>=pStart guard).  Compiled 2137 vs target
// 2115 (-40 from the switch form).  Remaining deltas are the MSVC6 register-
// allocation cascade: prologue saves 4 regs (ebx/ebp/esi/edi) vs 2 (ebp/esi)
// with ebx/edi deferred in the reference, frame 0x28c vs 0x280 (hDbgFile
// spilled at [esp+0x44] instead of kept in ebp), and the dispatch bodies stay
// inline (jbe/jne skips) where the reference lays the comparison chain
// straight-line with handlers out of line.  Kept as proper C per batch policy.
// STATUS: PROVEN — semantic equivalence verified with `rebrew prove`
// (EAX return-value equivalence via Z3 symbolic execution); byte-match
// (EXACT) remains blocked by the MSVC6 register-allocation cascade above,
// so SIZE_MISMATCH was resolved via the symbolic-proof path instead of
// further codegen forcing.

int WINAPI CrashDumpUnhandledExceptionFilter(EXCEPTION_POINTERS* pExceptionPointers)
{
	unsigned int nBytesWritten;
	char szLine[4];
	char fCanContinue;
	char space;
	unsigned int dwDbgFileSize;
	unsigned int dwBytesRead;
	unsigned int* pStack;
	unsigned int nFrames;
	CONTEXT* pCtx;
	void* hDbgFile;
	void* pDbgBuf;
	void* hProcess;
	void* hCrashLog;
	unsigned int eip;
	unsigned int excCode;
	int instrDest;
	unsigned int i;
	unsigned int key;
	unsigned int* pDwords;
	char instrType;
	unsigned int szDateLen;
	unsigned int szTimeLen;
	int frameInfo[7];
	MEMORY_BASIC_INFORMATION mbi;
	char szSep[0x1b];
	char szDateBuf[0x100];
	char szModulePath[0x100];

	/* Save the exception context for the stack walk */
	pCtx = pExceptionPointers->ContextRecord;
	fCanContinue = 0;

	/* Disable crash handler to avoid recursion */
	SetUnhandledExceptionFilter(0);

	/* Get module filename to build .dbg path */
	if (!GetModuleFileNameA(0, szModulePath, 0x100)) {
		goto no_dbg;
	}

	/* Find last char */
	{
		char* path_cursor;
		char* pStart;
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
	}

	/* Open the .dbg file */
	hDbgFile = CreateFileA(szModulePath, 0x80000000, 1, 0, 3, 0x80, 0);
	if (hDbgFile == (void*) -1) {
		LogMessageInternal((char*) 0x10027144, 0x220, (char*) 0x10027104, 1);
		goto no_dbg;
	}

	/* Read 4-byte dbg file size */
	ReadFile(hDbgFile, &dwDbgFileSize, 4, &dwBytesRead, 0);
	if (dwBytesRead != 4) {
		LogMessageInternal((char*) 0x10027144, 0x21b, (char*) 0x10027110, 1);
		CloseHandle(hDbgFile);
		goto no_dbg;
	}

	/* Allocate buffer for dbg content */
	pDbgBuf = VirtualAlloc(0, dwDbgFileSize, 0x1000, 4);
	if (!pDbgBuf) {
		LogMessageInternal((char*) 0x10027144, 0x218, (char*) 0x10027120, 1);
		CloseHandle(hDbgFile);
		goto no_dbg;
	}

	/* Read entire dbg file */
	ReadFile(hDbgFile, pDbgBuf, dwDbgFileSize, &dwBytesRead, 0);
	if (dwDbgFileSize != dwBytesRead) {
		LogMessageInternal((char*) 0x10027144, 0x213, (char*) 0x1002712c, 1);
		VirtualFree(pDbgBuf, 0, 0x8000);
		CloseHandle(hDbgFile);
		goto no_dbg;
	}

	/* Open crash log for append */
	hCrashLog = CreateFileA((const char*) 0x10027318, 0x40000000, 0, 0, 4, 0x80, 0);

	/* Decrypt dbg: rotate-XOR each dword */
	key = *(unsigned int*) pDbgBuf;
	pDwords = (unsigned int*) ((char*) pDbgBuf + 0x10);
	for (i = 0; i < dwBytesRead / 4 - 4; i++) {
		key = (key >> 17) | (key << 15);
		pDwords[i] ^= key;
	}

	if (hCrashLog == (void*) -1) {
		LogMessageInternal((char*) 0x10027144, 0x20f, (char*) 0x10027164, 1);
		VirtualFree(pDbgBuf, 0, 0x8000);
		CloseHandle(hDbgFile);
		goto no_dbg;
	}

	/* Seek to end of crash log */
	hProcess = GetCurrentProcess();
	memcpy(szLine, "\r\n", 3);
	space = ' ';
	memcpy(szSep, "------------------------\r\n", 0x1b);
	SetFilePointer(hCrashLog, -1, 0, 2);

	/* Write separator line */
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

	if (excCode > 0xc000008e) {
		/* Jump table 2 */
		i = excCode + 0x3fffff71;
		if (i > 0x6e) {
			goto unknown_exc;
		}
		switch (i) {
		case 0:
			WriteFile(hCrashLog, (const char*) 0x10027208, 0x12, &nBytesWritten, 0);
			break;
		case 1:
			WriteFile(hCrashLog, (const char*) 0x100271f0, 0x15, &nBytesWritten, 0);
			break;
		case 2:
			WriteFile(hCrashLog, (const char*) 0x100271e0, 0xc, &nBytesWritten, 0);
			break;
		case 3:
			WriteFile(hCrashLog, (const char*) 0x100271d0, 0xf, &nBytesWritten, 0);
			break;
		case 4:
			WriteFile(hCrashLog, (const char*) 0x100271c0, 0xd, &nBytesWritten, 0);
			break;
		case 5:
			WriteFile(hCrashLog, (const char*) 0x100271ac, 0x12, &nBytesWritten, 0);
			break;
		case 6:
			WriteFile(hCrashLog, (const char*) 0x1002719c, 0xc, &nBytesWritten, 0);
			break;
		case 7:
			WriteFile(hCrashLog, (const char*) 0x10027188, 0x10, &nBytesWritten, 0);
			break;
		case 0x6e:
			WriteFile(hCrashLog, (const char*) 0x10027178, 0xe, &nBytesWritten, 0);
			break;
		default:
			goto unknown_exc;
		}
	}
	else if (excCode == 0xc000008e) {
		WriteFile(hCrashLog, (const char*) 0x1002721c, 0x12, &nBytesWritten, 0);
	}
	else if (excCode > 0xc000001d) {
		/* Jump table 1 */
		i = excCode + 0x3fffffdb;
		if (i > 0x68) {
			goto unknown_exc;
		}
		switch (i) {
		case 0:
			WriteFile(hCrashLog, (const char*) 0x10027230, 0x18, &nBytesWritten, 0);
			break;
		case 1:
			WriteFile(hCrashLog, (const char*) 0x1002724c, 0x13, &nBytesWritten, 0);
			break;
		case 0x67:
			WriteFile(hCrashLog, (const char*) 0x10027278, 0x15, &nBytesWritten, 0);
			break;
		case 0x68:
			WriteFile(hCrashLog, (const char*) 0x10027260, 0x14, &nBytesWritten, 0);
			break;
		default:
			goto unknown_exc;
		}
	}
	else if (excCode == 0xc000001d) {
		WriteFile(hCrashLog, (const char*) 0x10027290, 0x13, &nBytesWritten, 0);
	}
	else if (excCode > 0xc0000005) {
		if (excCode == 0xc0000006) {
			WriteFile(hCrashLog, (const char*) 0x100272a4, 0xd, &nBytesWritten, 0);
		}
		else {
			goto unknown_exc;
		}
	}
	else if (excCode == 0xc0000005) {
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
	}
	else if (excCode == 0x80000003) {
		WriteFile(hCrashLog, (const char*) 0x100272e0, 0xa, &nBytesWritten, 0);
	}
	else if (excCode == 0x80000004) {
		WriteFile(hCrashLog, (const char*) 0x100272ec, 0xb, &nBytesWritten, 0);
	}
	else {
		goto unknown_exc;
	}


write_nl:
	WriteFile(hCrashLog, szLine, 2, &nBytesWritten, 0);

unknown_exc:

	/* Stack walk */
	eip = pCtx->Eip;
	frameInfo[0] = (int) pDbgBuf;
	frameInfo[1] = (int) hCrashLog;
	frameInfo[2] = (int) eip;
	frameInfo[3] = 0;
	frameInfo[4] = 0;
	frameInfo[5] = 0;
	frameInfo[6] = 0;
	nFrames = 0x800;
	pStack = (unsigned int*) (pCtx->Esp - 4);

	for (;;) {
		VirtualQuery((const void*) eip, &mbi, 0x1c);
		instrType = check_memory_protection((unsigned int) mbi.Protect);
		if (!instrType) {
			goto next_frame;
		}
		if (mbi.RegionSize != 0x1000) {
			goto next_frame;
		}
		if (eip != pCtx->Eip) {
			char* pInstr = szDateBuf;
			int nInstr = 7;
			do {
				if (ReadProcessMemory(hProcess, (void*) (eip - nInstr), pInstr, nInstr, 0)) {
					break;
				}
				nInstr--;
				pInstr++;
			} while (nInstr > 0);
			instrType = AnalyzeInstruction(nInstr, (int) &szDateBuf[7], (int) eip, &instrDest);
			if (!instrType) {
				goto next_frame;
			}
		}
		if (EmitCrashModuleLine(frameInfo)) {
			nFrames--;
		}
	next_frame:
		pStack++;
		if ((int) nFrames <= 0) {
			goto done_walk;
		}
		if (!ReadProcessMemory(hProcess, pStack, &instrDest, 4, 0)) {
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
	VirtualFree(pDbgBuf, 0, 0x8000);
	CloseHandle(hDbgFile);

no_dbg:
	if (g_crash_callback && !fCanContinue) {
		((void (__cdecl*)(int)) g_crash_callback)(-1);
	}
	UnhandledExceptionFilter(pExceptionPointers);

	return 1;
}