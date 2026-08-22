#include <stdio.h>
#include <string.h>
#include <time.h>
#include <windows.h>
void __cdecl LogMessageInternal(char* module, unsigned int line, char* msg, int severity);
extern char* __cdecl ctime(const time_t*);

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

char s__________________________________1002735c[] = "* ------------------------------------------------------------ *\n[%s], Date: %s";
char s__s__s_100270fc[] = "%s\\%s";
char s_LogFile_has_been_deleted__1002733c[] = "LogFile has been deleted!\n";
unsigned char g_file_write_mode[3] = {
    0x77, 0x74, 0x00,
};

