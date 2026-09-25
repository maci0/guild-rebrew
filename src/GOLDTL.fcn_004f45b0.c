// FUNCTION: GOLDTL 0x4f45b0
// SIZE: 147

extern unsigned char g_773d75;

/* The clamp is a macro expansion: the inner MINV is evaluated twice, which
 * gives the reference its repeated 100000.0 compare and shared arm. */
#define MAXV(a, b) (((a) > (b)) ? (a) : (b))
#define MINV(a, b) (((a) < (b)) ? (a) : (b))

double __cdecl log10(double x);
int __cdecl fcn_0050dac0(unsigned short id);
int __cdecl fcn_0050b710(int a, unsigned char k);
int __cdecl fcn_0050b750(int a, unsigned char k);

int __cdecl fcn_004f45b0(unsigned short* e)
{
	double x;
	int pr;

	pr = fcn_0050b710(fcn_0050dac0(*e), g_773d75);
	x = pr;
	x = MAXV(MINV(100000.0, x), 10000.0);
	x = x / (log10(x) + 1.0) * 0.1f;
	return fcn_0050b750((int) x, g_773d75);
}
