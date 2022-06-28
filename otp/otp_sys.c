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
 * File Name	: otp_sys.c
 * Version		: 1.0
 * Description	: This module provide OTP control functions.
 *********************************************************************************************************************/
/**********************************************************************************************************************
 * History : DD.MM.YYYY Version	 Description
 *		   : 01.09.2020 1.00	 First Release
 *********************************************************************************************************************/

/**********************************************************************************************************************
 Includes	<System Includes> , "Project Includes"
 *********************************************************************************************************************/
#include <stddef.h>
#include "types.h"
#include "common.h"
#include "devdrv.h"

#include "otp_sys.h"
#include "otp_iodefine.h"

/**********************************************************************************************************************
 Macro definitions
 *********************************************************************************************************************/
#ifdef	RZG2L
#define OTP_DUMMY_READ	(0x400 >> 2)
#endif
#ifdef	RZG2LC
#define OTP_DUMMY_READ	(0x400 >> 2)
#endif
#ifdef	RZV2L
#define OTP_DUMMY_READ	(0x400 >> 2)
#endif
#ifdef	RZG2UL
#define OTP_DUMMY_READ	(0x280 >> 2)
#endif

/**********************************************************************************************************************
 Local Typedef definitions
 *********************************************************************************************************************/

/**********************************************************************************************************************
 Exported global variables
 *********************************************************************************************************************/

/**********************************************************************************************************************
 Private (static) variables and functions
 *********************************************************************************************************************/
static void otp_dummy_read(void);

/**********************************************************************************************************************
 * Function Name: otp_open
 * Description	: Open the OTP
 * Arguments	: none
 * Return Value : 0:OTP_NO_ERRORS
 *				 -1:OTP_ALREADY_POWER_UP
 *********************************************************************************************************************/
int32_t otp_open(void)
{
	int32_t ret_val = OTP_NO_ERRORS;

	if (0 != OTP.OTPPWR.BIT.PWR)
	{
		ret_val = OTP_ALREADY_POWER_UP;
	}
	else
	{
		while ((0 != OTP.OTPSTR.BIT.CMD_RDY) || (1 != OTP.OTPFLAG.BIT.OTPFLAG))
		{
			; /* wait */
		}
		OTP.OTPPWR.WORD = OTP_OTPPWR_MASK & (OTP_OTPPWR_PWR | OTP_OTPPWR_ACCL);	/* APB I/F enable */
		while (1 != OTP.OTPSTR.BIT.CMD_RDY)
		{
			; /* wait */
		}
	}
	return ret_val;
}

/**********************************************************************************************************************
 * End of function otp_open
 *********************************************************************************************************************/

/**********************************************************************************************************************
 * Function Name: otp_close
 * Description	: Close the OTP
 * Arguments	: none
 * Return Value : none
 *********************************************************************************************************************/
void otp_close(void)
{
	otp_dummy_read();
	OTP.OTPPWR.WORD = OTP_OTPPWR_MASK & ~(OTP_OTPPWR_PWR | OTP_OTPPWR_ACCL);	/* APB I/F disable */
	while (0 != OTP.OTPSTR.BIT.CMD_RDY)
	{
		; /* wait */
	}
	return;
}

/**********************************************************************************************************************
 * End of function otp_close
 *********************************************************************************************************************/

/**********************************************************************************************************************
 * Function Name: otp_read
 * Description	: Read the value from the OTP
 * Arguments	: [in]	addr -
 *						Address of where reading the functions
 *				  [out]	value -
 *						Pointer of where to put the reading value
 * Return Value : 0:OTP_NO_ERRORS
 *				 -1:OTP_ADDRESS_INVALID
 *				 -2:OTP_PROTECTION_ERROR(read) mast be close.
 *				 -3:OTP_ECC_SIGLE_COLLECTION
 *				 -4:OTP_ECC_DOUBLE_DETECTION
 *				 -6:OTP_COMMAND_NOT_READY
 *********************************************************************************************************************/
int32_t otp_read(const uint32_t addr, uint32_t * const value)
{
	int32_t ret_val = OTP_NO_ERRORS;

	if ((0 != (addr & 0x03)) || ((addr >> 2) > 0x1FF))
	{
		ret_val = OTP_ADDRESS_INVALID;
	}
	else
	{
		while (1 != OTP.OTPSTR.BIT.CMD_RDY)
		{
			; /* Polling */
		}

		/* set word address to OTPADRRD */
		OTP.OTPADRRD.WORD = (addr >> 2);

		*value = OTP.OTPDATARD.WORD;

		if (0 != OTP.OTPSTR.BIT.ERR_RDY_RD)
		{
			OTP.OTPSTR.BIT.ERR_RDY_RD = 0;
			ret_val = OTP_COMMAND_NOT_READY;
		}
		else
		{
			if (0 != OTP.OTPSTR.BIT.ERR_RP)
			{
				ret_val = OTP_PROTECTION_ERROR;	/* mast be close. */
			}
			else
			{
				if (0 != OTP.OTPINTSTS.BIT.SECINTSTS)
				{
					ret_val = OTP_ECC_SIGLE_COLLECTION;
				}
				else if (0 != OTP.OTPINTSTS.BIT.DEDINTSTS)
				{
					ret_val = OTP_ECC_DOUBLE_DETECTION;
				}
				else
				{
					;	/* no error */
				}
			}
		}
	}

	return ret_val;
}

/**********************************************************************************************************************
 * End of function otp_read
 *********************************************************************************************************************/

/**********************************************************************************************************************
 * Function Name: otp_write
 * Description	: Write the value to OTP
 * Arguments	: [in]	addr -
 *						Address of where writing the functions
 *				  [in]	value -
 *						Value to write
 * Return Value : 0:OTP_NO_ERRORS
 *				 -1:OTP_ADDRESS_INVALID
 *				 -2:OTP_PROTECTION_ERROR(write) must be close.
 *				 -3:OTP_ECC_SIGLE_COLLECTION
 *				 -4:OTP_ECC_DOUBLE_DETECTION
 *				 -5:OTP_VERIFY_ERROR
 *				 -6:OTP_COMMAND_NOT_READY
 *********************************************************************************************************************/
int32_t otp_write(const uint32_t addr, const uint32_t value)
{
	int32_t ret_val = OTP_NO_ERRORS;

	if ((0 != (addr & 0x03)) || ((addr >> 2) > 0x1FF))
	{
		ret_val = OTP_ADDRESS_INVALID;
	}
	else
	{
		while (1 != OTP.OTPSTR.BIT.CMD_RDY)
		{
			; /* Polling */
		}

		/* set word address to OTPADRRD */
		OTP.OTPADRWR.WORD = (addr >> 2);

		OTP.OTPDATAWR.WORD = value;

		OTP.OTPSTAWR.BIT.STAWR = 1;

		if (0 != OTP.OTPSTR.BIT.ERR_RDY_WR)
		{
			OTP.OTPSTR.BIT.ERR_RDY_WR = 0;
			ret_val = OTP_COMMAND_NOT_READY;
		}
		else
		{
			while ((1 != OTP.OTPSTR.BIT.CMD_RDY) || (0 != OTP.OTPSTAWR.BIT.STAWR))
			{
				; /* Polling */
			}

			if ((0 != OTP.OTPSTR.BIT.ERR_WP) || (0 != OTP.OTPSTR.BIT.ERR_WR))
			{
				ret_val = OTP_PROTECTION_ERROR;	/* must be close. */
			}
			else
			{
				uint32_t read_value;

				ret_val = otp_read(addr, &read_value);

				if ((0 == ret_val) && (read_value != value))
				{
					ret_val = OTP_VERIFY_ERROR;
				}
			}
		}
	}

	return ret_val;
}

/**********************************************************************************************************************
 * End of function otp_write
 *********************************************************************************************************************/

/**********************************************************************************************************************
 * Function Name: otp_dummy_read
 * Description	: Special sequence for read processing
 * Arguments	: none
 * Return Value : none
 *********************************************************************************************************************/
static void otp_dummy_read(void)
{
	uint32_t value;

	while (1 != OTP.OTPSTR.BIT.CMD_RDY)
	{
		; /* Polling */
	}

	OTP.OTPADRRD.WORD = OTP_DUMMY_READ;

	value = OTP.OTPDATARD.WORD;

	return;
}

/**********************************************************************************************************************
 * End of function otp_dummy_read
 *********************************************************************************************************************/

/**********************************************************************************************************************
 * Function Name: err_int_clear
 * Description	: Clear error interrupt flag.
 * Arguments	: none
 * Return Value : Error address
 *********************************************************************************************************************/
uint32_t err_int_clear(void)
{
	uint32_t ret_val = 0xffffffff;

	if (0 != OTP.OTPINTSTS.BIT.SECINTSTS)
	{
		OTP.OTPINTSTS.BIT.SECINTSTS = 0;		/* clear status */
		ret_val = OTP.OTPSECADDR.WORD << 2;		/* ecc single collection address. */
	}
	else if (0 != OTP.OTPINTSTS.BIT.DEDINTSTS)
	{
		OTP.OTPINTSTS.BIT.DEDINTSTS = 0;		/* clear status */
		ret_val = OTP.OTPDEDADDR.WORD << 2;		/* ecc double collection address. */
	}
	else
	{
		;	/* no error */
	}

	return ret_val;
}

/**********************************************************************************************************************
 * End of function err_int_clear
 *********************************************************************************************************************/
