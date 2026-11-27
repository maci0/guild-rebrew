extern float g_662a18;
extern float g_662a68;
extern float g_662918;
extern double g_662908;
extern double g_662ad8;
extern double g_662ae0;
extern double g_662ae8;

int __cdecl rand(void);

/* ADDRESS: GOLDTL 0x00417570 */
unsigned char __cdecl d3_UpdateParticleEmitter(char* obj, int now)
{
	char* rec;
	int i;
	unsigned int dt;
	double span;
	double f1;
	double v;
	float fv; unsigned char flags;

	i = 0;
	rec = *(char**) (obj + 0x28);
	if (*(int*) (obj + 0xd8) <= 0) {
		return 1;
	}
	do { flags = *(unsigned char*) (rec + 0x51);
		if (flags & 1) {
			dt = (unsigned int) now - *(unsigned int*) (rec + 0x30);
			*(int*) (rec + 0x30) = now;
			span = (double) dt;
			f1 = span * g_662a68;
			*(float*) (rec + 0x38) = (float) (f1 * *(float*) rec + *(float*) (rec + 0x38));
			*(float*) (rec + 0x3c) = (float) (f1 * *(float*) (rec + 4) + *(float*) (rec + 0x3c));
			*(float*) (rec + 0x40) = (float) (f1 * *(float*) (rec + 8) + *(float*) (rec + 0x40));
			*(float*) (rec + 0x10) = fv = (float) (*(float*) (rec + 0x10) - f1 * *(float*) (obj + 4));
			if (0.0 < fv) {
				*(unsigned char*) (rec + 0x4f) = (unsigned char) (int) fv;
			} else {
				*(unsigned char*) (rec + 0x51) = flags & 0xfe;
			}
		} else {
			v = ((double) *(float*) (obj + 0xe4) * g_662ae8 + (double) *(float*) (obj + 0xe4) * g_662ae8)
			    * ((double) rand() * g_662a18)
			    - (double) *(float*) (obj + 0xe4) * g_662ae8;
			*(float*) (rec + 0x38) = (float) v;
			v = ((double) *(float*) (obj + 0xe4) * g_662ae0 + (double) *(float*) (obj + 0xe4) * g_662ae0)
			    * ((double) rand() * g_662a18)
			    - (double) *(float*) (obj + 0xe4) * g_662ae0;
			*(float*) (rec + 0x3c) = (float) v;
			v = ((double) *(float*) (obj + 0xe4) * g_662ae8 + (double) *(float*) (obj + 0xe4) * g_662ae8)
			    * ((double) rand() * g_662a18)
			    - (double) *(float*) (obj + 0xe4) * g_662ae8;
			*(float*) (rec + 0x40) = (float) v;
			*(float*) rec = (float) (((double) *(float*) obj * g_662ad8 + (double) *(float*) obj * g_662ad8) * ((double) rand() * g_662a18) - (double) *(float*) obj * g_662ad8);
			*(float*) (rec + 4) = (float) ((double) rand() * g_662a18 - g_662908 + *(float*) obj);
			*(float*) (rec + 8) = (float) (((double) *(float*) obj * g_662ad8 + (double) *(float*) obj * g_662ad8) * ((double) rand() * g_662a18) - (double) *(float*) obj * g_662ad8);
			*(unsigned char*) (rec + 0x4e) = (unsigned char) (rand() & 0x3f);
			*(unsigned char*) (rec + 0x4d) = (unsigned char) (rand() & 0x3f);
			*(unsigned char*) (rec + 0x4c) = (unsigned char) (rand() & 0x3f);
			*(float*) (rec + 0x10) = (float) (rand() & 0x3f);
			fv = *(float*) (obj + 0xe4) - 2.0f;
			*(float*) (rec + 0x48) = (float) (((double) fv + (double) fv) * ((double) rand() * g_662a18) - (double) fv + *(float*) (obj + 0xe4));
			*(int*) (rec + 0x30) = now;
			*(unsigned char*) (rec + 0x51) = *(unsigned char*) (rec + 0x51) | 1;
		}
		i++;
		rec += 0x54;
	} while (i < *(int*) (obj + 0xd8));
	return 1;
}
