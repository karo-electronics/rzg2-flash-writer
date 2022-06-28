/**********************************************************************************************************************
 * DISCLAIMER
 * This software is supplied by Renesas Electronics Corporation and is only intended for use with Renesas products. No
 * other uses are authorized. This software is owned by Renesas Electronics Corporation and is protected under all
 * applicable laws, including copyright laws.
 * THIS SOFTWARE IS PROVIDED "AS IS" AND RENESAS MAKES NO WARRANTIES REGARDING
 * THIS SOFTWARE, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING BUT NOT LIMITED TO WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT. ALL SUCH WARRANTIES ARE EXPRESSLY DISCLAIMED. TO THE MAXIMUM
 * EXTENT PERMITTED NOT PROHIBITED BY LAW, NEITHER RENESAS ELECTRONICS CORPORATION NOR ANY OF ITS AFFILIATED COMPANIES
 * SHALL BE LIABLE FOR ANY DIRECT, INDIRECT, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES FOR ANY REASON RELATED TO
 * THIS SOFTWARE, EVEN IF RENESAS OR ITS AFFILIATES HAVE BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
 * Renesas reserves the right, without notice, to make changes to this software and to discontinue the availability of
 * this software. By using this software, you agree to the additional terms and conditions found by accessing the
 * following link:
 * http://www.renesas.com/disclaimer
 *
 * Copyright (C) 2020 Renesas Electronics Corporation. All rights reserved.
 *********************************************************************************************************************/
/**********************************************************************************************************************
 * File Name	: otp_iodefine.h
 * Version		: 1.0
 * Description	: IO define header.
 *********************************************************************************************************************/
/**********************************************************************************************************************
 * History : DD.MM.YYYY Version	 Description
 *		   : 01.09.2020 1.00	 First Release
 *********************************************************************************************************************/

/**********************************************************************************************************************
 Includes	<System Includes> , "Project Includes"
 *********************************************************************************************************************/

/**********************************************************************************************************************
 Macro definitions
 *********************************************************************************************************************/
#ifndef	OTP_IODEFINE_H
#define	OTP_IODEFINE_H

#define	OTP_OTPPWR_PWR	(1 << 0)
#define	OTP_OTPPWR_ACCL	(1 << 4)
#define	OTP_OTPPWR_MASK	(0x00000011)

/**********************************************************************************************************************
 Global Typedef definitions
 *********************************************************************************************************************/
struct	st_otp
{
	union
	{
		uint32_t	WORD;
		struct
		{
			uint32_t	PWR:1;
			uint32_t	:3;
			uint32_t	ACCL:1;
			uint32_t	:27;
		} BIT;
	} OTPPWR;
	union
	{
		uint32_t	WORD;
		struct
		{
			uint32_t	CMD_RDY:1;
			uint32_t	ERR_WR:2;
			uint32_t	ERR_WP:1;
			uint32_t	ERR_RP:1;
			uint32_t	:3;
			uint32_t	ERR_RDY_WR:1;
			uint32_t	ERR_RDY_RD:1;
			uint32_t	:22;
		} BIT;
	} OTPSTR;
	union
	{
		uint32_t	WORD;
		struct
		{
			uint32_t	STAWR:1;
			uint32_t	:31;
		} BIT;
	} OTPSTAWR;
	union
	{
		uint32_t	WORD;
		struct
		{
			uint32_t	ADRWR:9;
			uint32_t	:23;
		} BIT;
	} OTPADRWR;
	union
	{
		uint32_t	WORD;
		struct
		{
			uint32_t	DATAWR:32;
		} BIT;
	} OTPDATAWR;
	union
	{
		uint32_t	WORD;
		struct
		{
			uint32_t	ADRRD:9;
			uint32_t	:23;
		} BIT;
	} OTPADRRD;
	union
	{
		uint32_t	WORD;
		struct
		{
			uint32_t	DATARD:32;
		} BIT;
	} OTPDATARD;
	union
	{
		uint32_t	WORD;
		struct
		{
			uint32_t	OTPFLAG:1;
			uint32_t	:31;
		} BIT;
	} OTPFLAG;
	union
	{
		uint32_t	WORD;
		struct
		{
			uint32_t	SECINTEN:1;
			uint32_t	DEDINTEN:1;
			uint32_t	:30;
		} BIT;
	} OTPINTEN;
	union
	{
		uint32_t	WORD;
		struct
		{
			uint32_t	SECINTSTS:1;
			uint32_t	DEDINTSTS:1;
			uint32_t	:30;
		} BIT;
	} OTPINTSTS;
	union
	{
		uint32_t	WORD;
		struct
		{
			uint32_t	SECADDR:9;
			uint32_t	:23;
		} BIT;
	} OTPSECADDR;
	union
	{
		uint32_t	WORD;
		struct
		{
			uint32_t	DEDADDR:9;
			uint32_t	:23;
		} BIT;
	} OTPDEDADDR;
};

#define	OTP	(*(volatile struct st_otp *)0x11860000)

/**********************************************************************************************************************
 External global variables
 *********************************************************************************************************************/

/**********************************************************************************************************************
 Exported global functions
 *********************************************************************************************************************/

#endif
