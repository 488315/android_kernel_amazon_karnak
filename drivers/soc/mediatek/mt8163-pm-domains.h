#include "mtk-pm-domains.h"
#include <dt-bindings/power/mt8163-power.h>

static const struct scpsys_domain_data scpsys_domain_data_mt8163[] = {
	[MT8163_POWER_DOMAIN_VDEC] = {
		.name = "vdec",
		.sta_mask = PWR_STATUS_VDEC,
		.ctl_offs = SPM_VDE_PWR_CON,
		.sram_pdn_bits = GENMASK(11, 8),
		.sram_pdn_ack_bits = GENMASK(12, 12),
	},
	[MT8163_POWER_DOMAIN_VENC] = {
		.name = "venc",
		.sta_mask = PWR_STATUS_VENC,
		.ctl_offs = SPM_VEN_PWR_CON,
		.sram_pdn_bits = GENMASK(11, 8),
		.sram_pdn_ack_bits = GENMASK(15, 12),
	},
	[MT8163_POWER_DOMAIN_ISP] = {
		.name = "isp",
		.sta_mask = PWR_STATUS_ISP,
		.ctl_offs = SPM_ISP_PWR_CON,
		.sram_pdn_bits = GENMASK(11, 8),
		.sram_pdn_ack_bits = GENMASK(13, 12),
	},
	[MT8163_POWER_DOMAIN_DISP] = {
		.name = "mm",
		.sta_mask = PWR_STATUS_DISP,
		.ctl_offs = SPM_DIS_PWR_CON,
		.sram_pdn_bits = GENMASK(11, 8),
		.sram_pdn_ack_bits = GENMASK(12, 12),
		.bp_infracfg = {
			BUS_PROT_UPDATE_TOPAXI(
			MT8163_TOP_AXI_PROT_EN_MM_M0),
		},
	},
	[MT8163_POWER_DOMAIN_AUDIO] = {
		.name = "audio",
		.sta_mask = PWR_STATUS_AUDIO,
		.ctl_offs = SPM_AUDIO_PWR_CON,
		.sram_pdn_bits = GENMASK(11, 8),
		.sram_pdn_ack_bits = GENMASK(15, 12),
	},
	[MT8163_POWER_DOMAIN_MFG_ASYNC] = {
		.name = "mfg_async",
		.sta_mask = PWR_STATUS_MFG_ASYNC,
		.ctl_offs = SPM_MFG_ASYNC_PWR_CON,
		.sram_pdn_bits = GENMASK(11, 8),
		.sram_pdn_ack_bits = 0,
		.bp_infracfg = {
			BUS_PROT_UPDATE_TOPAXI(
			MT8163_TOP_AXI_PROT_EN_MFG_M0 |
			MT8163_TOP_AXI_PROT_EN_MFG_SNOOP_OUT),
		},
	},
	[MT8163_POWER_DOMAIN_MFG] = {
		.name = "mfg",
		.sta_mask = PWR_STATUS_MFG,
		.ctl_offs = SPM_MFG_PWR_CON,
		.sram_pdn_bits = GENMASK(13, 8),
		.sram_pdn_ack_bits = GENMASK(16, 16),
	},
	[MT8163_POWER_DOMAIN_CONN] = {
		.name = "conn",
		.sta_mask = PWR_STATUS_CONN,
		.ctl_offs = SPM_CONN_PWR_CON,
		.sram_pdn_bits = GENMASK(8, 8),
		.sram_pdn_ack_bits = 0,
		.bp_infracfg = {
			BUS_PROT_UPDATE_TOPAXI(
			MT8163_TOP_AXI_PROT_EN_CCI_M2 |
			MT8163_TOP_AXI_PROT_EN_CONN2EMI |
			MT8163_TOP_AXI_PROT_EN_CONN2PERI),
		},
	},
};

static const struct scpsys_soc_data mt8163_scpsys_data = {
	.domains_data = scpsys_domain_data_mt8163,
	.num_domains = ARRAY_SIZE(scpsys_domain_data_mt8163),
};

