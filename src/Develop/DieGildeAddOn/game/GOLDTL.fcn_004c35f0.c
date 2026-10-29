extern double g_662b20;
extern int g_772e6c;
extern unsigned short g_774970;

float __cdecl gm_RandomFloat01(void);
int __cdecl fcn_004c3100(char*, int);
void __cdecl fcn_004c3030(int, int, char*, int);
float __cdecl fcn_0050f980(int, int, int);

/* Aggregates the city records by vote state, averages a weighted random score
 * over them and posts one of three localized messages for the winning side, or
 * -5 when that side has no identified representative. */
/* ADDRESS: GOLDTL 0x004c35f0 */
void __cdecl fcn_004c35f0(void)
{
	int* p;
	int average;
	int quiet;
	int loud;
	int quietId;
	int loudId;

	loud = 0;
	quiet = 0;
	loudId = 0xffff;
	quietId = 0xffff;
	average = 0;

	if (gm_RandomFloat01() > g_662b20) {
		return;
	}
	if (g_772e6c == 0) {
		g_772e6c = fcn_004c3100((char*) 0x68a674, 0);
	}
	for (p = (int*) 0x7e4260; (int) p < 0x7e42e0; p++) {
		if (*p == 0) {
			continue;
		}
		if (*(char*) (*p + 0x188) == 0) {
			continue;
		}
		if (*(char*) (*p + 9) == 0) {
			quiet++;
			quietId = *(unsigned short*) *p;
			average = (int) (fcn_0050f980(g_774970, quietId, 1) + average);
		} else {
			loud++;
			loudId = *(unsigned short*) *p;
			average = (int) (fcn_0050f980(g_774970, loudId, 1) + average);
		}
	}
	if (quiet + loud != 0) {
		average /= quiet + loud;
	}
	if (average < 0x32) {
		average = 0;
	} else if (average < 0x4b) {
		average = 1;
	} else if (average > 0x4b) {
		average = 2;
	}
	if (quiet >= loud) {
		if (quietId == 0xffff) {
			fcn_004c3030(-5, g_772e6c, (char*) 0x68a958, -1);
			return;
		}
		if (average == 0) {
			fcn_004c3030(quietId, g_772e6c, (char*) 0x68a968, -1);
			return;
		}
		if (average == 1) {
			fcn_004c3030(quietId, g_772e6c, (char*) 0x68a958, -1);
			return;
		}
		if (average >= 2) {
			fcn_004c3030(quietId, g_772e6c, (char*) 0x68a94c, -1);
			return;
		}
		return;
	}
	if (loudId == 0xffff) {
		if (quietId == loudId) {
			fcn_004c3030(-5, g_772e6c, (char*) 0x68a958, -1);
		}
		return;
	}
	if (average == 0) {
		fcn_004c3030(loudId, g_772e6c, (char*) 0x68a968, -1);
		return;
	}
	if (average == 1) {
		fcn_004c3030(loudId, g_772e6c, (char*) 0x68a958, -1);
		return;
	}
	if (average >= 2) {
		fcn_004c3030(loudId, g_772e6c, (char*) 0x68a94c, -1);
		return;
	}
}
