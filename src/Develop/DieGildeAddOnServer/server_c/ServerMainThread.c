// GLOBAL: SERVER 0x11764084
extern int g_max_players; /* 0x11764084 */
// GLOBAL: SERVER 0x11764088
extern int g_tick_rate;    /* 0x11764088 */
// FUNCTION: SERVER 0x100093a0
extern int g_tick_rate;    /* 0x11764088 */
extern int g_max_players; /* 0x11764084 */
#include "../../Units/Error/error.h"
#include "../../Units/m_alloc/m_alloc.h"

#include <stdio.h>
#include <string.h>
#include <windows.h>
#include <winsock2.h>
__declspec(dllimport) unsigned int __stdcall timeGetTime(void);
extern void __cdecl srand(unsigned int); /* CRT srand */

/* Command layer (local externs — server.c uses different signatures) */
int __cdecl cm_QueuePlayerCommand(unsigned int* player, unsigned char* data);
int __cdecl cm_ClosePlayerConnection(unsigned int* player_slot);
int __cdecl cm_ProcessCommandQueue(void);
/* Entity lifecycle (local externs) */
/* Network functions (local externs — signatures differ from net.h) */
int __cdecl srv_AcceptConnections(void);
void __cdecl srv_CleanupSockets(void);
int __cdecl srv_LoadBuf(void);
int __cdecl ProcessSendData(void);
int __cdecl SendBroadcastPacket(unsigned char* data, int size);

int __cdecl srv_RecvGame(void);
int __cdecl srv_Init(void);
int __cdecl sim_AdvanceGameClock(int* clock_state, int a2, int a3, int a4);
void __cdecl sim_SetSyncParams(int target, unsigned char type_id, unsigned int field_6, unsigned int field_10);

/* ServerMainThread: the main server orchestration loop.
 * PHASE 0: read game.ini config, init logging/sockets/game data.
 * PHASE 1 (Lobby): accept connections until every player has the
 *   0x800 ready flag; announce server info every 3s; handle
 *   disconnects (0x1000) and host disconnect (0x400).
 * PHASE 4 (Data send): stream the savegame to non-host clients in
 *   128-byte chunks (cmd 0x09), total size first (cmd 0x08).
 * PHASE 3 (Data receive): wait for host savegame data (flag 0x08).
 * PHASE 5 (Player allocation): wait for each player's character
 *   entity (flag 0x10).
 * PHASE 6 (Game loop): advance the game clock, broadcast sync
 *   packets (cmd 0x1E/0x20), process the command queue.
 *
 * Byte-exact against the reference in the linked build.  The match depends on:
 *   - globals addressed through symbols (g_connections, g_download_*,
 *     g_players_synced, ...), not raw integer addresses.  Through raw
 *     addresses msvc6 CSEs and allocates differently
 *     (docs/msvc6-c-shapes.md section 187): the transfer packet's
 *     store/push order, the payload `lea esi,[eax+ecx]`, the sync-block
 *     read order and several register choices all follow from it;
 *   - the transfer loop reads *transfer_progress for the -1 test, the
 *     packet offset and the payload address.  A local holding the value
 *     lets msvc6 substitute the compared constant into the offset store;
 *   - g_players_synced is cleared inside its scan loop, so msvc6 promotes
 *     it to edx and keeps the initial store of 1;
 *   - the transfer loop is `phase_complete = 0; while (phase_complete == 0)`;
 *     as a do/while the back-edge and exit branches swap. */


extern unsigned char g_connections[0x264264]; /* 0x101deb00: 8 slots of 0x264264 */
extern unsigned int g_download_slots[8]; /* 0x101deac8 */
extern char g_module_path[0x104]; /* 0x101de9a0 */
extern int g_current_year; /* 0x10035880 */
extern unsigned int g_download_buffer; /* 0x101deae8 */
extern int g_players_synced; /* 0x11764090: every player sent 0x20 */
extern unsigned int g_next_tick_time; /* 0x101deaf0 */
extern unsigned int g_download_total_size; /* 0x101deac0 */
extern int g_handler_started; /* 0x10034680 */
extern int g_clock_copy_mid; /* 0x10035888 */
extern unsigned short g_current_hour; /* 0x10035884 */
extern unsigned char g_host_flags; /* 0x101de464 */
extern short g_clock_copy_tail; /* 0x1003588c */
extern int g_game_speed_value; /* 0x1002c3f0 */

int __stdcall ServerMainThread(void* lpThreadParameter)
{
	char* module_path;
	char* ini_tail;
	unsigned int* player_slot;
	unsigned int* transfer_progress;
	unsigned int* payload_src;
	unsigned int* payload_dst;
	unsigned int connected_players;
	unsigned int now_tick;
	unsigned int current_tick;
	unsigned int last_announce_tick;
	unsigned int sync_timer;
	unsigned int sync_p0;
	unsigned int sync_p1;
	unsigned short sync_p2;
	int i;
	int phase_complete;
	unsigned int sent_bytes;
	unsigned int host_flags_word;
	unsigned int total_size;
	unsigned char host_flags;
	unsigned char cmd_buffer_primary[0x99];
	unsigned char cmd_buffer_secondary[0x99];
	unsigned int startup_cfg_words[27];
	char log_buffer[64];

	module_path = (char*) g_module_path;
	GetModuleFileNameA(0, module_path, 0x104);
	ini_tail = strrchr(module_path, 0x5c);
	*(unsigned int*) (ini_tail + 0) = *(unsigned int*) "\\game.ini";
	*(unsigned int*) (ini_tail + 4) = *(unsigned int*) ("\\game.ini" + 4);
	*(unsigned short*) (ini_tail + 8) = *(unsigned short*) ("\\game.ini" + 8);

	g_tick_rate = (int) GetPrivateProfileIntA("Config", "Port", 0x1d6b, module_path);
	g_max_players = 2;
	GetPrivateProfileStringA(
		"General",
		"GamePath",
		"\\project\\diegildeaddon\\game\\",
		(char*) 0x10029594,
		0x104,
		module_path
	);

	memcpy(startup_cfg_words, lpThreadParameter, 0x6a);

	if (*(unsigned short*) ((char*) startup_cfg_words + 2) == 1) {
		*((unsigned char*) startup_cfg_words + 0x27) = 0;
		*(unsigned int*) &g_max_players = *(unsigned int*) ((char*) startup_cfg_words + 0x26) & 0xff;
	}
	else if (*(unsigned short*) ((char*) startup_cfg_words + 2) == 4) {
		*((unsigned char*) startup_cfg_words + 0x27) = 0;
		*(unsigned int*) &g_max_players = *(unsigned int*) ((char*) startup_cfg_words + 0x26) & 0xff;
	}

	srv_Init();
	sprintf(log_buffer, "Waiting for %li Connection(s)\n", *(int*) &g_max_players);
	LogMessageInternal("D:\\Develop\\DieGildeAddOnServer\\server.c", 0x131, log_buffer, 1);

	srand(timeGetTime());
	last_announce_tick = 0;
	phase_complete = 0;
	while (phase_complete == 0) {
		if (*(int*) &g_handler_started != 0) {
			break;
		}
		connected_players = 0;
		player_slot = (unsigned int*) g_connections;
		do {
			if (*player_slot != 0) {
				connected_players = connected_players + 1;
			}
			player_slot = (unsigned int*) ((char*) player_slot + 0x264264);
		} while ((int) player_slot < (int) (g_connections + 0x1321320));

		srv_AcceptConnections();

		if (connected_players == *(unsigned int*) &g_max_players) {
			phase_complete = 1;
			for (player_slot = (unsigned int*) g_connections; (int) player_slot < (int) (g_connections + 0x1321320);
				player_slot = (unsigned int*) ((char*) player_slot + 0x264264)) {
				if ((*player_slot != 0) && ((*player_slot & 0x800) == 0)) {
					phase_complete = 0;
					goto lobby_check_announce;
				}
			}
			LogMessageInternal("D:\\Develop\\DieGildeAddOnServer\\server.c", 0x14e, "SERVER>>>> ALL PLAYER ARE READY", 1);
		}

	lobby_check_announce:
		now_tick = timeGetTime();
		if ((3000 < now_tick - last_announce_tick) || phase_complete) {
			*((unsigned char*) startup_cfg_words + 0x27) = (unsigned char) connected_players;
			SendBroadcastPacket((unsigned char*) 0x3039, (int) startup_cfg_words);
			last_announce_tick = timeGetTime();
		}

		if ((unsigned int) srv_LoadBuf() == 0xffffffff) {
			LogMessageInternal("D:\\Develop\\DieGildeAddOnServer\\server.c", 0x15f, "Datatransfer failed => terminating", 1);
			goto cleanup_and_exit;
		}

		if ((unsigned int) ProcessSendData() == 0xffffffff) {
			LogMessageInternal("D:\\Develop\\DieGildeAddOnServer\\server.c", 0x16a, "Datatransfer failed => terminating", 1);
			goto cleanup_and_exit;
		}

		player_slot = (unsigned int*) g_connections;
		do {
			if ((*player_slot & 0x1000) != 0) {
				if ((*player_slot & 0x400) != 0) {
					LogMessageInternal("D:\\Develop\\DieGildeAddOnServer\\server.c", 0x176, "Terminating, serving host requested <<END OF SESSION>>", 1);
					goto cleanup_and_exit;
				}
				cm_ClosePlayerConnection(player_slot);
			}
			player_slot = (unsigned int*) ((char*) player_slot + 0x264264);
		} while ((int) player_slot < (int) (g_connections + 0x1321320));

		Sleep(0x1e);
	}

	player_slot = (unsigned int*) g_connections;
	do {
		if ((*player_slot & 1) != 0) {
			*player_slot = (*player_slot & 0xfffffdff) | 0x4004;
		}
		player_slot = (unsigned int*) ((char*) player_slot + 0x264264);
	} while ((int) player_slot < (int) (g_connections + 0x1321320));

	i = 0;
	player_slot = (unsigned int*) g_connections;
	while ((int) player_slot < (int) (g_connections + 0x1321320)) {
		if ((*player_slot & 0x400) != 0) {
			goto host_slot_found;
		}
		player_slot = (unsigned int*) ((char*) player_slot + 0x264264);
		i = i + 1;
	}

	srv_CleanupSockets();

send_start_commands:
	Sleep(2000);
	i = 0;
	player_slot = (unsigned int*) g_connections;
	do {
		host_flags_word = *player_slot;
		if (host_flags_word != 0) {
			cmd_buffer_primary[0] = 4;
			cmd_buffer_primary[3] = 0xff;
			*(unsigned int*) (cmd_buffer_primary + 4) = 0xffffffff;
			*(unsigned int*) (cmd_buffer_primary + 0xc) = 0;
			cmd_buffer_primary[0x10] = (unsigned char) ((((host_flags_word & 8) != 0) ? 9 : 2));
			if (cm_QueuePlayerCommand(player_slot, cmd_buffer_primary) == -1) {
				goto cleanup_and_exit;
			}

			cmd_buffer_primary[0] = 0x20;
			cmd_buffer_primary[3] = 0xff;
			*(unsigned int*) (cmd_buffer_primary + 4) = 0xffffffff;
			*(unsigned int*) (cmd_buffer_primary + 0xc) = 0;
			cmd_buffer_primary[0x10] = 7;
			*(unsigned int*) (cmd_buffer_primary + 0x11) = (unsigned int) i;
			i = i + 1;
			if (cm_QueuePlayerCommand(player_slot, cmd_buffer_primary) == -1) {
				goto cleanup_and_exit;
			}
		}
		player_slot = (unsigned int*) ((char*) player_slot + 0x264264);
	} while ((int) player_slot < (int) (g_connections + 0x1321320));

	LogMessageInternal("D:\\Develop\\DieGildeAddOnServer\\server.c", 0x1ca, "Receiving Data\n", 1);
	phase_complete = 0;
	while (phase_complete == 0) {
		if (*(int*) &g_handler_started != 0) {
			break;
		}

		phase_complete = 1;
		player_slot = (unsigned int*) g_connections;
		while ((int) player_slot < (int) (g_connections + 0x1321320)) {
			if ((*player_slot & 8) != 0) {
				goto transfer_pending;
			}
			player_slot = (unsigned int*) ((char*) player_slot + 0x264264);
		}
		goto wait_start_io;

	host_slot_found:
		((unsigned int*) g_connections)[i * 0x99099] |= 8;
		goto send_start_commands;

	transfer_pending:
		phase_complete = 0;

	wait_start_io:
		if ((unsigned int) srv_LoadBuf() == 0xffffffff) {
			LogMessageInternal("D:\\Develop\\DieGildeAddOnServer\\server.c", 0x1df, "Datatransfer failed => terminating", 1);
			goto cleanup_and_exit;
		}

		if ((unsigned int) ProcessSendData() == 0xffffffff) {
			LogMessageInternal("D:\\Develop\\DieGildeAddOnServer\\server.c", 0x1df, "Datatransfer failed => terminating", 1);
			goto cleanup_and_exit;
		}

		Sleep(0x1e);
	}

	srv_RecvGame();
	LogMessageInternal("D:\\Develop\\DieGildeAddOnServer\\server.c", 0x1f9, "Initializing Client(s)\n", 1);
	if ((*(unsigned char*) &g_host_flags & 4) == 0) {
		LogMessageInternal("D:\\Develop\\DieGildeAddOnServer\\server.c", 0x1ff, "Sending data...", 1);
		phase_complete = 0;
		while (phase_complete == 0) {
			phase_complete = 1;
			player_slot = (unsigned int*) g_connections;
			transfer_progress = (unsigned int*) g_download_slots;
			do {
				if ((*player_slot & 4) != 0) {
					if (*transfer_progress == 0xffffffff) {
						total_size = *(unsigned int*) &g_download_total_size;
						cmd_buffer_primary[0] = 8;
						cmd_buffer_primary[3] = 0xff;
						*(unsigned int*) (cmd_buffer_primary + 4) = *transfer_progress;
						*(unsigned int*) (cmd_buffer_primary + 0xc) = 0;
						*(unsigned int*) (cmd_buffer_primary + 0x10) = total_size;
						if (cm_QueuePlayerCommand(player_slot, cmd_buffer_primary) == -1) {
							goto cleanup_and_exit;
						}
						*transfer_progress = 0;
					}
					else {
						payload_src = (unsigned int*) ((char*) *(void**) &g_download_buffer + *transfer_progress);
						payload_dst = (unsigned int*) (cmd_buffer_primary + 0x10);
						cmd_buffer_primary[0] = 9;
						cmd_buffer_primary[3] = 0xff;
						*(unsigned int*) (cmd_buffer_primary + 4) = 0xffffffff;
						*(unsigned int*) (cmd_buffer_primary + 0xc) = 0;
						memcpy(payload_dst, payload_src, 0x80);

						if (cm_QueuePlayerCommand(player_slot, cmd_buffer_primary) != -1) {
							*transfer_progress = *transfer_progress + 0x80;
						}
						else {
							LogMessageInternal("D:\\Develop\\DieGildeAddOnServer\\server.c", 0x228, "Error is not critical!\n", 1);
						}

						sent_bytes = *transfer_progress;
						if (sent_bytes >= *(unsigned int*) &g_download_total_size) {
							*player_slot = *player_slot & 0xfffffffb;
						}
					}

					phase_complete = 0;
				}

				transfer_progress = transfer_progress + 1;
				player_slot = (unsigned int*) ((char*) player_slot + 0x264264);
			} while ((int) transfer_progress < (int) (g_download_slots + 8));

			if ((unsigned int) srv_LoadBuf() == 0xffffffff) {
				LogMessageInternal("D:\\Develop\\DieGildeAddOnServer\\server.c", 0x23a, "Datatransfer failed => terminating", 1);
				goto cleanup_and_exit;
			}

			if ((unsigned int) ProcessSendData() == 0xffffffff) {
				LogMessageInternal("D:\\Develop\\DieGildeAddOnServer\\server.c", 0x23a, "Datatransfer failed => terminating", 1);
				goto cleanup_and_exit;
			}

			Sleep(0x1e);
		}
	}
	else {
		player_slot = (unsigned int*) g_connections;
		do {
			if ((*player_slot & 4) != 0) {
				*player_slot = *player_slot & 0xfffffffb;
			}
			player_slot = (unsigned int*) ((char*) player_slot + 0x264264);
		} while ((int) player_slot < (int) (g_connections + 0x1321320));
	}

	m_FreeTracked(*(void**) &g_download_buffer);
	host_flags = *(unsigned char*) &g_host_flags;

	/* the reference stores 0x101deae8 before 0x101deac0 (0x10009931,
	 * 0x10009937); the store order follows the source order here */
	*(void**) &g_download_buffer = (void*) 0;
	*(unsigned int*) &g_download_total_size = 0;
	if ((host_flags & 4) == 0) {
		LogMessageInternal("D:\\Develop\\DieGildeAddOnServer\\server.c", 0x262, "Waiting for allocation of Player(s)\n", 1);
		player_slot = (unsigned int*) g_connections;
		do {
			if ((*player_slot & 1) != 0) {
				*player_slot = *player_slot | 0x10;
			}
			player_slot = (unsigned int*) ((char*) player_slot + 0x264264);
		} while ((int) player_slot < (int) (g_connections + 0x1321320));

		phase_complete = 0;
		while (phase_complete == 0) {
			phase_complete = 1;
			player_slot = (unsigned int*) g_connections;
			while (phase_complete != 0) {
				if ((int) player_slot >= (int) (g_connections + 0x1321320)) {
					break;
				}
				if ((*player_slot & 0x10) != 0) {
					phase_complete = 0;
				}
				player_slot = (unsigned int*) ((char*) player_slot + 0x264264);
			}

			if ((unsigned int) srv_LoadBuf() == 0xffffffff) {
				LogMessageInternal("D:\\Develop\\DieGildeAddOnServer\\server.c", 0x278, "Datatransfer failed => terminating", 1);
				goto cleanup_and_exit;
			}

			if ((unsigned int) ProcessSendData() == 0xffffffff) {
				LogMessageInternal("D:\\Develop\\DieGildeAddOnServer\\server.c", 0x278, "Datatransfer failed => terminating", 1);
				goto cleanup_and_exit;
			}

			Sleep(0x1e);
		}
	}

	player_slot = (unsigned int*) g_connections;
	do {
		if ((*player_slot & 1) != 0) {
			cmd_buffer_secondary[0] = 4;
			cmd_buffer_secondary[3] = 0xff;
			*(unsigned int*) (cmd_buffer_secondary + 4) = 0xffffffff;
			*(unsigned int*) (cmd_buffer_secondary + 0xc) = 0;
			cmd_buffer_secondary[0x10] = 4;
			if (cm_QueuePlayerCommand(player_slot, cmd_buffer_secondary) == -1) {
				goto cleanup_and_exit;
			}
		}
		player_slot = (unsigned int*) ((char*) player_slot + 0x264264);
	} while ((int) player_slot < (int) (g_connections + 0x1321320));

	LogMessageInternal("D:\\Develop\\DieGildeAddOnServer\\server.c", 0x2a8, "Let's go!\n", 1);

	for (;;) {
		if (*(int*) &g_handler_started != 0) {
			*(int*) &g_handler_started = 0;
			return 0;
		}

		Sleep(0x1e);
		current_tick = GetTickCount();
		phase_complete = 0;
		player_slot = (unsigned int*) g_connections;
		while ((int) player_slot < (int) (g_connections + 0x1321320)) {
			if ((*player_slot != 0) && ((*player_slot & 0x40) != 0)) {
				goto check_sync_all_players;
			}
			player_slot = (unsigned int*) ((char*) player_slot + 0x264264);
		}
		goto process_pending_sync;

	check_sync_all_players:
		phase_complete = 0;
		player_slot = (unsigned int*) g_connections;
		while ((int) player_slot < (int) (g_connections + 0x1321320)) {
			if ((*player_slot != 0) && ((*player_slot & 0x40) == 0)) {
				phase_complete = 1;
				goto check_transfer_state;
			}
			player_slot = (unsigned int*) ((char*) player_slot + 0x264264);
		}

	process_pending_sync:
		player_slot = (unsigned int*) g_connections;
		do {
			if ((*player_slot != 0) && ((*player_slot & 0x40) != 0)) {
				LogMessageInternal("D:\\Develop\\DieGildeAddOnServer\\server.c", 0x2ce, "Usefull Sync", 1);
				*player_slot = *player_slot & 0xffffffbf;
				if (cm_QueuePlayerCommand(player_slot, (unsigned char*) ((char*) player_slot + 0x264154)) == -1) {
					goto cleanup_and_exit;
				}
			}
			player_slot = (unsigned int*) ((char*) player_slot + 0x264264);
		} while ((int) player_slot < (int) (g_connections + 0x1321320));

	check_transfer_state:
		if (*(int*) &g_players_synced == 0) {
			if (phase_complete) {
				goto game_loop_network_io;
			}

			*(int*) &g_players_synced = 1;
			player_slot = (unsigned int*) g_connections;
			do {
				if ((*player_slot != 0) && ((*player_slot & 0x20) == 0)) {
					*(int*) &g_players_synced = 0;
				}
				player_slot = (unsigned int*) ((char*) player_slot + 0x264264);
			} while ((int) player_slot < (int) (g_connections + 0x1321320));

			if (*(int*) &g_players_synced == 0) {
				goto game_loop_network_io;
			}

			player_slot = (unsigned int*) g_connections;
			do {
				if (*player_slot != 0) {
					*player_slot = *player_slot & 0xffffffdf;
				}
				player_slot = (unsigned int*) ((char*) player_slot + 0x264264);
			} while ((int) player_slot < (int) (g_connections + 0x1321320));
			*(unsigned int*) &g_next_tick_time = current_tick;
		}
		else if (phase_complete || (*(unsigned int*) &g_next_tick_time > current_tick)) {
			goto game_loop_network_io;
		}

		sim_AdvanceGameClock((int*) &g_current_year, 0, 1, 0);
		player_slot = (unsigned int*) g_connections;
		do {
			if (*player_slot != 0) {
				/* The clock struct at 0x10035880 is copied into the packet
				 * at cmd+0x10, so the 0x10035888 word lands at cmd+0x18.
				 * Target writes it as [esp+0x30]; the buffer base is
				 * esp+0x18 after the two argument pushes. */
				sync_timer = *(unsigned int*) &g_current_hour;
				sync_p0 = *(unsigned int*) &g_current_year;
				sync_p2 = *(unsigned short*) &g_clock_copy_tail;
				sync_p1 = *(unsigned int*) &g_clock_copy_mid;
				*(unsigned int*) (cmd_buffer_primary + 0x10) = sync_p0;
				*(unsigned int*) (cmd_buffer_primary + 0x14) = sync_timer;
				cmd_buffer_primary[0] = 0x1e;
				cmd_buffer_primary[3] = 0xff;
				*(unsigned int*) (cmd_buffer_primary + 4) = 0xffffffff;
				*(unsigned int*) (cmd_buffer_primary + 0xc) = 0;
				*(unsigned int*) (cmd_buffer_primary + 0x18) = sync_p1;
				*(unsigned short*) (cmd_buffer_primary + 0x1c) = sync_p2;
				if (cm_QueuePlayerCommand(player_slot, cmd_buffer_primary) == -1) {
					goto cleanup_and_exit;
				}
			}
			player_slot = (unsigned int*) ((char*) player_slot + 0x264264);
		} while ((int) player_slot < (int) (g_connections + 0x1321320));

		if (*(unsigned short*) &g_current_hour >= 0x17) {
			phase_complete = 1;
			player_slot = (unsigned int*) g_connections;
			do {
				if (*player_slot != 0) {
					cmd_buffer_secondary[0] = 0x20;
					cmd_buffer_secondary[3] = 0xff;
					*(unsigned int*) (cmd_buffer_secondary + 4) = 0xffffffff;
					*(unsigned int*) (cmd_buffer_secondary + 0xc) = 0;
					cmd_buffer_secondary[0x10] = 2;
					if (phase_complete) {
						*(unsigned int*) (cmd_buffer_secondary + 0x11) = 1;
						phase_complete = 0;
					}
					else {
						*(unsigned int*) (cmd_buffer_secondary + 0x11) = 0;
					}
					if (cm_QueuePlayerCommand(player_slot, cmd_buffer_secondary) == -1) {
						goto cleanup_and_exit;
					}
					*(int*) &g_players_synced = 0;
				}
				player_slot = (unsigned int*) ((char*) player_slot + 0x264264);
			} while ((int) player_slot < (int) (g_connections + 0x1321320));

			sent_bytes = *(unsigned int*) &g_current_year + 1;
			*(unsigned int*) &g_current_year = sent_bytes;
			sim_SetSyncParams(&g_current_year, 6, 0, 0);
		}

		*(unsigned int*) &g_next_tick_time += *(unsigned int*) &g_game_speed_value;

	game_loop_network_io:
		if ((unsigned int) srv_LoadBuf() == 0xffffffff) {
			LogMessageInternal("D:\\Develop\\DieGildeAddOnServer\\server.c", 0x348, "Datatransfer failed => terminating", 1);
			goto cleanup_and_exit;
		}

		if ((unsigned int) ProcessSendData() == 0xffffffff) {
			LogMessageInternal("D:\\Develop\\DieGildeAddOnServer\\server.c", 0x348, "Datatransfer failed => terminating", 1);
			goto cleanup_and_exit;
		}

		if (cm_ProcessCommandQueue() == -1) {
			goto cleanup_and_exit;
		}
	}

cleanup_and_exit:
	srv_CleanupSockets();
	return 0;
}
