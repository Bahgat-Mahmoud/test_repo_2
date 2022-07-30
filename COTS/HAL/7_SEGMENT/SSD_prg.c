/*
 * SSD_prg.c
seven segment interface
 *
 *  Created on: Jul 20, 2022
 *      Author: Bahgat Mahmoud
 */

#include  "../../LIB/STD_TYPES.h"

#include  "../../MCAL/DIO/DIO_int.h"
#include  "SSD_int.h"


//store  in flash and copy in RAM
static const u8 CGS_u8SSD_Nums[10] = 
{
	0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x47,0x7f,0x6f,0x77,0x7f,0x39,0x3f,0x79,0x71
};

void HSSD_vInit(void)
{
	MDIO_vSetPortDir(SSD_PORT,0xff);
}

void HSSD_vDisPlayNum(u8 A_u8Num)
{
	/*input validation*/
	if (A_u8Num < 10)
	{
#if SSD_TYPE==COM_CATHOOD
		MDIO_vSetPortVal( SSD_PORT, CGS_u8SSD_Nums[A_u8Num] ); //common cathood
#elif SSD_TYPE==COM_ANOOD
		MDIO_vSetPortVal(SSD_PORT, ~CGS_u8SSD_Nums[A_u8Num] ); //common anode
#endif

	}

}
void HSSD_vTurnOff(void)
{
#if SSD_TYPE==COM_CATHODE
	MDIO_vSetPortVal(SSD_PORT, 0x00);
#elif
	MDIO_vSetPortVal(SSD_PORT, 0xff);
#endif
}

