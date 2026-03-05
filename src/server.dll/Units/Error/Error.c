#include <stdio.h>
#include <string.h>
#include <windows.h>
#include <time.h>

extern int __cdecl crt_call_extra(char* buf, const char* fmt);
extern int __cdecl crt_write_check(const char* str, int stream);
extern void __cdecl LogMessageInternal(char*, unsigned int, char*, int);
extern char __cdecl check_memory_protection(void*);
extern char __cdecl AnalyzeInstruction(int, int, int, int*);
extern unsigned int __cdecl EmitCrashModuleLine(int*);
extern void* g_10034614;
extern char* __cdecl GetDebugRecordByIndex();
extern void __cdecl DispatchLogOutput(const char* text, int output_mask, int severity);
extern int g_severity_table[3];
extern unsigned int g_log_mode_flags;
extern int g_console_handle;
extern int g_owner_window;
extern void (*g_panic_callback)(void);
extern char g_log_message_buffer;
extern int g_handler_started;
extern int g_handler_flags;
extern char g_msg_buf[];
extern void __cdecl write_log(char*, int, char*);

// STATUS: RELOC
// ORIGIN: GAME
// SIZE: 290
// SYMBOL: _DispatchLogOutput
// ANALYSIS: Core logging sink. Takes an output_mask bitfield: bit 0 writes to file (looking up the correct file name via severity in a global table), bit 2 writes to OutputDebugStringA (debugger), bit 3 writes to the allocated Win32 Console using WriteConsoleA.
// FUNCTION: SERVER 0x10002640
// DispatchLogOutput

/* GLOBAL: SERVER 0x11766100 */
extern char g_log_buffer[256];

/* GLOBAL: SERVER 0x11766204 */
extern int g_log_file_handle;

/* GLOBAL: SERVER 0x10027078 */
extern int g_log_level_table[3];

/* GLOBAL: SERVER 0x10027084 */
extern char g_log_format_table[];

void __cdecl DispatchLogOutput(const char* msg, unsigned char flags, int level)
{
	char buf[260];
	unsigned int written;
	int stream;
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
		stream = crt_call_extra(buf, "at");
		if (stream != 0) {
			goto do_write;
		}

	fallback:
		sprintf(buf, "%s\\%s", g_log_buffer, "__server.log");
		stream = crt_call_extra(buf, "at");
		if (stream == 0) {
			goto skip;
		}

	do_write:
		crt_write_check(msg, stream);
		crt_write_check("\n", stream);
		fflush(stream);
	skip:;
	}

	if (flags & 4) {
		OutputDebugStringA(msg);
		OutputDebugStringA("\n");
	}

	if (flags & 8) {
		WriteFile(g_log_file_handle, msg, strlen(msg), &written, 0);
		WriteFile(g_log_file_handle, "\n", 1, &written, 0);
	}
}

// ORIGIN: GAME
// STATUS: MATCHING
// BLOCKER: comparison direction swap, instruction folding (lea vs mov), jump condition swap, loop rotation / branch layout, zero-extend pattern (xor vs mov)
// SIZE: 1836
// SYMBOL: _CrashDumpUnhandledExceptionFilter@4
// BLOCKER_DELTA: 1727
// ANALYSIS: Decrypts .dbg payload in-place using a 32-bit rolling XOR key (ROL15 per dword). | Validates the candidate instruction pointer is in a committed page before symbol emission. | Primary stack walk: read next return address from ESP-based stack slots (4-byte stride).
// FUNCTION: SERVER 0x10002770
// CrashDumpUnhandledExceptionFilter
// PROTOTYPE: int __stdcall CrashDumpUnhandledExceptionFilter(undefined exceptionPointers)

int __stdcall CrashDumpUnhandledExceptionFilter(EXCEPTION_POINTERS* pExceptionPointers)
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

	/* Open the .dbg file */
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

	/* Open crash log for append */
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
		instrType = check_memory_protection(mbi.Protect);
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

// STATUS: MATCHING
// ORIGIN: GAME
// BLOCKER: instruction folding (lea vs mov), loop rotation / branch layout
// SIZE: 376
// SYMBOL: _EmitCrashModuleLine
// FUNCTION: SERVER 0x10002fc0
// EmitCrashModuleLine

/* Auto-generated Ghidra decompilation */
// BLOCKER_DELTA: 370
// PROTOTYPE: uint __cdecl EmitCrashModuleLine(int * param_1)

unsigned int EmitCrashModuleLine(int* param_1)
{
	void* write_func;
	unsigned int record_idx;
	int* debug_record;
	int* entry_ptr;
	int* write_buf_ptr;
	int write_size;
	unsigned char* dbg_base;
	int write_count;
	unsigned char* newline_ptr;
	unsigned char separator[4];
	unsigned int format_val_a;
	unsigned char format_flag_a;
	unsigned int format_val_b;
	unsigned char format_flag_b;

	int stack_48;
	int stack_20;
	int stack_40;
	int stack_16;
	int stack_60;
	int stack_8;

	dbg_base = (unsigned char*) param_1[0];
	entry_ptr = (int*) (*(int*) (dbg_base + 0xc) + 0x10 + (int) dbg_base);
	record_idx = 0;
	if (*(unsigned int*) (dbg_base + 8) != 0) {
		do {
			if ((entry_ptr[1] <= param_1[2]) && (param_1[2] <= entry_ptr[2])) {
				format_flag_a = *(unsigned char*) 0x10027338;
				format_val_a = *(unsigned int*) 0x10027334;
				format_flag_b = *(unsigned char*) 0x10027330;
				format_val_b = *(unsigned int*) 0x1002732c;
				newline_ptr = 0;
				if (param_1[4] == 0) {
					param_1[4] = entry_ptr[1];
				}
				else if (param_1[4] == param_1[3]) {
					param_1[4] = entry_ptr[1];
					param_1[6] = param_1[6] + 1;
				}
				else {
					newline_ptr = (unsigned char*) &stack_16;
					if ((param_1[5] == 0) || (1 < param_1[6])) {
						if (*(char*) 0x1003461c == '\0') {
							return 0;
						}
					}
					else {
						newline_ptr = (unsigned char*) &stack_8;
						param_1[4] = entry_ptr[1];
						param_1[5] = param_1[5] + -1;
					}
				}
				write_count = entry_ptr[3];
				write_size = 0x10003091;
				debug_record = GetDebugRecordByIndex();
				write_func = (void*) &WriteFile;
				if (newline_ptr != 0) {
					dbg_base = (unsigned char*) &stack_20;
					write_count = 0;
					write_size = 4;
					write_buf_ptr = (int*) newline_ptr;
					((void (*)(int)) write_func)(param_1[1]);
				}
				dbg_base = (unsigned char*) &stack_20;
				write_count = 0;
				write_size = *entry_ptr + -1;
				write_buf_ptr = entry_ptr + 4;
				((void (*)(int)) write_func)(param_1[1]);
				if (debug_record != 0) {
					((void (*)(int, void*, int, void*, int)) write_func)(param_1[1], &stack_16, 1, &stack_40, 0);
					((void (*)(int, int*, int, void*, int)) write_func)(param_1[1], debug_record + 1, *debug_record + -1, &stack_60, 0);
				}
				((void (*)(int, void*, int, void*, int)) write_func)(param_1[1], &stack_48, 2, &stack_40, 0);
				return 1;
			}
			record_idx = record_idx + 1;
			entry_ptr = (int*) ((char*) entry_ptr + *entry_ptr + 0x10);
		} while (record_idx < *(unsigned int*) (dbg_base + 8));
	}
	return 0;
}

// ORIGIN: GAME
// STATUS: EXACT
// SIZE: 33
// SYMBOL: _GetDebugRecordByIndex
// FUNCTION: SERVER 0x10003140
// GetDebugRecordByIndex

/* Variable-length record accessor - walks a record table to find the nth entry */
// PROTOTYPE: char * __cdecl GetDebugRecordByIndex(char * param_1, uint param_2)

char* __cdecl GetDebugRecordByIndex(char* param_1, unsigned int param_2)
{
	char* result;

	if (param_2 < *(unsigned int*) (param_1 + 4)) {
		result = param_1 + 0x10;
		if (param_2 <= 0) {
			return result;
		}
		do {
			result = result + *(int*) result + 4;
		} while (--param_2);
		return result;
	}
	return 0;
}

// STATUS: RELOC
// ORIGIN: GAME
// SIZE: 240
// SYMBOL: _check_memory_protection
// NOTE: Function passes itself to VirtualQuery to check its own code page protection
// GHIDRA: IsExecutableOrReadableProtect
// ANALYSIS: Function passes itself to VirtualQuery to check its own code page protection
// FUNCTION: SERVER 0x10003170
// check_memory_protection
// PROTOTYPE: char __cdecl check_memory_protection(uint protect)

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

// STATUS: MATCHING
// ORIGIN: GAME
// SIZE: 183
// SYMBOL: _AnalyzeInstruction
// FUNCTION: SERVER 0x10003260
// AnalyzeInstruction
// PROTOTYPE: char __cdecl AnalyzeInstruction(int param_1, int param_2, int param_3, int * param_4)
char __cdecl AnalyzeInstruction(int param_1, int param_2, int param_3, int* param_4)
{
	*param_4 = 0;
	if (param_2 >= 5 && *(char*) (param_1 - 5) == (char) 0xe8) {
		*param_4 = *(int*) (param_1 - 4) + param_3;
		return 1;
	}
	if (param_2 >= 3 && *(char*) (param_1 - 3) == (char) 0xff && *(char*) (param_1 - 2) == '\x14') {
		return 2;
	}
	if (param_2 >= 6 && *(char*) (param_1 - 6) == (char) 0xff && *(char*) (param_1 - 5) == '\x15') {
		return 2;
	}
	if (param_2 >= 2) {
		char b1;
		b1 = *(char*) (param_1 - 2);
		if (b1 == (char) 0xff) {
			if (*(unsigned char*) (param_1 - 1) < 0x40) {
				return 2;
			}
			if ((*(unsigned char*) (param_1 - 1) & 0xf8) == 0xd0) {
				return 2;
			}
		}
	}
	if (param_2 >= 3 && *(char*) (param_1 - 3) == (char) 0xff && (*(unsigned char*) (param_1 - 2) & 0xf8) == 0x50) {
		return 2;
	}
	if (param_2 >= 7 && *(char*) (param_1 - 7) == (char) 0xff && (*(unsigned char*) (param_1 - 6) & 0xf8) == 0x90) {
		return 2;
	}
	return 0;
}

// STATUS: MATCHING
// ORIGIN: GAME
// BLOCKER: comparison direction swap, zero-extend pattern (xor vs mov)
// BLOCKER_DELTA: 83
// GHIDRA: DecodePotentialControlTransfer
// BLOCKER: instruction folding (lea vs mov)
// SIZE: 404
// SYMBOL: _InitializeLogAndErrorHandler
// FUNCTION: SERVER 0x10003320
// InitializeLogAndErrorHandler

/* Auto-generated Ghidra decompilation */
// BLOCKER_DELTA: 386
// ANALYSIS: Initialization routine for the server's telemetry. Registers the CrashDumpUnhandledExceptionFilter. Allocates a console if requested via flags. Truncates log files (__server.log, gilde_server.log) if they exceed 64KB (0x10000 bytes) and seeds them with a startup banner. | If file logging is enabled, validate/rotate server log targets.
// PROTOTYPE: void __cdecl InitializeLogAndErrorHandler(uint param_1, uint param_2, uint param_3, uint param_4)

void InitializeLogAndErrorHandler(
	unsigned int param_1,
	unsigned int param_2,
	unsigned int param_3,
	unsigned int param_4
)
{
	unsigned char* path_end;
	int file_handle;
	int file_size;
	unsigned int* log_level_ptr;
	int format_offset;
	unsigned int stack_buf_addr;
	unsigned int stack_return_addr;
	unsigned int stack_param;
	unsigned char* stack_ptr;
	unsigned char window_title[24];
	unsigned char module_path[260];

	int stack_efc;
	int stack_ddc;
	int stack_ee4;
	int stack_de0;

	*(unsigned int*) 0x10034610 = param_1;
	*(unsigned int*) 0x10034618 = param_4;
	*(unsigned int*) 0x1003461c = param_4 >> 4 & 1;
	*(unsigned int*) 0x10034614 = param_2;
	*(unsigned int*) 0x117660e0 = param_3;

	SetUnhandledExceptionFilter(0);
	stack_ptr = (unsigned char*) 0x10003375;
	time(0);
	stack_ptr = (unsigned char*) &stack_efc;
	stack_param = param_3;
	stack_return_addr = 0x10003390;
	GetWindowTextA(0, window_title, 0);
	stack_return_addr = 0x104;
	stack_buf_addr = 0x11766100;
	GetModuleFileNameA(0, module_path, 0);
	path_end = strrchr(0x11766100, 0x5c);
	*path_end = 0;
	_ctime((time_t*)&stack_ddc);
	sprintf((char*) 0x117640e0, (char*) 0x1002735c, &stack_ee4);
	if ((*(unsigned int*) 0x10034618 & 1) != 0) {
		format_offset = 0x10027084;
		do {
			sprintf((char*) &stack_de0, (char*) 0x100270fc, (char*) 0x11766100);
			file_handle = (int)fopen((char*)&stack_de0, (char*)0x100270f8);
			if (file_handle != 0) {
				fseek(file_handle, 0, 2);
				file_size = ftell((FILE*)file_handle);
				if (0x10000 < file_size) {
					fflush(file_handle);
					file_handle = (int)fopen((char*)&stack_de0, (char*)0x10027358);
					fputs(0x1002733c, file_handle);
				}
				fflush(file_handle);
			}
			format_offset = format_offset + 0x20;
		} while (format_offset < 0x100270e4);
	}
	if ((*(unsigned int*) 0x10034618 & 8) != 0) {
		AllocConsole();
		*(void**) 0x11766204 = GetStdHandle(0xfffffff5);
	}
	log_level_ptr = (unsigned int*) 0x10027078;
	do {
		DispatchLogOutput(0x117640e0, *(unsigned int*) 0x10034618, *log_level_ptr);
		log_level_ptr = log_level_ptr + 1;
	} while (log_level_ptr < (unsigned int*) 0x10027084);
	return;
}

// STATUS: RELOC
// ORIGIN: GAME
// SIZE: 83
// SYMBOL: _ShutdownLogAndErrorHandler
// FUNCTION: SERVER 0x100034c0
// ShutdownLogAndErrorHandler
// PROTOTYPE: void ShutdownLogAndErrorHandler(void)

void __cdecl ShutdownLogAndErrorHandler(void)
{
	int* p;

	p = g_severity_table;
	do {
		DispatchLogOutput("Error-Handler closed.\n", g_log_mode_flags, *p);
		p++;
	} while ((int) p < (int) (g_severity_table + 3));
	if (g_log_mode_flags & 8) {
		FreeConsole();
		g_console_handle = 0;
	}
	g_panic_callback = 0;
	g_owner_window = 0;
	g_log_mode_flags = 0;
}

// STATUS: RELOC
// ORIGIN: GAME
// SIZE: 160
// NOTE: Ghidra reports 160B but last 5 bytes are NOP alignment padding after noreturn _exit()
// SYMBOL: _ReportFatalError
// ANALYSIS: Ghidra reports 160B but last 5 bytes are NOP alignment padding after noreturn _exit()
// FUNCTION: SERVER 0x10003520
// ReportFatalError
// PROTOTYPE: void __cdecl ReportFatalError(char * modulePath, uint lineNumber, char * message)
__declspec(noreturn) void __cdecl _exit(int);

void __cdecl ReportFatalError(char* modulePath, unsigned int lineNumber, char* message)
{
	unsigned int flags;
	int dialogResult;

	if (g_panic_callback == 0) {
		MessageBoxA((HWND) 0, "ERROR Handler has not been started!", "Error!", 0x30);
		return;
	}
	flags = g_log_mode_flags;
	if (flags == 0) {
		return;
	}
	if ((flags & 0xf) != 0) {
		sprintf(&g_log_message_buffer, "FATAL ERROR (%s:%lu):\n%s\n", modulePath, lineNumber, message);
		flags = g_log_mode_flags;
	}
	if ((flags & 0xd) != 0) {
		DispatchLogOutput(&g_log_message_buffer, flags, 1);
		flags = g_log_mode_flags;
	}
	if ((flags & 2) == 0) {
		return;
	}
	dialogResult = MessageBoxA(g_owner_window, &g_log_message_buffer, "Fatal Error! Abort Program?", 0x124);
	if (dialogResult != 6) {
		return;
	}
	g_panic_callback();
	_exit(0xf);
}

// STATUS: RELOC
// ORIGIN: GAME
// SIZE: 119
// SYMBOL: _ReportMessage
// FUNCTION: SERVER 0x100035C0
// ReportMessage
// PROTOTYPE: void __cdecl ReportMessage(char * msg)

void __cdecl ReportMessage(char* msg)
{
	if (!g_handler_started) {
		MessageBoxA(0, "ERROR-Handler has not been started...", "Error!", 0x10030);
		return;
	}
	if (!g_handler_flags) {
		return;
	}
	if (g_handler_flags & 0x0d) {
		sprintf(g_msg_buf, "MESSAGE: %s\n", msg);
		write_log(g_msg_buf, g_handler_flags, (char*) 1);
	}
	if (g_handler_flags & 2) {
		MessageBoxA(0, msg, "Message:", 0x1030);
	}
}

// STATUS: RELOC
// ORIGIN: GAME
// SIZE: 132
// SYMBOL: _LogMessageInternal
// FUNCTION: SERVER 0x10003640
// LogMessageInternal
// PROTOTYPE: void __cdecl LogMessageInternal(char * module, uint line, char * msg, int severity)

void __cdecl LogMessageInternal(char* module, unsigned int line, char* msg, int severity)
{
	unsigned char flags;

	if (g_panic_callback == 0) {
		MessageBoxA((HWND) 0, "ERROR Handler has not been started!", "Error!", 0x10030);
		return;
	}
	flags = (unsigned char) g_log_mode_flags;
	if ((flags & 1) != 0) {
		if ((flags & 0x20) != 0) {
			sprintf(&g_log_message_buffer, "Time:%8lu\tModule '%s':\tLine:%lu:\t%s", timeGetTime(), module, line, msg);
		}
		else {
			sprintf(&g_log_message_buffer, "tModule '%s':\tLine:%lu:\t%s", module, line, msg);
		}
		DispatchLogOutput(&g_log_message_buffer, g_log_mode_flags, severity);
	}
}
