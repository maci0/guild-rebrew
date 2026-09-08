/* Intentionally empty: providing FatalAppExitA/IsBadWritePtr as local
 * functions does not remove KERNEL32 IAT entries while LIBCMT:mlock.obj
 * still references __imp__*. The fix is to fully replace mlock.obj. */
