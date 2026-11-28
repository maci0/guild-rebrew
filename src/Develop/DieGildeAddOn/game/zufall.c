/* Random-number helpers: their own object, the last game object of the link.
 * Both clients place these functions together, in this order, between the
 * trace unit (tr_*) and a vfs unit, apart from spiel.c. gm_RandomRange and
 * gm_RandomFloat01Squared are the clients' functions the server never calls;
 * /OPT:REF discards them. The file name is not attested; it sorts after
 * spiel.c, where the object links. */

extern float g_const_1_over_32767;

extern int __cdecl rand(void);
extern void __cdecl srand(unsigned int);
__declspec(dllimport) unsigned int __stdcall timeGetTime(void);
extern const float g_const_0_0;
extern float g_const_neg_1_0;

/* Returns a random integer in [0, n), or 0 for n == 0. */
/* ADDRESS: GOLDDE 0x00427ef0 */
/* ADDRESS: SERVERDE 0x10008640 */
int __cdecl gm_RandomMod(unsigned short n)
{
	if (n) {
		return rand() % n;
	}
	return 0;
}

/* Returns a random integer in [-n, n]. */
/* ADDRESS: GOLDTL 0x0042e430 */
int __cdecl gm_RandomRange(int n)
{
	return gm_RandomMod((unsigned short) (n + n + 1)) - n;
}

/* Returns a random float in [0, 1): rand() scaled by 1/32767. */
/* ADDRESS: GOLDDE 0x00427f10 */
/* ADDRESS: SERVERDE 0x10008660 */
double __cdecl gm_RandomFloat01(void)
{
	return (float) rand() * g_const_1_over_32767;
}

/* ADDRESS: GOLDDE 0x00427f30 */
/* ADDRESS: SERVERDE 0x10008680 */
float __cdecl gm_RandomQuadratic(void)
{
	float rand_val;

	rand_val = (float) gm_RandomFloat01();
	rand_val = (rand_val + rand_val) - 1.0f;
	return (rand_val < g_const_0_0 ? g_const_neg_1_0 : 1.0f) * rand_val * rand_val;
}

/* Returns gm_RandomFloat01() squared. */
/* ADDRESS: GOLDDE 0x00427f60 */
double __cdecl gm_RandomFloat01Squared(void)
{
	double v;

	v = gm_RandomFloat01();
	return v * v;
}

/* ADDRESS: GOLDDE 0x00427f70 */
/* ADDRESS: SERVERDE 0x100086b0 */
void __cdecl srv_SeedRandomWithTime(void)
{
	srand(timeGetTime());
}

/* ADDRESS: GOLDDE 0x00427f80 */
void __cdecl srv_SeedRandom(unsigned int seed)
{
	srand(seed);
}
