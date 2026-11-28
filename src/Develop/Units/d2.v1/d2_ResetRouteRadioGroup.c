extern char d2_RouteRadioGroupId[];


void __cdecl d2_ClearRadioGroup(int);

/* ADDRESS: GOLDDE 0x004abee0 */
void __cdecl d2_ResetRouteRadioGroup(void)
{
	if (*(int*) &d2_RouteRadioGroupId != -1) {
		d2_ClearRadioGroup(*(int*) &d2_RouteRadioGroupId);
	}
	*(int*) &d2_RouteRadioGroupId = -1;
}
