/* Aggregate the resident/visitor occupancy statistics into the caller's
   result block.  Entity counts come from the record array at 0x7f4ca0, the
   per-kind totals from the kind table at 0x696178, and the weight sums from
   the cell table at 0x99ef90. */

extern char g_7f4ca0[];          /* record array, stride 0x21c */
extern char g_868050[];          /* per-kind descriptor table */
extern char g_90e094[];          /* kind descriptor array, stride 0xa9 */
extern short g_696178[];         /* per-kind counters, 4 words each */
extern unsigned short g_696180;
extern float g_99ef90[];         /* cell table, 6 floats per entry */
extern float g_99ef94[];
extern float g_99f590[];
extern float g_6628a0;
extern float g_6628bc;
extern float g_6629c0;
extern float g_662a68;
extern double g_662908;
extern double g_6629c8;
extern double g_664e60;

void __cdecl fcn_004fad10(void);
int __cdecl fcn_004fa6f0(char*, int*, int*);
float __cdecl fcn_004fc520(void);
float __cdecl fcn_004fc3a0(int*);
double __cdecl fcn_004fc340(int*);

/* ADDRESS: GOLDTL 0x004faed0 */
void __cdecl fcn_004faed0(float* out)
{
	char* rec;
	char* ent;
	char* pos;
	unsigned char type;
	int total;
	int slot0_count;
	int slot1_count;
	int sum_a;
	int sum_b;
	int sum_c;
	int sum_d;
	int slot0_e;
	int slot1_e;
	int x;
	int y;
	int n;
	int idx;
	int limit;
	int* oi;
	float weight_a;
	float weight_b;
	float accum;
	float scale;
	float cell;
	float lit;
	float f;
	int buf_a[12];
	int buf_b[8];
	double w;

	oi = (int*) out;
	total = 0;
	slot0_count = 0;
	slot1_count = 0;
	sum_a = 0;
	sum_b = 0;
	sum_c = 0;
	sum_d = 0;
	slot0_e = 0;
	slot1_e = 0;
	weight_a = 0.0f;
	weight_b = 0.0f;
	accum = 0.0f;
	fcn_004fad10();
	for (rec = g_7f4ca0; rec < (char*) 0x85a0a0; rec += 0x21c) {
		if (*(short*) rec == -1) {
			continue;
		}
		if (*(unsigned char*) (rec + 2) != 0
		    && *(unsigned char*) (rec + 2) != 1) {
			continue;
		}
		total++;
		ent = *(char**) (rec + 0x16c);
		if (ent != 0) {
			pos = *(char**) (ent + 0x61);
			slot0_count++;
			if (pos != 0) {
				type = *(unsigned char*) ent;
				cell = *(unsigned char*) (g_868050 + type * 0x24d);
				if (!(cell >= 0x0b && cell <= 0x0d) && cell != 0x10) {
					if (fcn_004fa6f0(pos + 0x4c, &x, &y) != 0) {
						idx = y + x * 8;
						g_99ef94[idx * 6 + 1] = g_99ef94[idx * 6 + 1] + g_6628a0;
					}
				}
			}
		}
		ent = *(char**) (rec + 0x170);
		if (ent != 0) {
			pos = *(char**) (ent + 0x61);
			slot1_count++;
			if (pos != 0) {
				type = *(unsigned char*) ent;
				cell = *(unsigned char*) (g_868050 + type * 0x24d);
				if (!(cell >= 0x0b && cell <= 0x0d) && cell != 0x10) {
					if (fcn_004fa6f0(pos + 0x4c, &x, &y) != 0) {
						idx = y + x * 8;
						g_99ef94[idx * 6 + 1] = g_99ef94[idx * 6 + 1] + g_6628a0;
					}
				}
			}
		}
	}
	rec = g_90e094;
	for (n = 0x100; n != 0; n--) {
		type = *(unsigned char*) rec;
		if (type != 0 && type <= 0x43 && *(short*) (rec + 0x27) != -1) {
			weight_a = weight_a + *(unsigned short*) (g_696178 + type * 4);
			weight_b = weight_b + *(unsigned short*) (g_696178 + type * 4 + 2);
			sum_c = sum_c + *(unsigned short*) (g_696178 + type * 4 + 1);
			if (*(unsigned short*) (g_696178 + type * 4 + 1) != 0) {
				sum_a = sum_a
				    + *(unsigned char*) (g_868050 + type * 0x24d + 0x247);
				sum_b = sum_b
				    + *(unsigned char*) (g_868050 + type * 0x24d + 0x248);
			}
			if (*(unsigned short*) (g_696178 + type * 4 + 3) != 0) {
				sum_d = sum_d
				    + *(unsigned char*) (g_868050 + type * 0x24d + 0x247);
				slot0_e = slot0_e
				    + *(unsigned char*) (g_868050 + type * 0x24d + 0x248);
			}
		}
		rec += 0xa9;
	}
	limit = (int) g_696180 * 2;
	if (weight_a <= (float) limit) {
		weight_a = (float) limit;
	}
	oi[7] = sum_b;
	oi[4] = total;
	oi[8] = limit;
	out[5] = (float) ((((double) sum_a / (double) sum_b)
	    * ((double) sum_d / (double) slot0_e) + g_662908)
	    * ((double) total / (double) weight_a) * (double) sum_c);
	out[0] = fcn_004fc520();
	out[3] = g_6628a0 - (float) slot1_count / (double) total;
	out[1] = g_6628a0 - (float) slot0_count / (double) total;
	scale = g_6628a0 / ((float) total + (float) total);
	for (rec = (char*) g_99ef90; rec < (char*) 0x99f590; rec += 0x18) {
		for (n = 8; n != 0; n--) {
			f = *(float*) rec;
			if (f < g_6628a0) {
				f = g_6628a0;
			}
			*(float*) rec = f;
			weight_b = scale * *(float*) (rec + 4);
			*(float*) (rec + 4) = weight_b;
			accum = (*(float*) (rec - 4) / f) * weight_b + accum;
			rec += 0x18;
		}
	}
	lit = fcn_004fc3a0(buf_a);
	w = fcn_004fc340(buf_b);
	out[2] = (float) ((g_6629c8 - ((double) lit * (double) g_6629c0
	    + w * g_664e60)) * (double) accum);
	f = g_6628a0 - out[2];
	cell = f * out[0] * (g_6628a0 - out[1]) * (g_6628a0 - out[3]);
	out[9] = (cell + cell + (f + out[0] + (g_6628a0 - out[1])
	    + (g_6628a0 - out[3])) * g_6628bc) * g_662a68;
}
