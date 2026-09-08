#include <windows.h>
#include <stddef.h>

/* Game-local stdio stream object (MSVC6 _iobuf, _tmpfname omitted).
 * 7 members x 4 bytes = 0x1c. */
// SIZE 0x1c
typedef struct _iobuf {
    char* _ptr;    /* 0x00 */
    int _cnt;      /* 0x04 */
    char* _base;   /* 0x08 */
    int _flag;     /* 0x0c */
    int _file;     /* 0x10 */
    int _charbuf;  /* 0x14 */
    int _bufsiz;   /* 0x18 */
} CRT_FILE;

/* _flag bits: _IONBF|_IOMYBUF|_IOYOURBUF (unbuffered / user-visible buffer)
 * and _IOMYBUF|_IOYOURBUF (has a real buffer to stage through). */
#define _IOEOF  0x10
#define _IOERR  0x20

extern void __cdecl fcn_1001bb60(void*);  /* lock dispatch 0x1001bb60 */
extern void __cdecl fcn_1001bbb2(void*);  /* unlock dispatch 0x1001bbb2 */
extern void* __cdecl fcn_1001eab0(void*, const void*, size_t); /* memmove 0x1001eab0 */
extern int __cdecl fcn_1001e8b4(int, void*, size_t);           /* _write 0x1001e8b4 */
extern int __cdecl fcn_1001accd(CRT_FILE*);                    /* _flush 0x1001accd */
extern int __cdecl fcn_1001c083(int, CRT_FILE*);               /* _flsbuf 0x1001c083 */
extern int __cdecl fcn_1001eec1(int, void*, size_t);           /* _read 0x1001eec1 */
extern int __cdecl fcn_1001ede5(CRT_FILE*);                    /* _filbuf 0x1001ede5 */

// CFLAGS: /O1 /Gd
// FUNCTION: SERVER 0x1001a960 (was FUNCTION; provided by LIBCMT / library_msvc.h)

/* fwrite core (unlocked — the game's CRT has no per-call lock here).
 * Writes size*count bytes from buffer to the stream: staged through the
 * stream buffer when buffered, written directly via fcn_1001e8b4 (_write)
 * when the chunk is at least the block threshold, otherwise char-by-char
 * through fcn_1001c083 (_flsbuf).  Returns items written, or the partial
 * item count on error. */

size_t __cdecl fcn_1001a960(char* buffer, size_t size, size_t count, CRT_FILE* stream)
{
    char* buff = buffer;
    size_t bytes = size * count;
    size_t bytes_left = bytes;
    size_t threshold;
    size_t n;
    int r;

    if (bytes == 0)
        return 0;
    if (stream->_flag & 0x10c)
        threshold = stream->_bufsiz;
    else
        threshold = 0x1000;

    while (bytes_left != 0)
    {
        if ((stream->_flag & 0x108) && stream->_cnt != 0)
        {
            n = bytes_left < (size_t)stream->_cnt
                    ? bytes_left
                    : (size_t)stream->_cnt;
            fcn_1001eab0(stream->_ptr, buff, n);
            stream->_cnt -= n;
            stream->_ptr += n;
            bytes_left -= n;
            buff += n;
        }
        else if (bytes_left >= threshold)
        {
            if ((stream->_flag & 0x108) && fcn_1001accd(stream) != 0)
                return (bytes - bytes_left) / size;
            if (threshold != 0)
                n = bytes_left - bytes_left % threshold;
            else
                n = bytes_left;
            r = fcn_1001e8b4(stream->_file, buff, n);
            if (r == -1)
            {
                stream->_flag |= 0x20;
                return (bytes - bytes_left) / size;
            }
            buff += r;
            bytes_left -= r;
            if ((size_t)r < n)
            {
                stream->_flag |= 0x20;
                return (bytes - bytes_left) / size;
            }
            continue;
        }
        else
        {
            int c = *(signed char*)buff;

            if (fcn_1001c083(c, stream) == -1)
                return (bytes - bytes_left) / size;
            buff++;
            bytes_left--;
            threshold = stream->_bufsiz;
            if (stream->_bufsiz <= 0)
                threshold = 1;
        }
    }
    return count;
}

// CFLAGS: /O1 /Gd
// FUNCTION: SERVER 0x1001aa99 (was FUNCTION; provided by LIBCMT / library_msvc.h)

/* fread core (unlocked).  Reads size*count bytes into buffer: from the
 * stream buffer when buffered, directly via fcn_1001eec1 (_read) for large
 * chunks, otherwise char-by-char through fcn_1001ede5 (_filbuf).  Returns
 * items read, or the partial item count on EOF/error (sets _IOEOF/_IOERR). */

size_t __cdecl fcn_1001aa99(char* buffer, size_t size, size_t count, CRT_FILE* stream)
{
    char* buf = buffer;
    size_t bytes = size * count;
    size_t bytes_left = bytes;
    size_t threshold;

    if (bytes == 0)
        return 0;
    if (stream->_flag & 0x10c)
        threshold = stream->_bufsiz;
    else
        threshold = 0x1000;

    while (bytes_left != 0)
    {
        if ((stream->_flag & 0x10c) && stream->_cnt != 0)
        {
            size_t n = bytes_left < (size_t)stream->_cnt
                           ? bytes_left
                           : (size_t)stream->_cnt;
            fcn_1001eab0(buf, stream->_ptr, n);
            bytes_left -= n;
            stream->_cnt -= n;
            stream->_ptr += n;
            buf += n;
        }
        else if (bytes_left >= threshold)
        {
            size_t n;
            int r;

            if (threshold != 0)
                n = bytes_left - bytes_left % threshold;
            else
                n = bytes_left;
            r = fcn_1001eec1(stream->_file, buf, n);
            if (r == 0)
            {
                stream->_flag |= 0x10;
                return (bytes - bytes_left) / size;
            }
            if (r == -1)
            {
                stream->_flag |= 0x20;
                return (bytes - bytes_left) / size;
            }
            bytes_left -= r;
            buf += r;
        }
        else
        {
            int c = fcn_1001ede5(stream);

            if (c == -1)
                return (bytes - bytes_left) / size;
            *buf = (char)c;
            buf++;
            bytes_left--;
            threshold = stream->_bufsiz;
        }
    }
    return count;
}

// FUNCTION: SERVER 0x1001a931 (was FUNCTION; provided by LIBCMT / library_msvc.h)

/* Locked fwrite entry (PDB: _crt_locked_call4a).  Serializes the call with
 * the stream's own lock (fcn_1001bb60/fcn_1001bbb2, lock dispatch). */

size_t __cdecl fcn_1001a931(char* buffer, size_t size, size_t count, CRT_FILE* stream)
{
    size_t r;

    fcn_1001bb60(stream);
    r = fcn_1001a960(buffer, size, count, stream);
    fcn_1001bbb2(stream);
    return r;
}

// FUNCTION: SERVER 0x1001aa6a (was FUNCTION; provided by LIBCMT / library_msvc.h)

/* Locked fread entry (exported `fread` in the PDB).  Serializes the call
 * with the stream's own lock. */

size_t __cdecl fcn_1001aa6a(char* buffer, size_t size, size_t count, CRT_FILE* stream)
{
    size_t r;

    fcn_1001bb60(stream);
    r = fcn_1001aa99(buffer, size, count, stream);
    fcn_1001bbb2(stream);
    return r;
}
