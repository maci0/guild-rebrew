/* ADDRESS: GOLD 0x00fd7ba0 */
extern char g_10432c0[];
/* ADDRESS: GOLD 0x00411be0 */

int __cdecl fcn_00411be0(char* p)
{
	int r;

	r = (unsigned int) (p - g_10432c0) / 992;
	if (r < 0 || r > 0x3f) {
		r = -1;
	}
	return r;
}
