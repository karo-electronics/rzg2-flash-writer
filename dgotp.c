/*
 * Copyright (c) 2015-2021, Renesas Electronics Corporation. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include	<stddef.h>
#include	"types.h"
#include	"common.h"
#include	"devdrv.h"
#include	"dgotp.h"
#include	"otp/otp_sys.h"

#define	STR_BUF_SIZE	(64)
#define	KEY_BUF_SIZE	(16)

//////////////////////////////////////////
// SetAddInputKey
//////////////////////////////////////////
static void SetAddInputKey(uint32_t *Address)
{
	char		str[STR_BUF_SIZE];
	char		buf[KEY_BUF_SIZE], key[KEY_BUF_SIZE], chCnt, chPtr;
	uint32_t	loop;
	uint32_t	wrData;

	loop = 1;
	while(loop)
	{
		PutStr("  Please Input : H'", 0);
		GetStr(key, &chCnt);
		chPtr = 0;
		if (!GetStrBlk(key, buf, &chPtr, 0))
		{
			if (chPtr == 1)
			{
				/* Case Return */
			}
			else if((buf[0] == '.'))
			{
				/* Case End */
				loop = 0;
			}
			else if (chPtr > (char)((SIZE_32BIT << 1) + 1))
			{
				/* Case Data Size Over */
				PutStr("Syntax Error", 1);
			}
			else
			{
				if (HexAscii2Data((unsigned char*)buf, &wrData))
				{
					PutStr("Syntax Error", 1);
				}
				else
				{
					*Address = wrData;
					loop = 0;
				}
			}
		}
		else
		{
			PutStr("Syntax Error", 1);
		}
	}
}

/************************************************************************
	MODULE			: dgOTP_write				*
	FUNCTION		: write OTP				*
	COMMAND			: OTP_W					*
	INPUT PARAMETER		: OTP_W					*
*************************************************************************/
void dgOTP_write(void)
{
	char		str[STR_BUF_SIZE];
	uint32_t	OtpAddr, OtpData;
	int32_t		ret;

	PutStr("===== Write data to OTP ============", 1);
	PutStr("===== Please Input Address ============", 1);
	SetAddInputKey(&OtpAddr);
	PutStr("===== Please Input Data ============", 1);
	SetAddInputKey(&OtpData);

	ret = otp_open();
	if (OTP_NO_ERRORS != ret)
	{
		PutStr("Can't use OTP", 1);
		return;		// Error abort
	}
	ret = otp_write(OtpAddr, OtpData);
	switch (ret)
	{
	case	OTP_ECC_DOUBLE_DETECTION:	// -4:OTP_ECC_DOUBLE_DETECTION
		OtpAddr = err_int_clear();
		Data2HexAscii(OtpAddr, str, SIZE_32BIT);
		PutStr("ECC Double Error Detection at : H'", 0);
		PutStr(str, 1);
		break;
	case	OTP_ECC_SIGLE_COLLECTION:	// -3:OTP_ECC_SIGLE_COLLECTION
		/* fall through */
		OtpAddr = err_int_clear();
		Data2HexAscii(OtpAddr, str, SIZE_32BIT);
		PutStr("ECC Single Error Collection at : H'", 0);
		PutStr(str, 1);
		/* fall through */
	case	OTP_NO_ERRORS:				// 0:OTP_NO_ERRORS
		Data2HexAscii(OtpData, str, SIZE_32BIT);
		PutStr(" Read data : H'", 0);
		PutStr(str, 1);
		break;
	case	OTP_ADDRESS_INVALID:		// -1:OTP_ADDRESS_INVALID
		PutStr("Invalid address", 1);
		break;
	case	OTP_PROTECTION_ERROR:		// -2:OTP_PROTECTION_ERROR(write) must be close.
		PutStr("Write protected", 1);
		break;
	case	OTP_VERIFY_ERROR:			// -5:OTP_VERIFY_ERROR
		PutStr("Data verify failed", 1);
		break;
	case	OTP_COMMAND_NOT_READY:		// -6:OTP_COMMAND_NOT_READY
		PutStr("Command not ready", 1);
		break;
	default:
		PutStr("Internal Error", 1);
		break;
	}

	PutStr("=======================================", 1);
	otp_close();
}


/************************************************************************
	MODULE			: dgOTP_read				*
	FUNCTION		: read OTP				*
	COMMAND			: OTP_R					*
	INPUT PARAMETER		: OTP_R					*
*************************************************************************/
void dgOTP_read(void)
{
	char		str[STR_BUF_SIZE];
	uint32_t	OtpAddr, OtpData;
	int32_t		ret;

	PutStr("===== Read data from OTP ============", 1);
	PutStr("===== Please Input Address ============", 1);
	SetAddInputKey(&OtpAddr);

	ret = otp_open();
	if (OTP_NO_ERRORS != ret)
	{
		PutStr("Can't use OTP", 1);
		return;		// Error abort
	}
	OtpData = 0xaaaa5555;
	ret = otp_read(OtpAddr, &OtpData);
	switch (ret)
	{
	case	OTP_ECC_DOUBLE_DETECTION:	// -4:OTP_ECC_DOUBLE_DETECTION
		OtpAddr = err_int_clear();
		Data2HexAscii(OtpAddr, str, SIZE_32BIT);
		PutStr("ECC Double Error Detection at : H'", 0);
		PutStr(str, 1);
		break;
	case	OTP_ECC_SIGLE_COLLECTION:	// -3:OTP_ECC_SIGLE_COLLECTION
		/* fall through */
		OtpAddr = err_int_clear();
		Data2HexAscii(OtpAddr, str, SIZE_32BIT);
		PutStr("ECC Single Error Collection at : H'", 0);
		PutStr(str, 1);
		/* fall through */
	case	OTP_NO_ERRORS:				// 0:OTP_NO_ERRORS
		Data2HexAscii(OtpData, str, SIZE_32BIT);
		PutStr(" Read data : H'", 0);
		PutStr(str, 1);
		break;
	case	OTP_ADDRESS_INVALID:		// -1:OTP_ADDRESS_INVALID
		PutStr("Invalid address", 1);
		break;
	case	OTP_PROTECTION_ERROR:		// -2:OTP_PROTECTION_ERROR(read) mast be close.
		PutStr("Read protected", 1);
		break	;
	case	OTP_COMMAND_NOT_READY:		// -6:OTP_COMMAND_NOT_READY
		PutStr("Command not ready", 1);
		break;
	default:
		PutStr("Internal Error", 1);
		break;
	}

	PutStr("=======================================", 1);
	otp_close();
}

/************************************************************************
	MODULE			: dgOTP_dump				*
	FUNCTION		: dump OTP				*
	COMMAND			: OTP_D					*
	INPUT PARAMETER		: OTP_D					*
*************************************************************************/
void dgOTP_dump(void)
{
	char		str[STR_BUF_SIZE];
	uint32_t	OtpAddr, OtpData;
	int32_t		ret;
	int32_t		i;

	PutStr("===== Read data from OTP ============", 1);
	PutStr("===== Please Input Address ============", 1);
	SetAddInputKey(&OtpAddr);

	ret = otp_open();
	if (OTP_NO_ERRORS != ret)
	{
		PutStr("Can't use OTP", 1);
		return;		// Error abort
	}
	for (i = 0; (i < 16); i++)
	{
		OtpData = 0xaaaa5555;
		ret = otp_read((OtpAddr & ~0x3f) + (i << 2), &OtpData);
		switch (ret)
		{
	case	OTP_ECC_DOUBLE_DETECTION:	// -4:OTP_ECC_DOUBLE_DETECTION
		OtpAddr = err_int_clear();
		Data2HexAscii(OtpAddr, str, SIZE_32BIT);
		PutStr("ECC Double Error Detection at : H'", 0);
		PutStr(str, 1);
		break;
	case	OTP_ECC_SIGLE_COLLECTION:	// -3:OTP_ECC_SIGLE_COLLECTION
		/* fall through */
		OtpAddr = err_int_clear();
		Data2HexAscii(OtpAddr, str, SIZE_32BIT);
		PutStr("ECC Single Error Collection at : H'", 0);
		PutStr(str, 1);
		/* fall through */
		case	OTP_NO_ERRORS:				// 0:OTP_NO_ERRORS
			Data2HexAscii(OtpData, str, SIZE_32BIT);
			PutStr(" Read data : H'", 0);
			PutStr(str, 1);
			break;
		case	OTP_ADDRESS_INVALID:		// -1:OTP_ADDRESS_INVALID
			PutStr("Invalid address", 1);
			break;
		case	OTP_PROTECTION_ERROR:		// -2:OTP_PROTECTION_ERROR(read) mast be close.
			i = 16; // loop out
			PutStr("Read protected", 1);
			break;
		case OTP_COMMAND_NOT_READY:			// -6:OTP_COMMAND_NOT_READY
			PutStr("Command not ready", 1);
			break;
		default:
			PutStr("Internal Error", 1);
			break;
		}
	}

	PutStr("=======================================", 1);
	otp_close();
}
