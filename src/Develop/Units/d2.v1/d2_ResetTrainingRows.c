#include "client_types.h"
#include "Develop/Units/d2.v1/d2_training_rows.h"
 



// SIZE 0x40
 
 
 
 
 
 
 
 
 
 

void __cdecl d2_ResetTrainingRows(void)
{
	int i;
	int j;
	D2_TRAINING_ROW* r;

	for (i = 0; i < 32; i++) {
		r = (D2_TRAINING_ROW*) g_7774a0 + i;
		r->entity = 0;
		r->portrait_element = -1;
		r->row_element = -1;
		r->window = -1;
		for (j = 0; j < 6; j++) {
			r->item[j].button = -1;
			r->item[j].objekt_id = 0;
		}
	}
}
