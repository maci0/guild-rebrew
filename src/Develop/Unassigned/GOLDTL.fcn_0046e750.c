
/* ADDRESS: GOLDTL 0x0046e750 */
int __cdecl d2_PointInRect(int pointX, int pointY, int left, int top, int width, int height)
{
	if (pointX >= left && pointX <= left + width && pointY >= top && pointY <= top + height) {
		return 1;
	}
	return 0;
}
