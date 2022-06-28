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
 * File Name	: otp_sys.h
 * Version		: 1.0
 * Description	: header file for OTP control functions .
 *********************************************************************************************************************/
/**********************************************************************************************************************
 * History	: DD.MM.YYYY Version	Description
 *			: 01.09.2020 1.00		First Release
 *********************************************************************************************************************/

/**********************************************************************************************************************
 Includes	<System Includes> , "Project Includes"
 *********************************************************************************************************************/

/**********************************************************************************************************************
 Macro definitions
 *********************************************************************************************************************/
#ifndef	OTP_SYS_H_
#define	OTP_SYS_H_

/* CLK control */
#define	REG_CPG_BASE_ADR	(0x11010000uL)
#define	REG_CPG_CLKON_OTP	(*(volatile uint32_t *)(CPG_BASE_ADDR + 0x5A4uL))	/* offset 0x5A4 */	/* default 3 */
#define	REG_CPG_RSTMON_OTP	(*(volatile uint32_t *)(CPG_BASE_ADDR + 0xA24uL))	/* offset 0xA24 */	/* default 0 */
#define	REG_CPG_RST_OTP		(*(volatile uint32_t *)(CPG_BASE_ADDR + 0x8ACuL))	/* offset 0x8AC */	/* default 1 */

/* OTP error/status types */
#define	OTP_NO_ERRORS				(0)
#define	OTP_ALREADY_POWER_UP		(-1)
#define	OTP_ADDRESS_INVALID			(-1)
#define	OTP_PROTECTION_ERROR		(-2)
#define	OTP_ECC_SIGLE_COLLECTION	(-3)
#define	OTP_ECC_DOUBLE_DETECTION	(-4)
#define	OTP_VERIFY_ERROR			(-5)
#define	OTP_COMMAND_NOT_READY		(-6)

/**********************************************************************************************************************
 Global Typedef definitions
 *********************************************************************************************************************/

/**********************************************************************************************************************
 External global variables
 *********************************************************************************************************************/

/**********************************************************************************************************************
 Exported global functions
 *********************************************************************************************************************/
/* Open the OTP */
extern int32_t otp_open(void);
/* Close the OTP */
extern void otp_close(void);
/* Read the value from the OTP */
extern int32_t otp_write(const uint32_t addr, const uint32_t value);
/* Write the value to OTP */
extern int32_t otp_read(const uint32_t addr, uint32_t * const value);
/* Clear error interrupt flag. */
extern uint32_t err_int_clear(void);

#endif /* OTP_SYS_H_ */
