/* vfs_ReadCompressed: gzip payload reader (0x10008A90).
 *
 * Drives the zlib state machine over a stream whose deflate payload sits in
 * the VFS file at base_off + in_off: refills the input window with
 * fseek/fread, then either mirrors a stored block (flag == 0) or runs
 * inflate (flag != 0), folding every produced byte into the stream's
 * running crc32.  Returns the number of bytes produced, -1 on an I/O
 * failure, -100 when the stream has no input buffer and -102 when the
 * handle or stream pointer is null.
 *
 * Byte-exact.  `err` and `total` live in the reference's two stack slots
 * because three of the returns read them through volatile accesses;
 * every other access is plain.  Load-bearing spellings,
 * each measured against the reference object:
 *   - the post-loop tail as `if (err == 0) return total; return err;`:
 *     the `!= 0` form if-converts the err return into the shared epilogue
 *     and loses the reference's separate `return err` block;
 *   - `err = inflate(...)` as a plain store, so msvc6 schedules it after the
 *     `n` computation as the reference does (a volatile store pins it
 *     directly after the call);
 *   - the stored-block chunk as the `avail_out < avail_in` ternary, which
 *     loads avail_out first.
 * The previous body kept both accumulators volatile at declaration or at
 * every site and sat at 23 linked bytes over three documented "walls";
 * all three are gone in this body. */
// FUNCTION: GOLD 0x468420
// SIZE: 496
// FUNCTION: GOLDTL 0x465350
// SIZE: 496
// FUNCTION: SERVER 0x10008A90
// vfs_ReadCompressed

// SIZE 0x6c
typedef struct VFS_INFLATE {
	void* inbuf;            /* +0x00 read window */
	char* next_in;          /* +0x04 cursor into it */
	unsigned int avail_in;  /* +0x08 bytes left in it */
	char pad_00c[4];
	char* next_out;         /* +0x10 caller's output cursor */
	unsigned int avail_out; /* +0x14 space left at it */
	unsigned int total_out; /* +0x18 produced so far */
	char pad_01c[0x20];
	int in_off;             /* +0x3c consumed file offset */
	char pad_040[0x10];
	unsigned int crc;       /* +0x50 running checksum */
	char pad_054[4];
	unsigned int remaining; /* +0x58 compressed bytes not yet read */
	unsigned int cap;       /* +0x5c output size the caller asked for */
	void* file;             /* +0x60 VFS file handle */
	int flag;               /* +0x64 0 = stored block, 1 = deflate */
	int base_off;           /* +0x68 start of the payload */
} VFS_INFLATE;

extern unsigned int __cdecl crc32(unsigned int crc, unsigned char* buf, unsigned int len);
extern int __cdecl inflate(void* zstrm, int flush); /* 0x100058d0, zlib */
extern void* __cdecl fseek(void* stream, long offset, int whence);
extern unsigned int __cdecl fread(void* ptr, unsigned int size, unsigned int count, void* stream);

int __cdecl vfs_ReadCompressed(int handle, char* buf, unsigned int len)
{
	VFS_INFLATE* s;
	int err;
	int total;
	unsigned int n;
	unsigned int i;
	char* start;
	unsigned int before;

	err = 0;
	total = 0;
	if (handle == 0) {
		return -102;
	}
	s = *(VFS_INFLATE**) (handle + 0x7c);
	if (s == 0) {
		return -102;
	}
	if (s->inbuf == 0) {
		return -100;
	}
	if (len == 0) {
		return 0;
	}
	s->avail_out = len;
	s->next_out = buf;
	if (len > s->cap) {
		s->avail_out = s->cap;
	}
	while (s->avail_out > 0) {
		if (s->avail_in == 0 && s->remaining > 0) {
			n = 0x4000;
			if (s->remaining < 0x4000) {
				n = s->remaining;
			}
			if (n == 0) {
				return 0;
			}
			if (fseek(s->file, s->base_off + s->in_off, 0) != 0) {
				return -1;
			}
			if (fread(s->inbuf, n, 1, s->file) != 1) {
				return -1;
			}
			s->in_off += n;
			s->remaining -= n;
			s->next_in = s->inbuf;
			s->avail_in = n;
		}
		if (s->flag == 0) {
			n = (s->avail_out < s->avail_in) ? s->avail_out : s->avail_in;
			for (i = 0; i < n; i++) {
				s->next_out[i] = s->next_in[i];
			}
			s->crc = crc32(s->crc, (unsigned char*) s->next_out, n);
			s->cap -= n;
			s->avail_in -= n;
			s->avail_out -= n;
			s->next_out += n;
			s->next_in += n;
			s->total_out += n;
			total += n;
		} else {
			before = s->total_out;
			start = s->next_out;
			err = inflate(&s->next_in, 2);
			n = s->total_out - before;
			s->crc = crc32(s->crc, (unsigned char*) start, n);
			s->cap -= n;
			total += n;
			if (err == 1) {
				return total;
			}
			if (err != 0) {
				return *(volatile int*) &err;
			}
		}
	}
	if (err == 0) {
		return *(volatile int*) &total;
	}
	return *(volatile int*) &err;
}
