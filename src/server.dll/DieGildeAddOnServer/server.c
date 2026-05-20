#include "../Units/Error/error.h"
#include "../Units/m_alloc/m_alloc.h"

#include <stdio.h>
#include <string.h>
#include <windows.h>
#include <winsock2.h>
unsigned int __stdcall timeGetTime(void);

/* Command layer (local externs — server.c uses different signatures) */
int __cdecl cm_QueuePlayerCommand(unsigned int* player, unsigned char* data);
int __cdecl cm_ClosePlayerConnection(unsigned int* player_slot);
int __cdecl cm_ProcessCommandQueue(void);
int __cdecl lb_ExLobbyServerCommand(unsigned int*, int);

/* Entity lifecycle (local externs) */
void __cdecl gm_ResetAllEntities(void);
void __cdecl gm_CleanupAllEntities(void);
void __cdecl gm_CleanupObjectEntities(void);
void __cdecl gm_InitEntitySlots(void);
/* Network functions (local externs — signatures differ from net.h) */
int __cdecl AcceptConnections(void);
void __cdecl CleanupSockets(void);
int __cdecl ProcessReceiveData(void);
int __cdecl ProcessSendData(void);
int __cdecl ReceivePacketHeader(unsigned int* param_1);
int __cdecl SendBroadcastPacket(unsigned char* data, int size);
void __cdecl LogWinsockError(int param_1);

typedef int(__cdecl* handler_func)(unsigned char* pkt, int param);

extern DWORD WINAPI thread_proc(LPVOID);
extern int g_stop_flag;
void __cdecl InitBuildingTypeTable(void);
void __cdecl RecvGameSavegame(void);
int __cdecl srv_Init(void);
int __cdecl AdvanceGameClock(int* clock_state, int a2, int a3, int a4);
void __cdecl sim_SetSyncParams(int base_addr, unsigned char phase, unsigned int arg3, unsigned int arg4);
void __cdecl _seterrormode(int value);
void __cdecl ShutdownMemoryAllocator();
int __cdecl gm_Open(char*, char*);
int __cdecl sub_1001a299(char*, char*);
int __cdecl CreateListenSocket(int port);
void __cdecl InitPacketPool(int);
extern int g_net_socket;
int __cdecl QueueCommandForProcessing(unsigned int* conn, unsigned char* pkt); /* 0x1000a8f0 */
;
;
int __cdecl SendPlayerData(unsigned int*);
void __cdecl FreeCommandBuffer(unsigned int*, int);
extern unsigned int g_player_slots;
short __cdecl get_command_type(char*);
int __cdecl ahm_ProcessEntityChain(unsigned char* node);
extern handler_func g_dispatch_table[]; /* 0x1002c3f8 */
;
extern unsigned char g_connections[]; /* 0x101deb00 */
;

;
;
;
;
;
;

/* Console control handler for graceful shutdown.
 * Handles Ctrl+C and close events. Always returns 0. */

// FUNCTION: SERVER 0x10009310
// exit_handler
int __stdcall exit_handler(int a, int b, int c)
{
	return 1;
}

/* Server initialization: creates the main server thread
 * and stores its handle in g_thread_handle. */

// FUNCTION: SERVER 0x10009320
// Init

HANDLE g_thread_handle;

int __cdecl Init(LPVOID param)
{
	g_thread_handle = CreateThread(NULL, 0, thread_proc, param, 0, (LPDWORD) &param);
	return g_thread_handle != 0;
}

/* Server shutdown: signals the main thread to stop,
 * waits for it to complete, and closes the handle. */

// FUNCTION: SERVER 0x10009350
// Exit

void __cdecl Exit(void)
{
	if (!g_thread_handle) {
		return;
	}
	g_stop_flag = 1;
	do {
		Sleep(10);
	} while (g_stop_flag);
	WaitForSingleObject(g_thread_handle, 0);
	CloseHandle(g_thread_handle);
}

/* Main server thread entry point. Runs the game loop:
 * initializes systems, accepts connections, processes
 * commands, advances simulation, and handles I/O. */

// STUB: SERVER 0x100093a0
// ServerMainThread

int __cdecl ServerMainThread(void* lpThreadParameter)
{
	char* module_path;
	char* ini_tail;
	char* log_message;
	unsigned int* player_slot;
	unsigned int* transfer_progress;
	unsigned int* src_words;
	unsigned int* cfg_ptr;
	unsigned int* payload_src;
	unsigned int* payload_dst;
	unsigned int connected_players;
	unsigned int now_tick;
	unsigned int current_tick;
	unsigned int last_announce_tick;
	unsigned int sync_timer;
	unsigned int game_speed;
	unsigned int result;
	unsigned int line;
	int i;
	int phase_complete;
	unsigned char cmd_buffer_primary[0x99];
	unsigned char cmd_buffer_secondary[0x99];
	unsigned int startup_cfg_words[27];
	char log_buffer[64];

	module_path = (char*) 0x101de9a0;
	GetModuleFileNameA(0, module_path, 0x104);
	ini_tail = strrchr(module_path, 0x5c);
	*(unsigned int*) (ini_tail + 0) = *(unsigned int*) 0x1002993c;
	*(unsigned int*) (ini_tail + 4) = *(unsigned int*) 0x10029940;
	*(unsigned short*) (ini_tail + 8) = *(unsigned short*) 0x10029944;

	*(int*) 0x11764088 = (int) GetPrivateProfileIntA((char*) 0x1002992c, (char*) 0x10029934, 0x1d6b, module_path);
	*(int*) 0x11764084 = 2;
	GetPrivateProfileStringA(
		(char*) 0x100298f8,
		(char*) 0x10029900,
		(char*) 0x1002990c,
		(char*) 0x10029594,
		0x104,
		module_path
	);

	src_words = (unsigned int*) lpThreadParameter;
	cfg_ptr = startup_cfg_words;
	for (i = 0; i < 0x1a; i++) {
		*cfg_ptr = *src_words;
		src_words = src_words + 1;
		cfg_ptr = cfg_ptr + 1;
	}
	*(unsigned short*) cfg_ptr = (unsigned short) (*src_words);

	if (*(unsigned short*) ((char*) startup_cfg_words + 2) == 1) {
		*((unsigned char*) startup_cfg_words + 0x27) = 0;
		*(unsigned int*) 0x11764084 = *(unsigned int*) ((char*) startup_cfg_words + 0x26) & 0xff;
	}
	else if (*(unsigned short*) ((char*) startup_cfg_words + 2) == 4) {
		*((unsigned char*) startup_cfg_words + 0x27) = 0;
		*(unsigned int*) 0x11764084 = *(unsigned int*) ((char*) startup_cfg_words + 0x26) & 0xff;
	}

	srv_Init();
	sprintf(log_buffer, (char*) 0x100298d8, *(int*) 0x11764084);
	LogMessageInternal((char*) 0x100298b0, 0x131, log_buffer, 1);
	_seterrormode(timeGetTime());

	last_announce_tick = 0;
	phase_complete = 0;
	for (;;) {
		if (*(int*) 0x10034680 != 0) {
			break;
		}

		connected_players = 0;
		player_slot = (unsigned int*) 0x101deb00;
		do {
			if (*player_slot != 0) {
				connected_players = connected_players + 1;
			}
			player_slot = (unsigned int*) ((char*) player_slot + 0x264264);
		} while ((char*) player_slot < (char*) 0x114ffe20);

		AcceptConnections();

		if (connected_players == *(unsigned int*) 0x11764084) {
			phase_complete = 1;
			for (player_slot = (unsigned int*) 0x101deb00; (char*) player_slot < (char*) 0x114ffe20;
				player_slot = (unsigned int*) ((char*) player_slot + 0x264264)) {
				if ((*player_slot != 0) && ((*player_slot & 0x800) == 0)) {
					phase_complete = 0;
					goto lobby_check_announce;
				}
			}
			LogMessageInternal((char*) 0x100298b0, 0x14e, (char*) 0x10029890, 1);
		}

	lobby_check_announce:
		now_tick = timeGetTime();
		if ((3000 < now_tick - last_announce_tick) || phase_complete) {
			*((unsigned char*) startup_cfg_words + 0x27) = (unsigned char) connected_players;
			SendBroadcastPacket((unsigned char*) 0x3039, (int) startup_cfg_words);
			last_announce_tick = timeGetTime();
		}

		result = (unsigned int) ProcessReceiveData();
		if (result == 0xffffffff) {
			log_message = (char*) 0x1002986c;
			line = 0x15f;
			goto log_error_and_cleanup;
		}

		result = (unsigned int) ProcessSendData();
		if (result == 0xffffffff) {
			log_message = (char*) 0x1002986c;
			line = 0x16a;
			goto log_error_and_cleanup;
		}

		player_slot = (unsigned int*) 0x101deb00;
		do {
			if ((*player_slot & 0x1000) != 0) {
				if ((*player_slot & 0x400) != 0) {
					log_message = (char*) 0x10029834;
					line = 0x176;
					goto log_error_and_cleanup;
				}
				cm_ClosePlayerConnection(player_slot);
			}
			player_slot = (unsigned int*) ((char*) player_slot + 0x264264);
		} while ((char*) player_slot < (char*) 0x114ffe20);

		Sleep(0x1e);
		if (phase_complete) {
			break;
		}
	}

	player_slot = (unsigned int*) 0x101deb00;
	do {
		if ((*player_slot & 1) != 0) {
			*player_slot = (*player_slot & 0xfffffdff) | 0x4004;
		}
		player_slot = (unsigned int*) ((char*) player_slot + 0x264264);
	} while ((char*) player_slot < (char*) 0x114ffe20);

	i = 0;
	player_slot = (unsigned int*) 0x101deb00;
	do {
		if ((*player_slot & 0x400) != 0) {
			*(unsigned int*) ((char*) 0x101deb00 + i * 0x264264) =
				*(unsigned int*) ((char*) 0x101deb00 + i * 0x264264) | 8;
			goto send_start_commands;
		}
		player_slot = (unsigned int*) ((char*) player_slot + 0x264264);
		i = i + 1;
	} while ((char*) player_slot < (char*) 0x114ffe20);

	CleanupSockets();

send_start_commands:
	Sleep(2000);
	i = 0;
	player_slot = (unsigned int*) 0x101deb00;
	do {
		if (*player_slot != 0) {
			cmd_buffer_primary[0] = 4;
			*(unsigned int*) (cmd_buffer_primary + 0x10) = (unsigned int) ((((*player_slot & 8) != 0) ? 0 : 1) + 1);
			if (cm_QueuePlayerCommand(player_slot, cmd_buffer_primary) == -1) {
				goto cleanup_and_exit;
			}

			cmd_buffer_primary[0] = 0x20;
			*(unsigned int*) (cmd_buffer_primary + 9) = (unsigned int) i;
			cmd_buffer_primary[0x10] = 7;
			i = i + 1;
			if (cm_QueuePlayerCommand(player_slot, cmd_buffer_primary) == -1) {
				goto cleanup_and_exit;
			}
		}
		player_slot = (unsigned int*) ((char*) player_slot + 0x264264);
	} while ((char*) player_slot < (char*) 0x114ffe20);

	LogMessageInternal((char*) 0x100298b0, 0x1ca, (char*) 0x10029824, 1);
	for (;;) {
		if (*(int*) 0x10034680 != 0) {
			break;
		}

		phase_complete = 1;
		player_slot = (unsigned int*) 0x101deb00;
		do {
			if ((*player_slot & 8) != 0) {
				phase_complete = 0;
				break;
			}
			player_slot = (unsigned int*) ((char*) player_slot + 0x264264);
		} while ((char*) player_slot < (char*) 0x114ffe20);

		result = (unsigned int) ProcessReceiveData();
		if ((result == 0xffffffff) || (ProcessSendData() == -1)) {
			log_message = (char*) 0x1002986c;
			line = 0x1df;
			goto log_error_and_cleanup;
		}

		Sleep(0x1e);
		if (phase_complete) {
			break;
		}
	}

	RecvGameSavegame();
	LogMessageInternal((char*) 0x100298b0, 0x1f9, (char*) 0x1002980c, 1);
	if ((*(unsigned char*) 0x101de464 & 4) == 0) {
		LogMessageInternal((char*) 0x100298b0, 0x1ff, (char*) 0x100297fc, 1);
		do {
			phase_complete = 1;
			player_slot = (unsigned int*) 0x101deb00;
			transfer_progress = (unsigned int*) 0x101deac8;
			do {
				if ((*player_slot & 4) != 0) {
					if (*transfer_progress == 0xffffffff) {
						cmd_buffer_primary[0] = 8;
						*(unsigned int*) (cmd_buffer_primary + 0x10) = *(unsigned int*) 0x101deac0;
						if (cm_QueuePlayerCommand(player_slot, cmd_buffer_primary) == -1) {
							goto cleanup_and_exit;
						}
						*transfer_progress = 0;
					}
					else {
						cmd_buffer_primary[0] = 9;
						payload_src = (unsigned int*) ((char*) *(void**) 0x101deae8 + *transfer_progress);
						payload_dst = (unsigned int*) (cmd_buffer_primary + 0x10);
						for (i = 0x20; i != 0; i--) {
							*payload_dst = *payload_src;
							payload_dst = payload_dst + 1;
							payload_src = payload_src + 1;
						}

						if (cm_QueuePlayerCommand(player_slot, cmd_buffer_primary) == -1) {
							LogMessageInternal((char*) 0x100298b0, 0x228, (char*) 0x100297e4, 1);
						}
						else {
							*transfer_progress = *transfer_progress + 0x80;
						}

						if (*(unsigned int*) 0x101deac0 <= *transfer_progress) {
							*player_slot = *player_slot & 0xfffffffb;
						}
					}

					phase_complete = 0;
				}

				transfer_progress = transfer_progress + 1;
				player_slot = (unsigned int*) ((char*) player_slot + 0x264264);
			} while ((char*) transfer_progress < (char*) 0x101deae8);

			result = (unsigned int) ProcessReceiveData();
			if ((result == 0xffffffff) || (ProcessSendData() == -1)) {
				log_message = (char*) 0x1002986c;
				line = 0x23a;
				goto log_error_and_cleanup;
			}

			Sleep(0x1e);
		} while (!phase_complete);
	}
	else {
		player_slot = (unsigned int*) 0x101deb00;
		do {
			if ((*player_slot & 4) != 0) {
				*player_slot = *player_slot & 0xfffffffb;
			}
			player_slot = (unsigned int*) ((char*) player_slot + 0x264264);
		} while ((char*) player_slot < (char*) 0x114ffe20);
	}

	m_FreeTracked(*(void**) 0x101deae8);
	*(void**) 0x101deae8 = (void*) 0;
	*(unsigned int*) 0x101deac0 = 0;

	if ((*(unsigned char*) 0x101de464 & 4) == 0) {
		LogMessageInternal((char*) 0x100298b0, 0x262, (char*) 0x100297bc, 1);
		player_slot = (unsigned int*) 0x101deb00;
		do {
			if ((*player_slot & 1) != 0) {
				*player_slot = *player_slot | 0x10;
			}
			player_slot = (unsigned int*) ((char*) player_slot + 0x264264);
		} while ((char*) player_slot < (char*) 0x114ffe20);

		do {
			phase_complete = 1;
			player_slot = (unsigned int*) 0x101deb00;
			do {
				if ((char*) 0x114ffe1f < (char*) player_slot) {
					break;
				}
				if ((*player_slot & 0x10) != 0) {
					phase_complete = 0;
				}
				player_slot = (unsigned int*) ((char*) player_slot + 0x264264);
			} while (phase_complete);

			result = (unsigned int) ProcessReceiveData();
			if ((result == 0xffffffff) || (ProcessSendData() == -1)) {
				log_message = (char*) 0x1002986c;
				line = 0x278;
				goto log_error_and_cleanup;
			}

			Sleep(0x1e);
		} while (!phase_complete);
	}

	player_slot = (unsigned int*) 0x101deb00;
	do {
		if ((*player_slot & 1) != 0) {
			cmd_buffer_secondary[0] = 4;
			if (cm_QueuePlayerCommand(player_slot, cmd_buffer_secondary) == -1) {
				goto cleanup_and_exit;
			}
		}
		player_slot = (unsigned int*) ((char*) player_slot + 0x264264);
	} while ((char*) player_slot < (char*) 0x114ffe20);

	LogMessageInternal((char*) 0x100298b0, 0x2a8, (char*) 0x100297b0, 1);

	for (;;) {
		if (*(int*) 0x10034680 != 0) {
			*(int*) 0x10034680 = 0;
			return 0;
		}

		Sleep(0x1e);
		current_tick = GetTickCount();
		player_slot = (unsigned int*) 0x101deb00;
		do {
			if ((*player_slot != 0) && ((*player_slot & 0x40) != 0)) {
				player_slot = (unsigned int*) 0x101deb00;
				goto check_sync_all_players;
			}
			player_slot = (unsigned int*) ((char*) player_slot + 0x264264);
		} while ((char*) player_slot < (char*) 0x114ffe20);
		goto process_pending_sync;

		while ((player_slot = (unsigned int*) ((char*) player_slot + 0x264264)),
			   (char*) player_slot < (char*) 0x114ffe20) {
		check_sync_all_players:
			if ((*player_slot != 0) && ((*player_slot & 0x40) == 0)) {
				phase_complete = 1;
				goto check_transfer_state;
			}
		}

	process_pending_sync:
		phase_complete = 0;
		player_slot = (unsigned int*) 0x101deb00;
		do {
			if ((*player_slot != 0) && ((*player_slot & 0x40) != 0)) {
				LogMessageInternal((char*) 0x100298b0, 0x2ce, (char*) 0x100297a0, 1);
				*player_slot = *player_slot & 0xffffffbf;
				if (cm_QueuePlayerCommand(player_slot, (unsigned char*) ((char*) player_slot + 0x264154)) == -1) {
					goto cleanup_and_exit;
				}
			}
			player_slot = (unsigned int*) ((char*) player_slot + 0x264264);
		} while ((char*) player_slot < (char*) 0x114ffe20);

	check_transfer_state:
		if (*(int*) 0x11764090 == 0) {
			if (phase_complete) {
				goto game_loop_network_io;
			}

			*(int*) 0x11764090 = 1;
			phase_complete = 1;
			player_slot = (unsigned int*) 0x101deb00;
			do {
				if ((*player_slot != 0) && ((*player_slot & 0x20) == 0)) {
					*(int*) 0x11764090 = 0;
					phase_complete = 0;
				}
				player_slot = (unsigned int*) ((char*) player_slot + 0x264264);
			} while ((char*) player_slot < (char*) 0x114ffe20);

			if (!phase_complete) {
				goto game_loop_network_io;
			}

			player_slot = (unsigned int*) 0x101deb00;
			do {
				if (*player_slot != 0) {
					*player_slot = *player_slot & 0xffffffdf;
				}
				player_slot = (unsigned int*) ((char*) player_slot + 0x264264);
				*(unsigned int*) 0x101deaf0 = current_tick;
			} while ((char*) player_slot < (char*) 0x114ffe20);
		}
		else if (phase_complete || (current_tick < *(unsigned int*) 0x101deaf0)) {
			goto game_loop_network_io;
		}

		AdvanceGameClock((int*) 0x10035880, 0, 1, 0);
		player_slot = (unsigned int*) 0x101deb00;
		do {
			if (*player_slot != 0) {
				cmd_buffer_primary[0] = 0x1e;
				*(unsigned int*) (cmd_buffer_primary + 0x0c) = *(unsigned int*) 0x10035884;
				*(unsigned int*) (cmd_buffer_primary + 0x10) = *(unsigned int*) 0x10035880;
				*(unsigned int*) (cmd_buffer_primary + 0x18) = *(unsigned int*) 0x10035888;
				*(unsigned short*) (cmd_buffer_primary + 0x1c) = *(unsigned short*) 0x1003588c;
				if (cm_QueuePlayerCommand(player_slot, cmd_buffer_primary) == -1) {
					goto cleanup_and_exit;
				}
			}
			player_slot = (unsigned int*) ((char*) player_slot + 0x264264);
		} while ((char*) player_slot < (char*) 0x114ffe20);

		if (*(unsigned short*) 0x10035884 > 0x16) {
			phase_complete = 1;
			player_slot = (unsigned int*) 0x101deb00;
			do {
				if (*player_slot != 0) {
					cmd_buffer_secondary[0] = 0x20;
					if (phase_complete) {
						phase_complete = 0;
					}
					if (cm_QueuePlayerCommand(player_slot, cmd_buffer_secondary) == -1) {
						goto cleanup_and_exit;
					}
					*(int*) 0x11764090 = 0;
				}
				player_slot = (unsigned int*) ((char*) player_slot + 0x264264);
			} while ((char*) player_slot < (char*) 0x114ffe20);

			*(unsigned int*) 0x10035880 = *(unsigned int*) 0x10035880 + 1;
			sim_SetSyncParams(0x10035880, 6, 0, 0);
		}

		sync_timer = *(unsigned int*) 0x101deaf0;
		game_speed = *(unsigned int*) 0x1002c3f0;
		*(unsigned int*) 0x101deaf0 = sync_timer + game_speed;

	game_loop_network_io:
		result = (unsigned int) ProcessReceiveData();
		if ((result == 0xffffffff) || (ProcessSendData() == -1)) {
			log_message = (char*) 0x1002986c;
			line = 0x348;
			goto log_error_and_cleanup;
		}

		if (cm_ProcessCommandQueue() == -1) {
			goto cleanup_and_exit;
		}
	}

log_error_and_cleanup:
	LogMessageInternal((char*) 0x100298b0, line, log_message, 1);

cleanup_and_exit:
	CleanupSockets();
	return 0;
}

/* Initializes server subsystems: memory allocator, logging,
 * network sockets, game data tables, and entity pools. */

// FUNCTION: SERVER 0x10009d30
// srv_Init

__declspec(naked) int __cdecl srv_Init(void)
{
	__asm {
		sub esp, 0x504
		push ebx
		push esi
		push edi
		_emit 0xff
		_emit 0x15
		_emit 0x6c
		_emit 0x40
		_emit 0x02
		_emit 0x10
		push 2
		push eax
		_emit 0xff
		_emit 0x15
		_emit 0x68
		_emit 0x40
		_emit 0x02
		_emit 0x10
		push 3
		push 0
		push 0
		push 0x1000a010
		call InitializeLogAndErrorHandler
		push 0x7fa6
		call InitPacketPool
		mov edi, 0x10029594
		or ecx, 0xffffffff
		xor eax, eax
		lea edx, [esp + 0x20]
		repne scasb
		not ecx
		sub edi, ecx
		mov eax, ecx
		mov esi, edi
		mov edi, edx
		lea edx, [esp + 0x20]
		shr ecx, 2
		rep movsd
		mov ecx, eax
		xor eax, eax
		and ecx, 3
		rep movsb
		mov edi, 0x10029998
		or ecx, 0xffffffff
		repne scasb
		not ecx
		sub edi, ecx
		mov esi, edi
		mov ebx, ecx
		mov edi, edx
		or ecx, 0xffffffff
		repne scasb
		mov ecx, ebx
		dec edi
		shr ecx, 2
		rep movsd
		mov ecx, ebx
		lea eax, [esp + 0x20]
		and ecx, 3
		push eax
		rep movsb
		call gm_Open
		add esp, 0x18
		test eax, eax
		pop edi
		pop esi
		pop ebx
		jge L_gm_ok
		_emit 0x8d
		_emit 0x4c
		_emit 0x24
		_emit 0x00
		lea edx, [esp + 0x104]
		push ecx
		push 0x10029974
		push edx
		call sprintf
		lea eax, [esp + 0x110]
		push 1
		push eax
		push 0x3cd
		push 0x100298b0
		call LogMessageInternal
		add esp, 0x1c
		add esp, 1284
		ret
	L_gm_ok:
		call gm_InitEntitySlots
		call InitBuildingTypeTable
		_emit 0x8b
		_emit 0x0d
		_emit 0x88
		_emit 0x40
		_emit 0x76
		_emit 0x11
		push ecx
		call CreateListenSocket
		add esp, 4
		cmp eax, -1
		_emit 0xa3
		_emit 0xec
		_emit 0xea
		_emit 0x1d
		_emit 0x10
		jne L_socket_ok
		push 1
		push 0x10029948
		push 0x3db
		push 0x100298b0
		call LogMessageInternal
		add esp, 0x10
		add esp, 1284
		ret
	L_socket_ok:
		_emit 0xc7
		_emit 0x05
		_emit 0x90
		_emit 0x40
		_emit 0x76
		_emit 0x11
		_emit 0x00
		_emit 0x00
		_emit 0x00
		_emit 0x00
		add esp, 1284
		ret
	}
}

/* Creates the TCP listen socket for accepting client
 * connections. Calls WSAStartup, socket(), bind(), listen(). */

// FUNCTION: SERVER 0x10009e60
// CreateListenSocket

/* WSAStartup = 0x10024178, WSACleanup = 0x1002417c */
/* socket = 0x10024180, setsockopt = 0x10024184, ioctlsocket = 0x1002416c */
/* htons = 0x1002418c, bind = 0x10024190, listen = 0x10024160 */
/* closesocket = 0x10024198, shutdown = 0x10024174 */

// DATA: SERVER 0x101deb14
extern unsigned int g_player_slot_field;

// SIZE 0x10 — struct sockaddr_in (Winsock system struct)
int __cdecl CreateListenSocket(int port)
{
	char wsadata[0x190];
	int optval;
	struct sockaddr_in addr;
	int sock;

	/* init player slot flags */
	{
		unsigned int* p = &g_player_slot_field;
		do {
			*(int*) ((char*) p - 0x14) = 0;
			*p = 0xFFFFFFFF;
			p = (unsigned int*) ((char*) p + 0x264264);
		} while ((int) p < 0x114ffe34);
	}

	WSAStartup(0x101, (WSADATA*) wsadata);

	sock = socket(2, 1, 6);
	if (sock == -1) {
		goto cleanup_wsa;
	}

	/* SO_REUSEADDR */
	optval = 1;
	if (setsockopt(sock, 0xFFFF, 4, (const char*) &optval, 4) == -1) {
		goto close_sock;
	}

	/* SO_LINGER */
	optval = 1;
	if (setsockopt(sock, 0xFFFF, 0xFFFFFF7F, (const char*) &optval, 4) == -1) {
		goto close_sock;
	}

	/* SO_SNDBUF */
	optval = 0x20000;
	if (setsockopt(sock, 0xFFFF, 0x1002, (const char*) &optval, 4) == -1) {
		LogMessageInternal("D:\\Develop\\DieGildeAddOn\\online", 0x424, "setsockopt sndbuf failed", 1);
		goto close_sock;
	}

	/* SO_RCVBUF */
	optval = 0x20000;
	if (setsockopt(sock, 0xFFFF, 0x1001, (const char*) &optval, 4) == -1) {
		LogMessageInternal("D:\\Develop\\DieGildeAddOn\\online", 0x42b, "setsockopt rcvbuf failed", 1);
		goto close_sock;
	}

	/* FIONBIO */
	optval = 1;
	if (ioctlsocket(sock, 0x8004667E, (unsigned int*) &optval) == -1) {
		goto close_sock;
	}

	/* bind */
	addr.sin_family = 2;
	addr.sin_addr.s_addr = 0;
	addr.sin_port = htons((unsigned short) port);
	if (bind(sock, (const struct sockaddr*) &addr, 16) == -1) {
		goto close_sock;
	}

	/* listen */
	if (listen(sock, 5) == -1) {
		goto close_sock;
	}

	return sock;

close_sock:
	shutdown(sock, 2);
	closesocket(sock);

cleanup_wsa:
	WSACleanup();
	return -1;
}

/* Cleans up all network sockets. Closes client connections,
 * the listen socket, and calls WSACleanup. */

// FUNCTION: SERVER 0x1000A010
// CleanupSockets

void __cdecl CleanupSockets(void)
{
	int p;
	p = 0x101deb14;
	while (p < 0x114ffe34) {
		if (*(int*) (p - 0x14)) {
			shutdown(*(int*) p, 2);
			closesocket(*(int*) p);
		}
		p += 0x264264;
	}
	shutdown(g_net_socket, 2);
	closesocket(g_net_socket);
	WSACleanup();
	gm_InitEntitySlots();
	gm_ResetAllEntities();
	gm_CleanupObjectEntities();
	gm_CleanupAllEntities();
	ShutdownMemoryAllocator();
	ShutdownLogAndErrorHandler();
}

/* Accepts new client connections using select() + accept().
 * Assigns connected clients to player slots and configures
 * socket options (TCP_NODELAY, timeouts). */

// FUNCTION: SERVER 0x1000a080
// AcceptConnections

/* accept = 0x1002415c, setsockopt = 0x10024184, GetTickCount = 0x1002405c */

// DATA: SERVER 0x101deaec
extern int g_listen_socket;

// DATA: SERVER 0x101deb00
extern unsigned int g_player_slot_0;

// DATA: SERVER 0x114ffe20
extern unsigned int g_player_slot_overflow;

// DATA: SERVER 0x1003467c
extern unsigned int g_connection_counter;

extern char s_No_more_Slots_for_new_Connection_100299c8[];
extern char s_D__Develop_DieGildeAddOnServer_s_100298b0[];
extern char s_New_Connection_from__li__li__li__100299a0[];
extern int __cdecl sprintf(char*, const char*, ...);

__declspec(naked) int __cdecl AcceptConnections(void)
{
	__asm {
		_emit 0xa1
		_emit 0xec
		_emit 0xea
		_emit 0x1d
		_emit 0x10
		sub esp, 0x118
		cmp eax, -1
		push ebx
		push ebp
		push esi
		jne L_have_socket
		pop esi
		pop ebp
		or eax, 0xffffffff
		pop ebx
		add esp, 0x118
		ret
	L_have_socket:
		xor ebp, ebp
		mov eax, 0x101deb00
	L_find_loop:
		cmp dword ptr [eax], 0
		je L_found_slot
		add eax, 0x264264
		inc ebp
		cmp eax, 0x114ffe20
		jge L_no_slots
		jmp L_find_loop
	L_found_slot:
		mov eax, ebp
		shl eax, 4
		add eax, ebp
		shl eax, 8
		add eax, ebp
		shl eax, 4
		add eax, ebp
		lea eax, [eax + eax*8]
		lea esi, [eax*4 + 0x101deb00]
		test esi, esi
		jne L_do_accept
	L_no_slots:
		push 1
		push offset s_No_more_Slots_for_new_Connection_100299c8
		push 0x495
		push offset s_D__Develop_DieGildeAddOnServer_s_100298b0
		call LogMessageInternal
		_emit 0xa1
		_emit 0x20
		_emit 0xfe
		_emit 0x4f
		_emit 0x11
		add esp, 0x10
		test eax, eax
		jne L_ret_neg1
		mov esi, 0x114ffe20
	L_do_accept:
		_emit 0xa1
		_emit 0xec
		_emit 0xea
		_emit 0x1d
		_emit 0x10
		lea ecx, [esp + 0x10]
		lea edx, [esp + 0x14]
		push ecx
		push edx
		push eax
		mov dword ptr [esp + 0x1c], 0x10
		_emit 0xff
		_emit 0x15
		_emit 0x5c
		_emit 0x41
		_emit 0x02
		_emit 0x10
		mov ebx, eax
		cmp ebx, -1
		jne L_have_new_socket
	L_ret_neg1:
		pop esi
		pop ebp
		or eax, 0xffffffff
		pop ebx
		add esp, 0x118
		ret
	L_have_new_socket:
		push edi
		_emit 0x8b
		_emit 0x3d
		_emit 0x84
		_emit 0x41
		_emit 0x02
		_emit 0x10
		lea ecx, [esp + 0x10]
		push 4
		push ecx
		push 0x1002
		push 0xffff
		push ebx
		mov dword ptr [esp + 0x24], 0x10000
		call edi
		lea edx, [esp + 0x10]
		push 4
		push edx
		push 0x1001
		push 0xffff
		push ebx
		mov dword ptr [esp + 0x24], 0x10000
		call edi
		_emit 0xa1
		_emit 0x7c
		_emit 0x46
		_emit 0x03
		_emit 0x10
		lea edx, [esi + 0x26420c]
		inc eax
		mov ecx, 0x15
		_emit 0xa3
		_emit 0x7c
		_emit 0x46
		_emit 0x03
		_emit 0x10
		mov dword ptr [esi + 4], eax
		xor eax, eax
		mov edi, edx
		mov dword ptr [esi], 0x2103
		rep stosd
		stosw
		stosb
		mov eax, dword ptr [esi + 4]
		xor edi, edi
		cmp ebp, edi
		mov dword ptr [edx], eax
		jne L_skip_or400
		mov eax, dword ptr [esi]
		or ah, 4
		mov dword ptr [esi], eax
	L_skip_or400:
		mov dword ptr [esi + 0x14], ebx
		mov word ptr [esi + 0x14a], di
		mov word ptr [esi + 0x14c], di
		mov word ptr [esi + 0x14e], 0x19
		_emit 0xff
		_emit 0x15
		_emit 0x5c
		_emit 0x40
		_emit 0x02
		_emit 0x10
		add eax, 0x493e0
		xor ecx, ecx
		mov dword ptr [esi + 0x150], eax
	L_init_loop:
		mov eax, ecx
		shl eax, 4
		add eax, ecx
		lea edx, [esi + eax*8]
		add eax, edx
		cmp ecx, edi
		mov byte ptr [eax + 0x154], 0
		mov byte ptr [eax + 0x132154], 0
		jne L_not_first
		mov dword ptr [esi + 0x1e5], edi
		mov dword ptr [esi + 0x1321e5], edi
		jmp L_set_e9
	L_not_first:
		lea edx, [eax + 0xbb]
		cmp ecx, 0x1fff
		mov dword ptr [eax + 0x1e5], edx
		lea edx, [eax + 0x1320bb]
		mov dword ptr [eax + 0x1321e5], edx
		jge L_set_e9_zero
	L_set_e9:
		lea edx, [eax + 0x1ed]
		mov dword ptr [eax + 0x1e9], edx
		lea edx, [eax + 0x1321ed]
		mov dword ptr [eax + 0x1321e9], edx
		jmp L_init_next
	L_set_e9_zero:
		mov dword ptr [eax + 0x1e9], edi
		mov dword ptr [eax + 0x1321e9], edi
	L_init_next:
		inc ecx
		cmp ecx, 0x2000
		jl L_init_loop
		mov edx, dword ptr [esp + 0x1f]
		lea eax, [esi + 0x154]
		lea ecx, [esi + 0x132154]
		mov dword ptr [esi + 0x2641f8], eax
		mov eax, dword ptr [esp + 0x1e]
		and edx, 0xff
		mov dword ptr [esi + 0x2641fc], ecx
		mov ecx, dword ptr [esp + 0x1d]
		push edx
		mov edx, dword ptr [esp + 0x20]
		and eax, 0xff
		and ecx, 0xff
		push eax
		and edx, 0xff
		push ecx
		push edx
		lea eax, [esp + 0x38]
		push offset s_New_Connection_from__li__li__li__100299a0
		push eax
		mov dword ptr [esi + 0x2641f0], edi
		mov dword ptr [esi + 0x2641f4], edi
		call sprintf
		lea ecx, [esp + 0x40]
		push 1
		push ecx
		push 0x4e1
		push offset s_D__Develop_DieGildeAddOnServer_s_100298b0
		call LogMessageInternal
		add esp, 0x28
		mov eax, ebx
		pop edi
		pop esi
		pop ebp
		pop ebx
		add esp, 0x118
		ret
	}
}

/* Closes a specific player's network connection. Shuts down
 * the socket, clears the player slot, and broadcasts the
 * disconnect to other players. */

// FUNCTION: SERVER 0x1000a2e0
// cm_ClosePlayerConnection

int __cdecl cm_ClosePlayerConnection(unsigned int* player_slot)
{
	shutdown(player_slot[5], 2);
	closesocket(player_slot[5]);
	*player_slot = 0;
	player_slot[5] = 0xffffffff;
	player_slot[1] = 0;
	memset((char*) player_slot + 0x26420c, 0, 87);
	LogMessageInternal("D:\\Develop\\DieGildeAddOnServer\\server.c", 0x500, "Connection dropped.\n", 1);
	return 0;
}

/* Receives a packet header from a client socket. Reads the
 * fixed-size header, validates it, and returns the packet
 * size. Handles partial reads and disconnects. */

// FUNCTION: SERVER 0x1000a340
// ReceivePacketHeader

/* recv = 0x10024168, GetTickCount = 0x1002405c, WSAGetLastError = 0x10024170 */

__declspec(naked) int __cdecl ReceivePacketHeader(unsigned int* param_1)
{
	(void) param_1;
	__asm {
		push esi
		mov esi, dword ptr [esp + 8]
		push edi
		test byte ptr [esi], 0x80
		jne near L_ret0
		mov ax, word ptr [esi + 0x14a]
		_emit 0x8b
		_emit 0x3d
		_emit 0x68
		_emit 0x41
		_emit 0x02
		_emit 0x10
		cmp ax, 3
		jae L_load_eax_arg
		and eax, 0xffff
		mov ecx, 3
		sub ecx, eax
		push 0
		lea edx, [eax + esi + 0x18]
		mov eax, dword ptr [esi + 0x14]
		push ecx
		push edx
		push eax
		call edi
		test eax, eax
		jne L_after_recv1
		_emit 0xff
		_emit 0x15
		_emit 0x5c
		_emit 0x40
		_emit 0x02
		_emit 0x10
		cmp dword ptr [esi + 0x150], eax
		jae near L_ret0
		push 1
		push 0x10029a04
		push 0x52a
		push 0x100298b0
		call LogMessageInternal
		push esi
		call cm_ClosePlayerConnection
		add esp, 0x14
		or eax, 0xffffffff
		pop edi
		pop esi
		ret
	L_after_recv1:
		cmp eax, -1
		jne L_add_and_check
		jmp L_wsa_err
	L_load_eax_arg:
		mov eax, dword ptr [esp + 0xc]
	L_add_and_check:
		add word ptr [esi + 0x14a], ax
		mov ax, word ptr [esi + 0x14a]
		cmp ax, 3
		jb near L_ret0
		xor ecx, ecx
		and eax, 0xffff
		mov cx, word ptr [esi + 0x19]
		push 0
		sub ecx, eax
		lea edx, [eax + esi + 0x18]
		mov eax, dword ptr [esi + 0x14]
		push ecx
		push edx
		push eax
		call edi
		test eax, eax
		jne L_after_recv2
		_emit 0xff
		_emit 0x15
		_emit 0x5c
		_emit 0x40
		_emit 0x02
		_emit 0x10
		cmp dword ptr [esi + 0x150], eax
		jae near L_ret0
		push 1
		push 0x10029a04
		push 0x552
		push 0x100298b0
		call LogMessageInternal
		push esi
		call cm_ClosePlayerConnection
		add esp, 0x14
		or eax, 0xffffffff
		pop edi
		pop esi
		ret
	L_after_recv2:
		cmp eax, -1
		jne L_success
	L_wsa_err:
		_emit 0xff
		_emit 0x15
		_emit 0x70
		_emit 0x41
		_emit 0x02
		_emit 0x10
		cmp eax, 0x2733
		je L_ret0
		push eax
		call LogWinsockError
		push esi
		call cm_ClosePlayerConnection
		add esp, 8
		or eax, 0xffffffff
		pop edi
		pop esi
		ret
	L_success:
		add word ptr [esi + 0x14a], ax
		_emit 0xff
		_emit 0x15
		_emit 0x5c
		_emit 0x40
		_emit 0x02
		_emit 0x10
		mov cx, word ptr [esi + 0x14a]
		add eax, 0x493e0
		cmp cx, word ptr [esi + 0x19]
		mov dword ptr [esi + 0x150], eax
		jne L_ret0
		mov eax, dword ptr [esi]
		mov word ptr [esi + 0x14a], 0
		or al, 0x80
		mov dword ptr [esi], eax
	L_ret0:
		pop edi
		xor eax, eax
		pop esi
		ret
	}
}

/* Sends queued data to a client socket. Transmits buffered
 * outgoing packets with retry logic for partial sends. */

// FUNCTION: SERVER 0x1000a490
// SendPlayerData

/* send = 0x10024164, GetTickCount = 0x1002405c, WSAGetLastError = 0x10024170 */

int __cdecl SendPlayerData(unsigned int* param_1)
{
	int result;
	unsigned int tick;

	if (param_1[0] & 0x100) {
		return 0;
	}

	result = send(
		param_1[5],
		(const char*) param_1 + 0xb1 + *(unsigned short*) ((char*) param_1 + 0x14c),
		*(unsigned short*) ((char*) param_1 + 0xb2) - *(unsigned short*) ((char*) param_1 + 0x14c),
		0
	);

	if (result == 0) {
		tick = GetTickCount();
		if (param_1[84] < tick) {
			LogMessageInternal("D:\\Develop\\DieGildeAddOn\\online", 0x58f, "send timeout", 1);
			cm_ClosePlayerConnection(param_1);
			return -1;
		}
	}
	else if (result == -1) {
		if (WSAGetLastError() == 0x2733) {
			return 0;
		}
		cm_ClosePlayerConnection(param_1);
		return -1;
	}
	else if (result > 0) {
		*(unsigned short*) ((char*) param_1 + 0x14c) += (unsigned short) result;
		tick = GetTickCount();
		*(unsigned int*) ((char*) param_1 + 0x150) = tick + 0x493e0;
		if (*(unsigned short*) ((char*) param_1 + 0x14c) == *(unsigned short*) ((char*) param_1 + 0xb2)) {
			param_1[0] = param_1[0];
			*(unsigned short*) ((char*) param_1 + 0x14c) = 0;
			param_1[0] |= 0x100;
		}
	}

	return 0;
}

/* Processes received network data from all connected clients.
 * Reads incoming packets, reassembles fragmented data, and
 * dispatches complete commands for processing. */

// DATA: SERVER 0x101deac0
extern unsigned int g_download_total_size;
// DATA: SERVER 0x101deac4
extern unsigned int g_download_received;
// DATA: SERVER 0x101deac8
extern unsigned int g_download_slots[8];
// DATA: SERVER 0x101deae8
extern unsigned int g_download_buffer;

// FUNCTION: SERVER 0x1000a860
// ProcessSendData

__declspec(naked) int __cdecl ProcessSendData(void)
{
	__asm {
		push ebx
		push esi
		push edi
		mov ebx, 0x101deb00
	L_loop:
		test byte ptr [ebx], 1
		je L_next
		push ebx
		call SendPlayerData
		add esp, 4
		cmp eax, -1
		je L_ret_neg1
	L_inner:
		mov esi, dword ptr [ebx + 0x2641f4]
		test esi, esi
		je L_chk_result
		mov ecx, dword ptr [ebx]
		test ch, 1
		je L_chk_result
		lea edi, [ebx + 0xb1]
		mov ecx, 0x26
		rep movsd
		movsb
		mov eax, dword ptr [ebx + 0x2641f4]
		push eax
		push ebx
		call FreeCommandBuffer
		mov edi, dword ptr [ebx]
		push ebx
		and edi, 0xfffffeff
		mov dword ptr [ebx], edi
		call SendPlayerData
		add esp, 0xc
		cmp eax, -1
		je L_ret_neg1
		jmp L_inner
	L_chk_result:
		cmp eax, -1
		je L_ret_neg1
	L_next:
		add ebx, 0x264264
		cmp ebx, 0x114ffe20
		jge L_ret_ok
		jmp L_loop
	L_ret_neg1:
		pop edi
		pop esi
		or eax, 0xffffffff
		pop ebx
		ret
	L_ret_ok:
		pop edi
		pop esi
		xor eax, eax
		pop ebx
		ret
	}
}

/* Queues a command packet for server-side processing.
 * Copies the packet into the command queue buffer via memcpy. */

// FUNCTION: SERVER 0x1000A8F0
// QueueCommandForProcessing

void* memcpy(void*, const void*, unsigned int);

int __cdecl QueueCommandForProcessing(unsigned int* player_slot, unsigned char* cmd_data)
{
	char* buf;
	int tail;

	buf = *(char**) ((int) player_slot + 0x2641f8);
	if (buf == 0) {
		LogMessageInternal("D:\\Develop\\DieGildeAddOnServer\\server.c", 0x671, "Commandbuffer full!", 1);
		return -1;
	}
	*(int*) ((int) player_slot + 0x2641f8) = *(int*) (buf + 0x95);
	memcpy(buf, cmd_data, 0x99);
	*(short*) (buf + 1) = get_command_type(buf);
	tail = *(int*) ((int) player_slot + 0x2641f0);
	if (tail != 0) {
		while (*(int*) (tail + 0x95) != 0) {
			tail = *(int*) (tail + 0x95);
		}
		*(int*) (buf + 0x91) = tail;
		*(int*) (buf + 0x95) = 0;
		*(char**) (tail + 0x95) = buf;
		return 0;
	}
	*(int*) (buf + 0x91) = 0;
	*(int*) (buf + 0x95) = 0;
	*(char**) ((int) player_slot + 0x2641f0) = buf;
	return 0;
}

/* Queues a player command for processing. Wraps the command
 * with player slot info and adds to the processing queue. */

// FUNCTION: SERVER 0x1000A9A0
// cm_QueuePlayerCommand
void* memcpy(void*, const void*, unsigned int);

int __cdecl cm_QueuePlayerCommand(unsigned int* player_slot, unsigned char* cmd_data)
{
	char* buf;
	int tail;

	buf = *(char**) ((int) player_slot + 0x2641fc);
	if (buf == 0) {
		LogMessageInternal("D:\\Develop\\DieGildeAddOnServer\\server.c", 0x6b0, "Commandbuffer full!", 1);
		return -1;
	}
	*(int*) ((int) player_slot + 0x2641fc) = *(int*) (buf + 0x95);
	memcpy(buf, cmd_data, 0x99);
	*(short*) (buf + 1) = get_command_type(buf);
	tail = *(int*) ((int) player_slot + 0x2641f4);
	if (tail != 0) {
		while (*(int*) (tail + 0x95) != 0) {
			tail = *(int*) (tail + 0x95);
		}
		*(int*) (buf + 0x91) = tail;
		*(int*) (buf + 0x95) = 0;
		*(char**) (tail + 0x95) = buf;
		return 0;
	}
	*(int*) (buf + 0x91) = 0;
	*(int*) (buf + 0x95) = 0;
	*(char**) ((int) player_slot + 0x2641f4) = buf;
	return 0;
}

/* Unlinks a node from its current position in a doubly-linked
 * list and relinks it at the head. Used for LRU ordering. */

// FUNCTION: SERVER 0x1000AA50
// list_unlink_relink
void __cdecl list_unlink_relink(char* ctx, char* node)
{
	int prev;
	int next;
	prev = *(int*) (node + 0x91);
	if (prev) {
		next = *(int*) (node + 0x95);
		*(int*) (prev + 0x95) = next;
	}
	else {
		next = *(int*) (node + 0x95);
		*(int*) (ctx + 0x2641f4) = next;
	}
	next = *(int*) (node + 0x95);
	if (next) {
		prev = *(int*) (node + 0x91);
		*(int*) (next + 0x91) = prev;
	}
	*(int*) (node + 0x91) = 0;
	prev = *(int*) (ctx + 0x2641fc);
	*(int*) (node + 0x95) = prev;
	*(int*) (ctx + 0x2641fc) = (int) node;
}

/* Processes all queued commands in order. Dequeues each
 * command, dispatches to the appropriate Chk/Ex handler
 * pair, and writes response data back to clients. */

// STUB: SERVER 0x1000aac0
// cm_ProcessCommandQueue

int __cdecl cm_ProcessCommandQueue(void)
{
	unsigned int* slot;
	unsigned char* node;
	unsigned char* type5;
	unsigned char* next_save;
	unsigned char* next_field;
	volatile int result;
	int valid;
	unsigned int player_idx;
	unsigned char* conn;
	unsigned int i;

	for (slot = (unsigned int*) 0x10442cf0; (unsigned int) slot < 0x11764010;
		slot = (unsigned int*) ((unsigned char*) slot + 0x264264)) {
		node = (unsigned char*) slot[0];
		type5 = 0;

		while (node != 0) {
			next_save = *(unsigned char**) (node + 0x95);
			next_field = node + 0x95;
			valid = 1;

			if (type5 != 0) {
				if (*(unsigned char*) node != 6) {
					goto advance;
				}
				result = ahm_ProcessEntityChain(type5);
				if (result == 0) {
					valid = 0;
				}
				next_save = *(unsigned char**) (type5 + 0x95);
				next_field = type5 + 0x95;
				node = type5;
				type5 = 0;
				if (valid == 0) {
					goto advance;
				}
			}
			else {
				if (*(unsigned char*) node == 5) {
					type5 = node;
					goto advance;
				}
			}

			/* Unlink node from pending list */
			if (node == (unsigned char*) slot[0]) {
				slot[0] = (unsigned int) next_save;
			}
			else {
				*(unsigned int*) (*(unsigned int*) (node + 0x91) + 0x95) = *(unsigned int*) next_field;
				*(unsigned int*) (*(unsigned int*) next_field + 0x91) = *(unsigned int*) (node + 0x91);
			}
			*(unsigned int*) (node + 0x91) = 0;
			*(unsigned int*) next_field = slot[2];
			slot[2] = (unsigned int) node;

			if (*(unsigned char*) node >= 0x6a) {
				LogMessageInternal(
					"D:\\Develop\\DieGildeAddOnServer\\server.c",
					0x756,
					"Command-Type out of Range!\n",
					1
				);
				goto advance;
			}

			if (*(unsigned char*) node == 0x20 && node[0x10] == 0x0e) {
				player_idx = (unsigned int) node[3];
				if ((g_connections[player_idx * 0x264264] & 0x40) != 0) {
					LogMessageInternal("D:\\Develop\\DieGildeAddOnServer\\server.c", 0x72e, "Multisync!!!", 1);
				}
			}

			result = g_dispatch_table[(unsigned int) *(unsigned char*) node](node, 0);

			if (0 != result) {
				player_idx = (unsigned int) node[3];
				if ((g_connections[player_idx * 0x264264] & 1) == 0) {
					goto advance;
				}
				*(unsigned char*) node = 2;
				result = cm_QueuePlayerCommand((unsigned int*) &g_connections[player_idx * 0x264264], node);
				if (result != -1) {
					goto advance;
				}
				return -1;
			}

			/* Handler returned 0 */
			if (*(char*) node == 0x20 && node[0x10] == 0x0e) {
				player_idx = (unsigned int) node[3];
				memcpy((void*) (player_idx * 0x264264 + 0x10442c54), node, 153);
				goto advance;
			}

			player_idx = (unsigned int) node[3];
			conn = &g_connections[player_idx * 0x264264];
			if ((*conn & 1) != 0) {
				result = cm_QueuePlayerCommand((unsigned int*) conn, node);
				if (result == -1) {
					return -1;
				}
			}

			*(int*) (node + 4) = -1;
			i = 0;
			conn = &g_connections[0];
			do {
				if (i != (unsigned int) node[3] && (*conn & 1) != 0) {
					result = cm_QueuePlayerCommand((unsigned int*) conn, node);
					if (result == -1) {
						return -1;
					}
				}
				conn += 0x264264;
				i++;
			} while ((int) conn < 0x114ffe20);

		advance:
			node = next_save;
		}

	}

	return 0;
}

/* Logs a Winsock error by error code. Maps WSA error codes
 * to human-readable strings and passes to the log system. */

// FUNCTION: SERVER 0x1000ad40
// LogWinsockError

void __cdecl LogWinsockError(int param_1)
{
	char buf[256];

	switch (param_1) {
	case 0x276d:
		LogMessageInternal("D:\\Develop\\DieGildeAddOnServer\\server.c", 0x769, "WSANOTINITIALISED", 1);
		return;
	case 0x2742:
		LogMessageInternal(
			"D:\\Develop\\DieGildeAddOnServer\\server.c",
			0x76b,
			"WSAENETDOWN: The network subsystem has failed!",
			1
		);
		return;
	case 0x271e:
		LogMessageInternal(
			"D:\\Develop\\DieGildeAddOnServer\\server.c",
			0x76d,
			"WSAEFAULT: The buf parameter is not completely contained in a valid part of the user address space",
			1
		);
		return;
	case 0x2749:
		LogMessageInternal(
			"D:\\Develop\\DieGildeAddOnServer\\server.c",
			0x76f,
			"WSAENOTCONN: The socket is not connected.",
			1
		);
		return;
	case 0x2714:
		LogMessageInternal(
			"D:\\Develop\\DieGildeAddOnServer\\server.c",
			0x771,
			"WSAEINTR: The (blocking) call was canceled through WSACancelBlockingCall.",
			1
		);
		return;
	case 0x2734:
		LogMessageInternal(
			"D:\\Develop\\DieGildeAddOnServer\\server.c",
			0x773,
			"WSAEINPROGRESS: A blocking Windows Sockets 1.1 call is in progress, or the service provider is still "
			"processing a callback function.",
			1
		);
		return;
	case 0x2744:
		LogMessageInternal(
			"D:\\Develop\\DieGildeAddOnServer\\server.c",
			0x775,
			"WSAENETRESET: The connection has been broken due to the keep-alive activity detecting a failure while the "
			"operation was in progress.",
			1
		);
		return;
	case 0x2736:
		LogMessageInternal(
			"D:\\Develop\\DieGildeAddOnServer\\server.c",
			0x777,
			"WSAENOTSOCK: The descriptor is not a socket.",
			1
		);
		return;
	case 0x273d:
		LogMessageInternal(
			"D:\\Develop\\DieGildeAddOnServer\\server.c",
			0x779,
			"WSAEOPNOTSUPP: MSG_OOB was specified, but the socket is not stream-style such as type SOCK_STREAM, OOB "
			"data is not supported in the communication domain associated with this socket, or the socket is "
			"unidirectional and supports only send operations.",
			1
		);
		return;
	case 0x274a:
		LogMessageInternal(
			"D:\\Develop\\DieGildeAddOnServer\\server.c",
			0x77b,
			"WSAESHUTDOWN: The socket has been shut down; it is not possible to receive on a socket after shutdown has "
			"been invoked with how set to SD_RECEIVE or SD_BOTH.",
			1
		);
		return;
	case 0x2733:
		LogMessageInternal(
			"D:\\Develop\\DieGildeAddOnServer\\server.c",
			0x77d,
			"WSAEWOULDBLOCK: The socket is marked as nonblocking and the receive operation would block.",
			1
		);
		return;
	case 0x2738:
		LogMessageInternal(
			"D:\\Develop\\DieGildeAddOnServer\\server.c",
			0x77f,
			"WSAEMSGSIZE: The message was too large to fit into the specified buffer and was truncated.",
			1
		);
		return;
	case 0x2726:
		LogMessageInternal(
			"D:\\Develop\\DieGildeAddOnServer\\server.c",
			0x781,
			"WSAEINVAL: The socket has not been bound with bind, or an unknown flag was specified, or MSG_OOB was "
			"specified for a socket with SO_OOBINLINE enabled or (for byte stream sockets only) len was zero or "
			"negative.",
			1
		);
		return;
	case 0x2745:
		LogMessageInternal(
			"D:\\Develop\\DieGildeAddOnServer\\server.c",
			0x783,
			"WSAECONNABORTED: The virtual circuit was terminated due to a time-out or other failure. The application "
			"should close the socket as it is no longer usable.",
			1
		);
		return;
	case 0x274c:
		LogMessageInternal(
			"D:\\Develop\\DieGildeAddOnServer\\server.c",
			0x785,
			"WSAETIMEDOUT: The connection has been dropped because of a network failure or because the peer system "
			"failed to respond.",
			1
		);
		return;
	case 0x2746:
		LogMessageInternal(
			"D:\\Develop\\DieGildeAddOnServer\\server.c",
			0x787,
			"WSAECONNRESET: The virtual circuit was reset by the remote side executing a hard or abortive close. The "
			"application should close the socket as it is no longer usable. On a UPD-datagram socket this error would "
			"indicate that a previous send operation resulted in an ICMP >Port Unreachable< message.",
			1
		);
		return;
	default:
		sprintf(buf, "Unbekannter WinsockError %d", param_1);
		LogMessageInternal("D:\\Develop\\DieGildeAddOnServer\\server.c", 0x789, buf, 1);
		return;
	}
}

/* Initializes the building type lookup table. Loads building
 * definitions (costs, capacities, upgrade paths) from game
 * data into the runtime type table. */

extern char DAT_101de5a0[];

// FUNCTION: SERVER 0x1000b040
// InitBuildingTypeTable

__declspec(naked) void InitBuildingTypeTable(void)
{
	__asm {
		push ebp
		mov ebp, esp
		push ecx
		push ebx
		push edi
		mov dword ptr [ebp - 4], 0x3f0
		mov edi, offset DAT_101de5a0
		mov ebx, dword ptr [ebp - 4]
		xor eax, eax
		lea ecx, [edi + edi*2]
		and ecx, 3
		sub ebx, ecx
		jle L_after_stos
		rep stosb
		mov ecx, ebx
		and ebx, 3
		shr ecx, 2
		rep stosd
	L_after_stos:
		add ecx, ebx
		rep stosb
		xor ecx, ecx
		pop edi
		mov eax, offset DAT_101de5a0 + 4
		or edx, 0xffffffff
		pop ebx
	L_loop_init:
		mov byte ptr [eax - 4], cl
		mov dword ptr [eax], edx
		mov dword ptr [eax + 0x10], edx
		add eax, 0x18
		inc ecx
		cmp eax, offset DAT_101de5a0 + 0x3f4
		jl L_loop_init
		mov al, 1
		mov byte ptr [DAT_101de5a0 + 0x38], 2
		mov byte ptr [DAT_101de5a0 + 0x8], al
		mov byte ptr [DAT_101de5a0 + 0x20], al
		mov al, 4
		mov byte ptr [DAT_101de5a0 + 0x50], 3
		mov byte ptr [DAT_101de5a0 + 0x68], al
		mov byte ptr [DAT_101de5a0 + 0x80], al
		mov al, 7
		mov byte ptr [DAT_101de5a0 + 0x98], 5
		mov byte ptr [DAT_101de5a0 + 0xb0], 6
		mov byte ptr [DAT_101de5a0 + 0xc8], al
		mov byte ptr [DAT_101de5a0 + 0xe0], al
		mov byte ptr [DAT_101de5a0 + 0xf8], 8
		mov byte ptr [DAT_101de5a0 + 0x110], 9
		mov byte ptr [DAT_101de5a0 + 0x128], 0xa
		mov byte ptr [DAT_101de5a0 + 0x140], 0xb
		mov byte ptr [DAT_101de5a0 + 0x158], 0xc
		mov byte ptr [DAT_101de5a0 + 0x170], 0xd
		mov byte ptr [DAT_101de5a0 + 0x188], 0xe
		mov byte ptr [DAT_101de5a0 + 0x1a0], 0xf
		mov byte ptr [DAT_101de5a0 + 0x1b8], 0x10
		mov byte ptr [DAT_101de5a0 + 0x1d0], 0x11
		mov byte ptr [DAT_101de5a0 + 0x1e8], 0x12
		mov byte ptr [DAT_101de5a0 + 0x200], 0x13
		mov byte ptr [DAT_101de5a0 + 0x218], 0x14
		mov byte ptr [DAT_101de5a0 + 0x230], 0x15
		mov byte ptr [DAT_101de5a0 + 0x248], 0x16
		mov byte ptr [DAT_101de5a0 + 0x260], 0x17
		mov byte ptr [DAT_101de5a0 + 0x278], 0x18
		mov byte ptr [DAT_101de5a0 + 0x290], 0x19
		mov byte ptr [DAT_101de5a0 + 0x2a8], 0x1a
		mov byte ptr [DAT_101de5a0 + 0x2c0], 0x1b
		mov byte ptr [DAT_101de5a0 + 0x2d8], 0x1c
		mov byte ptr [DAT_101de5a0 + 0x2f0], 0x1d
		mov byte ptr [DAT_101de5a0 + 0x308], 0x1e
		mov byte ptr [DAT_101de5a0 + 0x320], 0x1f
		mov byte ptr [DAT_101de5a0 + 0x338], 0x20
		mov byte ptr [DAT_101de5a0 + 0x350], 0x21
		mov byte ptr [DAT_101de5a0 + 0x368], 0x22
		mov byte ptr [DAT_101de5a0 + 0x380], 0x23
		mov byte ptr [DAT_101de5a0 + 0x398], 0x24
		mov byte ptr [DAT_101de5a0 + 0x3b0], 0x25
		mov byte ptr [DAT_101de5a0 + 0x3c8], 0x26
		mov byte ptr [DAT_101de5a0 + 0x3e0], 0x27
		mov esp, ebp
		pop ebp
		ret
	}
}
