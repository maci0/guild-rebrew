


void __cdecl he_ShowZigeunerMessage(int, int);
void __cdecl fcn_0057c020(int, int);
void __cdecl fcn_0057c170(int, int);
void __cdecl fcn_0057c2e0(int, int);
void __cdecl fcn_0057c420(int, int);
void __cdecl fcn_0057c530(int, int);

void __cdecl fcn_0057bed0(int a, int b, int k)
{
	if (k == 0) {
		he_ShowZigeunerMessage(a, b);
	} else if (k == 1) {
		fcn_0057c020(a, b);
	} else if (k == 2) {
		fcn_0057c170(a, b);
	} else if (k == 3) {
		fcn_0057c2e0(a, b);
	} else if (k == 4) {
		fcn_0057c420(a, b);
	} else {
		fcn_0057c530(a, b);
	}
}
