/*
 * Copyright (c) 2020-2021, Renesas Electronics Corporation. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <stdint.h>
#include <ddr_internal.h>

const uint32_t mc_odt_pins_tbl[4] = {
	0x00000000	,
	0x00000000	,
	0x00000000	,
	0x00000000
};

const uint32_t mc_mr1_tbl[2] = {
	0x00000266	,
	0x00000000
};

const uint32_t mc_mr2_tbl[2] = {
	0x00000600	,
	0x00000200
};

const uint32_t mc_mr5_tbl[2] = {
	0x00000000	,
	0x00000000
};

const uint32_t mc_mr6_tbl[2] = {
	0x00000000	,
	0x00000000
};

const uint32_t mc_phy_settings_tbl[MC_PHYSET_NUM][2] = {
	{DDRMC_R040,	0x4F7F03B8	},
	{DDRMC_R041,	0x00003C28	},
	{DDRMC_R042,	0x00003C28	},
	{DDRMC_R043,	0x00000000	}
};

const uint32_t swizzle_mc_tbl[SWIZZLE_MC_NUM][2] = {
	{DDRMC_R030,	0x00000000	},
	{DDRMC_R031,	0x00000000	},
	{DDRMC_R032,	0x00000000	},
	{DDRMC_R033,	0x00000000	},
	{DDRMC_R034,	0x00000000	},
	{DDRMC_R035,	0x17181516	},
	{DDRMC_R036,	0x0000191A	},
	{DDRMC_R037,	0x00000000	},
	{DDRMC_R038,	0x00000000	}
};

const uint32_t swizzle_phy_tbl[SIZZLE_PHY_NUM][2] = {
	{DDRPHY_R29,			0x00000000	},
	{DDRPHY_R11,	0x04020100	},
	{DDRPHY_R29,			0x00000001	},
	{DDRPHY_R11,	0x08050603	},
	{DDRPHY_R29,			0x00000002	},
	{DDRPHY_R11,	0x0B0A0907	},
	{DDRPHY_R29,			0x00000003	},
	{DDRPHY_R11,	0x0F0E0D0C	},
	{DDRPHY_R29,			0x00000004	},
	{DDRPHY_R11,	0x13121110	},
	{DDRPHY_R29,			0x00000005	},
	{DDRPHY_R11,	0x17161514	},
	{DDRPHY_R29,			0x00000006	},
	{DDRPHY_R11,	0x1B1A1918	},
	{DDRPHY_R29,			0x00000007	},
	{DDRPHY_R11,	0x001E1D1C	}
};
