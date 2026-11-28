


typedef struct {
	unsigned int id;
	unsigned char pct;
	char pad[3];
} Share;
// SIZE 0x8

typedef struct {
	char pad0[0xc];
	Share e[7];
} Owner;
// SIZE 0x44

unsigned char* __cdecl hp_LookupProdEntry(int);

/* ADDRESS: GOLDDE 0x00596380 */
void __cdecl hp_UpdateProdSetting(int building, Owner* setting)
{
	unsigned char* prod_entry;
	unsigned short* prod_ids;
	int n;
	int k;
	int found;
	unsigned int id;
	unsigned int total;
	int cnt;
	int rem;
	int step;
	int j;

	prod_entry = hp_LookupProdEntry(building);
	if (prod_entry == 0) {
		return;
	}
	prod_ids = (unsigned short*) (prod_entry + 1);
	for (n = 0; n < 10; n++, prod_ids++) {
		if (*prod_ids != 0) {
			found = 0;
			id = *prod_ids;
			for (k = 0; k < 7; k++) {
				if (*prod_ids == setting->e[k].id) {
					found = 1;
				}
			}
			if (!found) {
				for (k = 0; k < 7; k++) {
					if (setting->e[k].id == 0) {
						setting->e[k].id = id;
						setting->e[k].pct = 0xe;
						break;
					}
				}
			}
		}
	}
	total = 0;
	cnt = 0;
	for (k = 0; k < 7; k++) {
		if (setting->e[k].id != 0) {
			cnt++;
			total += setting->e[k].pct;
		}
	}
	if (total == 100) {
		return;
	}
	if (total > 100) {
		rem = total - 100;
		step = -1;
	}
	else {
		rem = 100 - total;
		step = 1;
	}
	for (j = 0; rem != 0 && cnt != 0; j = (j + 1) % 7) {
		if (setting->e[j].id != 0) {
			if (setting->e[j].pct + step > -1 && setting->e[j].pct + step < 101) {
				setting->e[j].pct += step;
				rem--;
			}
		}
	}
}
