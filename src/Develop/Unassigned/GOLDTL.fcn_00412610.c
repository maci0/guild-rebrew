void __cdecl fcn_00411fe0(void);

// SIZE 0x4c
struct cam_412610 {
	int v[0x13];
};

extern short g_14ce8c0;
extern int g_14cf900[];

void __cdecl fcn_004124b0(void);


/* Resets the camera to its saved start state and reapplies it. */
/* ADDRESS: GOLDTL 0x00412610 */
void __cdecl fcn_00412610(void)
{
	fcn_00411fe0();
	(*(struct cam_412610*)&g_14ce8c0) = (*(struct cam_412610*)g_14cf900);
	fcn_004124b0();
}
