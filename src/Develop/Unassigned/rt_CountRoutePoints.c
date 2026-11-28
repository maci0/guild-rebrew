
/* ADDRESS: GOLDTL 0x004be340 */
/* ADDRESS: GOLDDE 0x004abec0 */
int __cdecl rt_CountRoutePoints(char* p)
{
	int n;

	n = 0;
	while (p != 0) {
		p = *(char**) (p + 0x3c);
		n++;
	}
	return n;
}
