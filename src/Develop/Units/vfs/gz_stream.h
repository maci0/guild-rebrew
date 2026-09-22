#ifndef GZ_STREAM_H
#define GZ_STREAM_H

/* Shared .gz descriptor, derived from zlib 1.1.3's gzio internals.
 *
 * The tree stages the gz code as two TUs (`vfs_c/check_header.c`,
 * `vfs_c/gzread.c`); both spelled the same struct inside their own file, so
 * it lifts here (shared-layout rule: two or more TUs -> leaves the .c). */
// SIZE 0x64 (sizeof on 32-bit: z_stream 0x38 + 9 ptr/int + mode + startpos;
// verified with an i686-mingw probe, round 1103)
typedef struct gz_stream {
    z_stream stream;
    int      z_err;   /* error code for last stream operation */
    int      z_eof;   /* set if end of input file */
    FILE     *file;   /* .gz file */
    Byte     *inbuf;  /* input buffer */
    Byte     *outbuf; /* output buffer */
    uLong    crc;     /* crc32 of uncompressed data */
    char     *msg;    /* error message */
    char     *path;   /* path name for debugging only */
    int      transparent; /* 1 if input file is not a .gz file */
    char     mode;    /* 'w' or 'r' */
    long     startpos; /* start of compressed data in file (header skipped) */
} gz_stream;

#endif /* GZ_STREAM_H */
