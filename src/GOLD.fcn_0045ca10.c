int __cdecl fcn_0045c610(int, int, int);

/* ADDRESS: GOLD 0x0045ca10 */
void __cdecl fcn_0045ca10(int obj)
{
	unsigned int i;

	if ((*(unsigned char*) (obj + 0x211) & 4) == 0)
		return;
	i = 0;
	if (*(unsigned int*) 0xfb9264 > 0) {
		do {
			fcn_0045c610(obj, *(int*) (0xfb91e0 + i * 4), *(int*) 0x633738);
			i++;
		} while (i < *(unsigned int*) 0xfb9264);
	}
}
