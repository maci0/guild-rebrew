extern float g_662b20;
extern int g_772e6c;
extern unsigned short g_774970;

float __cdecl fcn_0042e450(void);
int __cdecl fcn_004c3100(char*, int);
int __cdecl fcn_004c3030(int, int, char*, int);
float __cdecl fcn_0050f980(int, int, int);
int __cdecl fcn_0064d228(void);

/* ADDRESS: GOLDTL 0x004c35f0 */
void __cdecl fcn_004c35f0(void)
{
	int* p;
	int zeroId;
	int noneId;
	int zeroCount;
	int noneCount;
	int lastRand;
	int level;
	int total;

	lastRand = 0;
	zeroCount = 0;
	noneCount = 0;
	zeroId = 0xffff;
	noneId = 0xffff;

	if (fcn_0042e450() > g_662b20) {
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
			zeroCount++;
			zeroId = *(unsigned short*) *p;
			fcn_0050f980(g_774970, zeroId, 1);
		} else {
			noneCount++;
			noneId = *(unsigned short*) *p;
			fcn_0050f980(g_774970, noneId, 1);
		}
		lastRand = fcn_0064d228();
	}

	total = zeroCount + noneCount;
	if (total != 0) {
		lastRand /= total;
	}
	if (lastRand < 0x32) {
		level = 0;
	} else if (lastRand < 0x4b) {
		level = 1;
	} else if (lastRand > 0x4b) {
		level = 2;
	} else {
		level = lastRand;
	}

	if (zeroCount >= noneCount) {
		if (zeroId == 0xffff) {
			fcn_004c3030(-5, g_772e6c, (char*) 0x68a958, -1);
			return;
		}
		if (level == 0) {
			fcn_004c3030(zeroId, g_772e6c, (char*) 0x68a968, -1);
			return;
		}
		if (level == 1) {
			fcn_004c3030(zeroId, g_772e6c, (char*) 0x68a958, -1);
			return;
		}
		if (level >= 2) {
			fcn_004c3030(zeroId, g_772e6c, (char*) 0x68a94c, -1);
			return;
		}
		return;
	}

	if (noneId == 0xffff) {
		if (zeroId == noneId) {
			fcn_004c3030(-5, g_772e6c, (char*) 0x68a958, -1);
		}
		return;
	}
	if (level == 0) {
		fcn_004c3030(noneId, g_772e6c, (char*) 0x68a968, -1);
		return;
	}
	if (level == 1) {
		fcn_004c3030(noneId, g_772e6c, (char*) 0x68a958, -1);
		return;
	}
	if (level >= 2) {
		fcn_004c3030(noneId, g_772e6c, (char*) 0x68a94c, -1);
		return;
	}
}
