/* vfs_ReadCompressed — gzip payload reader (0x10008A90).

 * Drives the zlib state machine over a stream whose deflate payload sits in
 * the VFS file at base_off + in_off: refills the input window with
 * fseek/fread, then either mirrors a stored block (flag == 0) or runs
 * inflate (flag != 0), folding every produced byte into the stream's
 * running crc32.  Returns the number of bytes produced, -1 on an I/O
 * failure, -100 when the stream has no input buffer and -102 when the
 * handle or stream pointer is null.
 *
 * Residual: obj 499 against the target's 492. The target loads and tests
 * `handle` before the two accumulator zero-stores; these are `volatile int`,
 * which fixes the frame but keeps the stores at the top of the body. Moving
 * the stores below the guard checks (first use is `return result` at the
 * avail_out test) drops the object to 475 at 26/492, so the target's order is
 * not a plain source-order reordering.
 *
 * Volatility probed per accumulator (2026-09-10, .scratch/rvc/probe.py, obj /
 * matched of 492): both volatile 499/138 (current), both plain 469/29, plain
 * with `int*` address-escaped aliases 469/29 (msvc6 promotes them anyway, so
 * the address-escape lever does not work here), `done` volatile only 505/131,
 * `result` volatile only 465/22. The volatile on `result` is load-bearing;
 * `done` costs more than it buys on its own, and neither field is individually
 * the target's 492. `unsigned int` and `long` give the identical 499/138.
 *
 * The candidate is missing a 5-instruction epilogue the target has
 * (pop esi / pop ebp / pop ebx / add esp,8 / ret), 7 bytes, while running 14
 * bytes longer elsewhere; the instruction streams are too misaligned to
 * localise it further until the prologue order is fixed.
 */

/* 2026-09-13 (round 110): the span is fixed by reading the volatile `done`
 * ONCE.  The reference reuses eax across the two tests
 * (`cmp eax,1 / je / test eax,eax / jne`); ours re-read the volatile between
 * them.  Hoisting the read into a block-scoped `int d` gives
 *
 *   obj 497 -> 481        COMDAT span 512 -> 496  (= the reference's)
 *   register-agnostic matched 176 -> 171
 *
 * The content cost is real and was accepted only because the span is worth
 * +18 points of whole-.text match; docs/TODO.md round 110.
 */
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
	volatile int done;
	volatile int result;
	unsigned int n;
	int i;
	char* out;
	unsigned int produced;

	done = 0;
	result = 0;
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
		if (s->avail_in == 0) {
			n = s->remaining;
			if (n > 0) {
				/* The clamped chunk length is a SEPARATE variable, not `n`
				 * itself.  The target materialises the constant first
				 * (`mov edi,0x4000` / `cmp eax,edi` / `jae` / `mov edi,eax`)
				 * and keeps the dead `test edi,edi` that follows it;
				 * clamping `n` in place makes msvc6 emit the other min shape
				 * (`cmp edi,0x4000` / `jbe` / `mov edi,0x4000`) and drop the
				 * check.  Measured: 499 -> 497 bytes, aligned 76.5% -> 79.0%. */
				i = 0x4000;
				if (n < 0x4000) {
					i = n;
				}
				if (i == 0) {
					return 0;
				}
				if (fseek(s->file, s->base_off + s->in_off, 0) != 0) {
					return -1;
				}
				if (fread(s->inbuf, i, 1, s->file) != 1) {
					return -1;
				}
				s->in_off = s->in_off + i;
				s->remaining = s->remaining - i;
				s->next_in = s->inbuf;
				s->avail_in = i;
			}
		}
		if (s->flag == 0) {
			n = (s->avail_out < s->avail_in) ? s->avail_out : s->avail_in;
			i = 0;
			if (n > 0) {
				do {
					s->next_out[i] = s->next_in[i];
					i++;
				} while (i < n);
			}
			s->crc = crc32(s->crc, (unsigned char*) s->next_out, n);
			s->cap = s->cap - n;
			s->avail_in = s->avail_in - n;
			{
				int acc = result;
				s->avail_out = s->avail_out - n;
				s->next_out = s->next_out + n;
				s->next_in = s->next_in + n;
				s->total_out = s->total_out + n;
				result = acc + n;
			}
		} else {
			produced = s->total_out;
			out = s->next_out;
			{
				int z;
				unsigned int crc;
				z = inflate(&s->next_in, 2);
				crc = s->crc;
				n = s->total_out - produced;
				done = z;
				s->crc = crc32(crc, (unsigned char*) out, n);
			}
			s->cap = s->cap - n;
			result = result + n;
			{
				int d;
				d = done;
				if (d == 1) {
					return result;
				}
				if (d != 0) {
					return d;
				}
			}
		}
	}
	if (done == 0) {
		return result;
	}
	return done;
}
