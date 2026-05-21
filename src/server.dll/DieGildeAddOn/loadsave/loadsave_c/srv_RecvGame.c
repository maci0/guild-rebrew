#include "../../../Units/Error/error.h"
#include "../../../Units/m_alloc/m_alloc.h"
#include "../../../Units/vfs/vfs.h"
#include "../../game/entity.h"

#include <stdlib.h>

int __cdecl AllocGraveyardField(int);
extern int g_1002576c[];
extern int g_1002575c[];
extern void amt_FindEntity26(int);
extern void amt_FindEntity27(int);
extern char gm_RandomMod(int);
extern unsigned char __ftol();
extern void gm_AddOrAccumulateObject(int, int, int);
extern char g_100a9820[];
extern char g_1014d8e0[];
extern char g_10139820[];
int __cdecl ls_ReadVfsDataChecked(void* outBuffer, int elementSize, int elementCount, void* streamCtx);
extern int g_save_version;
extern int g_1002d4f0;
extern int g_1002d4f4;
extern char g_1002d4f8;
extern char g_1002d4fc;
extern int g_query_base;
extern int DAT_10035450;
int __cdecl ls_LoadGraveyardData(int stream_ctx, int dest_buf);
int __cdecl ahm_AllocAhmInfo(int building, int slot);
extern int g_file_version; /* 0x1002d4ec */
;
extern int g_entity_array_ptr; /* 0x1014d8c0 */
;
extern int g_101de454; /* 0x101de454 */
;
extern int g_101de55c; /* 0x101de55c */
;
extern unsigned int gm_LookupEntityRecordById(unsigned int);
extern int gm_ResolveEntityById(void**, void**, void**, int);
extern void gm_EntitySetField(void);
extern int g_101deae8;
extern int g_101deac0;
extern int g_101de560;
extern int g_save_info[2];
extern int OpenVfsStream(char*, char*, int);
int ls_LoadSavegameHeader(int, char*);
int ls_LoadExistingEntities(int);
unsigned int ls_LoadBuildingEntityState(unsigned int);
int ls_LoadDynamicEntities(void*);
int ls_LoadEntities(int);
int ls_LoadTownData(int);
extern int amt_fio_LoadAemter(int, int);
extern unsigned int ls_ID2Ptr(void);

/* Loads graveyard-specific data from a save file. Reads
 * production slots, worker assignments, and field states
 * for graveyard buildings. */

// FUNCTION: SERVER 0x10014260
// srv_RecvGame

int srv_RecvGame(void)
{
	int file_handle;
	int load_status;
	char* entity_state_ptr;

	file_handle = OpenVfsStream((char*) g_101deae8, (char*) g_101deac0, (int) (const char*) 0x1002944c);
	if (file_handle == 0) {
		LogMessageInternal(
			"D:\\Develop\\DieGildeAddOn\\loadsave\\loadsave.c",
			0x11fe,
			"ls_RecvGame(): Can\'t open File",
			1
		);
		m_FreeTracked((void*) g_101de560);
		g_101de560 = 0;
		return 0;
	}
	ls_LoadSavegameHeader(file_handle, (char*) g_save_info);
	if (((g_save_info[1] & 2) == 0) || (0x1005a < g_save_info[0]) || (g_save_info[0] < 0x10013)) {
		LogMessageInternal(
			"D:\\Develop\\DieGildeAddOn\\loadsave\\loadsave.c",
			0x120a,
			"srv_RecvGame(): Can\'t load Counter",
			1
		);
		CloseVfsStream(file_handle);
		m_FreeTracked((void*) g_101de560);
		g_101de560 = 0;
		return 0;
	}
	*(int*) 0x1003546c = 0;
	load_status = ls_ReadVfsDataChecked((void*) 0x10030b6c, 4, 1, (void*) file_handle);
	if (load_status != 0) {
		load_status = ls_ReadVfsDataChecked((void*) 0x1176408c, 4, 1, (void*) file_handle);
		if (load_status != 0) {
			load_status = ls_ReadVfsDataChecked((void*) 0x10035880, 0xe, 1, (void*) file_handle);
			if (load_status != 0) {
				load_status = ls_ReadVfsDataChecked((void*) 0x10035439, 1, 1, (void*) file_handle);
				if (load_status != 0) {
					load_status = ls_ReadVfsDataChecked((void*) 0x1003546c, 4, 1, (void*) file_handle);
					if (load_status != 0) {
						load_status = ls_ReadVfsDataChecked((void*) 0x1003542c, 4, 1, (void*) file_handle);
						if (load_status != 0) {
							load_status = ls_ReadVfsDataChecked((void*) 0x10035430, 4, 1, (void*) file_handle);
							if (load_status != 0) {
								load_status = ls_ReadVfsDataChecked((void*) 0x10035434, 4, 1, (void*) file_handle);
								if (load_status != 0) {
									ls_ReadVfsDataChecked((void*) 0x10035440, 4, 1, (void*) file_handle);
									ls_ReadVfsDataChecked((void*) 0x101de580, 0x18, 1, (void*) file_handle);
									if (g_save_version >= 0x10030) {
										ls_ReadVfsDataChecked((void*) 0x10030b70, 4, 1, (void*) file_handle);
									}
									if (g_save_version >= 0x1003d) {
										ls_ReadVfsDataChecked((void*) 0x10035408, 4, 1, (void*) file_handle);
									}
									else {
										*(int*) 0x10035408 = 1000000;
									}
									load_status = ls_LoadExistingEntities(file_handle);
									if (load_status != 0) {
										load_status = ls_LoadBuildingEntityState(file_handle);
										if (load_status == 0) {
											LogMessageInternal(
												"D:\\Develop\\DieGildeAddOn\\loadsave\\loadsave.c",
												0x123d,
												"LoadGame(): Can\'t load Buildings",
												1
											);
											CloseVfsStream(file_handle);
											m_FreeTracked((void*) g_101de560);
											g_101de560 = 0;
											return 0;
										}
										load_status = ls_LoadDynamicEntities((void*) file_handle);
										if (load_status == 0) {
											LogMessageInternal(
												"D:\\Develop\\DieGildeAddOn\\loadsave\\loadsave.c",
												0x1246,
												"srv_RecvGame(): Can\'t load Dynasties",
												1
											);
											CloseVfsStream(file_handle);
											m_FreeTracked((void*) g_101de560);
											g_101de560 = 0;
											return 0;
										}
										load_status = ls_LoadEntities(file_handle);
										if (load_status == 0) {
											LogMessageInternal(
												"D:\\Develop\\DieGildeAddOn\\loadsave\\loadsave.c",
												0x124f,
												"srv_RecvGame(): Can\'t load Players",
												1
											);
											CloseVfsStream(file_handle);
											m_FreeTracked((void*) g_101de560);
											g_101de560 = 0;
											return 0;
										}
										entity_state_ptr = (char*) 0x100358a2;
										do {
											if (*(unsigned short*) (entity_state_ptr - 2) != 0xffff &&
												*entity_state_ptr == '\x06') {
												*entity_state_ptr = '\x05';
											}
											entity_state_ptr = entity_state_ptr + 0x21c;
										} while ((int) entity_state_ptr < (int) 0x1009aca2);
										load_status = ls_LoadTownData(file_handle);
										if (load_status == 0) {
											LogMessageInternal(
												"D:\\Develop\\DieGildeAddOn\\loadsave\\loadsave.c",
												0x125b,
												"srv_RecvGame(): Can\'t load Towns",
												1
											);
											CloseVfsStream(file_handle);
											m_FreeTracked((void*) g_101de560);
											g_101de560 = 0;
											return 0;
										}
										if (g_save_version >= 0x10045) {
											load_status = amt_fio_LoadAemter(file_handle, g_save_version);
											if (load_status == 0) {
												LogMessageInternal(
													"D:\\Develop\\DieGildeAddOn\\loadsave\\loadsave.c",
													0x1266,
													"srv_RecvGame(): Can\'t load Aemter",
													1
												);
												CloseVfsStream(file_handle);
												return 0;
											}
										}
										load_status = ls_ID2Ptr();
										if (load_status != 0) {
											CloseVfsStream(file_handle);
											return 1;
										}
										LogMessageInternal(
											"D:\\Develop\\DieGildeAddOn\\loadsave\\loadsave.c",
											0x126f,
											"srv_RecvGame(): Can\'t convert IDs to Pointers",
											1
										);
										CloseVfsStream(file_handle);
										m_FreeTracked((void*) g_101de560);
										g_101de560 = 0;
										return 0;
									}
									LogMessageInternal(
										"D:\\Develop\\DieGildeAddOn\\loadsave\\loadsave.c",
										0x1234,
										"srv_RecvGame(): Can\'t load Objects",
										1
									);
									CloseVfsStream(file_handle);
									m_FreeTracked((void*) g_101de560);
									g_101de560 = 0;
									return 0;
								}
							}
						}
					}
				}
			}
		}
	}
	LogMessageInternal(
		"D:\\Develop\\DieGildeAddOn\\loadsave\\loadsave.c",
		0x121e,
		"srv_RecvGame(): Can\'t load Counter",
		1
	);
	CloseVfsStream(file_handle);
	m_FreeTracked((void*) g_101de560);
	g_101de560 = 0;
	return 0;
}
