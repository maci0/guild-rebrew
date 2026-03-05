#include <stdio.h>
#include <string.h>
#include <windows.h>
#include <winsock2.h>

typedef int(__cdecl* handler_func)(unsigned char* pkt, int param);

extern DWORD WINAPI thread_proc(LPVOID);
extern int g_stop_flag;
extern void __cdecl LogMessageInternal(char* file, unsigned int line, char* msg, int level);
extern int __cdecl AcceptConnections(void);
extern void __cdecl InitBuildingTypeTable(void);
extern int __cdecl ProcessReceiveData(void);
extern int __cdecl ProcessSendData(void);
extern int __cdecl ClosePlayerConnection(unsigned int* player_slot);
extern int __cdecl QueuePlayerCommand(unsigned int* player_slot, unsigned char* cmd_data);
extern void __cdecl SendBroadcastPacket(int port, void* config_data);
extern void __cdecl RecvGameSavegame(void);
extern void __cdecl CleanupSockets(void);
extern int __cdecl srv_Init(void);
extern int __cdecl AdvanceGameClock(int* clock_state, int a2, int a3, int a4);
extern int __cdecl cm_ProcessCommandQueue(void);
extern void __cdecl FreeTrackedHeapBlock(void* ptr);
extern void __cdecl SetSyncParams(int base_addr, unsigned char phase, unsigned int arg3, unsigned int arg4);
extern void __cdecl crt_getptd_set(unsigned int value);
extern void __cdecl reset_all_entities(void);
extern void __cdecl CleanupObjectEntities(void);
extern void __cdecl cleanup_all_entities(void);
extern void __cdecl ShutdownMemoryAllocator(void);
extern void __cdecl ShutdownLogAndErrorHandler(void);
extern int g_net_socket;
extern void __cdecl LogWinsockError(int error_code);
extern int __cdecl ReceivePacketHeader(unsigned int* conn); /* 0x1000a340 */;
extern int __cdecl QueueCommandForProcessing(unsigned int* conn, unsigned char* pkt); /* 0x1000a8f0 */;
extern int __cdecl lb_ExLobbyServerCommand(unsigned int* conn, unsigned char* pkt); /* 0x10014db0 */;
extern int __cdecl AllocateTrackedHeapBlock(unsigned int size, char* name); /* 0x10006580 */;
extern int __cdecl SendPlayerData(unsigned int*);
extern void __cdecl FreeCommandBuffer(unsigned int*, int);
extern unsigned int g_player_slots;
extern short __cdecl get_command_type(char*);
extern int __cdecl ProcessEntityChain(unsigned char* node);
extern handler_func g_dispatch_table[]; /* 0x1002c3f8 */;
extern unsigned char g_connections[]; /* 0x101deb00 */;

;
;
;
;
;
;

// STATUS: MATCHING
// ORIGIN: GAME
// SIZE: 170
// SYMBOL: exit_handler
// GHIDRA: exit_handler
// FUNCTION: SERVER 0x10009310
// exit_handler
// PROTOTYPE: int __stdcall exit_handler(int a, int b, int c)
int __stdcall exit_handler(int a, int b, int c)
{
	return 1;
}

// ORIGIN: GAME
// STATUS: RELOC
// SIZE: 42
// SYMBOL: _Init
// ANALYSIS: Create server main thread - called on DLL_PROCESS_ATTACH | Exported function called by the host engine to initialize the game server thread. Creates the core ServerMainThread and returns the handle validity.
// FUNCTION: SERVER 0x10009320
// Init
// PROTOTYPE: int __stdcall Init(LPVOID param)

HANDLE g_thread_handle;

int __cdecl Init(LPVOID param)
{
	g_thread_handle = CreateThread(NULL, 0, thread_proc, param, 0, (LPDWORD) &param);
	return g_thread_handle != 0;
}

// STATUS: RELOC
// ORIGIN: GAME
// SIZE: 68
// SYMBOL: _Exit
// ANALYSIS: Exported function called by the host engine to shut down the server thread. Sets a global shutdown flag, waits briefly, then forcefully terminates if necessary. | Signal shutdown and wait for thread to exit cleanly | Force terminate if thread doesn't exit within timeout
// FUNCTION: SERVER 0x10009350
// Exit
// PROTOTYPE: void __cdecl Exit(void)

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

// ORIGIN: GAME
// STATUS: MATCHING
// BLOCKER: comparison direction swap, instruction folding (lea vs mov), jump condition swap, loop rotation / branch layout, zero-extend pattern (xor vs mov)
// SIZE: 2434
// SYMBOL: _ServerMainThread
// BLOCKER_DELTA: 2223
// ANALYSIS: Core orchestration loop. Phase 1 (Lobby): Loops accepting connections until connected_players == g_max_players and every connected player has the 0x800 ready flag. Then transitions into Phase 2 (Transfer). | PHASE 0: Read game.ini config — server port (default 7531), game path, max players | Initialize server: thread priority, logging, packet pool, game data, listen socket | PHASE 1 — LOBBY: Wait for all players to connect and set ready flag (0x800). Broadcasts server info every 3 seconds. Processes network I/O. Handles disconnect requests (0x1000) and host disconnect (0x400 = terminate). | PHASE 3 — DATA RECEIVE: Wait for host to send savegame data (flag 0x08 cleared when done). Then call RecvGameSavegame to deserialize game state. | PHASE 5 — PLAYER ALLOCATION: Wait for each player to allocate their character entity (flag 0x10 set, cleared when cmd received). | PHASE 6 — GAME LOOP: Main simulation tick. Checks sync flags (0x40=sync data, 0x20=sync ready). Advances game clock, broadcasts sync packets (cmd 0x1E). Processes commands via ProcessAndBroadcastAllCommands. Speed controlled by g_game_speed_value. | PHASE 4 — DATA SEND: Stream savegame to all non-host clients in 128-byte chunks (cmd type 0x09). First sends total size (cmd type 0x08). Clears flag 0x04 when transfer complete per player.
// FUNCTION: SERVER 0x100093a0
// ServerMainThread
// PROTOTYPE: int __stdcall ServerMainThread(void * lpThreadParameter)

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
	crt_getptd_set(timeGetTime());

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
			player_slot = (unsigned int*) 0x101deb00;
			do {
				if ((*player_slot != 0) && ((*player_slot & 0x800) == 0)) {
					phase_complete = 0;
					goto lobby_check_announce;
				}
				player_slot = (unsigned int*) ((char*) player_slot + 0x264264);
			} while ((char*) player_slot < (char*) 0x114ffe20);
			LogMessageInternal((char*) 0x100298b0, 0x14e, (char*) 0x10029890, 1);
		}

	lobby_check_announce:
		now_tick = timeGetTime();
		if ((3000 < now_tick - last_announce_tick) || phase_complete) {
			*((unsigned char*) startup_cfg_words + 0x27) = (unsigned char) connected_players;
			SendBroadcastPacket(0x3039, startup_cfg_words);
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
				ClosePlayerConnection(player_slot);
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
			if (QueuePlayerCommand(player_slot, cmd_buffer_primary) == -1) {
				goto cleanup_and_exit;
			}

			cmd_buffer_primary[0] = 0x20;
			*(unsigned int*) (cmd_buffer_primary + 9) = (unsigned int) i;
			cmd_buffer_primary[0x10] = 7;
			i = i + 1;
			if (QueuePlayerCommand(player_slot, cmd_buffer_primary) == -1) {
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
						if (QueuePlayerCommand(player_slot, cmd_buffer_primary) == -1) {
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

						if (QueuePlayerCommand(player_slot, cmd_buffer_primary) == -1) {
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

	FreeTrackedHeapBlock(*(void**) 0x101deae8);
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
			if (QueuePlayerCommand(player_slot, cmd_buffer_secondary) == -1) {
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
				if (QueuePlayerCommand(player_slot, (unsigned char*) ((char*) player_slot + 0x264154)) == -1) {
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
				if (QueuePlayerCommand(player_slot, cmd_buffer_primary) == -1) {
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
					if (QueuePlayerCommand(player_slot, cmd_buffer_secondary) == -1) {
						goto cleanup_and_exit;
					}
					*(int*) 0x11764090 = 0;
				}
				player_slot = (unsigned int*) ((char*) player_slot + 0x264264);
			} while ((char*) player_slot < (char*) 0x114ffe20);

			*(unsigned int*) 0x10035880 = *(unsigned int*) 0x10035880 + 1;
			SetSyncParams(0x10035880, 6, 0, 0);
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

// STATUS: MATCHING
// ORIGIN: GAME
// BLOCKER: instruction folding (lea vs mov)
// SIZE: 296
// SYMBOL: _srv_Init
// BLOCKER_DELTA: 283
// FUNCTION: SERVER 0x10009d30
// srv_Init
// PROTOTYPE: int srv_Init(void)

int __cdecl srv_Init(void)
{
	char game_path[260];
	char data_path[260];
	int result;
	DWORD tick_count;
	char format_buf[32];

	tick_count = GetTickCount();
	SetThreadPriorityBoost(GetCurrentThread(), 2);
	wsprintfA(format_buf, "%c%c%c", 3, 0, 0);

	lstrcpyA(game_path, "\\project\\DieGilde\\game\\");
	lstrcpyA(data_path, "data\\");
	result = Open(game_path, data_path);

	if (result < 0) {
		char full_path[512];
		sub_1001a299(full_path, game_path);
		LogMessageInternal("Could not open gamefiles path:%s", 1, (int) full_path, 0x3cd);
		return 0;
	}

	InitEntitySlots();
	InitBuildingTypeTable();
	result = CreateListenSocket((void*) 0x11764088);

	if (result == -1) {
		LogMessageInternal("***ERROR: Initialization of Socket failed!", 1, 0x3db, 0);
		return 0;
	}

	return 1;
}

// STATUS: RELOC
// ORIGIN: GAME
// SIZE: 419
// SYMBOL: _CreateListenSocket
// FUNCTION: SERVER 0x10009e60
// CreateListenSocket

/* WSAStartup = 0x10024178, WSACleanup = 0x1002417c */
/* socket = 0x10024180, setsockopt = 0x10024184, ioctlsocket = 0x1002416c */
/* htons = 0x1002418c, bind = 0x10024190, listen = 0x10024160 */
/* closesocket = 0x10024198, shutdown = 0x10024174 */
// ANALYSIS: Initialize all player slots to disconnected state, then create TCP listen socket with SO_REUSEADDR, 128KB send/recv buffers, non-blocking mode, bind to port, and listen with backlog 5

/* GLOBAL: SERVER 0x101deb14 */
extern unsigned int g_player_slot_field;

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

	WSAStartup(0x101, wsadata);

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
	if (bind(sock, &addr, 16) == -1) {
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

// STATUS: RELOC
// ORIGIN: GAME
// SIZE: 112
// SYMBOL: _CleanupSockets
// FUNCTION: SERVER 0x1000A010
// CleanupSockets
// PROTOTYPE: void CleanupSockets(void)

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
	InitEntitySlots();
	reset_all_entities();
	CleanupObjectEntities();
	cleanup_all_entities();
	ShutdownMemoryAllocator();
	ShutdownLogAndErrorHandler();
}

// STATUS: MATCHING
// ORIGIN: GAME
// SIZE: 600
// SYMBOL: _AcceptConnections
// BLOCKER_DELTA: 542
// ANALYSIS: Iterates over g_player_slots looking for an empty slot. If one is found, calls Ordinal_1 (accept()) to accept a new connection, configures the socket, initializes the slot structures (receive_buffer, send_buffer), and flags it as a newly connected player.
// FUNCTION: SERVER 0x1000a080
// AcceptConnections

/* accept = 0x1002415c, setsockopt = 0x10024184, GetTickCount = 0x1002405c */

/* GLOBAL: SERVER 0x101deaec - listen socket */
extern int g_listen_socket;

/* GLOBAL: SERVER 0x101deb00 - first player slot (stride 0x264264 bytes) */
extern unsigned int g_player_slot_0;

/* GLOBAL: SERVER 0x114ffe20 - overflow slot */
extern unsigned int g_player_slot_overflow;

/* GLOBAL: SERVER 0x1003467c - connection counter */
extern unsigned int g_connection_counter;

int __cdecl AcceptConnections(void)
{
	char logbuf[0x100];
	struct sockaddr_in addr;
	int addrlen;
	int optval;
	int new_socket;
	unsigned int* slot;
	int slot_index;

	if (g_listen_socket == -1) {
		return -1;
	}

	slot_index = 0;
	{
		unsigned int* p = &g_player_slot_0;
		while (*p != 0) {
			p = (unsigned int*) ((char*) p + 0x264264);
			slot_index++;
			if ((int) p >= (int) &g_player_slot_overflow) {
				goto no_more_slots;
			}
		}
		slot = &g_player_slot_0 + (unsigned int) slot_index * 0x99099;
	}
	if (slot) {
		goto do_accept;
	}

no_more_slots:
	LogMessageInternal("D:\\Develop\\DieGildeAddOnServer\\server.c", 0x495, "No more Slots for new Connections!\n", 1);
	if (g_player_slot_overflow != 0) {
		return -1;
	}
	slot = &g_player_slot_overflow;

do_accept:
	addrlen = 0x10;
	new_socket = accept(g_listen_socket, &addr, &addrlen);
	if (new_socket == -1) {
		return -1;
	}

	optval = 0x10000;
	setsockopt(new_socket, 0xffff, 0x1002, (const char*) &optval, 4);
	optval = 0x10000;
	setsockopt(new_socket, 0xffff, 0x1001, (const char*) &optval, 4);

	g_connection_counter++;
	slot[1] = g_connection_counter;

	memset((char*) slot + 0x26420c, 0, 87);
	*(unsigned int*) ((char*) slot + 0x26420c) = g_connection_counter;

	slot[0] = 0x2103;
	if (slot_index == 0) {
		slot[0] |= 0x400;
	}
	slot[5] = (unsigned int) new_socket;
	*(unsigned short*) ((char*) slot + 0x14a) = 0;
	*(unsigned short*) ((char*) slot + 0x14c) = 0;
	*(unsigned short*) ((char*) slot + 0x14e) = 0x19;
	slot[0x54] = GetTickCount() + 0x493e0;

	{
		int i;
		for (i = 0; i < 0x2000; i++) {
			unsigned char* e;
			int tmp;
			tmp = i;
			tmp <<= 4;
			tmp += i;
			e = (unsigned char*) slot + (unsigned int) tmp * 8 + tmp;

			e[0x154] = 0;
			e[0x132154] = 0;

			if (i == 0) {
				*(unsigned int*) (e + 0x1e5) = 0;
				*(unsigned int*) (e + 0x1321e5) = 0;
				*(unsigned int*) (e + 0x1e9) = (unsigned int) (e + 0x1ed);
				*(unsigned int*) (e + 0x1321e9) = (unsigned int) (e + 0x1321ed);
			}
			else {
				*(unsigned int*) (e + 0x1e5) = (unsigned int) (e + 0xbb);
				*(unsigned int*) (e + 0x1321e5) = (unsigned int) (e + 0x1320bb);
				if (i < 0x1fff) {
					*(unsigned int*) (e + 0x1e9) = (unsigned int) (e + 0x1ed);
					*(unsigned int*) (e + 0x1321e9) = (unsigned int) (e + 0x1321ed);
				}
				else {
					*(unsigned int*) (e + 0x1e9) = 0;
					*(unsigned int*) (e + 0x1321e9) = 0;
				}
			}
		}
	}

	*(unsigned int**) ((char*) slot + 0x2641f8) = (unsigned int*) ((char*) slot + 0x154);
	*(unsigned int**) ((char*) slot + 0x2641fc) = (unsigned int*) ((char*) slot + 0x132154);
	*(unsigned int*) ((char*) slot + 0x2641f0) = 0;
	*(unsigned int*) ((char*) slot + 0x2641f4) = 0;

	{
		unsigned char* ip = (unsigned char*) &addr.sin_addr;
		sprintf(
			logbuf,
			"New Connection from %li.%li.%li.%li\n",
			(unsigned int) ip[0],
			(unsigned int) ip[1],
			(unsigned int) ip[2],
			(unsigned int) ip[3]
		);
		LogMessageInternal("D:\\Develop\\DieGildeAddOnServer\\server.c", 0x4e1, logbuf, 1);
	}

	return new_socket;
}

// STATUS: RELOC
// ORIGIN: GAME
// SIZE: 96
// SYMBOL: _ClosePlayerConnection
// ANALYSIS: Shutdown socket (SD_BOTH) | Close socket handle
// FUNCTION: SERVER 0x1000a2e0
// ClosePlayerConnection
// PROTOTYPE: int __cdecl ClosePlayerConnection(uint * player_slot)

int __cdecl ClosePlayerConnection(unsigned int* player_slot)
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

// STATUS: MATCHING
// ORIGIN: GAME
// SIZE: 336
// SYMBOL: _ReceivePacketHeader
// FUNCTION: SERVER 0x1000a340
// ReceivePacketHeader

/* recv = 0x10024168, GetTickCount = 0x1002405c, WSAGetLastError = 0x10024170 */
// ANALYSIS: Ingress parser boundary for per-player receive buffer. Validation behavior: handles recv==0 timeout via player_slot[0x54] deadline, treats recv==-1 + WSAEWOULDBLOCK as retry, closes connection on other socket errors. | Stage 1 ingress: ensure first 3 bytes of packet are present (1-byte opcode + 2-byte total length). | Length-driven read: remaining bytes = header.total_length - bytes_received so far. | 0x2733 matches WSAEWOULDBLOCK (non-fatal on nonblocking socket).
// PROTOTYPE: int __cdecl ReceivePacketHeader(uint * param_1)

int __cdecl ReceivePacketHeader(unsigned int* param_1)
{
	int result;
	unsigned int tick;
	unsigned short hdr_recv;
	unsigned short pkt_size;
	int wsa_err;

	if (param_1[0] & 0x80) {
		return 0;
	}

	hdr_recv = *(unsigned short*) ((char*) param_1 + 0x14a);

	if (hdr_recv >= 3) {
		goto add_and_check;
	}

	result = recv(param_1[5], (char*) param_1 + 0x18 + hdr_recv, 3 - hdr_recv, 0);

	if (result == 0) {
		tick = GetTickCount();
		if (*(unsigned int*) ((char*) param_1 + 0x150) < tick) {
			LogMessageInternal("D:\\Develop\\DieGildeAddOnServer\\server.c", 0x52a, "Connection timed out.\n", 1);
			ClosePlayerConnection(param_1);
			return -1;
		}
		return 0;
	}
	if (result == -1) {
		goto handle_wsa_error;
	}

add_and_check:
	*(unsigned short*) ((char*) param_1 + 0x14a) += (unsigned short) result;
	hdr_recv = *(unsigned short*) ((char*) param_1 + 0x14a);
	if (hdr_recv < 3) {
		return 0;
	}

	pkt_size = *(unsigned short*) ((char*) param_1 + 0x19);
	result = recv(param_1[5], (char*) param_1 + 0x18 + hdr_recv, pkt_size - hdr_recv, 0);

	if (result == 0) {
		tick = GetTickCount();
		if (*(unsigned int*) ((char*) param_1 + 0x150) < tick) {
			LogMessageInternal("D:\\Develop\\DieGildeAddOnServer\\server.c", 0x552, "Connection timed out.\n", 1);
			ClosePlayerConnection(param_1);
			return -1;
		}
		return 0;
	}
	if (result == -1) {
	handle_wsa_error:
		wsa_err = WSAGetLastError();
		if (wsa_err == 0x2733) {
			return 0;
		}
		LogWinsockError(wsa_err);
		ClosePlayerConnection(param_1);
		return -1;
	}

	*(unsigned short*) ((char*) param_1 + 0x14a) += (unsigned short) result;
	tick = GetTickCount();
	*(unsigned int*) ((char*) param_1 + 0x150) = tick + 0x493e0;
	if (*(unsigned short*) ((char*) param_1 + 0x14a) == *(unsigned short*) ((char*) param_1 + 0x19)) {
		*(unsigned short*) ((char*) param_1 + 0x14a) = 0;
		param_1[0] |= 0x80;
	}

	return 0;
}

// STATUS: RELOC
// ORIGIN: GAME
// SIZE: 211
// SYMBOL: _SendPlayerData
// FUNCTION: SERVER 0x1000a490
// SendPlayerData

/* send = 0x10024164, GetTickCount = 0x1002405c, WSAGetLastError = 0x10024170 */
// ANALYSIS: Send data via socket (Ordinal_19 = send)
// PROTOTYPE: int __cdecl SendPlayerData(uint * param_1)

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
			ClosePlayerConnection(param_1);
			return -1;
		}
	}
	else if (result == -1) {
		if (WSAGetLastError() == 0x2733) {
			return 0;
		}
		ClosePlayerConnection(param_1);
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

// STATUS: MATCHING
// ORIGIN: GAME
// BLOCKER: instruction folding (lea vs mov), jump condition swap, loop rotation / branch layout
// SIZE: 750
// SYMBOL: _ProcessReceiveData
// BLOCKER_DELTA: 453
// ANALYSIS: Iterates over g_player_slots. If a slot is connected, loops calling ReceivePacketHeader to ingest stream data into the receive_buffer. Once a full CommandPacket is received, validates and queues it onto the incoming_cmd_queue via QueueCommandForProcessing. It also handles commands for bulk transfer (0x08, 0x09).
// FUNCTION: SERVER 0x1000a570
// ProcessReceiveData

/* GLOBAL: SERVER 0x101deac0 */
extern unsigned int g_download_total_size;
/* GLOBAL: SERVER 0x101deac4 */
extern unsigned int g_download_received;
/* GLOBAL: SERVER 0x101deac8 */
extern unsigned int g_download_slots[8];
/* GLOBAL: SERVER 0x101deae8 */
extern unsigned int g_download_buffer;

int __cdecl ProcessReceiveData(void)
{
	char logbuf_hi[256];
	char logbuf_lo[256];
	unsigned char pktbuf[156];
	int ret;
	unsigned int* conn;
	int i;
	unsigned int status;

	i = 0;
	conn = (unsigned int*) 0x101deb00;

	do {
		if ((*(unsigned char*) conn & 1) != 0) {
			do {
				ret = ReceivePacketHeader(conn);
				if (ret == -1) {
					return -1;
				}
				status = *conn;
				if ((status & 0x80) == 0) {
					break;
				}
				if (status & 2) {
					if (*(unsigned char*) (conn + 6) == 3) {
						conn[0xb] = conn[1];
						conn[0xc] = 2 - ((*conn & 0x400) != 0);
						if (QueuePlayerCommand(conn, (unsigned char*) (conn + 6)) == -1) {
							return -1;
						}
					}
					status = *conn & 0xffffff7d | 0x200;
					goto set_status;
				}
				if (status & 0x200) {
					LogMessageInternal("D:\\Develop\\DieGildeAddOnServer\\server.c", 0x5df, "LOBBY mode", 1);
					if (*(unsigned char*) (conn + 6) == 0x5f) {
						if (lb_ExLobbyServerCommand(conn, (unsigned char*) (conn + 6)) == -1) {
							return -1;
						}
						sprintf(logbuf_lo, "status after lb_ExLobbyServerCommand: %i", *conn);
						LogMessageInternal("D:\\Develop\\DieGildeAddOnServer\\server.c", 0x5e5, logbuf_lo, 1);
					}
					*conn = *conn & 0xffffff7f;
					sprintf(logbuf_lo, "leaving lobby branch: %i", *conn);
					LogMessageInternal("D:\\Develop\\DieGildeAddOnServer\\server.c", 0x5e9, logbuf_lo, 1);
					goto done_inner;
				}
				if (status & 8) {
					if (*(unsigned char*) (conn + 6) == 8) {
						g_download_received = 0;
						g_download_total_size = conn[10];
						memset(g_download_slots, 0xff, 32);
						g_download_buffer = AllocateTrackedHeapBlock(conn[10], "srv_LoadBuf");
					}
					else if (*(unsigned char*) (conn + 6) == 9) {
						memcpy((void*) (g_download_buffer + g_download_received), conn + 10, 0x80);
						g_download_received = g_download_received + 0x80;
					}
					if (g_download_received >= g_download_total_size) {
						*conn = *conn & 0xfffffff7;
					}
					status = *conn & 0xffffff7f;
					goto set_status;
				}
				if (status & 4) {
					sprintf(logbuf_hi, "Unexpected Request from connection nr %i", i);
					LogMessageInternal("D:\\Develop\\DieGildeAddOnServer\\server.c", 0x609, logbuf_hi, 1);
					*conn = *conn & 0xffffff7f;
					pktbuf[0] = 2;
					if (QueuePlayerCommand(conn, pktbuf) == -1) {
						return -1;
					}
					goto done_inner;
				}
				*((unsigned char*) conn + 0x1b) = (unsigned char) i;
				if (status & 0x10) {
					if (QueueCommandForProcessing(conn, (unsigned char*) (conn + 6)) != 0) {
						return -1;
					}
					status = *conn & 0xffffff6f;
					goto set_status;
				}
				if (QueueCommandForProcessing(conn, (unsigned char*) (conn + 6)) != 0) {
					return -1;
				}
				status = *conn & 0xffffff7f;
			set_status:
				*conn = status;
			done_inner:;
			} while ((*(unsigned char*) conn & 1) != 0);
			if (ret == -1) {
				return -1;
			}
		}
		conn = (unsigned int*) ((char*) conn + 0x264264);
		i++;
	} while (conn < (unsigned int*) 0x114ffe20);

	if ((*(unsigned char*) 0x114ffe20 & 1) == 0) {
		return 0;
	}
admin_loop:
	i = ReceivePacketHeader((unsigned int*) 0x114ffe20);
	if (i == -1) {
		return 0;
	}
	if ((*(unsigned char*) 0x114ffe20 & 0x80) != 0) {
		pktbuf[0] = 2;
		QueuePlayerCommand((unsigned int*) 0x114ffe20, pktbuf);
		ClosePlayerConnection((unsigned int*) 0x114ffe20);
		return 0;
	}
	if ((*(unsigned char*) 0x114ffe20 & 1) != 0) {
		goto admin_loop;
	}
	return 0;
}

// STATUS: MATCHING
// ORIGIN: GAME
// SIZE: 131
// SYMBOL: _ProcessSendData
// FUNCTION: SERVER 0x1000a860
// ProcessSendData
// PROTOTYPE: int ProcessSendData(void)

void* __cdecl memcpy(void*, const void*, unsigned int);

int __cdecl ProcessSendData(void)
{
	unsigned int* p;
	int result;
	int* cmd;

	p = &g_player_slots;
	do {
		if (*p & 1) {
			result = SendPlayerData(p);
			for (;;) {
				if (result == -1) {
					return -1;
				}
				cmd = *(int**) ((char*) p + 0x2641f4);
				if (cmd == 0 || !(*p & 0x100)) {
					break;
				}
				memcpy((char*) p + 0xb1, cmd, 0x99);
				FreeCommandBuffer(p, *(int*) ((char*) p + 0x2641f4));
				*p = *p & ~0x100;
				result = SendPlayerData(p);
			}
			if (result == -1) {
				return -1;
			}
		}
		p = (unsigned int*) ((char*) p + 0x264264);
	} while ((int) p < 0x114ffe20);
	return 0;
}

// STATUS: RELOC
// ORIGIN: GAME
// BLOCKER: loop rotation / branch layout
// BLOCKER_DELTA: 70
// ANALYSIS: Iterates over g_player_slots. If a slot is connected, calls SendPlayerData. Next, if there are pending commands in outgoing_cmd_queue, copies them down into the local send_buffer, frees the command from the queue using FreeCommandBuffer, clears the flag indicating pending commands, and calls SendPlayerData again.
// SIZE: 170
// SYMBOL: _QueueCommandForProcessing
// ANALYSIS: Takes a raw command payload, pulls an available CommandPacket struct from incoming_cmd_freelist, populates it, calculates command type via 0x1000c710, and appends it to the tail of incoming_cmd_queue.
// SYMBOL: _QueueCommandForProcessing
// FUNCTION: SERVER 0x1000A8F0
// QueueCommandForProcessing
// PROTOTYPE: int __cdecl QueueCommandForProcessing(int player_slot, char * cmd_data)

void* memcpy(void*, const void*, unsigned int);

int __cdecl QueueCommandForProcessing(int player_slot, char* cmd_data)
{
	char* buf;
	int tail;

	buf = *(char**) (player_slot + 0x2641f8);
	if (buf == 0) {
		LogMessageInternal("D:\\Develop\\DieGildeAddOnServer\\server.c", 0x671, "Commandbuffer full!", 1);
		return -1;
	}
	*(int*) (player_slot + 0x2641f8) = *(int*) (buf + 0x95);
	memcpy(buf, cmd_data, 0x99);
	*(short*) (buf + 1) = get_command_type(buf);
	tail = *(int*) (player_slot + 0x2641f0);
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
	*(char**) (player_slot + 0x2641f0) = buf;
	return 0;
}

// STATUS: RELOC
// ORIGIN: GAME
// SIZE: 170
// SYMBOL: _QueuePlayerCommand
// ANALYSIS: Takes a raw command payload, pulls an available CommandPacket struct from outgoing_cmd_freelist, populates it, and appends it to the tail of outgoing_cmd_queue. | Get free command buffer from pool
// SYMBOL: _QueuePlayerCommand
// FUNCTION: SERVER 0x1000A9A0
// QueuePlayerCommand
// PROTOTYPE: int __cdecl QueuePlayerCommand(int player_slot, char * cmd_data)
void* memcpy(void*, const void*, unsigned int);

int __cdecl QueuePlayerCommand(int player_slot, char* cmd_data)
{
	char* buf;
	int tail;

	buf = *(char**) (player_slot + 0x2641fc);
	if (buf == 0) {
		LogMessageInternal("D:\\Develop\\DieGildeAddOnServer\\server.c", 0x6b0, "Commandbuffer full!", 1);
		return -1;
	}
	*(int*) (player_slot + 0x2641fc) = *(int*) (buf + 0x95);
	memcpy(buf, cmd_data, 0x99);
	*(short*) (buf + 1) = get_command_type(buf);
	tail = *(int*) (player_slot + 0x2641f4);
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
	*(char**) (player_slot + 0x2641f4) = buf;
	return 0;
}

// STATUS: EXACT
// ORIGIN: GAME
// SIZE: 97
// SYMBOL: _list_unlink_relink
// GHIDRA: FreeCommandBuffer
// FUNCTION: SERVER 0x1000AA50
// list_unlink_relink
// PROTOTYPE: void __cdecl list_unlink_relink(char * ctx, char * node)
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

// STATUS: MATCHING
// ORIGIN: GAME
// BLOCKER: comparison direction swap, instruction folding (lea vs mov), loop rotation / branch layout, zero-extend pattern (xor vs mov)
// SIZE: 639
// SYMBOL: _cm_ProcessCommandQueue
// BLOCKER_DELTA: 567
// ANALYSIS: Master Command Router. Iterates over every slot's incoming_cmd_queue. Evaluates commands via g_command_handlers. Upon validation, pushes valid commands to the sender's outgoing queue (to acknowledge) and broadcasts them to all other connected players' outgoing queues. Recognizes 0x05/0x06 to batch list and pass to ProcessEntityChain.
// FUNCTION: SERVER 0x1000aac0
// cm_ProcessCommandQueue
// PROTOTYPE: int cm_ProcessCommandQueue(void)

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

	slot = (unsigned int*) 0x10442cf0;

	do {
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
				result = ProcessEntityChain(type5);
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
				result = QueuePlayerCommand(&g_connections[player_idx * 0x264264], node);
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
				result = QueuePlayerCommand(conn, node);
				if (result == -1) {
					return -1;
				}
			}

			*(int*) (node + 4) = -1;
			i = 0;
			conn = &g_connections[0];
			do {
				if (i != (unsigned int) node[3] && (*conn & 1) != 0) {
					result = QueuePlayerCommand(conn, node);
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

		slot = (unsigned int*) ((unsigned char*) slot + 0x264264);
	} while ((unsigned int) slot < 0x11764010);

	return 0;
}

// STATUS: RELOC
// ORIGIN: GAME
// SIZE: 768
// SYMBOL: _LogWinsockError
// FUNCTION: SERVER 0x1000ad40
// LogWinsockError
// PROTOTYPE: void __cdecl LogWinsockError(int param_1)

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

// STATUS: MATCHING
// ORIGIN: GAME
// BLOCKER: instruction folding (lea vs mov), zero-extend pattern (xor vs mov)
// SIZE: 372
// SYMBOL: _InitBuildingTypeTable
// FUNCTION: SERVER 0x1000b040
// InitBuildingTypeTable

/* Auto-generated Ghidra decompilation */
// BLOCKER_DELTA: 365
// PROTOTYPE: void InitBuildingTypeTable(void)

void InitBuildingTypeTable(void)
{
	unsigned int* table_ptr;
	char type_index;
	int count;

	table_ptr = (unsigned int*) 0x101de5a0;
	for (count = 0; count != 0; count = count + -1) {
		*table_ptr = 0;
		table_ptr = table_ptr + 1;
	}
	for (count = 0xfc; count != 0; count = count + -1) {
		*table_ptr = 0;
		table_ptr = table_ptr + 1;
	}
	for (count = 0; count != 0; count = count + -1) {
		*table_ptr = 0;
		table_ptr = table_ptr + 1;
	}
	type_index = '\0';
	table_ptr = (unsigned int*) 0x101de5a4;
	do {
		*(((char*) table_ptr) - 1) = type_index;
		*table_ptr = 0xffffffff;
		table_ptr[4] = 0xffffffff;
		table_ptr = (unsigned int*) (((char*) table_ptr) + 0x18);
		type_index = type_index + '\x01';
	} while ((char*) table_ptr < (char*) 0x101de994);

	*(unsigned char*) 0x101de5d8 = 2;
	*(unsigned char*) 0x101de5a8 = 1;
	*(unsigned char*) 0x101de5c0 = 1;
	*(unsigned char*) 0x101de5f0 = 3;
	*(unsigned char*) 0x101de608 = 4;
	*(unsigned char*) 0x101de620 = 4;
	*(unsigned char*) 0x101de638 = 5;
	*(unsigned char*) 0x101de650 = 6;
	*(unsigned char*) 0x101de668 = 7;
	*(unsigned char*) 0x101de680 = 7;
	*(unsigned char*) 0x101de698 = 8;
	*(unsigned char*) 0x101de6b0 = 9;
	*(unsigned char*) 0x101de6c8 = 10;
	*(unsigned char*) 0x101de6e0 = 0xb;
	*(unsigned char*) 0x101de6f8 = 0xc;
	*(unsigned char*) 0x101de710 = 0xd;
	*(unsigned char*) 0x101de728 = 0xe;
	*(unsigned char*) 0x101de740 = 0xf;
	*(unsigned char*) 0x101de758 = 0x10;
	*(unsigned char*) 0x101de770 = 0x11;
	*(unsigned char*) 0x101de788 = 0x12;
	*(unsigned char*) 0x101de7a0 = 0x13;
	*(unsigned char*) 0x101de7b8 = 0x14;
	*(unsigned char*) 0x101de7d0 = 0x15;
	*(unsigned char*) 0x101de7e8 = 0x16;
	*(unsigned char*) 0x101de800 = 0x17;
	*(unsigned char*) 0x101de818 = 0x18;
	*(unsigned char*) 0x101de830 = 0x19;
	*(unsigned char*) 0x101de848 = 0x1a;
	*(unsigned char*) 0x101de860 = 0x1b;
	*(unsigned char*) 0x101de878 = 0x1c;
	*(unsigned char*) 0x101de890 = 0x1d;
	*(unsigned char*) 0x101de8a8 = 0x1e;
	*(unsigned char*) 0x101de8c0 = 0x1f;
	*(unsigned char*) 0x101de8d8 = 0x20;
	*(unsigned char*) 0x101de8f0 = 0x21;
	*(unsigned char*) 0x101de908 = 0x22;
	*(unsigned char*) 0x101de920 = 0x23;
	*(unsigned char*) 0x101de938 = 0x24;
	*(unsigned char*) 0x101de950 = 0x25;
	*(unsigned char*) 0x101de968 = 0x26;
	*(unsigned char*) 0x101de980 = 0x27;
	return;
}
