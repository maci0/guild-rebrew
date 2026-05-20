#include <stdio.h>
#include <string.h>
#include <time.h>
#include <windows.h>
void __cdecl LogMessageInternal(char* module, unsigned int line, char* msg, int severity);
extern char* __cdecl _ctime(const time_t*);

char __cdecl check_memory_protection(unsigned int);
char __cdecl AnalyzeInstruction(int, int, int, int*);
unsigned int __cdecl EmitCrashModuleLine(int*);
extern void* g_10034614;
char* __cdecl GetDebugRecordByIndex();
void __cdecl DispatchLogOutput(const char* text, unsigned char output_mask, int severity);
extern int g_severity_table[3];
extern unsigned int g_log_mode_flags;
extern int g_console_handle;
extern int g_owner_window;
extern void (*g_panic_callback)(void);
extern char g_log_message_buffer;
extern int g_handler_started;
extern int g_handler_flags;
extern char g_msg_buf[];
void __cdecl write_log(char*, int, char*);

/* Dispatches a log message to the configured output handlers
 * (file, debugger, etc.). Routes based on severity level. */

// STUB: SERVER 0x10002770
// CrashDumpUnhandledExceptionFilter

int WINAPI CrashDumpUnhandledExceptionFilter(EXCEPTION_POINTERS* pExceptionPointers)
{
	char szModulePath[0x100];
	char* p;
	char* pStart;
	void* hDbgFile;
	unsigned int dwDbgFileSize;
	unsigned int dwBytesRead;
	void* pDbgBuf;
	void* hCrashLog;
	void* hProcess;
	char szDateLen;
	char szTimeLen;
	char szDateBuf[0x100];
	char szTimeBuf[0x100];
	char szExcDesc[0x100];
	unsigned int i;
	unsigned int* pDwords;
	unsigned int key;
	unsigned int nDwords;
	unsigned int excCode;
	EXCEPTION_RECORD* pExcRec;
	const char* pExcName;
	unsigned int excNameLen;
	unsigned int nBytesWritten;
	unsigned int nBytesRead2;
	int instrDest;
	char instrType;
	char fCanContinue;
	int frameInfo[7];
	MEMORY_BASIC_INFORMATION mbi;
	unsigned int nFrames;
	unsigned int* pStack;
	unsigned int eip;
	unsigned int idx;

	/* Disable crash handler to avoid recursion */
	SetUnhandledExceptionFilter(0);

	/* Save exception pointer for callback */
	frameInfo[0] = (int) pExceptionPointers;

	/* Get module filename to build .dbg path */
	GetModuleFileNameA(0, szModulePath, 0x100);

	/* Find last char */
	p = szModulePath;
	if (*p != '\0') {
		while (*(p + 1)) {
			p++;
		}
		/* Search backwards for '.' */
		pStart = szModulePath;
		while (p >= pStart) {
			if (*p == '.') {
				break;
			}
			p--;
		}
		if (p >= pStart && *p == '.') {
			p++;
			*p = 'd';
			p++;
			*p = 'b';
			p++;
			*p = 'g';
			*(p + 1) = '\0';
		}
	}

	/* gm_Open the .dbg file */
	hDbgFile = CreateFileA(szModulePath, 0x80000000, 1, 0, 3, 0x80, 0);
	hCrashLog = (void*) -1;
	frameInfo[1] = (int) hCrashLog;

	if (hDbgFile == (void*) -1) {
		goto no_dbg;
	}

	/* Read 4-byte dbg file size */
	ReadFile(hDbgFile, &dwDbgFileSize, 4, &dwBytesRead, 0);
	if (dwBytesRead != 4) {
		goto close_dbg;
	}

	/* Allocate buffer for dbg content */
	pDbgBuf = VirtualAlloc(0, dwDbgFileSize, 0x1000, 4);
	frameInfo[2] = (int) pDbgBuf;
	if (!pDbgBuf) {
		goto close_dbg;
	}

	/* Read entire dbg file */
	ReadFile(hDbgFile, pDbgBuf, dwDbgFileSize, &dwBytesRead, 0);
	if (dwDbgFileSize != dwBytesRead) {
		goto bad_dbg_free;
	}

	/* gm_Open crash log for append */
	hCrashLog = CreateFileA((const char*) 0x10027318, 0x40000000, 0, 0, 4, 0x80, 0);
	frameInfo[1] = (int) hCrashLog;

	/* Decrypt dbg: rotate-XOR each dword */
	key = *(unsigned int*) pDbgBuf;
	nDwords = dwBytesRead / 4 - 4;
	pDwords = (unsigned int*) ((char*) pDbgBuf + 0x10);
	i = 0;
	if (nDwords != 0) {
		do {
			unsigned int rotkey;
			rotkey = (key >> 17) | (key << 15);
			pDwords[i] ^= rotkey;
			i++;
		} while (i < nDwords);
	}

	if (hCrashLog == (void*) -1) {
		goto bad_dbg_free;
	}

	/* Seek to end of crash log */
	hProcess = GetCurrentProcess();
	SetFilePointer(hCrashLog, -1, 0, 2);

	/* Write separator line */
	WriteFile(hCrashLog, (const char*) 0x100272f8, 0x1a, &nBytesWritten, 0);

	/* Write date */
	szDateLen = (char) GetDateFormatA(0x400, 2, 0, 0, szDateBuf, 0x100);
	if (szDateLen) {
		WriteFile(hCrashLog, szDateBuf, (unsigned int) (szDateLen - 1), &nBytesWritten, 0);
		{
			char sp = ' ';
			WriteFile(hCrashLog, &sp, 1, &nBytesWritten, 0);
		}
	}

	/* Write time */
	szTimeLen = (char) GetTimeFormatA(0x400, 8, 0, 0, szTimeBuf, 0x100);
	if (szTimeLen) {
		WriteFile(hCrashLog, szTimeBuf, (unsigned int) (szTimeLen - 1), &nBytesWritten, 0);
		{
			char nl[2];
			nl[0] = '\r';
			nl[1] = '\n';
			WriteFile(hCrashLog, nl, 2, &nBytesWritten, 0);
		}
	}

	/* Classify exception */
	pExcRec = pExceptionPointers->ExceptionRecord;
	excCode = pExcRec->ExceptionCode;
	pExcName = 0;
	excNameLen = 0;

	if (excCode == 0x80000003) {
		/* BREAKPOINT */
		pExcName = (const char*) 0x100272e0;
		excNameLen = 0xa;
		goto write_exc_name_nl;
	}
	if (excCode == 0x80000004) {
		/* SINGLE_STEP */
		pExcName = (const char*) 0x100272ec;
		excNameLen = 0xb;
		goto write_exc_name_nl;
	}
	if (excCode == 0xc0000005) {
		/* ACCESS_VIOLATION */
		WriteFile(hCrashLog, (const char*) 0x100272cc, 0x11, &nBytesWritten, 0);
		if (pExcRec->ExceptionInformation[0] == 0) {
			WriteFile(hCrashLog, (const char*) 0x100272c4, 5, &nBytesWritten, 0);
		}
		else {
			WriteFile(hCrashLog, (const char*) 0x100272bc, 6, &nBytesWritten, 0);
		}
		sprintf(szExcDesc, (const char*) 0x100272b4, pExcRec->ExceptionInformation[1]);
		{
			char* s2 = szExcDesc;
			unsigned int l2;
			while (*s2) {
				s2++;
			}
			l2 = (unsigned int) (s2 - szExcDesc);
			WriteFile(hCrashLog, szExcDesc, l2, &nBytesWritten, 0);
		}
		goto write_nl;
	}
	if (excCode == 0xc000001d) {
		pExcName = (const char*) 0x10027290;
		excNameLen = 0x13;
		goto write_exc_name_nl;
	}
	if (excCode > 0xc000001d && excCode < 0xc000008e) {
		/* Jump table 1 */
		idx = excCode + 0x3fffffdb;
		if (idx > 0x68) {
			goto unknown_exc;
		}
		switch (idx) {
		case 0:
			pExcName = (const char*) 0x10027278;
			excNameLen = 0x15;
			break;
		case 1:
			pExcName = (const char*) 0x10027260;
			excNameLen = 0x14;
			break;
		case 2:
			pExcName = (const char*) 0x1002724c;
			excNameLen = 0x13;
			break;
		case 3:
			pExcName = (const char*) 0x10027230;
			excNameLen = 0x18;
			break;
		case 4:
			pExcName = (const char*) 0x1002721c;
			excNameLen = 0x12;
			break;
		default:
			goto unknown_exc;
		}
		goto write_exc_name_nl;
	}
	if (excCode == 0xc000008e) {
		pExcName = (const char*) 0x1002721c;
		excNameLen = 0x12;
		goto write_exc_name_nl;
	}
	if (excCode > 0xc000008e) {
		/* Jump table 2 */
		idx = excCode + 0x3fffff71;
		if (idx > 0x6e) {
			goto unknown_exc;
		}
		switch (idx) {
		case 0:
			pExcName = (const char*) 0x10027208;
			excNameLen = 0x12;
			break;
		case 1:
			pExcName = (const char*) 0x100271f0;
			excNameLen = 0x15;
			break;
		case 2:
			pExcName = (const char*) 0x100271e0;
			excNameLen = 0xc;
			break;
		case 3:
			pExcName = (const char*) 0x100271d0;
			excNameLen = 0xf;
			break;
		case 4:
			pExcName = (const char*) 0x100271c0;
			excNameLen = 0xd;
			break;
		case 5:
			pExcName = (const char*) 0x100271ac;
			excNameLen = 0x12;
			break;
		case 6:
			pExcName = (const char*) 0x1002719c;
			excNameLen = 0xc;
			break;
		case 7:
			pExcName = (const char*) 0x10027188;
			excNameLen = 0x10;
			break;
		case 0x6e:
			pExcName = (const char*) 0x10027178;
			excNameLen = 0xe;
			WriteFile(hCrashLog, pExcName, excNameLen, &nBytesWritten, 0);
			goto write_nl;
		default:
			goto unknown_exc;
		}
		goto write_exc_name_nl;
	}

unknown_exc:
	goto write_nl;

write_exc_name_nl:
	if (pExcName) {
		WriteFile(hCrashLog, pExcName, excNameLen, &nBytesWritten, 0);
	}
write_nl: {
	char nl[2];
	nl[0] = '\r';
	nl[1] = '\n';
	WriteFile(hCrashLog, nl, 2, &nBytesWritten, 0);
}

	/* Stack walk */
	eip = pExceptionPointers->ContextRecord->Eip;
	pDbgBuf = (void*) ((char*) pDbgBuf - 4);
	frameInfo[3] = (int) pDbgBuf;
	frameInfo[4] = (int) hCrashLog;
	frameInfo[5] = eip;
	frameInfo[6] = 0;
	nFrames = 0x800;
	pStack = (unsigned int*) ((unsigned int) pExceptionPointers->ContextRecord->Esp - 4);

	while (nFrames > 0) {
		pStack++;
		VirtualQuery((const void*) *pStack, &mbi, 0x1c);
		instrType = check_memory_protection((unsigned int) mbi.Protect);
		if (!instrType || mbi.RegionSize < 0x1000) {
			goto next_frame;
		}
		if (eip != pExceptionPointers->ContextRecord->Eip) {
			instrType = AnalyzeInstruction((int) *pStack, 7, (int) *pStack, &instrDest);
			if (!instrType) {
				goto next_frame;
			}
			if (!EmitCrashModuleLine(frameInfo)) {
				goto next_frame;
			}
		}
		nFrames--;
		frameInfo[5] = (int) pStack;
		eip = *pStack;
		if ((int) nFrames <= 0) {
			goto done_walk;
		}
		ReadProcessMemory(hProcess, (const void*) frameInfo[4], szExcDesc, 4, &nBytesRead2);
		if (nBytesRead2 != 0) {
			goto next_frame;
		}
	next_frame:;
	}

done_walk:

	/* Restore pDbgBuf pointer */
	pDbgBuf = (void*) frameInfo[3];

	if (hCrashLog != (void*) -1) {
		CloseHandle(hCrashLog);
	}
	VirtualFree(pDbgBuf, 0, 0x8000);

close_dbg:
	CloseHandle(hDbgFile);

no_dbg:
	fCanContinue = frameInfo[3] != 0;

	if (g_10034614) {
		((void(__cdecl*)(EXCEPTION_POINTERS*)) g_10034614)(pExceptionPointers);
	}

	if (!fCanContinue) {
		LogMessageInternal((char*) 0x10027144, 0x20f, (char*) 0x10027164, 1);
	}
	else {
		LogMessageInternal((char*) 0x10027144, 0x213, (char*) 0x10027164, 1);
		VirtualFree(pDbgBuf, 0, 0x8000);
		CloseHandle(hCrashLog);
	}

	UnhandledExceptionFilter(pExceptionPointers);

	return 1;

bad_dbg_free:
	VirtualFree(pDbgBuf, 0, 0x8000);
	CloseHandle(hDbgFile);
	goto no_dbg;
}

/* Emits one line of module information for crash dumps.
 * Writes module name, base address, and size to the dump file. */
