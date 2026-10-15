double __cdecl fcn_0050f980(int, int, int);
#include "Develop/DieGildeAddOn/game/spiel.h"
int __cdecl fcn_005c6270(void*, int);
int __cdecl abs(int);

/* ADDRESS: GOLD 0x004aab90 */
/* ADDRESS: GOLDTL 0x004aacb0 */

int __cdecl fcn_004aacb0(unsigned short* a1, unsigned short* a2, unsigned short* a3, int* a4)
{
	float d2;
	float q2;
	float d3;
	float q3;
	float s2;
	float s3;

	*a4 = 0;
	if (a1 == a3)
		return 0;
	if (a1 == a2)
		return 1;
	d2 = fcn_0050f980(*a2, *a1, 1);
	q2 = fcn_00507f10((char*) a2, 4);
	d3 = fcn_0050f980(*a3, *a1, 1);
	q3 = fcn_00507f10((char*) a3, 4);
	s2 = q2 * 0.34 + d2 * 0.66;
	s3 = q3 * 0.34 + d3 * 0.66;
	if (fcn_005c6270(a2, 0x2be) != 0)
		d2 += 0.2f;
	if (fcn_005c6270(a3, 0x2be) != 0)
		d3 += 0.2f;
	if (abs((int) (d2 - d3)) * 0.66 > abs((int) (q2 - q3)) * 0.33)
		*a4 = 1;
	else
		*a4 = 2;
	if (s2 - 5.0f > s3)
		return 1;
	if (s3 - 5.0f > s2)
		return 0;
	return 2;
}
