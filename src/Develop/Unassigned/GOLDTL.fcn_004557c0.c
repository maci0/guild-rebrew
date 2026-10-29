typedef struct
{
	float m[4][4];
} fcn_004557c0_Mat;
// SIZE 0x40

void __cdecl fcn_00455700(char* a, int b, fcn_004557c0_Mat* m, fcn_004557c0_Mat* out);
fcn_004557c0_Mat* __stdcall fcn_005eb970(fcn_004557c0_Mat* out, fcn_004557c0_Mat* a, fcn_004557c0_Mat* b);

/* ADDRESS: GOLDTL 0x004557c0 */
void __cdecl fcn_004557c0(char* a, char* o, int b, fcn_004557c0_Mat* out)
{
	fcn_004557c0_Mat id;
	fcn_004557c0_Mat tmp;

	id.m[0][1] = id.m[0][2] = id.m[0][3] = id.m[1][0] = id.m[1][2] = id.m[1][3] = id.m[2][0] = id.m[2][1] = id.m[2][3] = id.m[3][0] = id.m[3][1] = id.m[3][2] = 0.0f;
	id.m[0][0] = id.m[1][1] = id.m[2][2] = id.m[3][3] = 1.0f;
	if (o != 0) {
		fcn_00455700(a, b, &id, &tmp);
		tmp.m[3][0] -= *(float*) (o + 0x4c);
		tmp.m[3][1] -= *(float*) (o + 0x50);
		tmp.m[3][2] -= *(float*) (o + 0x54);
		tmp.m[3][0] -= *(float*) (o + 0x78);
		tmp.m[3][1] -= *(float*) (o + 0x7c);
		tmp.m[3][2] -= *(float*) (o + 0x80);
		fcn_005eb970(out, &tmp, (fcn_004557c0_Mat*) (o + 0x18c));
	} else {
		fcn_00455700(a, b, &id, out);
	}
}
