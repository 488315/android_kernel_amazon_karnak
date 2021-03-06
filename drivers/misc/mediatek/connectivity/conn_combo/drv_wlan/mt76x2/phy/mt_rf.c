/*
 ***************************************************************************
 * Copyright (c) 2015 MediaTek Inc.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 ***************************************************************************

	Module Name:
	mt_rf.c
*/

#include "rt_config.h"

int mt_rf_write(RTMP_ADAPTER *ad, u8 rf_idx, u16 offset, u32 data)
{
	u32 i = 0;
	u32 value;
	int ret = 0;

#ifdef RTMP_MAC_USB
	if (IS_USB_INF(ad)) {
		RTMP_SEM_EVENT_WAIT(&ad->reg_atomic, ret);
		if (ret != 0) {
			DBGPRINT(RT_DEBUG_ERROR, ("reg_atomic get failed(ret=%d)\n", ret));
			return STATUS_UNSUCCESSFUL;
		}
	}
#endif /* RTMP_MAC_USB */

	/* rf data */
	RTMP_IO_WRITE32(ad, W_RFDATA, data);

	/* rf control */
	RTMP_IO_READ32(ad, RF_CTRL, &value);

	/* rf address */
	value &= ~RF_ADDR_MASK;
	value |= RF_ADDR(offset);

	/* write control */
	value |= RF_R_W_CTRL;

	/* rf index */
	value &= ~RF_IDX_MASK;
	value |= RF_IDX(rf_idx);

	RTMP_IO_WRITE32(ad, RF_CTRL, value);

	do {
		RTMP_IO_READ32(ad, RF_CTRL, &value);

		if (RF_READY(value))
			break;
		i++;
		/* RtmpOsMsDelay(1); */
		RtmpusecDelay(50);
		/* } while ((i < MAX_BUSY_COUNT) && (!RTMP_TEST_FLAG(ad, fRTMP_ADAPTER_NIC_NOT_EXIST))); */
	} while ((i < MAX_BUSY_COUNT_US) && (!RTMP_TEST_FLAG(ad, fRTMP_ADAPTER_NIC_NOT_EXIST)));

	/* if ((i == MAX_BUSY_COUNT) || (RTMP_TEST_FLAG(ad, fRTMP_ADAPTER_NIC_NOT_EXIST))) { */
	if ((i == MAX_BUSY_COUNT_US) || (RTMP_TEST_FLAG(ad, fRTMP_ADAPTER_NIC_NOT_EXIST))) {
		DBGPRINT_RAW(RT_DEBUG_ERROR, ("Retry count exhausted or device removed!!!\n"));
		ret = STATUS_UNSUCCESSFUL;
	}
#ifdef RTMP_MAC_USB
	if (IS_USB_INF(ad))
		RTMP_SEM_EVENT_UP(&ad->reg_atomic);
#endif /* RTMP_MAC_USB */

	return ret;
}

int mt_rf_read(RTMP_ADAPTER *ad, u8 rf_idx, u16 offset, u32 *data)
{
	u32 i = 0;
	u32 value;
	int ret = STATUS_SUCCESS;

#ifdef RTMP_MAC_USB
	if (IS_USB_INF(ad)) {
		RTMP_SEM_EVENT_WAIT(&ad->reg_atomic, ret);
		if (ret != 0) {
			DBGPRINT(RT_DEBUG_ERROR, ("reg_atomic get failed(ret=%d)\n", ret));
			return STATUS_UNSUCCESSFUL;
		}
	}
#endif /* RTMP_MAC_USB */

	/* rf control */
	RTMP_IO_READ32(ad, RF_CTRL, &value);

	/* rf address */
	value &= ~RF_ADDR_MASK;
	value |= RF_ADDR(offset);

	/* read control */
	value &= ~RF_R_W_CTRL;

	/* rf index */
	value &= ~RF_IDX_MASK;
	value |= RF_IDX(rf_idx);

	RTMP_IO_WRITE32(ad, RF_CTRL, value);

	do {
		RTMP_IO_READ32(ad, RF_CTRL, &value);

		if (RF_READY(value))
			break;
		i++;
		/* RtmpOsMsDelay(1); */
		RtmpusecDelay(50);
		/* } while ((i < MAX_BUSY_COUNT) && (!RTMP_TEST_FLAG(ad, fRTMP_ADAPTER_NIC_NOT_EXIST))); */
	} while ((i < MAX_BUSY_COUNT_US) && (!RTMP_TEST_FLAG(ad, fRTMP_ADAPTER_NIC_NOT_EXIST)));

	/* if ((i == MAX_BUSY_COUNT) || (RTMP_TEST_FLAG(ad, fRTMP_ADAPTER_NIC_NOT_EXIST))) { */
	if ((i == MAX_BUSY_COUNT_US) || (RTMP_TEST_FLAG(ad, fRTMP_ADAPTER_NIC_NOT_EXIST))) {
		DBGPRINT_RAW(RT_DEBUG_ERROR, ("Retry count exhausted or device removed!!!\n"));
		ret = STATUS_UNSUCCESSFUL;
		goto done;
	}

	/* rf data */
	RTMP_IO_READ32(ad, R_RFDATA, data);

done:
#ifdef RTMP_MAC_USB
	if (IS_USB_INF(ad))
		RTMP_SEM_EVENT_UP(&ad->reg_atomic);
#endif /* RTMP_MAC_USB */

	return ret;
}
