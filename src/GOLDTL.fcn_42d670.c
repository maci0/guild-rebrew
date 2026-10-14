/* ADDRESS: GOLDTL 0x0149d188 */
extern int g_149d188[];
/* ADDRESS: GOLD 0x01432028 */
extern int g_149d188[];



int __cdecl fcn_0042d630(int);
int __cdecl m_FreeTracked(int);

void __cdecl fcn_0042d670(int a)
{
	int i;
	int x;
	i = fcn_0042d630(a);
	if (i == -1) {
		return;
	}
	x = g_149d188[i * 29];
	m_FreeTracked(x);
	g_149d188[i * 29] = 0;
}
