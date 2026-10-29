typedef struct StatRow StatRow;
struct StatRow {
	unsigned short id;
	short pad;
	int count;
	float ratio;
	float vc;
	float v10;
	float v14;
	float v18;
	float comb;
	int points;
};

int __cdecl fcn_004e8b40(unsigned char, int*);
int __cdecl gm_WalkEntityChain(unsigned short);
float __cdecl fcn_0050f980(int, int, int);
int __cdecl sprintf(char*, const char*, ...);

/* ADDRESS: GOLDTL 0x005091d0 */
void __cdecl fcn_005091d0(int* pn, StatRow* rows)
{
	int tmp[6];
	char buf[0x100];
	int n = 0;
	int i;
	int j;
	int sum;
	int cnt;
	int max = 0;
	int v;
	float fsum;
	float fmax;
	float fpts;
	float v1;
	unsigned char* p;
	StatRow* q;
	StatRow* r;

	q = rows;
	p = (unsigned char*) 0x7f4ca2;
	i = 0;
	do {
		if (n >= 8) {
			break;
		}
		if (*p == 6 || *p == 7 || *p == 5) {
			q->id = (unsigned short) i;
			n++;
			q++;
		}
		p += 0x21c;
		i++;
	} while ((int) p < 0x85a0a2);
	*pn = n;
	if (n == 0) {
		return;
	}
	for (i = 0; i < *pn; i++) {
		r = rows + i;
		sum = 0;
		p = (unsigned char*) (r->id * 0x21c + 0x7f4d20);
		for (j = 0; j < 5; j++) {
			sum += *p++;
		}
		r->v18 = (float) sum * 0.0007936508f;
		r->vc = (float) *(unsigned char*) (r->id * 0x21c + 0x7f4cad) * 0.11111111f;
		fcn_004e8b40(*(unsigned char*) (r->id * 0x21c + 0x7f4e06), tmp);
		v1 = (float) (tmp[2] & 0xff);
		fcn_004e8b40(*(unsigned char*) (r->id * 0x21c + 0x7f4e09), tmp);
		r->v10 = ((float) (tmp[2] & 0xff) + v1) * 0.07692308f;
		fsum = 0.0f;
		cnt = 0;
		for (j = 0, p = (unsigned char*) 0x7f4ca2; (int) p < 0x85a0a2; j++, p += 0x21c) {
			if (j == r->id) {
				continue;
			}
			if (*(unsigned short*) (p - 2) == 0xffff) {
				continue;
			}
			if (*p == 6 || *p == 7 || *p == 5 || *p == 4) {
				fsum += fcn_0050f980(r->id, j, 1);
				cnt++;
			}
		}
		r->v14 = fsum * 0.01f / (float) cnt;
		v = gm_WalkEntityChain(r->id);
		if (v > 1) {
			v = gm_WalkEntityChain(r->id);
		} else {
			v = 1;
		}
		r->count = v;
		if (v > max) {
			max = v;
		}
	}
	fmax = (float) max;
	fpts = fmax * 0.0001f;
	for (i = 0; i < *pn; i++) {
		r = rows + i;
		r->ratio = (float) r->count / fmax;
		r->comb = 0.15f * (r->vc + r->v10 + r->v14) + 0.3f * r->ratio + 0.25f * r->v18;
		r->points = (int) (fpts * r->comb);
		sprintf(buf, "player %i: sum:%f points:%i verm\xf6gen:%i vermoegen_trend:%f ansehen:%f talente:%f amt:%f",
		        i, (double) r->comb, r->points, r->count, (double) r->ratio,
		        (double) r->v14, (double) r->v18, (double) r->v10);
	}
}
