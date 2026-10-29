/*
 * Building animation callback.
 *
 * The millisecond stamp drives the animation: the delta to the previous call
 * is stored on the object, the geometry sync runs when the object is visible
 * and the per-building animation records are then advanced.
 *
 * Reconstructed range 0x432480..0x432517: the delta update, the geometry sync
 * guard and the animation record fetch. The native body continues at 0x432517
 * with the nested per-record animation walk through 0x433772; that part is not
 * reconstructed here.
 */

int __cdecl fcn_0045cbe0(int, int);

/* ADDRESS: GOLDTL 0x00432480 */
void __cdecl fcn_00432480(int a0, int a1)
{
	int d;
	int e;
	unsigned int ms;

	ms = (unsigned int) a1 & 0x7fffffff;
	d = ms - *(int*) (a0 + 0x40);
	*(int*) (a0 + 0x40) = ms;
	if (!d) {
		return;
	}
	if (*(int*) (a0 + 0x1ec)) {
		if ((a1 >= 0) && *(int*) (a0 + 0x1cc) &&
		    !(*(unsigned char*) (*(int*) (a0 + 0x1ec) + 0x163d) & 0x40) &&
		    (*(int*) (a0 + 0x218) == 4)) {
			fcn_0045cbe0(a0, ms);
		}
		e = *(int*) (a0 + 0x1ec);
	}
}
