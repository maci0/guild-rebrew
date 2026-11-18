
/* ADDRESS: GOLDTL 0x0046e750 */
int __cdecl fcn_0046e750(int pointX, int pointY, int left, int top, int width, int height)
{
	if (pointX >= left && pointX <= left + width && pointY >= top && pointY <= top + height) {
		return 1;
	}
	return 0;
}
