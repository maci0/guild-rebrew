extern int d2_ScrollPergaForm;
int d2_ScrollPergaTopElem = 0xffffffff;
int d2_ScrollPergaBottomElem = 0xffffffff;



void __cdecl d2_DestroyForm(int);

/* ADDRESS: GOLDDE 0x0051de50 */
void __cdecl d2_DestroyScrollPerga(void)
{
	if (d2_ScrollPergaForm != -1) {
		d2_DestroyForm(d2_ScrollPergaForm);
		d2_ScrollPergaForm = -1;
		d2_ScrollPergaTopElem = -1;
		d2_ScrollPergaBottomElem = -1;
	}
}
