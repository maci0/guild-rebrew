typedef struct fcn_004c09b0_node fcn_004c09b0_node;
struct fcn_004c09b0_node {
	int* f0;
	int f4;
	int f8;
	fcn_004c09b0_node* next;
};
// SIZE 0x10

extern int g_772d2c;
extern char* g_772d34;

void __cdecl fcn_004c24c0(float, int);
void __cdecl fcn_00426170(int*, int);
void __cdecl m_FreeTracked(void*);

/* ADDRESS: GOLD 0x004c01b0 */
/* ADDRESS: GOLDTL 0x004c09b0 */

void __cdecl fcn_004c09b0(void)
{
	fcn_004c09b0_node* next;

	if (g_772d2c != 0) {
		g_772d2c = 0;
		fcn_004c24c0(1.0f, 2000);
	}
	while ((*(fcn_004c09b0_node**)&g_772d34) != 0) {
		next = (*(fcn_004c09b0_node**)&g_772d34)->next;
		fcn_00426170((*(fcn_004c09b0_node**)&g_772d34)->f0, 0);
		m_FreeTracked((*(fcn_004c09b0_node**)&g_772d34));
		(*(fcn_004c09b0_node**)&g_772d34) = next;
	}
}
