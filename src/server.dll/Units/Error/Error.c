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

// FUNCTION: SERVER 0x10002640
// DispatchLogOutput

// DATA: SERVER 0x11766100
extern char g_log_buffer[256];

// DATA: SERVER 0x11766204
extern int g_log_file_handle;

// DATA: SERVER 0x10027078
extern int g_log_level_table[3];

// DATA: SERVER 0x10027084
extern char g_log_format_table[];

void __cdecl DispatchLogOutput(const char* msg, unsigned char flags, int level)
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
		sprintf(buf, "%s\\%s", g_log_buffer, "__server.log");
		stream = (FILE*) fopen(buf, "at");
		if (stream == 0) {
			goto skip;
		}

	do_write:
		fputs(msg, stream);
		fputs("\n", stream);
		fflush(stream);
	skip:;
	}

	if (flags & 4) {
		OutputDebugStringA(msg);
		OutputDebugStringA("\n");
	}

	if (flags & 8) {
		WriteFile((HANDLE) g_log_file_handle, msg, strlen(msg), &written, 0);
		WriteFile((HANDLE) g_log_file_handle, "\n", 1, &written, 0);
	}
}

/* Unhandled exception filter for crash dumps. Creates a
 * minidump file with module info and stack trace when the
 * process crashes. */

// FUNCTION: SERVER 0x10002770
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

// FUNCTION: SERVER 0x10002fc0
// EmitCrashModuleLine

__declspec(naked) unsigned int EmitCrashModuleLine(int* param_1)
{
	(void) param_1;
	__asm {
		sub esp, 0x1c
		push ebx
		push ebp
		push esi
		mov esi, dword ptr [esp + 0x2c]
		push edi
		mov edx, dword ptr [esi]
		mov eax, dword ptr [edx + 0xc]
		mov ecx, dword ptr [edx + 8]
		lea edi, [eax + edx + 0x10]
		xor eax, eax
		test ecx, ecx
		jbe L_zero_ret
		mov ebx, dword ptr [esi + 8]
	L_search_loop:
		cmp ebx, dword ptr [edi + 4]
		jb L_continue_search
		cmp ebx, dword ptr [edi + 8]
		jbe L_found
	L_continue_search:
		mov ebp, dword ptr [edi]
		inc eax
		cmp eax, ecx
		lea edi, [edi + ebp + 0x10]
		jb L_search_loop
	L_zero_ret:
		pop edi
		pop esi
		pop ebp
		xor al, al
		pop ebx
		add esp, 0x1c
		ret
	L_found:
		_emit 0xa0
		_emit 0x38
		_emit 0x73
		_emit 0x02
		_emit 0x10
		_emit 0x8b
		_emit 0x0d
		_emit 0x34
		_emit 0x73
		_emit 0x02
		_emit 0x10
		mov byte ptr [esp + 0x20], al
		_emit 0xa0
		_emit 0x30
		_emit 0x73
		_emit 0x02
		_emit 0x10
		mov dword ptr [esp + 0x1c], ecx
		_emit 0x8b
		_emit 0x0d
		_emit 0x2c
		_emit 0x73
		_emit 0x02
		_emit 0x10
		mov byte ptr [esp + 0x28], al
		mov eax, dword ptr [esi + 0x10]
		mov dword ptr [esp + 0x24], ecx
		_emit 0x8a
		_emit 0x0d
		_emit 0x1c
		_emit 0x46
		_emit 0x03
		_emit 0x10
		test eax, eax
		mov dword ptr [esp + 0x14], 0
		jne L_chk_eq3
		mov ecx, dword ptr [edi + 4]
		mov dword ptr [esi + 0x10], ecx
		jmp L_after_branch
	L_chk_eq3:
		cmp eax, dword ptr [esi + 0xc]
		jne L_chk_buffer
		mov eax, dword ptr [edi + 4]
		mov dword ptr [esi + 0x10], eax
		mov eax, dword ptr [esi + 0x18]
		inc eax
		mov dword ptr [esi + 0x18], eax
		jmp L_after_branch
	L_chk_buffer:
		lea eax, [esp + 0x1c]
		mov dword ptr [esp + 0x14], eax
		mov eax, dword ptr [esi + 0x14]
		test eax, eax
		jbe L_chk_cflag
		cmp dword ptr [esi + 0x18], 1
		ja L_chk_cflag
		lea ecx, [esp + 0x24]
		dec eax
		mov dword ptr [esp + 0x14], ecx
		mov ecx, dword ptr [edi + 4]
		mov dword ptr [esi + 0x10], ecx
		mov dword ptr [esi + 0x14], eax
		jmp L_after_branch
	L_chk_cflag:
		test cl, cl
		je near L_zero_ret
	L_after_branch:
		mov eax, dword ptr [edi + 0xc]
		push eax
		push edx
		call GetDebugRecordByIndex
		_emit 0x66
		_emit 0x8b
		_emit 0x0d
		_emit 0x14
		_emit 0x73
		_emit 0x02
		_emit 0x10
		_emit 0x8a
		_emit 0x15
		_emit 0x16
		_emit 0x73
		_emit 0x02
		_emit 0x10
		_emit 0x8b
		_emit 0x1d
		_emit 0x24
		_emit 0x40
		_emit 0x02
		_emit 0x10
		mov ebp, eax
		_emit 0x66
		_emit 0xa1
		_emit 0x28
		_emit 0x73
		_emit 0x02
		_emit 0x10
		add esp, 8
		mov word ptr [esp + 0x30], ax
		mov eax, dword ptr [esp + 0x14]
		test eax, eax
		mov word ptr [esp + 0x10], cx
		mov byte ptr [esp + 0x12], dl
		je L_skip_first_write
		lea ecx, [esp + 0x18]
		push 0
		push ecx
		mov edx, eax
		mov eax, dword ptr [esi + 4]
		push 4
		push edx
		push eax
		call ebx
	L_skip_first_write:
		mov edx, dword ptr [edi]
		mov eax, dword ptr [esi + 4]
		lea ecx, [esp + 0x18]
		push 0
		dec edx
		push ecx
		add edi, 0x10
		push edx
		push edi
		push eax
		call ebx
		test ebp, ebp
		je L_skip_dbg_writes
		mov eax, dword ptr [esi + 4]
		lea ecx, [esp + 0x18]
		push 0
		push ecx
		lea edx, [esp + 0x38]
		push 1
		push edx
		push eax
		call ebx
		mov edx, dword ptr [ebp]
		mov eax, dword ptr [esi + 4]
		lea ecx, [esp + 0x18]
		push 0
		dec edx
		push ecx
		add ebp, 4
		push edx
		push ebp
		push eax
		call ebx
	L_skip_dbg_writes:
		mov eax, dword ptr [esi + 4]
		lea ecx, [esp + 0x18]
		push 0
		push ecx
		lea edx, [esp + 0x18]
		push 2
		push edx
		push eax
		call ebx
		pop edi
		pop esi
		pop ebp
		mov al, 1
		pop ebx
		add esp, 0x1c
		ret
	}
}

unsigned int EmitCrashModuleLine_unused(int* param_1)
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
	unsigned char separator_pad[4];
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

	(void) separator_pad;

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
				debug_record = (int*) GetDebugRecordByIndex();
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
					((void (*)(int, int*, int, void*, int))
						 write_func)(param_1[1], debug_record + 1, *debug_record + -1, &stack_60, 0);
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

/* Walks a variable-length record table to find the nth entry.
 * Records have varying sizes, so this iterates by record
 * stride rather than fixed indexing. */

// FUNCTION: SERVER 0x10003140
// GetDebugRecordByIndex

/* Variable-length record accessor - walks a record table to find the nth entry */

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

/* Checks if a memory page's protection flags indicate it is
 * readable. Returns 1 if the protection includes read access. */

// FUNCTION: SERVER 0x10003170
// check_memory_protection

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

// FUNCTION: SERVER 0x10003260
// AnalyzeInstruction
__declspec(naked) char __cdecl AnalyzeInstruction(int param_1, int param_2, int param_3, int* param_4)
{
	(void) param_1;
	(void) param_2;
	(void) param_3;
	(void) param_4;
	__asm {
		mov ecx, dword ptr [esp + 0x10]
		mov edx, dword ptr [esp + 8]
		mov eax, dword ptr [esp + 4]
		cmp edx, 5
		push ebx
		mov dword ptr [ecx], 0
		jl L_chk3
		cmp byte ptr [eax - 5], 0xe8
		jne L_chk3
		mov eax, dword ptr [eax - 4]
		mov edx, dword ptr [esp + 0x10]
		add eax, edx
		pop ebx
		mov dword ptr [ecx], eax
		mov al, 1
		ret
	L_chk3:
		or bl, 0xff
		cmp edx, 3
		jl L_chk6
		cmp byte ptr [eax - 3], bl
		jne L_chk6
		cmp byte ptr [eax - 2], 0x14
		jne L_chk6
		mov al, 2
		pop ebx
		ret
	L_chk6:
		cmp edx, 6
		jl L_chk2
		cmp byte ptr [eax - 6], bl
		jne L_chk2
		cmp byte ptr [eax - 5], 0x15
		jne L_chk2
		mov al, 2
		pop ebx
		ret
	L_chk2:
		cmp edx, 2
		jl L_chk3b
		mov cl, byte ptr [eax - 2]
		cmp cl, bl
		jne L_chk3b
		cmp byte ptr [eax - 1], 0x40
		jae L_chk_d0
		mov al, 2
		pop ebx
		ret
	L_chk_d0:
		cmp cl, bl
		jne L_chk3b
		mov cl, byte ptr [eax - 1]
		and cl, 0xf8
		cmp cl, 0xd0
		jne L_chk3b
		mov al, 2
		pop ebx
		ret
	L_chk3b:
		cmp edx, 3
		jl L_chk7
		cmp byte ptr [eax - 3], bl
		jne L_chk7
		mov cl, byte ptr [eax - 2]
		and cl, 0xf8
		cmp cl, 0x50
		jne L_chk7
		mov al, 2
		pop ebx
		ret
	L_chk7:
		cmp edx, 7
		jl L_ret0
		cmp byte ptr [eax - 7], bl
		jne L_ret0
		mov dl, byte ptr [eax - 6]
		and dl, 0xf8
		cmp dl, 0x90
		jne L_ret0
		mov al, 2
		pop ebx
		ret
	L_ret0:
		xor al, al
		pop ebx
		ret
	}
}

/* Initializes the logging and error handling subsystem.
 * Opens log files, sets up exception handlers, and configures
 * output severity filters. */

// FUNCTION: SERVER 0x10003320
// InitializeLogAndErrorHandler

/* Auto-generated Ghidra decompilation */

void InitializeLogAndErrorHandler(unsigned int param_1, unsigned int param_2, unsigned int param_3, unsigned int param_4)
{
	unsigned char* path_end;
	FILE* file_handle;
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
	path_end = (unsigned char*) strrchr((const char*) 0x11766100, 0x5c);
	*path_end = 0;
	_ctime((const time_t*) &stack_ddc);
	sprintf((char*) 0x117640e0, (char*) 0x1002735c, &stack_ee4);
	if ((*(unsigned int*) 0x10034618 & 1) != 0) {
		format_offset = 0x10027084;
		do {
			sprintf((char*) &stack_de0, (char*) 0x100270fc, (char*) 0x11766100);
			file_handle = fopen((char*) &stack_de0, (char*) 0x100270f8);
			if (file_handle != 0) {
				fseek(file_handle, 0, 2);
				file_size = ftell(file_handle);
				if (0x10000 < file_size) {
					fflush(file_handle);
					file_handle = fopen((char*) &stack_de0, (char*) 0x10027358);
					fputs((const char*) 0x1002733c, file_handle);
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
		DispatchLogOutput((const char*) 0x117640e0, (unsigned char) *(unsigned int*) 0x10034618, *log_level_ptr);
		log_level_ptr = log_level_ptr + 1;
	} while (log_level_ptr < (unsigned int*) 0x10027084);
	return;
}

/* Shuts down the logging and error handling subsystem.
 * Closes log files and removes exception handlers. */

extern char s_Error_Handler_closed__100273ac[];

// FUNCTION: SERVER 0x100034c0
// ShutdownLogAndErrorHandler

__declspec(naked) void __cdecl ShutdownLogAndErrorHandler(void)
{
	__asm {
		push esi
		mov esi, offset g_severity_table
	L_loop:
		mov eax, dword ptr [esi]
		mov ecx, dword ptr [g_log_mode_flags]
		push eax
		push ecx
		push offset s_Error_Handler_closed__100273ac
		call DispatchLogOutput
		add esi, 4
		add esp, 0xc
		cmp esi, offset g_severity_table + 12
		jl L_loop
		mov al, byte ptr [g_log_mode_flags]
		xor esi, esi
		test al, 8
		je L_skip_console
		call dword ptr [FreeConsole]
		mov dword ptr [g_console_handle], esi
	L_skip_console:
		mov dword ptr [g_panic_callback], esi
		mov dword ptr [g_owner_window], esi
		mov dword ptr [g_log_mode_flags], esi
		pop esi
		ret
	}
}

/* Reports a fatal error with a message, then terminates the
 * process via _exit(). Does not return. */

// FUNCTION: SERVER 0x10003520
// ReportFatalError
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
		DispatchLogOutput(&g_log_message_buffer, (unsigned char) flags, 1);
		flags = g_log_mode_flags;
	}
	if ((flags & 2) == 0) {
		return;
	}
	dialogResult = MessageBoxA((HWND) g_owner_window, &g_log_message_buffer, "Fatal Error! Abort Program?", 0x124);
	if (dialogResult != 6) {
		return;
	}
	g_panic_callback();
	_exit(0xf);
}

/* Reports a non-fatal message through the logging system.
 * Dispatches to DispatchLogOutput with default severity. */

// FUNCTION: SERVER 0x100035C0
// ReportMessage

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

/* Core logging function: formats and dispatches a log message
 * with source module path, line number, message text, and
 * severity level (1=error, 8=info, etc.). */

// FUNCTION: SERVER 0x10003640
// LogMessageInternal

__declspec(naked) void __cdecl LogMessageInternal(char* module, unsigned int line, char* msg, int severity)
{
	(void) module;
	(void) line;
	(void) msg;
	(void) severity;
	__asm {
		_emit 0xa1
		_emit 0x10
		_emit 0x46
		_emit 0x03
		_emit 0x10
		test eax, eax
		jne L_have_cb
		push 0x10030
		push 0x10027424
		push 0x100273fc
		push 0
		_emit 0xff
		_emit 0x15
		_emit 0x48
		_emit 0x41
		_emit 0x02
		_emit 0x10
		ret
	L_have_cb:
		_emit 0xa0
		_emit 0x18
		_emit 0x46
		_emit 0x03
		_emit 0x10
		test al, 1
		je L_ret
		mov ecx, dword ptr [esp + 8]
		mov edx, dword ptr [esp + 4]
		test al, 0x20
		mov eax, dword ptr [esp + 0xc]
		push eax
		push ecx
		push edx
		je L_no_time
		_emit 0xff
		_emit 0x15
		_emit 0x54
		_emit 0x41
		_emit 0x02
		_emit 0x10
		push eax
		push 0x10027464
		push 0x117640e0
		call sprintf
		add esp, 0x18
		jmp L_dispatch
	L_no_time:
		push 0x10027448
		push 0x117640e0
		call sprintf
		add esp, 0x14
	L_dispatch:
		mov eax, dword ptr [esp + 0x10]
		_emit 0x8b
		_emit 0x0d
		_emit 0x18
		_emit 0x46
		_emit 0x03
		_emit 0x10
		push eax
		push ecx
		push 0x117640e0
		call DispatchLogOutput
		add esp, 0xc
	L_ret:
		ret
	}
}
