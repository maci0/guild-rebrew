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
 *
 * 2026-09-14 (matched 425 -> 447, matched-reloc 445 -> 467, obj 480 -> 496 =
 * the reference's span, real body 492): the missing 12 bytes were a whole
 * third exit.  The reference has THREE separate epilogues because its tail
 * returns re-READ the volatile `done` (`jne 0x10008c70` / `mov eax,[esp+0x14]`
 * / pops / ret) instead of returning the register that already holds it; with
 * `return d;` and `return t_done;` msvc6 needs no load and tail-merges both
 * onto the `return result` epilogue, which is 12 bytes shorter.  Spelling the
 * two returns `return *(volatile int*) &done;` restores exit C byte for byte.
 * The `d = *(volatile int*) &done;` read also moved up into the block that
 * follows the crc32 call, ahead of `s->cap -= n; result += n;`, which is where
 * the reference schedules it (`mov eax,[esp+0x28]` before `add esp,0x14`);
 * both tails then match from `sub ebx,edi` onward.
 * Residual 45 bytes: the clamp tests eax before materialising edi (`test
 * eax,eax` / `mov edi,eax` against `mov edi,eax` / `test edi,edi`), the
 * stored-block accumulator keeps `n` in edi (`add edi,eax` against `add
 * eax,edi`), the pre-call crc goes to ecx instead of edx, and the crc32
 * argument cleanup `add esp,0x14` is scheduled four instructions earlier than
 * the reference's.  Probed and inert on this body: `n + acc` for `acc + n`,
 * the old `result` read into a local before the call, `result += n` moved
 * above the crc32 call, the `done` read after `s->cap -= n` (446-459).
 *
 * 2026-09-14 (round 187) -- CLOSED.  The 24 remaining bytes are THREE walls
 * and nothing else; all 11 structural diffs reduce to them, so do not
 * re-probe this function without a new allocator finding.
 *   A (4B at 0x10008b2a, diffs 1-2): the clamp order above.  WALL per
 *     shapes 85 -- the pinned value is the CONSTANT 0x4000 and msvc6
 *     rematerialises an immediate at each use however the source scopes it,
 *     so there is no definition site to move.  Every alternative clamp shape
 *     is spent (ternary obj 512 = span violation/159, second local 155,
 *     `i < 1` 155, assign-first obj 512/146).
 *   B (2B at 0x10008be8, diffs 3-4): the accumulator direction; diff 4 is
 *     purely downstream of diff 3.  WALL by measurement -- splitting the
 *     spill (`acc = acc + n;` then the volatile store) scores 404/424, -44.
 *   C (18B at 0x10008c10-0x10008c2f, diffs 5-11): ONE fact, not seven.  The
 *     reference sinks `add esp,0x14` four instructions later, so it reads
 *     `result`/`done` at PRE-cleanup displacements [esp+0x24]/[esp+0x28]
 *     where we read post-cleanup [esp+0x14]/[esp+0x10] -- the pairs differ
 *     by exactly the 0x14 cleanup, and the edx-vs-ecx scratch choice is the
 *     same decision.  WALL, doubly confirmed: hoisting the reads below the
 *     crc32 call is BYTE-IDENTICAL to baseline (an independent proof that
 *     this schedule is a compiler fixed point), and a volatile `result` read
 *     before the crc store scores 446/466, -2.
 *     Shapes 86b does NOT apply -- its boundary requires the stores to
 *     differ in SOURCE order, and they do not; this is the scheduler sinking
 *     a stack cleanup, which C89 cannot express.
 *     AMENDED round 188: the fixed point is the CLEANUP PLACEMENT, not the
 *     argument reads.  A service-pack sweep found msvc-6.0-sp5-pp emits the
 *     reference's tail verbatim (`8b5e5c / 8b542424 / 894650 / 8b442428 /
 *     83c414`, i.e. pre-cleanup [esp+0x24]/[esp+0x28] with `add esp,0x14`
 *     sunk four instructions) and its mismatch list ENDS at offset 395.
 *     So group C is reachable -- just not from C89 under sp6.  Do not pin
 *     sp5-pp: it scores 461/492 here because it wrecks the 270-360
 *     midsection, and a per-function toolchain pin never reaches the linked
 *     bytes anyway (the CMake compiler is fixed by the toolchain file).
 *     See shapes 90.
 * Floor: 448/468 of 492 at real body 492 (= reference) and span 496.  Note
 * per shapes 88 that 496 is already the next multiple of 16 above 492, so
 * there is ZERO span headroom -- any edit adding one byte crosses to 512 and
 * breaks position alignment for every later symbol.
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
/* 2026-09-14 (matched 447 -> 448, matched-reloc 467 -> 468, aligned 191,
 * obj 496, real body 496 = the reference's): the one remaining non-relocation
 * byte in the head was the loop's ENTRY-guard displacement.  The reference's
 * `jbe` at 0x10008b0f targets the *result* epilogue (0x10008c59), not the
 * shared `done` test at 0x10008c51, because `done` is provably 0 on that edge.
 * Our volatile read at the post-loop test blocked that fold, so the `jbe`
 * landed on the merged test block.  Reading `done` PLAINLY at that one test --
 * the two `return` reads stay volatile -- reproduces the reference's target and
 * moves nothing else (the tail block 0x10008c51..0x10008c6f is unchanged, the
 * frame is unchanged, and the two separate epilogues survive).  Making the
 * whole tail plain instead collapses the frame (obj 480, matched 21): the
 * volatile reads there are what keep `done`'s and `result`'s memory homes, so
 * the qualifier is per *site*, not per variable (allocator Finding 61).
 * Probed and much worse on this body, all with the frame and the two epilogues
 * intact or not: ternary clamp (obj 512, matched 159), clamp through a second
 * local (155), `i < 1` for the zero test (155), assign-first clamp (obj 512,
 * 146), `n + acc` read through the volatile pointer for `acc` (416), dropping
 * the `acc` local entirely (400), plain `done` store (25), the in-loop `d` read
 * made plain (byte-identical), and hoisting the `s->cap`/`result` reads into
 * locals above the volatile read (byte-identical -- the scheduler reschedules
 * them back, so the 16-byte crc32-call schedule below is a fixed point).
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
	/* The accumulators are plain locals whose *accesses* carry the volatile
	 * qualifier, not the declarations.  Both spellings keep the values in
	 * memory, but a volatile *declaration* makes the two entry zero-stores
	 * scheduling barriers, so msvc6 keeps the `handle` load/test behind them;
	 * the reference loads and tests `handle` above the pushes
	 * (`mov eax,[esp+0xc]` / `push ebx` / `push ebp` / `push esi` /
	 * `test eax,eax` / `push edi` / store / store / `jne`).  Qualifying the
	 * use sites instead reproduces that prologue byte for byte. */
	int done;
	int result;
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
				*(volatile int*) &result = acc + n;
			}
		} else {
			produced = s->total_out;
			out = s->next_out;
			{
				int z;
				unsigned int crc;
				int d;
				z = inflate(&s->next_in, 2);
				crc = s->crc;
				n = s->total_out - produced;
				*(volatile int*) &done = z;
				s->crc = crc32(crc, (unsigned char*) out, n);
				d = *(volatile int*) &done;
				s->cap = s->cap - n;
				result = result + n;
				if (d == 1) {
					return *(volatile int*) &result;
				}
				if (d != 0) {
					return *(volatile int*) &done;
				}
			}
		}
	}
	if (done == 0) {
		return *(volatile int*) &result;
	}
	return *(volatile int*) &done;
}
