#include <string.h>

/* Seed the 6x6 control-point lattice, run the cumulative edge interpolation
 * and clear the duplicate corners where the rows meet. */
/* ADDRESS: GOLDTL 0x004d3800 */
void __cdecl fcn_004d3800(void)
{
	float* p;
	float t;
	int i;
	int j;
	int k;
	int n;

	memset((void*) 0x9b43e0, 0, 0x2d0);
	*(float*) 0x9b43e0 = 10.0f;
	*(float*) 0x9b43e4 = 10.0f;
	*(float*) 0x9b43f0 = 30.0f;
	*(float*) 0x9b43f4 = 50.0f;
	*(float*) 0x9b43f8 = 40.0f;
	*(float*) 0x9b43fc = 20.0f;
	*(float*) 0x9b4408 = 20.0f;
	*(float*) 0x9b440c = 20.0f;
	*(float*) 0x9b4410 = 80.0f;
	*(float*) 0x9b4414 = 20.0f;
	*(float*) 0x9b4420 = 0.0f;
	*(float*) 0x9b4424 = 0.0f;
	*(float*) 0x9b4428 = 70.0f;
	*(float*) 0x9b442c = 30.0f;
	*(float*) 0x9b4438 = 0.0f;
	*(float*) 0x9b443c = 0.0f;
	*(float*) 0x9b4440 = 50.0f;
	*(float*) 0x9b4444 = 50.0f;
	*(float*) 0x9b4450 = 0.0f;
	*(float*) 0x9b4454 = 0.0f;
	*(float*) 0x9b4458 = 10.0f;
	*(float*) 0x9b445c = 10.0f;
	*(float*) 0x9b4468 = 30.0f;
	*(float*) 0x9b446c = 50.0f;
	*(float*) 0x9b4470 = 80.0f;
	*(float*) 0x9b4474 = 20.0f;
	*(float*) 0x9b4480 = 0.0f;
	*(float*) 0x9b4484 = 0.0f;
	*(float*) 0x9b4488 = 80.0f;
	*(float*) 0x9b448c = 20.0f;
	*(float*) 0x9b4498 = 0.0f;
	*(float*) 0x9b449c = 0.0f;
	*(float*) 0x9b44a0 = 60.0f;
	*(float*) 0x9b44a4 = 40.0f;
	*(float*) 0x9b44b0 = 0.0f;
	*(float*) 0x9b44b4 = 0.0f;
	*(float*) 0x9b44b8 = 50.0f;
	*(float*) 0x9b44bc = 50.0f;
	*(float*) 0x9b44c8 = 0.0f;
	*(float*) 0x9b44cc = 0.0f;
	*(float*) 0x9b44d0 = 5.0f;
	*(float*) 0x9b44d8 = 5.0f;
	*(float*) 0x9b44e0 = 20.0f;
	*(float*) 0x9b44e4 = 70.0f;
	*(float*) 0x9b44e8 = 50.0f;
	*(float*) 0x9b44f0 = 10.0f;
	*(float*) 0x9b44f8 = 20.0f;
	*(float*) 0x9b44fc = 20.0f;
	*(float*) 0x9b4500 = 80.0f;
	*(float*) 0x9b4508 = 20.0f;
	*(float*) 0x9b4510 = 0.0f;
	*(float*) 0x9b4514 = 0.0f;
	*(float*) 0x9b4518 = 70.0f;
	*(float*) 0x9b4520 = 30.0f;
	*(float*) 0x9b4528 = 0.0f;
	*(float*) 0x9b452c = 0.0f;
	*(float*) 0x9b4530 = 50.0f;
	*(float*) 0x9b4538 = 50.0f;
	*(float*) 0x9b4540 = 0.0f;
	*(float*) 0x9b4544 = 0.0f;
	*(float*) 0x9b4548 = 20.0f;
	*(float*) 0x9b4550 = 80.0f;
	*(float*) 0x9b4558 = 0.0f;
	*(float*) 0x9b455c = 0.0f;
	*(float*) 0x9b4560 = 30.0f;
	*(float*) 0x9b4568 = 70.0f;
	*(float*) 0x9b4570 = 0.0f;
	*(float*) 0x9b4574 = 0.0f;
	*(float*) 0x9b4578 = 40.0f;
	*(float*) 0x9b4580 = 60.0f;
	*(float*) 0x9b4588 = 0.0f;
	*(float*) 0x9b458c = 0.0f;
	*(float*) 0x9b4590 = 60.0f;
	*(float*) 0x9b45a0 = 0.0f;
	*(float*) 0x9b45a4 = 0.0f;
	*(float*) 0x9b45b8 = 0.0f;
	*(float*) 0x9b45bc = 0.0f;
	*(float*) 0x9b45c8 = 0.0f;
	*(float*) 0x9b45e0 = 0.0f;
	*(float*) 0x9b45f8 = 0.0f;
	*(float*) 0x9b4600 = 0.0f;
	*(float*) 0x9b4604 = 0.0f;
	*(float*) 0x9b4610 = 0.0f;
	*(float*) 0x9b4618 = 0.0f;
	*(float*) 0x9b461c = 0.0f;
	*(float*) 0x9b4628 = 0.0f;
	*(float*) 0x9b4630 = 0.0f;
	*(float*) 0x9b4634 = 0.0f;
	*(float*) 0x9b4640 = 0.0f;
	*(float*) 0x9b4658 = 0.0f;
	*(float*) 0x9b4670 = 0.0f;
	*(float*) 0x9b4678 = 0.0f;
	*(float*) 0x9b467c = 0.0f;
	*(float*) 0x9b4688 = 0.0f;
	*(float*) 0x9b4690 = 0.0f;
	*(float*) 0x9b4694 = 0.0f;
	*(float*) 0x9b46a0 = 0.0f;
	*(float*) 0x9b46a8 = 0.0f;
	*(float*) 0x9b46ac = 0.0f;
	*(float*) 0x9b4598 = 40.0f;
	*(float*) 0x9b45a8 = 70.0f;
	*(float*) 0x9b45b0 = 30.0f;
	*(float*) 0x9b45c0 = 20.0f;
	*(float*) 0x9b45d0 = 10.0f;
	*(float*) 0x9b45d4 = 70.0f;
	*(float*) 0x9b45d8 = 30.0f;
	*(float*) 0x9b45e8 = 20.0f;
	*(float*) 0x9b45ec = 50.0f;
	*(float*) 0x9b45f0 = 100.0f;
	*(float*) 0x9b4608 = 100.0f;
	*(float*) 0x9b4620 = 100.0f;
	*(float*) 0x9b4638 = 20.0f;
	*(float*) 0x9b4648 = 10.0f;
	*(float*) 0x9b464c = 70.0f;
	*(float*) 0x9b4650 = 30.0f;
	*(float*) 0x9b4660 = 20.0f;
	*(float*) 0x9b4664 = 50.0f;
	*(float*) 0x9b4668 = 100.0f;
	*(float*) 0x9b4680 = 100.0f;
	*(float*) 0x9b4698 = 100.0f;

	p = (float*) 0x9b43e0;
	do {
		for (j = 5; j != 0; j--) {
			for (k = 0; k < 6; k++) {
				t = *p * 0.01;
				*p = t;
				if (k != 0) {
					*p = t + *(p - 1);
				}
				p++;
			}
		}
	} while (p < (float*) 0x9b46b0);
	for (i = 0; i < 6; i++) {
		for (j = 0; j < 5; j++) {
			for (k = 1; k < 6; k++) {
				p = (float*) 0x9b43e0 + (i * 5 + j) * 6 + k;
				for (n = 6 - k; n != 0; n--) {
					if (*p == *(p - 1)) {
						*p = 0.0f;
					}
					p++;
				}
			}
		}
	}
}
