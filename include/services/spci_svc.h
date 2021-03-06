/*
 * Copyright (c) 2019, Arm Limited. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef SPCI_SVC_H
#define SPCI_SVC_H

#include <lib/smccc.h>
#include <lib/utils_def.h>
#include <tools_share/uuid.h>

/* SPCI error codes. */
#define SPCI_ERROR_NOT_SUPPORTED	-1
#define SPCI_ERROR_INVALID_PARAMETER	-2
#define SPCI_ERROR_NO_MEMORY		-3
#define SPCI_ERROR_BUSY			-4
#define SPCI_ERROR_INTERRUPTED		-5
#define SPCI_ERROR_DENIED		-6
#define SPCI_ERROR_RETRY		-7

/* The macros below are used to identify SPCI calls from the SMC function ID */
#define SPCI_FNUM_MIN_VALUE	U(0x60)
#define SPCI_FNUM_MAX_VALUE	U(0x7f)
#define is_spci_fid(fid) __extension__ ({		\
	__typeof__(fid) _fid = (fid);			\
	((GET_SMC_NUM(_fid) >= SPCI_FNUM_MIN_VALUE) &&	\
	 (GET_SMC_NUM(_fid) <= SPCI_FNUM_MAX_VALUE)); })

/* SPCI_VERSION helpers */
#define SPCI_VERSION_MAJOR		U(0)
#define SPCI_VERSION_MAJOR_SHIFT	16
#define SPCI_VERSION_MAJOR_MASK		U(0x7FFF)
#define SPCI_VERSION_MINOR		U(9)
#define SPCI_VERSION_MINOR_SHIFT	0
#define SPCI_VERSION_MINOR_MASK		U(0xFFFF)

#define MAKE_SPCI_VERSION(major, minor) \
	((((major) & SPCI_VERSION_MAJOR_MASK) <<  SPCI_VERSION_MAJOR_SHIFT) | \
	 (((minor) & SPCI_VERSION_MINOR_MASK) << SPCI_VERSION_MINOR_SHIFT))
#define SPCI_VERSION_COMPILED		MAKE_SPCI_VERSION(SPCI_VERSION_MAJOR, \
							  SPCI_VERSION_MINOR)

/* SPCI_MSG_SEND helpers */
#define SPCI_MSG_SEND_ATTRS_BLK_SHIFT	U(0)
#define SPCI_MSG_SEND_ATTRS_BLK_MASK	U(0x1)
#define SPCI_MSG_SEND_ATTRS_BLK		U(0)
#define SPCI_MSG_SEND_ATTRS_BLK_NOT	U(1)
#define SPCI_MSG_SEND_ATTRS(blk)		\
	(((blk) & SPCI_MSG_SEND_ATTRS_BLK_MASK) \
	<< SPCI_MSG_SEND_ATTRS_BLK_SHIFT)

/* Get SPCI fastcall std FID from function number */
#define SPCI_FID(smc_cc, func_num)			\
		((SMC_TYPE_FAST << FUNCID_TYPE_SHIFT) |	\
		 ((smc_cc) << FUNCID_CC_SHIFT) |	\
		 (OEN_STD_START << FUNCID_OEN_SHIFT) |	\
		 ((func_num) << FUNCID_NUM_SHIFT))

/* SPCI function numbers */
#define SPCI_FNUM_ERROR			U(0x60)
#define SPCI_FNUM_SUCCESS		U(0x61)
#define SPCI_FNUM_INTERRUPT		U(0x62)
#define SPCI_FNUM_VERSION		U(0x63)
#define SPCI_FNUM_FEATURES		U(0x64)
#define SPCI_FNUM_RX_RELEASE		U(0x65)
#define SPCI_FNUM_RXTX_MAP		U(0x66)
#define SPCI_FNUM_RXTX_UNMAP		U(0x67)
#define SPCI_FNUM_PARTITION_INFO_GET	U(0x68)
#define SPCI_FNUM_ID_GET		U(0x69)
#define SPCI_FNUM_MSG_POLL		U(0x6A)
#define SPCI_FNUM_MSG_WAIT		U(0x6B)
#define SPCI_FNUM_MSG_YIELD		U(0x6C)
#define SPCI_FNUM_MSG_RUN		U(0x6D)
#define SPCI_FNUM_MSG_SEND		U(0x6E)
#define SPCI_FNUM_MSG_SEND_DIRECT_REQ	U(0x6F)
#define SPCI_FNUM_MSG_SEND_DIRECT_RESP	U(0x70)
#define SPCI_FNUM_MEM_DONATE		U(0x71)
#define SPCI_FNUM_MEM_LEND		U(0x72)
#define SPCI_FNUM_MEM_SHARE		U(0x73)
#define SPCI_FNUM_MEM_RETRIEVE_REQ	U(0x74)
#define SPCI_FNUM_MEM_RETRIEVE_RESP	U(0x75)
#define SPCI_FNUM_MEM_RELINQUISH	U(0x76)
#define SPCI_FNUM_MEM_RECLAIM		U(0x77)

/* SPCI SMC32 FIDs */
#define SPCI_ERROR		SPCI_FID(SMC_32, SPCI_FNUM_ERROR)
#define SPCI_SUCCESS_SMC32	SPCI_FID(SMC_32, SPCI_FNUM_SUCCESS)
#define SPCI_INTERRUPT		SPCI_FID(SMC_32, SPCI_FNUM_INTERRUPT)
#define SPCI_VERSION		SPCI_FID(SMC_32, SPCI_FNUM_VERSION)
#define SPCI_FEATURES		SPCI_FID(SMC_32, SPCI_FNUM_FEATURES)
#define SPCI_RX_RELEASE		SPCI_FID(SMC_32, SPCI_FNUM_RX_RELEASE)
#define SPCI_RXTX_MAP_SMC32	SPCI_FID(SMC_32, SPCI_FNUM_RXTX_MAP)
#define SPCI_RXTX_UNMAP		SPCI_FID(SMC_32, SPCI_FNUM_RXTX_UNMAP)
#define SPCI_PARTITION_INFO_GET	SPCI_FID(SMC_32, SPCI_FNUM_PARTITION_INFO_GET)
#define SPCI_ID_GET		SPCI_FID(SMC_32, SPCI_FNUM_ID_GET)
#define SPCI_MSG_POLL		SPCI_FID(SMC_32, SPCI_FNUM_MSG_POLL)
#define SPCI_MSG_WAIT		SPCI_FID(SMC_32, SPCI_FNUM_MSG_WAIT)
#define SPCI_MSG_YIELD		SPCI_FID(SMC_32, SPCI_FNUM_MSG_YIELD)
#define SPCI_MSG_RUN		SPCI_FID(SMC_32, SPCI_FNUM_MSG_RUN)
#define SPCI_MSG_SEND		SPCI_FID(SMC_32, SPCI_FNUM_MSG_SEND)
#define SPCI_MSG_SEND_DIRECT_REQ_SMC32 \
	SPCI_FID(SMC_32, SPCI_FNUM_MSG_SEND_DIRECT_REQ)
#define SPCI_MSG_SEND_DIRECT_RESP_SMC32	\
	SPCI_FID(SMC_32, SPCI_FNUM_MSG_SEND_DIRECT_RESP)
#define SPCI_MEM_DONATE_SMC32	SPCI_FID(SMC_32, SPCI_FNUM_MEM_DONATE)
#define SPCI_MEM_LEND_SMC32	SPCI_FID(SMC_32, SPCI_FNUM_MEM_LEND)
#define SPCI_MEM_SHARE_SMC32	SPCI_FID(SMC_32, SPCI_FNUM_MEM_SHARE)
#define SPCI_MEM_RETRIEVE_REQ_SMC32 \
	SPCI_FID(SMC_32, SPCI_FNUM_MEM_RETRIEVE_REQ)
#define SPCI_MEM_RETRIEVE_RESP	SPCI_FID(SMC_32, SPCI_FNUM_MEM_RETRIEVE_RESP)
#define SPCI_MEM_RELINQUISH	SPCI_FID(SMC_32, SPCI_FNUM_MEM_RELINQUISH)
#define SPCI_MEM_RECLAIM	SPCI_FID(SMC_32, SPCI_FNUM_MEM_RECLAIM)

/* SPCI SMC64 FIDs */
#define SPCI_SUCCESS_SMC64	SPCI_FID(SMC_64, SPCI_FNUM_SUCCESS)
#define SPCI_RXTX_MAP_SMC64	SPCI_FID(SMC_64, SPCI_FNUM_RXTX_MAP)
#define SPCI_MSG_SEND_DIRECT_REQ_SMC64 \
	SPCI_FID(SMC_64, SPCI_FNUM_MSG_SEND_DIRECT_REQ)
#define SPCI_MSG_SEND_DIRECT_RESP_SMC64	\
	SPCI_FID(SMC_64, SPCI_FNUM_MSG_SEND_DIRECT_RESP)
#define SPCI_MEM_DONATE_SMC64	SPCI_FID(SMC_64, SPCI_FNUM_MEM_DONATE)
#define SPCI_MEM_LEND_SMC64	SPCI_FID(SMC_64, SPCI_FNUM_MEM_LEND)
#define SPCI_MEM_SHARE_SMC64	SPCI_FID(SMC_64, SPCI_FNUM_MEM_SHARE)
#define SPCI_MEM_RETRIEVE_REQ_SMC64 \
	SPCI_FID(SMC_64, SPCI_FNUM_MEM_RETRIEVE_REQ)

/*
 * Reserve a special value for traffic targeted to the Hypervisor or SPM.
 */
#define SPCI_TARGET_INFO_MBZ		U(0x0)

/*
 * Reserve a special value for MBZ parameters.
 */
#define SPCI_PARAM_MBZ			U(0x0)

#endif /* SPCI_SVC_H */
