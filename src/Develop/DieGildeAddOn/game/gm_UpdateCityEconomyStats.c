void __cdecl gm_PostPeriodicCityReport(void);
extern float gm_CityPopulation, gm_TargetCityPopulation;
/* ADDRESS: GOLDTL 0x004fb4e0 */
/* ADDRESS: GOLDDE 0x004e71f0 */
void __cdecl gm_UpdateCityEconomyStats(char* a)
{
	int count;
	int sum;
	int acc[5];
	float f14;
	float f18;
	char* rec;
	int j;
	unsigned char w;

	count = 0;
	sum = 0;
	*(int*) ((char*) 0x99f5e0 + 0x00) = *(int*) (a + 0x00);
	*(int*) ((char*) 0x99f5e0 + 0x04) = *(int*) (a + 0x04);
	*(int*) ((char*) 0x99f5e0 + 0x08) = *(int*) (a + 0x08);
	*(int*) ((char*) 0x99f5e0 + 0x0c) = *(int*) (a + 0x0c);
	*(int*) ((char*) 0x99f5e0 + 0x10) = *(int*) (a + 0x10);
	f14 = *(float*) (a + 0x14);
	*(float*) ((char*) 0x99f5e0 + 0x14) = f14;
	f18 = *(float*) (a + 0x18);
	*(float*) ((char*) 0x99f5e0 + 0x18) = f18;
	*(int*) ((char*) 0x99f5e0 + 0x1c) = *(int*) (a + 0x1c);
	*(int*) ((char*) 0x99f5e0 + 0x20) = *(int*) (a + 0x20);
	*(int*) ((char*) 0x99f5e0 + 0x24) = *(int*) (a + 0x24);
	*(int*) 0x99ec14 = *(int*) (a + 0x28);
	*(int*) 0x99f590 = *(int*) (a + 0x2c);
	*(int*) 0x99f594 = *(int*) (a + 0x30);
	*(int*) 0x99f598 = *(int*) (a + 0x34);
	*(unsigned short*) 0x99f59c = *(unsigned short*) (a + 0x38);
	gm_CityPopulation = f18;
	gm_TargetCityPopulation = f14;

	acc[0] = 0;
	acc[1] = 0;
	acc[2] = 0;
	acc[3] = 0;
	acc[4] = 0;
	for (rec = (char*) 0x7f4ca2; (int) rec < (int) 0x85a0a2; rec += 0x21c) {
		if (*(short*) (rec - 2) == -1) {
			continue;
		}
		if (*(unsigned char*) rec >= 0xa) {
			continue;
		}
		if (*(unsigned char*) (rec + 6) == 0) {
			continue;
		}
		count++;
		w = *(unsigned char*) (rec + 0xb);
		sum += w;
		sum += w * 4;
		for (j = 0; j < 5; j++) {
			acc[j] += *(unsigned char*) (rec + 0x7e + j);
		}
	}
	for (j = 0; j < 5; j++) {
		*(unsigned char*) (0x99f580 + j) = (unsigned char) ((double) acc[j] / (double) count);
	}
	*(unsigned char*) 0x99f585 = (unsigned char) ((double) sum / (double) count);
	gm_PostPeriodicCityReport();
}
