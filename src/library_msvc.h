/* CRT initialization is stock crt0dat.obj code. _cinit is external;
 * _initterm is private to that member and has no game-callable declaration.
 * Managed sizes are45 and26. Complete native code/operand checks and the
 * raw server.map identify LIBCMT:crt0dat.obj; see docs/TODO.md. */

/* Gold LIBC classifications. Comments only; no declarations and no storage.
 * 0x5dedd8 _fsopen / __fsopen, fopen.obj, 32 bytes.
 * 0x5dedf8 fopen / _fopen, fopen.obj, 19 bytes.
 * 0x5defef ctime / _ctime, ctime.obj, 25 bytes.
 * 0x5e5157 _getstream / __getstream, stream.obj, 120 bytes.
 * 0x5e4fe7 _openfile / __openfile, _open.obj, 368 bytes.
 * 0x5e5269 asctime / _asctime, asctime.obj, 174 bytes.
 * 0x5e533f localtime / _localtime, localtim.obj, 352 bytes.
 * Not a raw-link provider. */

#if 0
// MSVC CRT library symbols for SERVER (matchable by PDB name)
// These functions come from LIBCMT.lib (static CRT, /MT)
// Not compiled - annotation-only markers for reccmp matching


// _fclose


// __fclose_lk


// _sprintf


// _ftell



// __ftell_lk



// _fseek



// _strrchr



// _ctime


// _fopen


// _time


// _exit



// __exit



// __cexit


// __errno


// ___doserrno


// _malloc



// __nh_malloc


// __malloc


// _fwrite



// _fread



// __fread



// _free



// __fflush_lk



// __flush



// crt_locked_putc



// _strncpy



// _strchr



// _strstr



// __fpmath



// _toupper



// _srand_impl



// _rand



// __ftol



// _printf



// _realloc



// __CRT_INIT@12



// __DllMainCRTStartup@12



// __amsg_exit



// __initstdio



// crt_fcloseall_thunk



// __lock_file



// __unlock_file



// __close



// __free_osfhnd



// __stbuf



// _strlen



// __openfile



// __getstream



// __flsbuf



// __output



// __ioinit



// __lseek



// __lseek_lk



// ___loctotime_t



// __mlock



// __munlock



// __mtinit



// __getptd



// __freeptd



// ___heap_select



// __heap_term



// ___sbh_heap_init



// ___sbh_free_block



// ___sbh_alloc_block



// ___sbh_alloc_new_region



// ___sbh_alloc_new_group



// ___sbh_resize_block



// ___old_sbh_new_region



// ___old_sbh_decommit_pages



// ___old_sbh_find_block



// ___old_sbh_alloc_block



// ___old_sbh_alloc_block_from_page



// ___old_sbh_resize_block



// __except_handler3



// __local_unwind2



// __write_lk



// _memmove



// __filbuf



// __read_lk



// __forcdecpt



// __cropzeros



// __positive



// __fassign



// __cftoe



// __cftof



// __cfltcvt



// ___crtLCMapStringA



// __isctype



// _strcat



// __setenvp



// __setargv



// ___crtGetEnvironmentStringsA



// __NMSG_WRITE



// _calloc



// __fcloseall



// __alloc_osfhnd



// __open_osfhandle



// __get_osfhandle



// __lock_fhandle



// __sopen



// _wctomb



// __wctomb_lk



// __aulldiv



// __aullrem



// __tzset



// _strncmp



// _memset



// __controlfp



// __tolower



// __ld12tod



// __atodbl



// __atoldbl



// __fptostr



// __fltout2



// ___dtold



// __fptrap



// _strcmp



// _strcspn



// _strpbrk



// ___crtGetStringTypeA



// __setmbcp



// __chsize_lk



// _atoi



// _getenv



// ___add_12



// ___shl_12



// ___shr_12



// ___strgtold12



// __ld12cvt



// __strnicmp



// __setmode_lk



// __allmul



// __mbsnbicoll



// ___ld12mul



// ___crtCompareStringA



// _strncnt



// ___crtsetenv



// __mbschr



// __strdup



// --- CRT internal functions (custom Ghidra names, no PDB symbols) ---


// _fputs



// _crt_locked_read



// _SeekFileHandleUnlocked



// _doexit



// lock_0d



// unlock_0d



// __initterm



// _dosmaperr



// unlock_09a



// unlock_09b



// _crt_locked_call4a



// unlock_09c



// unlock_09d



// __alloca_probe



// signal_lock



// __flsall



// init_fptrs



// crt_toupper



// _memmove2



// unlock_09e



// _unlock_9



// _lock_stream



// _unlock_stream



// _free_buf



// crt_cond_cleanup



// _write_char



// _write_multi_char



// _write_string



// _stream_read_dword



// _stream_read_qword



// _stream_read_word



// _ioterm



// _asctime



// _format_digits



// _localtime



// crt_delete_cs



// crt_delete_locks



// crt_close_handle



// __initptd



// __callnewh



// crt_get_osver



// crt_heap_init



// crt_find_entry



// __sbh_decommit_pages



// update_page_entry



// _seh_filter



// _ValidateEH3RN



// _EH3_save_context_entry



// _EH3_save_context



// exsup



// seh_local_unwind_thunk



// crt_write_wrap



// _crt_lseek_wrap



// _commit



// crt_const_call



// ___IsNonwritableInCurrentImage



// __IsProcessorFeaturePresent



// __ecvt



// __fcvt



// ___cfltcvt_g



// _crt_strcpy_advance



// CopyCString



// _parse_cmdline



// __FF_MSGBANNER



// unlock_09f



// unlock_09g



// free_osfhnd



// slot_unlock



// slot_check_flag



// crt_buf_alloc



// crt_once_init



// _crt_locked_call



// __isindst_lk



// cvtdate



// _gmtime_lk



// call_with_zero



// _strtoxl



// clear_bit_call



// crt_cvt_osflag



// _abstract_cw



// crt_tolower_wrapper



// _check_bits_clear



// set_bit_range



// ___sbh_dealloc_bitmap



// copy_3dwords



// zero_12bytes



// check_all_zero



// ___sbh_bitmap_shift



// wrapper_ctx1



// wrapper_ctx2



// __crtGetACP_getcodepage



// code_translate



// CrtIoInfoInit



// _setSBUpLow



// _crt_cinit_once



// ___crtMessageBoxA



// overflow_add



// __stricmp



// __allmul_slow



// __wenvsetup



// _mantold_shl



// _crt_env_search



// _copy_environ



// --- zlib internal functions (custom Ghidra names, not in PDB) ---


// bit_reverse



// free_wrap



// ___ld12cvt


#endif


// __cinit

/* Gold uses the stock single-threaded free.obj body; raw-map provider pending. */

// _free
