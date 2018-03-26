#include "vdp.h"

// requires F18A or 9938!!
int set_text80_raw() {
	int unblank = VDP_MODE1_16K | VDP_MODE1_UNBLANK | VDP_MODE1_TEXT | VDP_MODE1_INT;
	VDP_SET_REGISTER(VDP_REG_MODE0, VDP_MODE0_80COL);
	VDP_SET_REGISTER(VDP_REG_MODE1, VDP_MODE1_16K | VDP_MODE1_TEXT);
	VDP_SET_REGISTER(VDP_REG_SIT, 0x00);	gImage = 0x000;
	VDP_SET_REGISTER(VDP_REG_PDT, 0x02);	gPattern = 0x1000;
	// no sprites and no color in text mode anyway
	nTextRow = 80 * 23;
	nTextEnd = (80 * 24) - 1;
	nTextPos = nTextRow;
	return unblank;
}

void set_text80() {
    int x = set_text80_raw();
    VDP_SET_REGISTER(VDP_REG_MODE1, x);
    VDP_REG1_KSCAN_MIRROR = x;
}

#ifdef ENABLE_F18A_ECM
void set_text80_ecm(void)
{
    int x = set_text80_raw();
    VDP_SET_REGISTER(VDP_REG_MODE1, x);
    VDP_REG1_KSCAN_MIRROR = x;

    VDP_SET_REGISTER(0x31, 0x10);  // set ECM 1-bit color mode
    VDP_SET_REGISTER(VDP_REG_CT, 0x20);		gColor = 0x800;
}
#endif
