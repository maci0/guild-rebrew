/* Fades the objects of a selected animation slot in or out after a mode switch
   and stores the new current slot. */

int __cdecl main_RunFrameLoop(void*, int);
int __cdecl d2_UpdateKanoneDialog(int, int, int);
void __cdecl d3_NormalizeVector(float*);
void __cdecl d3_SetNodePosition(char*, int*);
char __cdecl d3_SetObjectVisible(char*, char);

/* ADDRESS: GOLDTL 0x00588710 */
/* ADDRESS: GOLDDE 0x0056e3d0 */
void __cdecl d2_SwitchKanoneMode(int obj, int state, int res, int selectedIndex, int loopMask)
{
	unsigned int start = *(unsigned int*) 0x6b7fac;
	float f;
	float vec[4];
	float pos[4];
	float t0, t1;
	float factor;
	int i;

	if (selectedIndex == *(int*) (state + 0xa0) || selectedIndex > *(int*) (state + 0xdc)) {
		return;
	}
	while (main_RunFrameLoop((void*) d2_SwitchKanoneMode, loopMask) != 0) {
		d2_UpdateKanoneDialog(obj, state, res);
		if ((float) (*(unsigned int*) 0x6b7fac - start) >
		    *(float*) 0x665f3c) {
			*(int*) 0x774654 = 1;
		} else {
			f = (float) (*(unsigned int*) 0x6b7fac - start) /
			    *(float*) 0x665f3c;
			vec[0] = *(float*) (state + 0x24);
			vec[2] = *(float*) (state + 0x2c);
			vec[1] = 0.0f;
			d3_NormalizeVector(vec);
			factor = *(float*) 0x665f40;
			factor *= f;
			vec[0] *= factor; vec[1] *= factor; vec[2] *= factor;
			vec[0] = *(float*) state - vec[0];
			vec[1] = *(float*) (state + 4) - vec[1];
			vec[2] = *(float*) (state + 8) - vec[2];
			d3_SetNodePosition((char*) *(int*) (state + 0x98), (int*) vec);
			t0 = *(float*) 0x662d40; t1 = *(float*) 0x662d44; pos[2] = *(float*) 0x662d48;
			factor = *(float*) 0x665f40;
			factor *= f;
			pos[0] = factor * t0; t1 *= factor; pos[2] *= factor;
			pos[0] = *(float*) 0x665f28 + pos[0];
			pos[1] = *(float*) 0x665f2c + t1;
			pos[2] = *(float*) 0x665f30 + pos[2];
			d3_SetNodePosition((char*) *(int*) (state + 0x9c), (int*) pos);
		}
	}
	for (i = 0; i != 3; i++) {
		d3_SetObjectVisible((char*) *(int*) (state + 0x8c + i * 4), 0);
	}
	d3_SetObjectVisible((char*) *(int*) (state + 0x8c + selectedIndex * 4), 1);
	*(int*) (state + 0xa0) = selectedIndex;
	start = *(unsigned int*) 0x6b7fac;
	while (main_RunFrameLoop((void*) d2_SwitchKanoneMode, loopMask) != 0) {
		d2_UpdateKanoneDialog(obj, state, res);
		if ((float) (*(unsigned int*) 0x6b7fac - start) >
		    *(float*) 0x665f3c) {
			*(int*) 0x774654 = 1;
		} else {
			vec[0] = *(float*) (state + 0x24);
			vec[2] = *(float*) (state + 0x2c);
			vec[1] = 0.0f;
			f = 1.0f -
			    (float) (*(unsigned int*) 0x6b7fac - start) /
			        *(float*) 0x665f3c;
			d3_NormalizeVector(vec);
			factor = *(float*) 0x665f40;
			factor *= f;
			vec[0] *= factor; vec[1] *= factor; vec[2] *= factor;
			vec[0] = *(float*) state - vec[0];
			vec[1] = *(float*) (state + 4) - vec[1];
			vec[2] = *(float*) (state + 8) - vec[2];
			d3_SetNodePosition((char*) *(int*) (state + 0x98), (int*) vec);
			t0 = *(float*) 0x662d40; t1 = *(float*) 0x662d44; pos[2] = *(float*) 0x662d48;
			factor = *(float*) 0x665f40;
			factor *= f;
			pos[0] = factor * t0; t1 *= factor; pos[2] *= factor;
			pos[0] = *(float*) 0x665f28 + pos[0];
			pos[1] = *(float*) 0x665f2c + t1;
			pos[2] = *(float*) 0x665f30 + pos[2];
			d3_SetNodePosition((char*) *(int*) (state + 0x9c), (int*) pos);
		}
	}
	*(int*) (state + 0x6c) = *(int*) 0x6b7fac;
}
