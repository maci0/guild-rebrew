/* Intentionally empty: providing FatalAppExitA/IsBadWritePtr as local
 * functions does not remove KERNEL32 IAT entries while LIBCMT:mlock.obj
 * still references __imp__*. The fix is to fully replace mlock.obj.
 *
 * Re-confirmed by measurement: defining `BOOL WINAPI IsBadWritePtr(...)` here
 * emits _IsBadWritePtr@8, but sbheap.obj only ever references the indirect
 * slot __imp__IsBadWritePtr@8, which still resolves from KERNEL32.lib and the
 * import survives. Displacing sbheap.obj outright (sbh_pool.c + sbh_aliases.c)
 * is what actually removes it. */
