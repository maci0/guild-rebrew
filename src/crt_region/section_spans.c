/* Span annotations for bytes the link already emits.
 * Extern only: this file adds no initialized object, so raw .data
 * stays where the split link put it. Each array is the hole between
 * two named globals, named for the global that follows it.
 */

/* Eight player slots plus the admin slot, stride 0x264264. */
// GLOBAL: SERVER 0x101deb00
extern unsigned char g_connections[9 * 0x264264];

/* .data */
// GLOBAL: SERVER 0x10027000
extern unsigned char g_before_g_broadcast_ff[0x30];

// GLOBAL: SERVER 0x10027035
extern unsigned char g_text_before_Sending_Broadcast[0x23];

// GLOBAL: SERVER 0x10027059
extern unsigned char g_before_g_log_level_table[0x1f];

// GLOBAL: SERVER 0x100270e6
extern unsigned char g_before_g_log_default_name[0x2];

// GLOBAL: SERVER 0x100270f5
extern unsigned char g_before_g_crashdump_data[0xf];

// GLOBAL: SERVER 0x100272f8
extern unsigned char g_before_g_crashdump_tail[0x20];

// GLOBAL: SERVER 0x1002733d
extern unsigned char g_before_g_file_write_mode[0x1b];

// GLOBAL: SERVER 0x1002735b
extern unsigned char g_text_before_error_log_banner[0x1];

// GLOBAL: SERVER 0x1002735d
extern unsigned char g_text_before_Error_Handler_closed[0x4f];

// GLOBAL: SERVER 0x100273ad
extern unsigned char g_text_before_Fatal_Error_Abort_Program[0x17];

// GLOBAL: SERVER 0x100273c5
extern unsigned char g_text_before_FATAL_ERROR_s_lu_s[0x1b];

// GLOBAL: SERVER 0x100273e1
extern unsigned char g_text_before_ERROR_Handler_has_not_been[0x1b];

// GLOBAL: SERVER 0x100273fd
extern unsigned char g_text_before_error_title[0x27];

// GLOBAL: SERVER 0x10027425
extern unsigned char g_text_before_message_title[0x7];

// GLOBAL: SERVER 0x1002742d
extern unsigned char g_text_before_MESSAGE_s[0xb];

// GLOBAL: SERVER 0x10027439
extern unsigned char g_text_before_tModule_s_Line_lu_s[0xf];

// GLOBAL: SERVER 0x10027449
extern unsigned char g_text_before_Time_8lu_Module_s_Line[0x1b];

// GLOBAL: SERVER 0x10027465
extern unsigned char g_before_gz_magic[0x23];

// GLOBAL: SERVER 0x10027490
extern unsigned char g_text_before_m_pool_alloc_tp_m_pool[0x16d0];

// GLOBAL: SERVER 0x10028b61
extern unsigned char g_text_before_m_pool_get_free_tp_m_pool[0x17];

// GLOBAL: SERVER 0x10028b79
extern unsigned char g_text_before_Unknown_winsock_error_u[0x63];

// GLOBAL: SERVER 0x10028bdd
extern unsigned char g_text_before_WSAECONNRESET[0x1b];

// GLOBAL: SERVER 0x10028bf9
extern unsigned char g_text_before_WSAETIMEDOUT[0x12b];

// GLOBAL: SERVER 0x10028d25
extern unsigned char g_text_before_WSAECONNABORTED[0x7b];

// GLOBAL: SERVER 0x10028da1
extern unsigned char g_text_before_WSAEINVAL[0x9b];

// GLOBAL: SERVER 0x10028e3d
extern unsigned char g_text_before_WSAEMSGSIZE[0xd3];

// GLOBAL: SERVER 0x10028f11
extern unsigned char g_text_before_WSAEWOULDBLOCK[0x5b];

// GLOBAL: SERVER 0x10028f6d
extern unsigned char g_text_before_WSAESHUTDOWN[0x5b];

// GLOBAL: SERVER 0x10028fc9
extern unsigned char g_text_before_WSAEOPNOTSUPP[0x9f];

// GLOBAL: SERVER 0x10029069
extern unsigned char g_text_before_WSAENOTSOCK[0xfb];

// GLOBAL: SERVER 0x10029165
extern unsigned char g_text_before_WSAENETRESET[0x2f];

// GLOBAL: SERVER 0x10029195
extern unsigned char g_text_before_WSAEINPROGRESS[0x87];

// GLOBAL: SERVER 0x1002921d
extern unsigned char g_text_before_WSAEINTR[0x87];

// GLOBAL: SERVER 0x100292a5
extern unsigned char g_text_before_WSAENOTCONN[0x4b];

// GLOBAL: SERVER 0x100292f1
extern unsigned char g_text_before_WSAEFAULT[0x2b];

// GLOBAL: SERVER 0x1002931d
extern unsigned char g_text_before_WSAENETDOWN[0x63];

// GLOBAL: SERVER 0x10029381
extern unsigned char g_text_before_WSANOTINITIALISED[0x2f];

// GLOBAL: SERVER 0x100293b1
extern unsigned char g_text_before_Cant_set_SO_SNDBUF[0x13];

// GLOBAL: SERVER 0x100293c5
extern unsigned char g_text_before_Cant_set_SO_RCVBUF[0x1f];

// GLOBAL: SERVER 0x100293e5
extern unsigned char g_text_before_gzip_mode_rb[0x67];

// GLOBAL: SERVER 0x10029451
extern unsigned char g_before_g_gzip_magic_8b[0x3];

// GLOBAL: SERVER 0x10029455
extern unsigned char g_text_before_D_Develop_Units_vfs_vfs_c[0x3];

// GLOBAL: SERVER 0x10029459
extern unsigned char g_text_before_vfs_gz_compressed_file_s_i[0x1b];

// GLOBAL: SERVER 0x10029475
extern unsigned char g_text_before_fmt_hex_length[0x2f];

// GLOBAL: SERVER 0x100294a5
extern unsigned char g_text_before_This_is_Gilde_talking_can_you_h[0xc7];

// GLOBAL: SERVER 0x1002956d
extern unsigned char g_before_g_game_path[0x27];

// GLOBAL: SERVER 0x100297a0
extern unsigned char g_before_g_office_float_table[0x350];

// GLOBAL: SERVER 0x10029bb4
extern unsigned char g_before_g_office_role_templates[0x4];

// GLOBAL: SERVER 0x10029c58
extern unsigned char g_text_before_amt_cant_load_msetter[0x320];

// GLOBAL: SERVER 0x10029f79
extern unsigned char g_text_before_amt_cant_load_status[0x2b];

// GLOBAL: SERVER 0x10029fa5
extern unsigned char g_text_before_amt_cant_load_pcount[0x27];

// GLOBAL: SERVER 0x10029fcd
extern unsigned char g_text_before_amt_cant_load_mamt[0x27];

// GLOBAL: SERVER 0x10029ff5
extern unsigned char g_text_before_amt_cant_load_mplayerid[0x27];

// GLOBAL: SERVER 0x1002a01d
extern unsigned char g_text_before_amt_cant_load_id[0x2b];

// GLOBAL: SERVER 0x1002a049
extern unsigned char g_text_before_amt_count_mismatch[0x23];

// GLOBAL: SERVER 0x1002a06d
extern unsigned char g_text_before_D_Develop_DieGildeAddOn_game_ae[0x33];

// GLOBAL: SERVER 0x1002a0a1
extern unsigned char g_text_before_amt_cant_load_count[0x27];

// GLOBAL: SERVER 0x1002a0c9
extern unsigned char g_before_g_alchemy_one[0x27];

// GLOBAL: SERVER 0x1002a0f9
extern unsigned char g_text_before_D_Develop_DieGildeAddOn_game_al[0x13];

// GLOBAL: SERVER 0x1002a10d
extern unsigned char g_text_before_ahm_ExAllocAlchemist_array_over[0x33];

// GLOBAL: SERVER 0x1002a141
extern unsigned char g_text_before_ahm_ExAllocAlchemist_wrong_type[0x27];

// GLOBAL: SERVER 0x1002a169
extern unsigned char g_text_before_ahm_ExAllocAlchemist_cant_find[0x33];

// GLOBAL: SERVER 0x1002a19d
extern unsigned char g_before_g_alchemy_random_table[0x2f];

// GLOBAL: SERVER 0x1002c3fc
extern unsigned char g_before_g_chain_handler_table[0x1a4];

// GLOBAL: SERVER 0x1002c5a4
extern unsigned char g_text_before_cm_ChkChangeBits_Invalid_actio[0x460];

// GLOBAL: SERVER 0x1002ca05
extern unsigned char g_text_before_cm_ChkChangeBits_Invalid_Id[0x4f];

// GLOBAL: SERVER 0x1002ca55
extern unsigned char g_text_before_cm_ChkSetGebBesitzer_Invalid_I[0x1f];

// GLOBAL: SERVER 0x1002ca75
extern unsigned char g_text_before_cm_ChkCutsceneReady_failed[0x33];

// GLOBAL: SERVER 0x1002caa9
extern unsigned char g_text_before_Invalid_Commandtype_in_Execution[0x23];

// GLOBAL: SERVER 0x1002cacd
extern unsigned char g_text_before_Invalid_GI_Id_for_cmdt_ALLOC_B[0x23];

// GLOBAL: SERVER 0x1002caf1
extern unsigned char g_text_before_gm_AllocGebaeude_failed[0x43];

// GLOBAL: SERVER 0x1002cb35
extern unsigned char g_text_before_Invalid_GI_Id_for_cmdt_ALLOC_S[0x1b];

// GLOBAL: SERVER 0x1002cb51
extern unsigned char g_text_before_cm_ExAllocSpieler_gm_AllocSpie[0x3b];

// GLOBAL: SERVER 0x1002cb8d
extern unsigned char g_text_before_cm_ExChangePlayerIdentity_fail[0x63];

// GLOBAL: SERVER 0x1002cbf1
extern unsigned char g_text_before_cm_ExChangePlayerIdentity_exec[0x23];

// GLOBAL: SERVER 0x1002cc15
extern unsigned char g_text_before_cm_ExKillSpieler_Could_not_fin[0x53f];

// GLOBAL: SERVER 0x1002d155
extern unsigned char g_text_before_ex_set_owner_missing_a[0x53];

// GLOBAL: SERVER 0x1002d1a9
extern unsigned char g_text_before_ex_set_owner_missing_b[0x37];

// GLOBAL: SERVER 0x1002d1e1
extern unsigned char g_text_before_ex_set_owner_missing_c[0x33];

// GLOBAL: SERVER 0x1002d215
extern unsigned char g_text_before_cm_ExSetWohnsitz_Residence_is[0x2b];

// GLOBAL: SERVER 0x1002d241
extern unsigned char g_text_before_ex_set_home_missing_a[0x27];

// GLOBAL: SERVER 0x1002d269
extern unsigned char g_text_before_ex_set_home_missing_b[0x2f];

// GLOBAL: SERVER 0x1002d299
extern unsigned char g_text_before_cm_ExSetGebUpgrade_already_hi[0x27];

// GLOBAL: SERVER 0x1002d2c1
extern unsigned char g_text_before_cm_ExSetGebUpgrade_Could_not_f[0x2b];

// GLOBAL: SERVER 0x1002d2ed
extern unsigned char g_text_before_cm_ExEmployWorker_Illegal_gw[0x2b];

// GLOBAL: SERVER 0x1002d319
extern unsigned char g_text_before_cm_ExEmployWorker_Illegal_geb[0x23];

// GLOBAL: SERVER 0x1002d33d
extern unsigned char g_text_before_cm_ExKillTransporter_invalid_t[0x97];

// GLOBAL: SERVER 0x1002d3d5
extern unsigned char g_text_before_cm_ExCreateGeb_failed[0x2b];

// GLOBAL: SERVER 0x1002d401
extern unsigned char g_text_before_cm_ExCreateGeb_Could_not_find[0x1b];

// GLOBAL: SERVER 0x1002d41d
extern unsigned char g_before_g_file_version[0xcf];

// GLOBAL: SERVER 0x1002d4f9
extern unsigned char g_before_g_plant_info_table[0x37f];

// GLOBAL: SERVER 0x1002d888
extern unsigned char g_text_before_plt_SetPlantMap_Could_not_fin[0x108];

// GLOBAL: SERVER 0x1002d991
extern unsigned char g_text_before_D_Develop_DieGildeAddOn_auxilla[0x2f];

// GLOBAL: SERVER 0x1002d9c1
extern unsigned char g_text_before_plt_SetPlantMap_Map_is_not_al[0x2b];

// GLOBAL: SERVER 0x1002d9ed
extern unsigned char g_before_g_plant_pair_table[0x43];

// GLOBAL: SERVER 0x1002db90
extern unsigned char g_before_g_plant_flag[0x160];

// GLOBAL: SERVER 0x1002dcf4
extern unsigned char g_before_g_spiel_const_table[0x54];

// GLOBAL: SERVER 0x100308f4
extern unsigned char g_before_g_next_object_id[0x278];

// GLOBAL: SERVER 0x10030b85
extern unsigned char g_before_g_query_filter_extra1[0x3];

// GLOBAL: SERVER 0x10030b91
extern unsigned char g_before_g_query_filter_max_id[0x3];

// GLOBAL: SERVER 0x10030b9f
extern unsigned char g_before_g_stat_table[0x1];

// GLOBAL: SERVER 0x10030eec
extern unsigned char g_text_before_fmt_player_id[0x684];

// GLOBAL: SERVER 0x10031592
extern unsigned char g_text_before_alloc_spieler_bug[0x2];

// GLOBAL: SERVER 0x100315a9
extern unsigned char g_text_before_family_count_overflow[0x3];

// GLOBAL: SERVER 0x100315e3
extern unsigned char g_text_before_fmt_sp_id[0x1];

// GLOBAL: SERVER 0x10031602
extern unsigned char g_text_before_alloc_spieler_array_overflow[0x2];

// GLOBAL: SERVER 0x10031627
extern unsigned char g_before_FPinit[0x1b1];

// GLOBAL: SERVER 0x100317dc
extern unsigned char g_before_g_crt_exit_hook[0x14];

// GLOBAL: SERVER 0x100317f4
extern unsigned char g_before_g_lock_stream_table[0x4];

// GLOBAL: SERVER 0x100317f9
extern unsigned char g_before_locktable[0x2b3];

// GLOBAL: SERVER 0x10031b70
extern unsigned char g_before_g_old_sbh_region_head[0x8];

// GLOBAL: SERVER 0x10031b79
extern unsigned char g_before_g_block_alloc_threshold[0x2023];

// GLOBAL: SERVER 0x10033ba0
extern unsigned char g_before_g_rterrlist[0x350];

// GLOBAL: SERVER 0x10033f38
extern unsigned char g_before_g_panic_callback[0x6d8];

// GLOBAL: SERVER 0x1003461d
extern unsigned char g_before_g_array_count[0x7];

// GLOBAL: SERVER 0x10034644
extern unsigned char g_before_g_stream_pool[0x2c];

// GLOBAL: SERVER 0x10034671
extern unsigned char g_before_g_stream_count[0x7];

// GLOBAL: SERVER 0x10034684
extern unsigned char g_data_section_tail[0x97c];


/* .rdata */
/* Import slots. Names with a stdcall decoration are not C
 * identifiers; the marker's metadata name is the symbol. */
// DATA: SERVER 0x10024004
// DATA: SERVER 0x10024008
// DATA: SERVER 0x1002400c
// DATA: SERVER 0x10024010
// DATA: SERVER 0x10024014
// DATA: SERVER 0x10024018
// DATA: SERVER 0x1002401c
// DATA: SERVER 0x10024020
// DATA: SERVER 0x10024024
// DATA: SERVER 0x10024028
// DATA: SERVER 0x1002402c
// DATA: SERVER 0x10024030
// DATA: SERVER 0x10024034
// DATA: SERVER 0x10024038
// DATA: SERVER 0x1002403c
// DATA: SERVER 0x10024040
// DATA: SERVER 0x10024044
// DATA: SERVER 0x10024048
// DATA: SERVER 0x1002404c
// DATA: SERVER 0x10024050
// DATA: SERVER 0x10024054
// DATA: SERVER 0x10024058
// DATA: SERVER 0x1002405c
// DATA: SERVER 0x10024060
// DATA: SERVER 0x10024064
// DATA: SERVER 0x10024068
// DATA: SERVER 0x1002406c
// DATA: SERVER 0x10024070
// DATA: SERVER 0x10024074
// DATA: SERVER 0x10024078
// GLOBAL: SERVER 0x1002407c
extern unsigned char g_iat_after_LCMapStringW[0xc];

// DATA: SERVER 0x10024088
// DATA: SERVER 0x1002408c
// DATA: SERVER 0x10024090
// DATA: SERVER 0x10024094
// DATA: SERVER 0x10024098
// DATA: SERVER 0x1002409c
// DATA: SERVER 0x100240a0
// GLOBAL: SERVER 0x100240a4
extern unsigned char g_iat_after_GetCPInfo[0x1c];

// DATA: SERVER 0x100240c0
// DATA: SERVER 0x100240c4
// GLOBAL: SERVER 0x100240c8
extern unsigned char g_iat_after_ExitProcess[0x4];

// DATA: SERVER 0x100240cc
// DATA: SERVER 0x100240d0
// DATA: SERVER 0x100240d4
// DATA: SERVER 0x100240d8
// DATA: SERVER 0x100240dc
// DATA: SERVER 0x100240e0
// DATA: SERVER 0x100240e4
// DATA: SERVER 0x100240e8
// DATA: SERVER 0x100240ec
// DATA: SERVER 0x100240f0
// DATA: SERVER 0x100240f4
// GLOBAL: SERVER 0x100240f8
extern unsigned char g_iat_after_InitializeCriticalSection[0xc];

// DATA: SERVER 0x10024104
// DATA: SERVER 0x10024108
// DATA: SERVER 0x1002410c
// DATA: SERVER 0x10024110
// DATA: SERVER 0x10024114
// DATA: SERVER 0x10024118
// DATA: SERVER 0x1002411c
// GLOBAL: SERVER 0x10024120
extern unsigned char g_iat_after_TlsGetValue[0x4];

// DATA: SERVER 0x10024124
// GLOBAL: SERVER 0x10024128
extern unsigned char g_iat_after_RtlUnwind[0x4];

// DATA: SERVER 0x1002412c
// DATA: SERVER 0x10024130
// DATA: SERVER 0x10024134
// DATA: SERVER 0x10024138
// DATA: SERVER 0x1002413c
// DATA: SERVER 0x10024140
// GLOBAL: SERVER 0x10024144
extern unsigned char g_iat_after_LCMapStringA[0x4];

// DATA: SERVER 0x10024148
// DATA: SERVER 0x1002414c
// GLOBAL: SERVER 0x10024150
extern unsigned char g_iat_after_GetWindowTextA[0x4];

// DATA: SERVER 0x10024154
// GLOBAL: SERVER 0x10024158
extern unsigned char g_iat_after_timeGetTime[0x4];

// DATA: SERVER 0x1002415c
// DATA: SERVER 0x10024160
// DATA: SERVER 0x10024164
// DATA: SERVER 0x10024168
// DATA: SERVER 0x1002416c
// DATA: SERVER 0x10024170
// DATA: SERVER 0x10024174
// DATA: SERVER 0x10024178
// DATA: SERVER 0x1002417c
// DATA: SERVER 0x10024180
// DATA: SERVER 0x10024184
// DATA: SERVER 0x10024188
// DATA: SERVER 0x1002418c
// DATA: SERVER 0x10024190
// DATA: SERVER 0x10024194
// DATA: SERVER 0x10024198
// GLOBAL: SERVER 0x1002419c
extern unsigned char g_iat_after_closesocket[0x4];


// GLOBAL: SERVER 0x100245a0
extern unsigned char g_before_g_rdata_restore[0xd48];

// GLOBAL: SERVER 0x100252e9
extern unsigned char g_before_g_graveyard_const_a[0x397];

// GLOBAL: SERVER 0x10025684
extern unsigned char g_before_g_const_2[0x4];

// GLOBAL: SERVER 0x100256a8
extern const float g_const_neg_1_0f;

// GLOBAL: SERVER 0x100256ac
extern const float g_const_1_over_252;

// GLOBAL: SERVER 0x100256bc
extern const float g_const_0_2f;

// GLOBAL: SERVER 0x100256c0
extern const float g_const_2f;

// GLOBAL: SERVER 0x100256d8
extern unsigned char g_before_g_const_0_25[0x3c];


// GLOBAL: SERVER 0x100257cc
extern unsigned char g_before_g_const_half[0x4];

// GLOBAL: SERVER 0x100257d4
extern unsigned char g_before_g_const_one_d[0x4];

// GLOBAL: SERVER 0x100257e0
extern unsigned char g_before_g_const_0_2[0x30];


// GLOBAL: SERVER 0x10025f8c
extern unsigned char g_before_g_const_8[0x4];

// GLOBAL: SERVER 0x10025fa4
extern unsigned char g_before_g_const_896_0[0x4];

// GLOBAL: SERVER 0x10025fc0
extern unsigned char g_rdata_before_imports[0x648];

/* Import descriptors, name table, and export directory. postlink copies
 * this span from the reference; the raw link does not emit it. */
// GLOBAL: SERVER 0x10026608
extern unsigned char g_import_bookkeeping[0x879];


/* .bss */
// GLOBAL: SERVER 0x10035000
extern unsigned char g_before_g_sequence_counter[0x408];

// GLOBAL: SERVER 0x10035410
extern unsigned char g_before_g_next_family_index[0x1c];

// GLOBAL: SERVER 0x10035438
extern unsigned char g_before_g_current_season[0x1];

// GLOBAL: SERVER 0x1003543a
extern unsigned char g_before_g_active_player_count[0x2];

// GLOBAL: SERVER 0x1003544a
extern unsigned char g_before_g_dynasty_scan_count[0x2];

// GLOBAL: SERVER 0x10035455
extern unsigned char g_before_g_query_count[0x3];

// GLOBAL: SERVER 0x1003545f
extern unsigned char g_before_g_query_filter_base[0x5];

// GLOBAL: SERVER 0x1003547c
extern unsigned char g_before_osver[0x38];

// GLOBAL: SERVER 0x100354cc
extern unsigned char g_before_envp[0x4];

// GLOBAL: SERVER 0x100354d4
extern unsigned char g_before_pgmptr[0xc];

// GLOBAL: SERVER 0x100354e4
extern unsigned char g_before_g_crt_exit_tail_flag[0x4];

// GLOBAL: SERVER 0x100354e9
extern unsigned char g_before_C_Termination_Done[0x3];

// GLOBAL: SERVER 0x100354f0
extern unsigned char g_before_proc_attached[0xc];

// GLOBAL: SERVER 0x10035504
extern unsigned char g_before_error_mode[0x4];

// GLOBAL: SERVER 0x10035510
extern unsigned char g_before_g_new_handler_retry[0x8c];

// GLOBAL: SERVER 0x100355a8
extern unsigned char g_before_g_crt_module_filename[0x30];

// GLOBAL: SERVER 0x100356e4
extern unsigned char g_before_pfnMessageBoxA[0x154];

// GLOBAL: SERVER 0x10035844
extern unsigned char g_before_g_current_year[0x3c];

// GLOBAL: SERVER 0x10035886
extern unsigned char g_before_g_clock_copy_mid[0x2];

// GLOBAL: SERVER 0x1003588e
extern unsigned char g_before_g_slot_table[0x12];

// GLOBAL: SERVER 0x100358a8
extern unsigned char g_before_g_entity_ref_table[0x54];

// GLOBAL: SERVER 0x10035900
extern unsigned char g_before_g_entity_type_bytes[0x104];

// GLOBAL: SERVER 0x10035a05
extern unsigned char g_before_g_entity_records[0x7];

// GLOBAL: SERVER 0x1003660c
extern unsigned char g_before_g_entity_base[0x64694];

// GLOBAL: SERVER 0x1009aca1
extern unsigned char g_before_g_dynamic_entities[0x1];

// GLOBAL: SERVER 0x1009aca3
extern unsigned char g_before_g_some_limit[0x59];

// GLOBAL: SERVER 0x1009ad00
extern unsigned char g_before_g_entity_end[0xa60];

// GLOBAL: SERVER 0x1009b761
extern unsigned char g_before_g_player_record_dst[0x3];

// GLOBAL: SERVER 0x1009b768
extern unsigned char g_before_g_slot_array[0x8];

// GLOBAL: SERVER 0x1009b774
extern unsigned char g_before_g_entity_type_table[0xd4bc];

// GLOBAL: SERVER 0x100a8c3c
extern unsigned char g_before_g_entity_slot_table[0x58];

// GLOBAL: SERVER 0x100a8c98
extern unsigned char g_before_g_player_record_src[0x60];

// GLOBAL: SERVER 0x100a8cfc
extern unsigned char g_before_g_dispatch_table_a[0x90ba0];



// GLOBAL: SERVER 0x101de458
extern unsigned char g_before_g_save_info[0x8];


// GLOBAL: SERVER 0x101de564
extern unsigned char g_before_g_office_slots[0x3c];

// GLOBAL: SERVER 0x101de990
extern unsigned char g_before_g_module_path[0x10];

// GLOBAL: SERVER 0x101deaa4
extern unsigned char g_before_g_download_total_size[0x1c];

// GLOBAL: SERVER 0x101deaf4
extern unsigned char g_before_g_player_slot_table[0xc];

// GLOBAL: SERVER 0x11764098
extern unsigned char g_before_g_alloc_root_name[0x8];

// GLOBAL: SERVER 0x117640a8
extern unsigned char g_before_g_alloc_root_size_total[0x8];

// GLOBAL: SERVER 0x117640c8
extern unsigned char g_before_g_log_message_buffer[0x18];

// GLOBAL: SERVER 0x117640e1
extern unsigned char g_before_g_owner_window[0x1fff];

// GLOBAL: SERVER 0x117660e4
extern unsigned char g_before_g_log_buffer[0x1c];

// GLOBAL: SERVER 0x11766200
extern unsigned char g_before_g_log_file_handle[0x4];

// GLOBAL: SERVER 0x11766208
extern unsigned char g_before_sbh_pHeaderScan[0x230];

// GLOBAL: SERVER 0x1176643c
extern void *__sbh_pHeaderDefer;

// GLOBAL: SERVER 0x11766454
extern unsigned char g_before_g_stream_group_table[0xc];

// GLOBAL: SERVER 0x11766568
extern unsigned char g_before_nstream[0x1018];

// GLOBAL: SERVER 0x11767594
extern unsigned char g_bss_section_tail[0x8];
