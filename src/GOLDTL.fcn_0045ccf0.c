extern int g_10405c8;
extern const float g_662e70[15];
extern float g_1040544[15];
extern float g_10404c4[15];
extern float g_1040584[15];
extern float g_1040504[15];

/* ADDRESS: GOLD 0x00460ca0 */
/* ADDRESS: GOLDTL 0x0045ccf0 */

void __cdecl fcn_0045ccf0(unsigned int now)
{
	float dt;
	float d;
	int i;

	if (now - (*(unsigned int*)&g_10405c8) == 0) {
		return;
	}
	dt = (float) (now - (*(unsigned int*)&g_10405c8));
	(*(unsigned int*)&g_10405c8) = now;
	for (i = 0; i < 15; i++) {
		d = dt * g_662e70[i];
		g_1040544[i] += d;
		if (g_1040544[i] > 1.0f) {
			g_1040544[i] -= 1.0f;
		}
		g_10404c4[i] += d;
		if (g_10404c4[i] > 1.0f) {
			g_10404c4[i] -= 1.0f;
		}
	}
	for (i = 0; i < 15; i++) {
		d = dt * g_662e70[i];
		g_1040584[i] -= d;
		if (g_1040584[i] < 0.0f) {
			g_1040584[i] += 1.0f;
		}
		g_1040504[i] -= d;
		if (g_1040504[i] < 0.0f) {
			g_1040504[i] += 1.0f;
		}
	}
}
