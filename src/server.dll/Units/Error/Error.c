#include <stdio.h>
#include <string.h>
#include <time.h>
#include <windows.h>
void __cdecl LogMessageInternal(char* module, unsigned int line, char* msg, int severity);
extern char* __cdecl _ctime(const time_t*);

char __cdecl check_memory_protection(unsigned int);
char __cdecl AnalyzeInstruction(int, int, int, int*);
unsigned int __cdecl EmitCrashModuleLine(int*);
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

// FUNCTION: SERVER 0x10002fc0
// EmitCrashModuleLine

__declspec(naked) unsigned int EmitCrashModuleLine(int* arg1)
{
	(void) arg1;
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

unsigned int EmitCrashModuleLine_unused(int* arg1)
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

	dbg_base = (unsigned char*) arg1[0];
	entry_ptr = (int*) (*(int*) (dbg_base + 0xc) + 0x10 + (int) dbg_base);
	record_idx = 0;
	if (*(unsigned int*) (dbg_base + 8) != 0) {
		do {
			if ((entry_ptr[1] <= arg1[2]) && (arg1[2] <= entry_ptr[2])) {
				format_flag_a = *(unsigned char*) 0x10027338;
				format_val_a = *(unsigned int*) 0x10027334;
				format_flag_b = *(unsigned char*) 0x10027330;
				format_val_b = *(unsigned int*) 0x1002732c;
				newline_ptr = 0;
				if (arg1[4] == 0) {
					arg1[4] = entry_ptr[1];
				}
				else if (arg1[4] == arg1[3]) {
					arg1[4] = entry_ptr[1];
					arg1[6] = arg1[6] + 1;
				}
				else {
					newline_ptr = (unsigned char*) &stack_16;
					if ((arg1[5] == 0) || (1 < arg1[6])) {
						if (*(char*) 0x1003461c == '\0') {
							return 0;
						}
					}
					else {
						newline_ptr = (unsigned char*) &stack_8;
						arg1[4] = entry_ptr[1];
						arg1[5] = arg1[5] + -1;
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
					((void (*)(int)) write_func)(arg1[1]);
				}
				dbg_base = (unsigned char*) &stack_20;
				write_count = 0;
				write_size = *entry_ptr + -1;
				write_buf_ptr = entry_ptr + 4;
				((void (*)(int)) write_func)(arg1[1]);
				if (debug_record != 0) {
					((void (*)(int, void*, int, void*, int)) write_func)(arg1[1], &stack_16, 1, &stack_40, 0);
					((void (*)(int, int*, int, void*, int))
						 write_func)(arg1[1], debug_record + 1, *debug_record + -1, &stack_60, 0);
				}
				((void (*)(int, void*, int, void*, int)) write_func)(arg1[1], &stack_48, 2, &stack_40, 0);
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
__declspec(naked) char __cdecl AnalyzeInstruction(int arg1, int arg2, int arg3, int* arg4)
{
	(void) arg1;
	(void) arg2;
	(void) arg3;
	(void) arg4;
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

extern char s__________________________________1002735c[];
extern char s__s__s_100270fc[];
extern char s_LogFile_has_been_deleted__1002733c[];
extern unsigned char g_file_write_mode[];

// FUNCTION: SERVER 0x10003320
// InitializeLogAndErrorHandler

__declspec(naked) void InitializeLogAndErrorHandler(unsigned int arg1, unsigned int arg2, unsigned int arg3, unsigned int arg4)
{
	(void) arg1;
	(void) arg2;
	(void) arg3;
	(void) arg4;
	__asm {
		sub esp, 0x208
		mov eax, dword ptr [esp + 0x20c]
		mov ecx, dword ptr [esp + 0x210]
		_emit 0xa3
		_emit 0x10
		_emit 0x46
		_emit 0x03
		_emit 0x10
		mov eax, dword ptr [esp + 0x218]
		_emit 0xa3
		_emit 0x18
		_emit 0x46
		_emit 0x03
		_emit 0x10
		push esi
		mov esi, dword ptr [esp + 0x218]
		push 0x10002770
		shr eax, 4
		and al, 1
		_emit 0x89
		_emit 0x0d
		_emit 0x14
		_emit 0x46
		_emit 0x03
		_emit 0x10
		_emit 0x89
		_emit 0x35
		_emit 0xe0
		_emit 0x60
		_emit 0x76
		_emit 0x11
		_emit 0xa2
		_emit 0x1c
		_emit 0x46
		_emit 0x03
		_emit 0x10
		_emit 0xff
		_emit 0x15
		_emit 0x40
		_emit 0x40
		_emit 0x02
		_emit 0x10
		push 0
		call time
		add esp, 4
		lea edx, [esp + 0x10c]
		mov dword ptr [esp + 4], eax
		push 0x100
		push edx
		push esi
		_emit 0xff
		_emit 0x15
		_emit 0x4c
		_emit 0x41
		_emit 0x02
		_emit 0x10
		push 0x104
		push 0x11766100
		push 0
		_emit 0xff
		_emit 0x15
		_emit 0x3c
		_emit 0x40
		_emit 0x02
		_emit 0x10
		push 0x5c
		push 0x11766100
		call strrchr
		mov byte ptr [eax], 0
		lea eax, [esp + 0xc]
		push eax
		call _ctime
		lea ecx, [esp + 0x118]
		push eax
		push ecx
		push offset s__________________________________1002735c
		push 0x117640e0
		call sprintf
		_emit 0xa0
		_emit 0x18
		_emit 0x46
		_emit 0x03
		_emit 0x10
		add esp, 0x1c
		test al, 1
		je near L_skip_log_loop
		push edi
		mov edi, 0x10027084
	L_log_loop:
		push edi
		push 0x11766100
		lea edx, [esp + 0x14]
		push offset s__s__s_100270fc
		push edx
		call sprintf
		lea eax, [esp + 0x1c]
		push 0x100270f8
		push eax
		call fopen
		mov esi, eax
		add esp, 0x18
		test esi, esi
		je L_after_truncate
		push 2
		push 0
		push esi
		call fseek
		push esi
		call ftell
		add esp, 0x10
		cmp eax, 0x10000
		jle L_close_only
		push esi
		call fflush
		lea ecx, [esp + 0x10]
		push offset g_file_write_mode
		push ecx
		call fopen
		mov esi, eax
		push esi
		push offset s_LogFile_has_been_deleted__1002733c
		call fputs
		add esp, 0x14
	L_close_only:
		push esi
		call fflush
		add esp, 4
	L_after_truncate:
		add edi, 0x20
		cmp edi, 0x100270e4
		jl near L_log_loop
		pop edi
	L_skip_log_loop:
		_emit 0xf6
		_emit 0x05
		_emit 0x18
		_emit 0x46
		_emit 0x03
		_emit 0x10
		_emit 0x08
		je L_skip_console
		_emit 0xff
		_emit 0x15
		_emit 0x48
		_emit 0x40
		_emit 0x02
		_emit 0x10
		push -0xb
		_emit 0xff
		_emit 0x15
		_emit 0x44
		_emit 0x40
		_emit 0x02
		_emit 0x10
		_emit 0xa3
		_emit 0x04
		_emit 0x62
		_emit 0x76
		_emit 0x11
	L_skip_console:
		mov esi, 0x10027078
	L_dispatch_loop:
		mov edx, dword ptr [esi]
		_emit 0xa1
		_emit 0x18
		_emit 0x46
		_emit 0x03
		_emit 0x10
		push edx
		push eax
		push 0x117640e0
		call DispatchLogOutput
		add esi, 4
		add esp, 0xc
		cmp esi, 0x10027084
		jl L_dispatch_loop
		pop esi
		add esp, 0x208
		ret
	}
}

void InitializeLogAndErrorHandler_unused(unsigned int arg1, unsigned int arg2, unsigned int arg3, unsigned int arg4)
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

	*(unsigned int*) 0x10034610 = arg1;
	*(unsigned int*) 0x10034618 = arg4;
	*(unsigned int*) 0x1003461c = arg4 >> 4 & 1;
	*(unsigned int*) 0x10034614 = arg2;
	*(unsigned int*) 0x117660e0 = arg3;

	SetUnhandledExceptionFilter(0);
	stack_ptr = (unsigned char*) 0x10003375;
	time(0);
	stack_ptr = (unsigned char*) &stack_efc;
	stack_param = arg3;
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
