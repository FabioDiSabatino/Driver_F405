/**
 *******************************************************************************
 * @file    LPS25HB_Driver.c
 * @author  MEMS Application Team
 * @version V2.0.0
 * @date    10-December-2015
 * @brief   LPS25HB Platform Independent Driver
 *******************************************************************************
 * @attention
 *
 * <h2><center>&copy; COPYRIGHT(c) 2016 STMicroelectronics</center></h2>
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *   1. Redistributions of source code must retain the above copyright notice,
 *      this list of conditions and the following disclaimer.
 *   2. Redistributions in binary form must reproduce the above copyright notice,
 *      this list of conditions and the following disclaimer in the documentation
 *      and/or other materials provided with the distribution.
 *   3. Neither the name of STMicroelectronics nor the names of its contributors
 *      may be used to endorse or promote products derived from this software
 *      without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 ******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include "LPS25HB_Driver.h"

#ifdef  USE_FULL_ASSERT_LPS25HB
#include <stdio.h>
#endif

/** @addtogroup Environmental_Sensor
* @{
*/

/** @defgroup LPS25HB_DRIVER
* @brief LPS25HB DRIVER
* @{
*/

/** @defgroup LPS25HB_Imported_Function_Prototypes
* @{
*/
//extern uint8_t Sensor_IO_Write( void *handle, uint8_t WriteAddr, uint8_t *pBuffer, uint16_t nBytesToWrite );
//extern uint8_t Sensor_IO_Read( void *handle, uint8_t ReadAddr, uint8_t *pBuffer, uint16_t nBytesToRead );
/**
* @}
*/

/** @defgroup LPS25HB_My_Private_Variables
* @{
*/
uint32_t I2C_Timeout = 0x1000;    					//Added By Me!!! *<! Value of Timeout when I2C communication fails */
uint8_t LPS25HB_1[5] = 	{							//Added By Me!!!
							LPS25HB_REF_P_XL_VAL,	 
							LPS25HB_REF_P_L_VAL, 	
							LPS25HB_REF_P_H_VAL, 	
							LPS25HB_WHO_AM_I_VAL, 	
							LPS25HB_RES_CONF_VAL
						};
uint8_t LPS25HB_2[5] = 	{							//Added By Me!!!
							LPS25HB_CTRL_VAL1,	 
							LPS25HB_CTRL_VAL2, 	
							LPS25HB_CTRL_VAL3, 	
							LPS25HB_CTRL_VAL4, 	
							LPS25HB_INTERRUPT_CFG_VAL
						};
uint8_t LPS25HB_3[4] = 	{							//Added By Me!!!
							LPS25HB_CTRL_FIFO_VAL,	 
							LPS25HB_STATUS_FIFO_VAL, 	
							LPS25HB_THS_P_LOW_VAL, 	
							LPS25HB_THS_P_HIGH_VAL
						};

/**
* @}
*/

/** @defgroup LPS25HB_My_Private_Functions
* @{
*/

/*******************************************************************************
 * @brief  Read a register of the device through BUS
 * @param  B_Addr Device address on BUS
 * @param  Reg The target register address to read
 * @param  pBuffer The data to be read
 * @param  Size Number of bytes to be read
 * @retval 0 in case of success
 * @retval 1 in case of failure
 *******************************************************************************/
uint8_t I2C_ReadData(uint8_t B_Addr, uint8_t Reg, uint8_t* pBuffer, uint16_t Size)
{
  HAL_StatusTypeDef status = HAL_OK;

  status = HAL_I2C_Mem_Read(&hi2c1, B_Addr, (uint16_t)Reg, I2C_MEMADD_SIZE_8BIT, &pBuffer[0], Size, I2C_Timeout);
  /* Check the communication status */
  if( status != HAL_OK )
  {
    /* Execute user timeout callback */
    // I2C_Error( B_Addr );
    return 1;
  }
  else
  {
    return 0;
  }
}

/**
 * @brief  Write data to the register of the device through BUS
 * @param  B_Addr Device address on BUS
 * @param  Reg The target register address to be written
 * @param  pBuffer The data to be written
 * @param  Size Number of bytes to be written
 * @retval 0 in case of success
 * @retval 1 in case of failure
 */
uint8_t I2C_WriteData(uint8_t B_Addr, uint8_t Reg, uint8_t* pBuffer, uint16_t Size)
{
  HAL_StatusTypeDef status = HAL_OK;

  status = HAL_I2C_Mem_Write(&hi2c1, B_Addr, (uint16_t)Reg, I2C_MEMADD_SIZE_8BIT, &pBuffer[0], Size, I2C_Timeout);
  /* Check the communication status */
  if( status != HAL_OK )
  {
    /* Execute user timeout callback */
    // I2C_EXPBD_Error( B_Addr );
    return 1;
  }
  else
  {
    return 0;
  }
}

/**
 * @brief  Write data to the register of the device through BUS in DMA mode
 * @param  B_Addr Device address on BUS
 * @param  Reg The target register address to be written
 * @param  pBuffer The data to be written
 * @param  Size Number of bytes to be written
 * @retval 0 in case of success
 * @retval 1 in case of failure
 */
uint8_t I2C_WriteData_DMA(uint8_t B_Addr, uint8_t Reg, uint8_t* pBuffer, uint16_t Size)
{
  HAL_StatusTypeDef status = HAL_OK;

  status = HAL_I2C_Mem_Write_DMA(&hi2c1, B_Addr, (uint16_t)Reg, I2C_MEMADD_SIZE_8BIT, &pBuffer[0], Size);
  /* Check the communication status */
  if( status != HAL_OK )
  {
    /* Execute user timeout callback */
    // I2C_EXPBD_Error( B_Addr );
    return 1;
  }
  else
  {
    return 0;
  }
}

/*******************************************************************************
* Function Name   : LPS25HB_ReadReg
* Description   : Generic Reading function. It must be fullfilled with either
*         : I2C or SPI reading functions
* Input       : Register Address
* Output      : Data Read
* Return      : Status [LPS25HB_ERROR, LPS25HB_OK]
*******************************************************************************/
LPS25HB_Error_et LPS25HB_ReadReg(uint8_t B_Addr, uint8_t RegAddr, uint16_t NumByteToRead, uint8_t *Data)
{

  if ( NumByteToRead > 1 ) RegAddr |= 0x80;
  
  if (I2C_ReadData(B_Addr, RegAddr, Data, NumByteToRead))
    return LPS25HB_ERROR;
  else
    return LPS25HB_OK;
}

/*******************************************************************************
* Function Name	: LPS25HB_WriteReg
* Description  	: Generic Writing function in normal mode. It must be fullfilled with either
*         		: I2C or SPI writing function
* Input       	: Register Address, Data to be written
* Output      	: None
* Return      	: Status [LPS25HB_ERROR, LPS25HB_OK]
*******************************************************************************/
LPS25HB_Error_et LPS25HB_WriteReg(uint8_t B_Addr, uint8_t RegAddr, uint16_t NumByteToWrite, uint8_t *Data)
{

  if ( NumByteToWrite > 1 ) RegAddr |= 0x80;
  
  if (I2C_WriteData(B_Addr, RegAddr, Data, NumByteToWrite))
    return LPS25HB_ERROR;
  else
    return LPS25HB_OK;
}

/*******************************************************************************
* Function Name	: LPS25HB_WriteReg
* Description   : Generic Writing function in DMA mode. It must be fullfilled with either
*         		: I2C or SPI writing function
* Input       	: Register Address, Data to be written
* Output      	: None
* Return      	: Status [LPS25HB_ERROR, LPS25HB_OK]
*******************************************************************************/
LPS25HB_Error_et LPS25HB_WriteReg_DMA(uint8_t B_Addr, uint8_t RegAddr, uint16_t NumByteToWrite, uint8_t *Data)
{

  if ( NumByteToWrite > 1 ) RegAddr |= 0x80;

  if (I2C_WriteData_DMA(B_Addr, RegAddr, Data, NumByteToWrite))
    return LPS25HB_ERROR;
  else
    return LPS25HB_OK;
}

/*******************************************************************************
* Function Name	: LPS25HB_Init
* Description   : Generic Writing function. It must be fullfilled with either
*         		: I2C or SPI writing function
* Input       	: Register Address, Data to be written
* Output      	: None
* Return      	: Status [LPS25HB_ERROR, LPS25HB_OK]
*******************************************************************************/
LPS25HB_Error_et LPS25HB_Init(uint8_t B_Addr, uint8_t RegAddr, uint8_t *RegValues, uint8_t Size)
{
	if (LPS25HB_WriteReg_DMA(B_Addr, RegAddr, Size, &RegValues[0]))
		return LPS25HB_ERROR;
//	HAL_I2C_Mem_Write_DMA(&hi2c1,B_Addr,0,I2C_MEMADD_SIZE_8BIT,&RegValues[0],Size);

	return LPS25HB_OK;

}

/*******************************************************************************
* Function Name	: LPS25HB_Init_New
* Description   : Generic Writing function. It must be fullfilled with either
*         		: I2C or SPI writing function
* Input       	: Register Address, Data to be written
* Output      	: None
* Return      	: Status [LPS25HB_ERROR, LPS25HB_OK]
*******************************************************************************/
LPS25HB_Error_et LPS25HB_Init_New(uint8_t B_Addr)
{
	uint8_t tmp;

	 tmp = (uint8_t)LPS25HB_REF_P_XL_VAL;
	 if(LPS25HB_WriteReg(B_Addr, LPS25HB_REF_P_XL_REG, 1, &tmp))
	   return LPS25HB_ERROR;

	 tmp = (uint8_t)LPS25HB_REF_P_L_VAL;
	 if(LPS25HB_WriteReg(B_Addr, LPS25HB_REF_P_L_REG, 1, &tmp))
	   return LPS25HB_ERROR;

	 tmp = (uint8_t)LPS25HB_REF_P_H_VAL;
	 if(LPS25HB_WriteReg(B_Addr, LPS25HB_REF_P_H_REG, 1, &tmp))
	   return LPS25HB_ERROR;

	 tmp = (uint8_t)LPS25HB_RES_CONF_VAL;
	 if(LPS25HB_WriteReg(B_Addr, LPS25HB_RES_CONF_REG, 1, &tmp))
	   return LPS25HB_ERROR;

	 tmp = (uint8_t)LPS25HB_CTRL_VAL1;
	 if(LPS25HB_WriteReg(B_Addr, LPS25HB_CTRL_REG1, 1, &tmp))
	   return LPS25HB_ERROR;

	 tmp = (uint8_t)LPS25HB_CTRL_VAL2;
	 if(LPS25HB_WriteReg(B_Addr, LPS25HB_CTRL_REG2, 1, &tmp))
	   return LPS25HB_ERROR;
	 else
	   HAL_Delay(3); 				//The Reboot Process takes about 2.2 ms to complete

	 tmp = (uint8_t)LPS25HB_CTRL_VAL3;
	 if(LPS25HB_WriteReg(B_Addr, LPS25HB_CTRL_REG3, 1, &tmp))
	   return LPS25HB_ERROR;

	 tmp = (uint8_t)LPS25HB_CTRL_VAL4;
	 if(LPS25HB_WriteReg(B_Addr, LPS25HB_CTRL_REG4, 1, &tmp))
	   return LPS25HB_ERROR;

	 tmp = (uint8_t)LPS25HB_INTERRUPT_CFG_VAL;
	 if(LPS25HB_WriteReg(B_Addr, LPS25HB_INTERRUPT_CFG_REG, 1, &tmp))
	   return LPS25HB_ERROR;

	 tmp = (uint8_t)LPS25HB_CTRL_FIFO_VAL;
	 if(LPS25HB_WriteReg(B_Addr, LPS25HB_CTRL_FIFO_REG, 1, &tmp))
	   return LPS25HB_ERROR;

	 tmp = (uint8_t)LPS25HB_STATUS_FIFO_VAL;
	 if(LPS25HB_WriteReg(B_Addr, LPS25HB_STATUS_FIFO_REG, 1, &tmp))
	   return LPS25HB_ERROR;

	 tmp = (uint8_t)LPS25HB_THS_P_LOW_VAL;
	 if(LPS25HB_WriteReg(B_Addr, LPS25HB_THS_P_LOW_REG, 1, &tmp))
	   return LPS25HB_ERROR;

	 tmp = (uint8_t)LPS25HB_THS_P_HIGH_VAL;
	 if(LPS25HB_WriteReg(B_Addr, LPS25HB_THS_P_HIGH_REG, 1, &tmp))
	   return LPS25HB_ERROR;

	 tmp = (uint8_t)LPS25HB_RPDS_L_VAL;
	 if(LPS25HB_WriteReg(B_Addr, LPS25HB_RPDS_L_REG, 1, &tmp))
	   return LPS25HB_ERROR;

	 tmp = (uint8_t)LPS25HB_RPDS_H_VAL;
	 if(LPS25HB_WriteReg(B_Addr, LPS25HB_RPDS_H_REG, 1, &tmp))
	   return LPS25HB_ERROR;

	 if (LPS25HB_Get_DeviceID(LPS25HB_BADDR, &tmp))
		return LPS25HB_ERROR;

	 if (tmp != LPS25HB_WHO_AM_I_VAL)
		return LPS25HB_ERROR;

	return LPS25HB_OK;
}

/*******************************************************************************
* Function Name	: MX_LPS25HB_Init
* Description   : LPS25HB Global init
*         		: I2C or SPI writing function
* Input       	: None
* Output      	: None
* Return      	: Status [LPS25HB_ERROR, LPS25HB_OK]
*******************************************************************************/
LPS25HB_Error_et MX_LPS25HB_Init()
{
/*	if (LPS25HB_Init(LPS25HB_BADDR, 0x08, LPS25HB_1, 5))
		return LPS25HB_ERROR;
	HAL_Delay(i2c_delay);
	if (LPS25HB_Init(LPS25HB_BADDR, 0x20, LPS25HB_2, 5))
		return LPS25HB_ERROR;
	HAL_Delay(i2c_delay);
	if (LPS25HB_Init(LPS25HB_BADDR, 0x2E, LPS25HB_3, 4))
		return LPS25HB_ERROR;
	HAL_Delay(i2c_delay); */

	if (LPS25HB_Init_New(LPS25HB_BADDR))
		return LPS25HB_ERROR;
	return LPS25HB_OK;
}

/**
* @brief Set the reference pressure 24-bit data subtracted from the sensor output
* measurement.
* @detail REF_P_XL & REF_P_L & REF_P_H is expressed as signed number.
* @param  *B_Addr Device B_Addr.
* @param  Raw Pressure reference
* @retval Status [LPS25HB_ERROR, LPS25HB_OK]
*/
LPS25HB_Error_et LPS25HB_Set_Reference_Pressure(uint8_t B_Addr, int32_t P_ref)
{
  uint8_t buffer[3];

  buffer[0] = (uint8_t)(P_ref);
  buffer[1] = (uint8_t)(((uint16_t)(P_ref)) >> 8);
  buffer[2] = (uint8_t)(((uint32_t)(P_ref)) >> 16);

  /* Disable DIFF_EN bit in CTRL_REG1 */
  if(LPS25HB_Set_InterruptCircuitEnable(B_Addr, LPS25HB_DISABLE))
    return LPS25HB_ERROR;

  if(LPS25HB_WriteReg(B_Addr, LPS25HB_REF_P_XL_REG, 3, buffer))
    return LPS25HB_ERROR;

  /* Enable DIFF_EN bit in CTRL_REG1 */
  if(LPS25HB_Set_InterruptCircuitEnable(B_Addr, LPS25HB_ENABLE))
    return LPS25HB_ERROR;

  return LPS25HB_OK;
}

/**
* @}
*/

/** @defgroup LPS25HB_Public_Functions
* @{
*/

/**
* @brief  Read identification code by WHO_AM_I register
* @param  *handle Device handle.
* @param  Buffer to fill by Device identification Value.
* @retval Status [LPS25HB_ERROR, LPS25HB_OK]
*/
LPS25HB_Error_et LPS25HB_Get_DeviceID(uint8_t B_Addr, uint8_t* deviceid)
{
  if (LPS25HB_ReadReg(B_Addr, LPS25HB_WHO_AM_I_REG, 1, deviceid))
    return LPS25HB_ERROR;
    
  return LPS25HB_OK;
}

/**
* @brief  Get the LPS25HB driver version.
* @param  Version Driver version
* @retval Status [LPS25HB_ERROR, LPS25HB_OK]
*/
LPS25HB_Error_et LPS25HB_Get_DriverVersion(LPS25HB_DriverVersion_st *Version)
{
  Version->Major = LPS25HB_DriverVersion_Major;
  Version->Minor = LPS25HB_DriverVersion_Minor;
  Version->Point = LPS25HB_DriverVersion_Point;
  
  return LPS25HB_OK;
}

/**
* @brief  Set LPS25HB Pressure and Temperature Resolution Mode
* @param  *B_Addr Device B_Addr.
* @param  Pressure Resolution
* @param  Temperature Resolution
* @retval Status [LPS25HB_ERROR, LPS25HB_OK]
*/
LPS25HB_Error_et LPS25HB_Set_Avg(uint8_t B_Addr, LPS25HB_Avgp_et avgp, LPS25HB_Avgt_et avgt )
{
  uint8_t tmp;
  
  LPS25HB_assert_param(IS_LPS25HB_AVGT(avgt));
  LPS25HB_assert_param(IS_LPS25HB_AVGP(avgp));
  
  if(LPS25HB_ReadReg(B_Addr, LPS25HB_RES_CONF_REG, 1, &tmp))
    return LPS25HB_ERROR;
    
  tmp &= ~(LPS25HB_AVGT_MASK | LPS25HB_AVGP_MASK);
  tmp |= (uint8_t)avgp;
  tmp |= (uint8_t)avgt;
  
  if(LPS25HB_WriteReg(B_Addr, LPS25HB_RES_CONF_REG, 1, &tmp) )
    return LPS25HB_ERROR;
    
  return LPS25HB_OK;
}

/**
* @brief  Exit the shutdown mode for LPS25HB.
* @param  *B_Addr Device B_Addr.
* @retval Status [LPS25HB_ERROR, LPS25HB_OK]
*/
LPS25HB_Error_et LPS25HB_Activate(uint8_t B_Addr)
{
  if(LPS25HB_Set_PowerDownMode(B_Addr, LPS25HB_SET))
    return LPS25HB_ERROR;
    
  return LPS25HB_OK;
}

/**
* @brief  Enter the shutdown mode for LPS25HB.
* @param  *B_Addr Device B_Addr.
* @retval Status [LPS25HB_ERROR, LPS25HB_OK]
*/
LPS25HB_Error_et LPS25HB_DeActivate(uint8_t B_Addr)
{
  if(LPS25HB_Set_PowerDownMode(B_Addr, LPS25HB_RESET))
    return LPS25HB_ERROR;
    
  return LPS25HB_OK;
}

/**
* @brief  Set LPS25HB Pressure Resolution Mode
* @param  *B_Addr Device B_Addr.
* @param  Pressure Resolution
* @retval Status [LPS25HB_ERROR, LPS25HB_OK]
*/
LPS25HB_Error_et LPS25HB_Set_AvgP(uint8_t B_Addr, LPS25HB_Avgp_et avgp)
{
  uint8_t tmp;
  
  LPS25HB_assert_param(IS_LPS25HB_AVGP(avgp));
  
  if(LPS25HB_ReadReg(B_Addr, LPS25HB_RES_CONF_REG, 1, &tmp))
    return LPS25HB_ERROR;
    
  tmp &= ~LPS25HB_AVGP_MASK;
  tmp |= (uint8_t)avgp;
  
  if(LPS25HB_WriteReg(B_Addr, LPS25HB_RES_CONF_REG, 1, &tmp))
    return LPS25HB_ERROR;
    
  return LPS25HB_OK;
}

/**
* @brief  Set LPS25HB Temperature Resolution Mode
* @param  *B_Addr Device B_Addr.
* @param  Temperature Resolution
* @retval Status [LPS25HB_ERROR, LPS25HB_OK]
*/
LPS25HB_Error_et LPS25HB_Set_AvgT(uint8_t B_Addr, LPS25HB_Avgt_et avgt)
{
  uint8_t tmp;
  
  LPS25HB_assert_param(IS_LPS25HB_AVGT(avgt));
  
  if(LPS25HB_ReadReg(B_Addr, LPS25HB_RES_CONF_REG, 1, &tmp))
    return LPS25HB_ERROR;
    
  tmp &= ~LPS25HB_AVGT_MASK;
  tmp |= (uint8_t)avgt;
  
  if(LPS25HB_WriteReg(B_Addr, LPS25HB_RES_CONF_REG, 1, &tmp))
    return LPS25HB_ERROR;
    
  return LPS25HB_OK;
}

/**
* @brief  Get LPS25HB Pressure Resolution Mode
* @param  *B_Addr Device B_Addr.
* @param  Pressure Resolution
* @retval Status [LPS25HB_ERROR, LPS25HB_OK]
*/
LPS25HB_Error_et LPS25HB_Get_AvgP(uint8_t B_Addr, LPS25HB_Avgp_et* avgp)
{
  uint8_t tmp;
  
  if(LPS25HB_ReadReg(B_Addr, LPS25HB_RES_CONF_REG, 1, &tmp))
    return LPS25HB_ERROR;
    
  *avgp = (LPS25HB_Avgp_et)(tmp & LPS25HB_AVGP_MASK);
  
  return LPS25HB_OK;
}

/**
* @brief  Get LPS25HB Temperature Resolution Mode
* @param  *B_Addr Device B_Addr.
* @param  Temperature Resolution
* @retval Status [LPS25HB_ERROR, LPS25HB_OK]
*/
LPS25HB_Error_et LPS25HB_Get_AvgT(uint8_t B_Addr, LPS25HB_Avgt_et* avgt)
{
  uint8_t tmp;
  
  if(LPS25HB_ReadReg(B_Addr, LPS25HB_RES_CONF_REG, 1, &tmp) )
    return LPS25HB_ERROR;
    
  *avgt = (LPS25HB_Avgt_et)(tmp & LPS25HB_AVGT_MASK);
  
  return LPS25HB_OK;
}

/**
* @brief  Set LPS25HB Output Data Rate
* @param  *B_Addr Device B_Addr.
* @param  Output Data Rate
* @retval Status [LPS25HB_ERROR, LPS25HB_OK]
*/
LPS25HB_Error_et LPS25HB_Set_Odr(uint8_t B_Addr, LPS25HB_Odr_et odr)
{
  uint8_t tmp;
  
  LPS25HB_assert_param(IS_LPS25HB_ODR(odr));
  
  if(LPS25HB_ReadReg(B_Addr, LPS25HB_CTRL_REG1, 1, &tmp))
    return LPS25HB_ERROR;
    
  tmp &= ~LPS25HB_ODR_MASK;
  tmp |= (uint8_t)odr;
  
  if(LPS25HB_WriteReg(B_Addr, LPS25HB_CTRL_REG1, 1, &tmp))
    return LPS25HB_ERROR;
    
  return LPS25HB_OK;
}

/**
* @brief  Get LPS25HB Output Data Rate
* @param  *B_Addr Device B_Addr.
* @param  Buffer to empty with Output Data Rate
* @retval Status [LPS25HB_ERROR, LPS25HB_OK]
*/
LPS25HB_Error_et LPS25HB_Get_Odr(uint8_t B_Addr, LPS25HB_Odr_et* odr)
{
  uint8_t tmp;
  
  if(LPS25HB_ReadReg(B_Addr, LPS25HB_CTRL_REG1, 1, &tmp))
    return LPS25HB_ERROR;
    
  *odr = (LPS25HB_Odr_et)(tmp & LPS25HB_ODR_MASK);
  
  return LPS25HB_OK;
}

/**
* @brief  SET/RESET LPS25HB Power Down Mode bit
* @param  *B_Addr Device B_Addr.
* @param  LPS25HB_SET (Active Mode)/LPS25HB_RESET (Power Down Mode)
* @retval Status [LPS25HB_ERROR, LPS25HB_OK]
*/
LPS25HB_Error_et LPS25HB_Set_PowerDownMode(uint8_t B_Addr, LPS25HB_BitStatus_et pd)
{
  uint8_t tmp;
  
  LPS25HB_assert_param(IS_LPS25HB_BitStatus(pd));
  
  if(LPS25HB_ReadReg(B_Addr, LPS25HB_CTRL_REG1, 1, &tmp))
    return LPS25HB_ERROR;
    
  tmp &= ~LPS25HB_PD_MASK;
  tmp |= ((uint8_t)pd) << LPS25HB_PD_BIT;
  
  if(LPS25HB_WriteReg(B_Addr, LPS25HB_CTRL_REG1, 1, &tmp))
    return LPS25HB_ERROR;
    
  return LPS25HB_OK;
}

/**
* @brief  Set Block Data Mode
* @detail It is recommended to set BDU bit to �1�.
* @detail This feature avoids reading LSB and MSB related to different samples.
* @param  *B_Addr Device B_Addr.
* @param  LPS25HB_BDU_CONTINUOS_UPDATE, LPS25HB_BDU_NO_UPDATE
* @retval Status [LPS25HB_ERROR, LPS25HB_OK]
*/
LPS25HB_Error_et LPS25HB_Set_Bdu(uint8_t B_Addr, LPS25HB_Bdu_et bdu)
{
  uint8_t tmp;
  
  LPS25HB_assert_param(IS_LPS25HB_BDUMode(bdu));
  
  if(LPS25HB_ReadReg(B_Addr, LPS25HB_CTRL_REG1, 1, &tmp))
    return LPS25HB_ERROR;
    
  tmp &= ~LPS25HB_BDU_MASK;
  tmp |= ((uint8_t)bdu);
  
  if(LPS25HB_WriteReg(B_Addr, LPS25HB_CTRL_REG1, 1, &tmp))
    return LPS25HB_ERROR;
    
  return LPS25HB_OK;
}

/**
* @brief  Get Block Data Mode
* @param  *B_Addr Device B_Addr.
* @param  Buffer to empty whit thw bdu mode read from sensor
* @retval Status [LPS25HB_ERROR, LPS25HB_OK]
*/
LPS25HB_Error_et LPS25HB_Get_Bdu(uint8_t B_Addr, LPS25HB_Bdu_et* bdu)
{
  uint8_t tmp;
  
  if(LPS25HB_ReadReg(B_Addr, LPS25HB_CTRL_REG1, 1, &tmp))
    return LPS25HB_ERROR;
    
  *bdu = (LPS25HB_Bdu_et)(tmp & LPS25HB_BDU_MASK);
  
  return LPS25HB_OK;
}

/**
* @brief  Enable/Disable Interrupt Circuit.
* @param  *B_Addr Device B_Addr.
* @param  LPS25HB_ENABLE/LPS25HB_DISABLE
* @retval Status [LPS25HB_ERROR, LPS25HB_OK]
*/
LPS25HB_Error_et LPS25HB_Set_InterruptCircuitEnable(uint8_t B_Addr, LPS25HB_State_et diff_en)
{
  uint8_t tmp;
  
  LPS25HB_assert_param(IS_LPS25HB_State(diff_en));
  
  if(LPS25HB_ReadReg(B_Addr, LPS25HB_CTRL_REG1, 1, &tmp))
    return LPS25HB_ERROR;
    
  tmp &= ~LPS25HB_DIFF_EN_MASK;
  tmp |= ((uint8_t)diff_en) << LPS25HB_DIFF_EN_BIT;
  
  if(LPS25HB_WriteReg(B_Addr, LPS25HB_CTRL_REG1, 1, &tmp))
    return LPS25HB_ERROR;
    
  return LPS25HB_OK;
}

/**
* @brief  Get the Interrupt Circuit bit.
* @param  *B_Addr Device B_Addr.
* @param  Buffer to fill whith diff_en mode read from sensor
* @retval Status [LPS25HB_ERROR, LPS25HB_OK]
*/
LPS25HB_Error_et LPS25HB_Get_InterruptCircuitEnable(uint8_t B_Addr, LPS25HB_State_et* diff_en)
{
  uint8_t tmp;
  
  if(LPS25HB_ReadReg(B_Addr, LPS25HB_CTRL_REG1, 1, &tmp))
    return LPS25HB_ERROR;
    
  *diff_en = (LPS25HB_State_et)((tmp & LPS25HB_DIFF_EN_MASK) >> LPS25HB_DIFF_EN_BIT);
  
  return LPS25HB_OK;
}

/**
* @brief  Set ResetAutoZero Function bit
* @details REF_P reg (@0x08..0A) set pressure reference to default tmp RPDS reg (0x39/3A).
* @param  *B_Addr Device B_Addr.
* @retval Status [LPS25HB_ERROR, LPS25HB_OK]
*/
LPS25HB_Error_et LPS25HB_ResetAZ(uint8_t B_Addr)
{
  uint8_t tmp;
  
  if(LPS25HB_ReadReg(B_Addr, LPS25HB_CTRL_REG1, 1, &tmp))
    return LPS25HB_ERROR;
    
  /* Set the RESET_AZ bit*/
  /* RESET_AZ is self cleared*/
  tmp |= LPS25HB_RESET_AZ_MASK;
  
  if(LPS25HB_WriteReg(B_Addr, LPS25HB_CTRL_REG1, 1, &tmp))
    return LPS25HB_ERROR;
    
  return LPS25HB_OK;
}

/**
* @brief  Set SPI mode: 3 Wire Interface or 4 Wire Interface
* @param  *B_Addr Device B_Addr.
* @param  LPS25HB_SPI_3_WIRE, LPS25HB_SPI_4_WIRE
* @retval Status [LPS25HB_ERROR, LPS25HB_OK]
*/
LPS25HB_Error_et LPS25HB_Set_SpiInterface(uint8_t B_Addr, LPS25HB_SPIMode_et spimode)
{
  uint8_t tmp;
  
  LPS25HB_assert_param(IS_LPS25HB_SPIMode(spimode));
  
  if(LPS25HB_ReadReg(B_Addr, LPS25HB_CTRL_REG1, 1, &tmp))
    return LPS25HB_ERROR;
    
  tmp &= ~LPS25HB_SIM_MASK;
  tmp |= (uint8_t)spimode;
  
  if(LPS25HB_WriteReg(B_Addr, LPS25HB_CTRL_REG1, 1, &tmp))
    return LPS25HB_ERROR;
    
  return LPS25HB_OK;
}

/**
* @brief  Get SPI mode: 3 Wire Interface or 4 Wire Interface
* @param  *B_Addr Device B_Addr.
* @param  Buffet to empty with spi mode read from Sensor
* @retval Status [LPS25HB_ERROR, LPS25HB_OK]
*/
LPS25HB_Error_et LPS25HB_Get_SpiInterface(uint8_t B_Addr, LPS25HB_SPIMode_et* spimode)
{
  uint8_t tmp;
  
  if(LPS25HB_ReadReg(B_Addr, LPS25HB_CTRL_REG1, 1, &tmp))
    return LPS25HB_ERROR;
    
  *spimode = (LPS25HB_SPIMode_et)(tmp & LPS25HB_SIM_MASK);
  
  return LPS25HB_OK;
}

/**
* @brief  Enable/Disable I2C Mode
* @param  *B_Addr Device B_Addr.
* @param  State: Enable (reset bit)/ Disable (set bit)
* @retval Status [LPS25HB_ERROR, LPS25HB_OK]
*/
LPS25HB_Error_et LPS25HB_Set_I2C(uint8_t B_Addr, LPS25HB_State_et statei2c)
{
  uint8_t tmp;
  
  LPS25HB_assert_param(IS_LPS25HB_State(statei2c));
  
  if(LPS25HB_ReadReg(B_Addr, LPS25HB_CTRL_REG2, 1, &tmp))
    return LPS25HB_ERROR;
    
  tmp &= ~LPS25HB_I2C_MASK;
  if(statei2c == LPS25HB_DISABLE)
  {
    tmp |= LPS25HB_I2C_MASK;
  }
  
  if(LPS25HB_WriteReg(B_Addr, LPS25HB_CTRL_REG2, 1, &tmp))
    return LPS25HB_ERROR;
    
  return LPS25HB_OK;
}

/**
* @brief  Set the one-shot bit in order to start acquisition when the ONE SHOT mode
has been selected by the ODR configuration.
* @detail   Once the measurement is done, ONE_SHOT bit will self-clear.
* @param  *B_Addr Device B_Addr.
* @retval Status [LPS25HB_ERROR, LPS25HB_OK]
*/
LPS25HB_Error_et LPS25HB_StartOneShotMeasurement(uint8_t B_Addr)
{
  uint8_t tmp;
  
  if(LPS25HB_ReadReg(B_Addr, LPS25HB_CTRL_REG2, 1, &tmp))
    return LPS25HB_ERROR;
    
  /* Set the one shot bit */
  /* Once the measurement is done, one shot bit will self-clear*/
  tmp |= LPS25HB_ONE_SHOT_MASK;
  
  if(LPS25HB_WriteReg(B_Addr, LPS25HB_CTRL_REG2, 1, &tmp))
    return LPS25HB_ERROR;
    
  return LPS25HB_OK;
}

/**
* @brief  Set AutoZero Function bit
* @detail When set to �1�, the actual pressure output is copied in the REF_P reg (@0x08..0A)
* @param  *B_Addr Device B_Addr.
* @param  LPS25HB_SET/LPS25HB_RESET
* @retval Status [LPS25HB_ERROR, LPS25HB_OK]
*/
LPS25HB_Error_et LPS25HB_Set_AutoZeroFunction(uint8_t B_Addr, LPS25HB_BitStatus_et autozero)
{
  uint8_t tmp;
  
  LPS25HB_assert_param(IS_LPS25HB_BitStatus(autozero));
  
  if(LPS25HB_ReadReg(B_Addr, LPS25HB_CTRL_REG2, 1, &tmp))
    return LPS25HB_ERROR;
    
  tmp &=  ~LPS25HB_AUTO_ZERO_MASK;
  tmp |= ((uint8_t)autozero) << LPS25HB_AUTO_ZERO_BIT;
  
  if(LPS25HB_WriteReg(B_Addr, LPS25HB_CTRL_REG2, 1, &tmp))
    return LPS25HB_ERROR;
    
  return LPS25HB_OK;
}

/**
* @brief   Software Reset. Self-clearing upon completion
* @param  *B_Addr Device B_Addr.
* @retval Status [LPS25HB_ERROR, LPS25HB_OK]
*/
LPS25HB_Error_et LPS25HB_SwReset(uint8_t B_Addr)
{
  uint8_t tmp;
  
  if(LPS25HB_ReadReg(B_Addr, LPS25HB_CTRL_REG2, 1, &tmp))
    return LPS25HB_ERROR;
    
  tmp |= (0x01 << LPS25HB_SW_RESET_BIT);
  
  if(LPS25HB_WriteReg(B_Addr, LPS25HB_CTRL_REG2, 1, &tmp))
    return LPS25HB_ERROR;
    
  return LPS25HB_OK;
}

/**
* @brief  Reboot Memory Content
* @param  *B_Addr Device B_Addr.
* @retval Status [LPS25HB_ERROR, LPS25HB_OK]
*/
LPS25HB_Error_et LPS25HB_MemoryBoot(uint8_t B_Addr)
{
  uint8_t tmp;
  
  if(LPS25HB_ReadReg(B_Addr, LPS25HB_CTRL_REG2, 1, &tmp))
    return LPS25HB_ERROR;
    
  tmp |= (0x01 << LPS25HB_BOOT_BIT);
  
  if(LPS25HB_WriteReg(B_Addr, LPS25HB_CTRL_REG2, 1, &tmp))
    return LPS25HB_ERROR;
    
  return LPS25HB_OK;
}

/**
* @brief   Software Reset ann Reboot Memory Content.
* @detail  The device is reset to the power on configuration if the SWRESET bit is set to �1�
and BOOT is set to �1�; Self-clearing upon completion.
* @param  *B_Addr Device B_Addr.
* @retval  Status [LPS25HB_ERROR, LPS25HB_OK]
*/
LPS25HB_Error_et LPS25HB_SwResetAndMemoryBoot(uint8_t B_Addr)
{
  uint8_t tmp;
  
  if(LPS25HB_ReadReg(B_Addr, LPS25HB_CTRL_REG2, 1, &tmp))
    return LPS25HB_ERROR;
    
  tmp |= ((0x01 << LPS25HB_SW_RESET_BIT) | (0x01 << LPS25HB_BOOT_BIT));
  
  if(LPS25HB_WriteReg(B_Addr, LPS25HB_CTRL_REG2, 1, &tmp))
    return LPS25HB_ERROR;
    
  return LPS25HB_OK;
}

/**
* @brief   Enable/Disable FIFO Mode
* @param  *B_Addr Device B_Addr.
* @param  LPS25HB_ENABLE/LPS25HB_DISABLE
* @retval  Status [LPS25HB_ERROR, LPS25HB_OK]
*/
LPS25HB_Error_et LPS25HB_Set_FifoModeUse(uint8_t B_Addr, LPS25HB_State_et status)
{
  uint8_t tmp;
  
  LPS25HB_assert_param(IS_LPS25HB_State(status));
  
  if(LPS25HB_ReadReg(B_Addr, LPS25HB_CTRL_REG2, 1, &tmp))
    return LPS25HB_ERROR;
    
  tmp &= ~LPS25HB_FIFO_EN_MASK;
  tmp |= ((uint8_t)status) << LPS25HB_FIFO_EN_BIT;
  
  if(LPS25HB_WriteReg(B_Addr, LPS25HB_CTRL_REG2, 1, &tmp))
    return LPS25HB_ERROR;
    
  return LPS25HB_OK;
}

/**
* @brief   Enable/Disable FIFO Watermark Level Use
* @param  *B_Addr Device B_Addr.
* @param  LPS25HB_ENABLE/LPS25HB_DISABLE
* @retval  Status [LPS25HB_ERROR, LPS25HB_OK]
*/
LPS25HB_Error_et LPS25HB_Set_FifoWatermarkLevelUse(uint8_t B_Addr, LPS25HB_State_et status)
{
  uint8_t tmp;
  
  LPS25HB_assert_param(IS_LPS25HB_State(status));
  
  if(LPS25HB_ReadReg(B_Addr, LPS25HB_CTRL_REG2, 1, &tmp))
    return LPS25HB_ERROR;
    
  tmp &= ~LPS25HB_WTM_EN_MASK;
  tmp |= ((uint8_t)status) << LPS25HB_WTM_EN_BIT;
  
  if(LPS25HB_WriteReg(B_Addr, LPS25HB_CTRL_REG2, 1, &tmp))
    return LPS25HB_ERROR;
    
  return LPS25HB_OK;
}

/**
* @brief  Enable/Disable 1 HZ ODR Decimation
* @param  *B_Addr Device B_Addr.
* @param  LPS25HB_ENABLE/LPS25HB_DISABLE
* @retval Status [LPS25HB_ERROR, LPS25HB_OK]
*/
LPS25HB_Error_et LPS25HB_Set_FifoMeanDecUse(uint8_t B_Addr, LPS25HB_State_et status)
{
  uint8_t tmp;
  
  LPS25HB_assert_param(IS_LPS25HB_State(status));
  
  if(LPS25HB_ReadReg(B_Addr, LPS25HB_CTRL_REG2, 1, &tmp))
    return LPS25HB_ERROR;
    
  tmp &= ~LPS25HB_FIFO_MEAN_MASK;
  tmp |= ((uint8_t)status) << LPS25HB_FIFO_MEAN_BIT;
  
  if(LPS25HB_WriteReg(B_Addr, LPS25HB_CTRL_REG2, 1, &tmp))
    return LPS25HB_ERROR;
    
  return LPS25HB_OK;
}

/**
* @brief   Enable/Disable Interrupt Active High (default tmp 0) or Low(tmp 1)
* @param  *B_Addr Device B_Addr.
* @param  LPS25HB_ENABLE/LPS25HB_DISABLE
* @retval  Status [LPS25HB_ERROR, LPS25HB_OK]
*/
LPS25HB_Error_et LPS25HB_Set_InterruptActiveLevel(uint8_t B_Addr, LPS25HB_State_et status)
{
  uint8_t tmp;
  
  LPS25HB_assert_param(IS_LPS25HB_State(status));
  
  if(LPS25HB_ReadReg(B_Addr, LPS25HB_CTRL_REG3, 1, &tmp))
    return LPS25HB_ERROR;
    
  tmp &= ~LPS25HB_INT_H_L_MASK;
  tmp |= ((uint8_t)status) << LPS25HB_INT_H_L_BIT;
  
  if(LPS25HB_WriteReg(B_Addr, LPS25HB_CTRL_REG3, 1, &tmp))
    return LPS25HB_ERROR;
    
  return LPS25HB_OK;
}

/**
* @brief   Push-pull/open drain selection on interrupt pads. Default tmp: 0
* @param  *B_Addr Device B_Addr.
* @param  LPS25HB_PushPull/LPS25HB_OpenDrain
* @retval  Status [LPS25HB_ERROR, LPS25HB_OK]
*/
LPS25HB_Error_et LPS25HB_Set_InterruptOutputType(uint8_t B_Addr, LPS25HB_OutputType_et output)
{
  uint8_t tmp;
  
  LPS25HB_assert_param(IS_LPS25HB_OutputType(output));
  
  if(LPS25HB_ReadReg(B_Addr, LPS25HB_CTRL_REG3, 1, &tmp))
    return LPS25HB_ERROR;
    
  tmp &= ~LPS25HB_PP_OD_MASK;
  tmp |= (uint8_t)output;
  
  if(LPS25HB_WriteReg(B_Addr, LPS25HB_CTRL_REG3, 1, &tmp))
    return LPS25HB_ERROR;
    
  return LPS25HB_OK;
}

/**
* @brief   Set Data signal on INT1 pad control bits. Default tmp: 00
* @param  *B_Addr Device B_Addr.
* @param  PS25H_DATA,LPS25HB_P_HIGH_LPS25HB_P_LOW,LPS25HB_P_LOW_HIGH
* @retval  Status [LPS25HB_ERROR, LPS25HB_OK]
*/
LPS25HB_Error_et LPS25HB_Set_InterruptControlConfig(uint8_t B_Addr, LPS25HB_OutputSignalConfig_et config)
{
  uint8_t tmp;
  
  LPS25HB_assert_param(IS_LPS25HB_OutputSignal(config));
  
  if(LPS25HB_ReadReg(B_Addr, LPS25HB_CTRL_REG3, 1, &tmp))
    return LPS25HB_ERROR;
    
  tmp &= ~(LPS25HB_INT1_S2_MASK | LPS25HB_INT1_S1_MASK);
  tmp |= (uint8_t)config;
  
  if(LPS25HB_WriteReg(B_Addr, LPS25HB_CTRL_REG3, 1, &tmp))
    return LPS25HB_ERROR;
    
  return LPS25HB_OK;
}

/**
* @brief   Set INT1 interrupt pins configuration
* @param  *B_Addr Device B_Addr.
* @param   LPS25HB_EMPTY,LPS25HB_WTM,LPS25HB_OVR,LPS25HB_DATA_READY
* @retval  Status [LPS25HB_ERROR, LPS25HB_OK]
*/
LPS25HB_Error_et LPS25HB_Set_InterruptDataConfig(uint8_t B_Addr, LPS25HB_DataSignalType_et signal)
{
  uint8_t tmp;
  
  LPS25HB_assert_param(IS_LPS25HB_DataSignal(signal));
  
  if(LPS25HB_ReadReg(B_Addr, LPS25HB_CTRL_REG4, 1, &tmp))
    return LPS25HB_ERROR;
    
  tmp &= ~(LPS25HB_P1_EMPTY_MASK | LPS25HB_P1_WTM_MASK \
           | LPS25HB_P1_OVERRUN_MASK  | LPS25HB_P1_DRDY_MASK );
  tmp |= (uint8_t)signal;
  
  if(LPS25HB_WriteReg(B_Addr, LPS25HB_CTRL_REG4, 1, &tmp))
    return LPS25HB_ERROR;
    
  return LPS25HB_OK;
}

/**
* @brief   Enable\Disable Interrupt Generation on differential pressure low and/or high event
* @param  *B_Addr Device B_Addr.
* @param  LPS25HB_DISABLE_INT, LPS25HB_PHE,LPS25HB_PLE,LPS25HB_PLE_PHE
* @retval  Status [LPS25HB_ERROR, LPS25HB_OK]
*/
LPS25HB_Error_et LPS25HB_Set_InterruptDifferentialConfig(uint8_t B_Addr, LPS25HB_InterruptDiffConfig_et config)
{
  uint8_t tmp;
  
  LPS25HB_assert_param(IS_LPS25HB_InterruptDiff(config));
  
  if(LPS25HB_ReadReg(B_Addr, LPS25HB_INTERRUPT_CFG_REG, 1, &tmp))
    return LPS25HB_ERROR;
    
  tmp &= ~(LPS25HB_PL_E_MASK | LPS25HB_PH_E_MASK);
  tmp |= (uint8_t)config;
  if(config != LPS25HB_DISABLE_INT)
  {
    /* Enable DIFF_EN bit in CTRL_REG1 */
    if(LPS25HB_Set_InterruptCircuitEnable(B_Addr, LPS25HB_ENABLE))
      return LPS25HB_ERROR;
  }
  
  if(LPS25HB_WriteReg(B_Addr, LPS25HB_INTERRUPT_CFG_REG, 1, &tmp))
    return LPS25HB_ERROR;
    
  return LPS25HB_OK;
}

/**
* @brief   Enable/Disable Latch Interrupt request into INT_SOURCE register.
* @param  *B_Addr Device B_Addr.
* @param  LPS25HB_ENABLE/LPS25HB_DISABLE
* @retval  Status [LPS25HB_ERROR, LPS25HB_OK]
*/
LPS25HB_Error_et LPS25HB_LatchInterruptRequest(uint8_t B_Addr, LPS25HB_State_et status)
{
  uint8_t tmp;
  
  LPS25HB_assert_param(IS_LPS25HB_State(status));
  
  if(LPS25HB_ReadReg(B_Addr, LPS25HB_INTERRUPT_CFG_REG, 1, &tmp))
    return LPS25HB_ERROR;
    
  tmp &= ~LPS25HB_LIR_MASK;
  tmp |= (((uint8_t)status) << LPS25HB_LIR_BIT);
  
  if(LPS25HB_WriteReg(B_Addr, LPS25HB_INTERRUPT_CFG_REG, 1, &tmp))
    return LPS25HB_ERROR;
    
  return LPS25HB_OK;
}

/**
* @brief   Get the Interrupt Generation on differential pressure status event.
* @detail  The INT_SOURCE register is cleared by reading it.
* @param  *B_Addr Device B_Addr.
* @param  Status Event Flag: PH,PL,IA
* @retval  Status [LPS25HB_ERROR, LPS25HB_OK]
*/
LPS25HB_Error_et LPS25HB_Get_InterruptDifferentialEventStatus(uint8_t B_Addr,
    LPS25HB_InterruptDiffStatus_st* interruptsource)
{
  uint8_t tmp;
  
  if(LPS25HB_ReadReg(B_Addr, LPS25HB_INTERRUPT_SOURCE_REG, 1, &tmp))
    return LPS25HB_ERROR;
    
  interruptsource->PH = (uint8_t)(tmp & LPS25HB_PH_MASK);
  interruptsource->PL = (uint8_t)((tmp & LPS25HB_PL_MASK) >> LPS25HB_PL_BIT);
  interruptsource->IA = (uint8_t)((tmp & LPS25HB_IA_MASK) >> LPS25HB_IA_BIT);
  
  return LPS25HB_OK;
}

/**
* @brief   Get the status of Pressure and Temperature data
* @param  *B_Addr Device B_Addr.
* @param  Data Status Flag:  TempDataAvailable, TempDataOverrun, PressDataAvailable, PressDataOverrun
* @retval  Status [LPS25HB_ERROR, LPS25HB_OK]
*/
LPS25HB_Error_et LPS25HB_Get_DataStatus(uint8_t B_Addr, LPS25HB_DataStatus_st* datastatus)
{
  uint8_t tmp;
  
  if(LPS25HB_ReadReg(B_Addr, LPS25HB_STATUS_REG, 1, &tmp))
    return LPS25HB_ERROR;
    
  datastatus->TempDataAvailable = (tmp & LPS25HB_TDA_MASK);
  datastatus->PressDataAvailable = (uint8_t)((tmp & LPS25HB_PDA_MASK) >> LPS25HB_PDA_BIT);
  datastatus->TempDataOverrun = (uint8_t)((tmp & LPS25HB_TOR_MASK) >> LPS25HB_TOR_BIT);
  datastatus->PressDataOverrun = (uint8_t)((tmp & LPS25HB_POR_MASK) >> LPS25HB_POR_BIT);
  
  return LPS25HB_OK;
}

/**
* @brief    Get the raw pressure tmp
* @detail   The data are expressed as PRESS_OUT_H/_L/_XL in 2�s complement.
Pout(hPA)=PRESS_OUT / 4096
* @param  *B_Addr Device B_Addr.
* @param  The buffer to fill with the pressure raw tmp
* @retval  Status [LPS25HB_ERROR, LPS25HB_OK]
*/
LPS25HB_Error_et LPS25HB_Get_RawPressure(uint8_t B_Addr, int32_t *raw_press)
{
  uint8_t buffer[3];
  uint32_t tmp = 0;
  uint8_t i;
  
  if(LPS25HB_ReadReg(B_Addr, LPS25HB_PRESS_OUT_XL_REG, 3, buffer))
    return LPS25HB_ERROR;
    
  /* Build the raw data */
  for(i = 0; i < 3; i++)
    tmp |= (((uint32_t)buffer[i]) << (8 * i));
    
  /* convert the 2's complement 24 bit to 2's complement 32 bit */
  if(tmp & 0x00800000)
    tmp |= 0xFF000000;
    
  *raw_press = ((int32_t)tmp);
  
  return LPS25HB_OK;
}

/**
* @brief    Get the Pressure value in hPA.
* @detail   The data are expressed as PRESS_OUT_H/_L/_XL in 2�s complement.
Pout(hPA)=PRESS_OUT / 4096
* @param  *B_Addr Device B_Addr.
* @param  The buffer to fill with the pressure value that must be divided by 100 to get the value in hPA (mbar)
* @retval  Status [LPS25HB_ERROR, LPS25HB_OK]
*/
LPS25HB_Error_et LPS25HB_Get_Pressure(uint8_t B_Addr, int32_t* Pout)
{
  int32_t raw_press;
  
  if(LPS25HB_Get_RawPressure(B_Addr, &raw_press))
    return LPS25HB_ERROR;
    
  *Pout = (raw_press * 100) / 4096;
  
  return LPS25HB_OK;
}

/**
* @brief    Get the Raw Temperature tmp.
* @detail   Temperature data are expressed as TEMP_OUT_H&TEMP_OUT_L as 2�s complement number.
Tout(degC)=42.5+ (TEMP_OUT/480)
* @param  *B_Addr Device B_Addr.
* @param  Buffer to empty with the temperature raw tmp.
* @retval   Status [LPS25HB_ERROR, LPS25HB_OK]
*/
LPS25HB_Error_et LPS25HB_Get_RawTemperature(uint8_t B_Addr, int16_t* raw_data)
{
  uint8_t buffer[2];
  uint16_t tmp;
  
  if(LPS25HB_ReadReg(B_Addr, LPS25HB_TEMP_OUT_L_REG, 2, buffer))
    return LPS25HB_ERROR;
    
  /* Build the raw tmp */
  tmp = (((uint16_t)buffer[1]) << 8) + (uint16_t)buffer[0];
  
  *raw_data = ((int16_t)tmp);
  
  return LPS25HB_OK;
}

/**
* @brief    Get the Temperature value in �C.
* @detail   Temperature data are expressed as TEMP_OUT_H&TEMP_OUT_L as 2�s complement number.
* Tout(degC)=42.5+ (TEMP_OUT/480)
* @param  *B_Addr Device B_Addr.
* @param  Buffer to fill with the temperature value that must be divided by 10 to get the value in �C
* @retval   Status [LPS25HB_ERROR, LPS25HB_OK]
*/
LPS25HB_Error_et LPS25HB_Get_Temperature(uint8_t B_Addr, int16_t* Tout)
{
  int16_t raw_data;
  
  if(LPS25HB_Get_RawTemperature(B_Addr, &raw_data))
    return LPS25HB_ERROR;
    
  *Tout = (raw_data/48) + 425;
  
  return LPS25HB_OK;
}

/**
* @brief    Get the threshold tmp used for pressure interrupt generation (hPA).
* @detail   THS_P=THS_P_H&THS_P_L and is expressed as unsigned number.
P_ths(hPA)=(THS_P)/16.
* @param    Buffer to empty with the pressure threshold in hPA
* @retval   Status [LPS25HB_ERROR, LPS25HB_OK]
*/
LPS25HB_Error_et LPS25HB_Get_PressureThreshold(uint8_t B_Addr, int16_t* P_ths)
{
  uint8_t tempReg[2];
  
  if(LPS25HB_ReadReg(B_Addr, LPS25HB_THS_P_LOW_REG, 2, tempReg))
    return LPS25HB_ERROR;
    
  *P_ths = (((((uint16_t)tempReg[1]) << 8) + tempReg[0]) / 16);
  
  return LPS25HB_OK;
}

/**
* @brief    Set the threshold tmp used for pressure interrupt generation (hPA).
* @detail   THS_P=THS_P_H&THS_P_L and is expressed as unsigned number.
* P_ths(hPA)=(THS_P)/16.
* @param  *B_Addr Device B_Addr.
* @param  Pressure threshold in hPA
* @retval   Status [LPS25HB_ERROR, LPS25HB_OK]
*/
LPS25HB_Error_et LPS25HB_Set_PressureThreshold(uint8_t B_Addr, int16_t P_ths)
{
  uint8_t buffer[2];
  
  buffer[0] = (uint8_t)(16 * P_ths);
  buffer[1] = (uint8_t)(((uint16_t)(16 * P_ths)) >> 8);
  
  if(LPS25HB_WriteReg(B_Addr, LPS25HB_THS_P_LOW_REG, 2, buffer))
    return LPS25HB_ERROR;
    
  return LPS25HB_OK;
}

/**
* @brief  Set Fifo Mode
* @param  *B_Addr Device B_Addr.
* @param  FIFO mode
* @retval Status [LPS25HB_ERROR, LPS25HB_OK]
*/
LPS25HB_Error_et LPS25HB_Set_FifoMode(uint8_t B_Addr, LPS25HB_FifoMode_et fifomode)
{
  uint8_t tmp;
  
  LPS25HB_assert_param(IS_LPS25HB_FifoMode(fifomode));
  
  if(LPS25HB_ReadReg(B_Addr, LPS25HB_CTRL_FIFO_REG, 1, &tmp))
    return LPS25HB_ERROR;
    
  tmp &= ~LPS25HB_FMODE_MASK;
  tmp |= (uint8_t)fifomode;
  
  if(LPS25HB_WriteReg(B_Addr, LPS25HB_CTRL_FIFO_REG, 1, &tmp))
    return LPS25HB_ERROR;
    
  return LPS25HB_OK;
}

/**
* @brief    Get Fifo Mode
* @param  *B_Addr Device B_Addr.
* @param  Buffer to fill with fifo mode value
* @retval   Status [LPS25HB_ERROR, LPS25HB_OK]
*/
LPS25HB_Error_et LPS25HB_Get_FifoMode(uint8_t B_Addr, LPS25HB_FifoMode_et* fifomode)
{
  uint8_t tmp;
  
  if(LPS25HB_ReadReg(B_Addr, LPS25HB_CTRL_FIFO_REG, 1, &tmp))
    return LPS25HB_ERROR;
    
  tmp &= ~LPS25HB_WTM_POINT_MASK;
  *fifomode = (LPS25HB_FifoMode_et)tmp;
  
  return LPS25HB_OK;
}

/**
* @brief  Get the Fifo Status
* @param  *B_Addr Device B_Addr.
* @param  Status Flag: FIFO_WTM,FIFO_EMPTY,FIFO_FULL,FIFO_LEVEL
* @retval Status [LPS25HB_ERROR, LPS25HB_OK]
*/
LPS25HB_Error_et LPS25HB_Get_FifoStatus(uint8_t B_Addr, LPS25HB_FifoStatus_st* status)
{
  uint8_t tmp;
  
  if(LPS25HB_ReadReg(B_Addr, LPS25HB_STATUS_FIFO_REG, 1, &tmp))
    return LPS25HB_ERROR;
    
  status->FIFO_WTM = (uint8_t)((tmp & LPS25HB_WTM_FIFO_MASK) >> LPS25HB_WTM_FIFO_BIT);
  status->FIFO_FULL = (uint8_t)((tmp & LPS25HB_FULL_FIFO_MASK) >> LPS25HB_FULL_FIFO_BIT);
  status->FIFO_EMPTY = (uint8_t)((tmp & LPS25HB_EMPTY_FIFO_MASK) >> LPS25HB_EMPTY_FIFO_BIT);
  status->FIFO_LEVEL = (uint8_t)(tmp & LPS25HB_DIFF_POINT_MASK);
  
  return LPS25HB_OK;
}

/**
* @brief  Set Watermark Value
* @param  *B_Addr Device B_Addr.
* @param  wtmlevel = [0,31]
* @retval Status [LPS25HB_ERROR, LPS25HB_OK]
*/
LPS25HB_Error_et LPS25HB_Set_FifoWatermarkLevel(uint8_t B_Addr, uint8_t wtmlevel)
{
  uint8_t tmp;
  
  LPS25HB_assert_param(IS_LPS25HB_WtmLevel(wtmlevel));
  
  if(LPS25HB_ReadReg(B_Addr, LPS25HB_CTRL_FIFO_REG, 1, &tmp))
    return LPS25HB_ERROR;
    
  tmp &= ~LPS25HB_WTM_POINT_MASK;
  tmp |= wtmlevel;
  
  if(LPS25HB_WriteReg(B_Addr, LPS25HB_CTRL_FIFO_REG, 1, &tmp))
    return LPS25HB_ERROR;
    
  return LPS25HB_OK;
}

/**
* @brief  Get Watermark Value
* @param  *B_Addr Device B_Addr.
* @param  wtmlevel tmp read from sensor
* @retval Status [LPS25HB_ERROR, LPS25HB_OK]
*/
LPS25HB_Error_et LPS25HB_Get_FifoWatermarkLevel(uint8_t B_Addr, uint8_t *wtmlevel)
{
  if(LPS25HB_ReadReg(B_Addr, LPS25HB_CTRL_FIFO_REG, 1, wtmlevel))
    return LPS25HB_ERROR;
    
  *wtmlevel &= LPS25HB_WTM_POINT_MASK;
  
  return LPS25HB_OK;
}

/**
* @brief   Set the number of sample to perform moving average when FIFO_MEAN_MODE is used
* @param  *B_Addr Device B_Addr.
* @param  LPS25HB_FIFO_SAMPLE_2,LPS25HB_FIFO_SAMPLE_4,LPS25HB_FIFO_SAMPLE_8,LPS25HB_FIFO_SAMPLE_16,LPS25HB_FIFO_SAMPLE_32
* @retval  Status [LPS25HB_ERROR, LPS25HB_OK]
*/
LPS25HB_Error_et LPS25HB_Set_FifoSampleSize(uint8_t B_Addr, LPS25HB_FifoMeanModeSample_et samplesize)
{
  uint8_t tmp;
  
  LPS25HB_assert_param(IS_LPS25HB_FifoMeanModeSample(samplesize));
  
  if(LPS25HB_ReadReg(B_Addr, LPS25HB_CTRL_FIFO_REG, 1, &tmp))
    return LPS25HB_ERROR;
    
  tmp &= ~LPS25HB_WTM_POINT_MASK;
  tmp |= (uint8_t)samplesize;
  
  
  if(LPS25HB_WriteReg(B_Addr, LPS25HB_CTRL_FIFO_REG, 1, &tmp))
    return LPS25HB_ERROR;
    
  return LPS25HB_OK;
}

/**
* @brief   Get the number of sample to perform moving average when FIFO_MEAN_MODE is used
* @param  *B_Addr Device B_Addr.
* @param  buffer to fill with sample size tmp
* @retval  Status [LPS25HB_ERROR, LPS25HB_OK]
*/
LPS25HB_Error_et LPS25HB_Get_FifoSampleSize(uint8_t B_Addr, LPS25HB_FifoMeanModeSample_et* samplesize)
{
  uint8_t tmp;
  
  if(LPS25HB_ReadReg(B_Addr, LPS25HB_CTRL_FIFO_REG, 1, &tmp))
    return LPS25HB_ERROR;
    
  tmp &= LPS25HB_WTM_POINT_MASK;
  *samplesize = (LPS25HB_FifoMeanModeSample_et)tmp;
  
  return LPS25HB_OK;
}

/**
* @brief   Get the reference pressure after soldering for computing differential pressure (hPA)
* @param  *B_Addr Device B_Addr.
* @param  buffer to fill with the he pressure tmp (hPA)
* @retval  Status [LPS25HB_ERROR, LPS25HB_OK]
*/
LPS25HB_Error_et LPS25HB_Get_PressureOffsetValue(uint8_t B_Addr, int16_t *pressoffset)
{
  uint8_t buffer[2];
  int16_t raw_press;
  
  if(LPS25HB_ReadReg(B_Addr, LPS25HB_RPDS_L_REG, 2, buffer))
    return LPS25HB_ERROR;
    
  raw_press = (int16_t)((((uint16_t)buffer[1]) << 8) + (uint16_t)buffer[0]);
  
  *pressoffset = (raw_press * 100) / 4096;
  
  return LPS25HB_OK;
}

/**
* @brief   Set Generic Configuration
* @param  *B_Addr Device B_Addr.
* @param  LPS25HB Configuration structure
* @retval  Status [LPS25HB_ERROR, LPS25HB_OK]
*/
LPS25HB_Error_et LPS25HB_Set_GenericConfig(uint8_t B_Addr, LPS25HB_ConfigTypeDef_st* pxLPS25HBInit)
{
  /* Step 1. Init REF_P register*/
  /* The REF_P is the Reference Pressure. Its reset tmp is 0x00*/
  /* The REF_P will be set to the defualt RPDS (0x39h) tmp  if Reset_AZ is enabled.*/
  /* The REF_P will be set the actual pressure output if AutoZero is enabled*/
  
  if((pxLPS25HBInit->Reset_AZ) == LPS25HB_ENABLE)
  {
    if(LPS25HB_ResetAZ(B_Addr))
      return LPS25HB_ERROR;
  }
  else if((pxLPS25HBInit->AutoZero) == LPS25HB_ENABLE)
  {
    if(LPS25HB_Set_AutoZeroFunction(B_Addr, LPS25HB_SET))
      return LPS25HB_ERROR;
  }
  
  /* Step 2. Init the Pressure and Temperature Resolution*/
  if(LPS25HB_Set_Avg(B_Addr, pxLPS25HBInit->PressResolution, pxLPS25HBInit->TempResolution))
    return LPS25HB_ERROR;
    
  /* Step 3. Init the Output Data Rate*/
  if(LPS25HB_Set_Odr(B_Addr, pxLPS25HBInit->OutputDataRate))
    return LPS25HB_ERROR;
  /*Step 4. BDU bit is used to inhibit the output registers update between the reading of upper and
  lower register parts. In default mode (BDU = �0�), the lower and upper register parts are
  updated continuously. If it is not sure to read faster than output data rate, it is recommended
  to set BDU bit to �1�. In this way, after the reading of the lower (upper) register part, the
  content of that output registers is not updated until the upper (lower) part is read too.
  This feature avoids reading LSB and MSB related to different samples.*/
  
  if(LPS25HB_Set_Bdu(B_Addr, pxLPS25HBInit->BDU))
    return LPS25HB_ERROR;
    
  /*Step 5. SIM bit selects the SPI serial interface mode.*/
  /* This feature has effect only if SPI interface is used*/
  
  if(LPS25HB_Set_SpiInterface(B_Addr, pxLPS25HBInit->Sim))
    return LPS25HB_ERROR;
    
  return LPS25HB_OK;
}

/**
* @brief   Get Generic Configuration
* @param  *B_Addr Device B_Addr.
* @param  LPS25HB Configuration structure
* @retval  Status [LPS25HB_ERROR, LPS25HB_OK]
*/
LPS25HB_Error_et LPS25HB_Get_GenericConfig(uint8_t B_Addr, LPS25HB_ConfigTypeDef_st* pxLPS25HBInit)
{
  uint8_t tmp;
  
  if(LPS25HB_ReadReg(B_Addr, LPS25HB_RES_CONF_REG, 1, &tmp))
    return LPS25HB_ERROR;
    
  pxLPS25HBInit->PressResolution = (LPS25HB_Avgp_et)(tmp & LPS25HB_AVGP_MASK);
  pxLPS25HBInit->TempResolution = (LPS25HB_Avgt_et)(tmp & LPS25HB_AVGT_MASK);
  
  if(LPS25HB_ReadReg(B_Addr, LPS25HB_CTRL_REG1, 1, &tmp))
    return LPS25HB_ERROR;
     
  pxLPS25HBInit->OutputDataRate = (LPS25HB_Odr_et)(tmp & LPS25HB_ODR_MASK);
  
  pxLPS25HBInit->BDU = (LPS25HB_Bdu_et)(tmp & LPS25HB_BDU_MASK);
  pxLPS25HBInit->Sim = (LPS25HB_SPIMode_et)(tmp & LPS25HB_SIM_MASK);
  
  if(LPS25HB_ReadReg(B_Addr, LPS25HB_CTRL_REG2, 1, &tmp))
    return LPS25HB_ERROR;
    
  pxLPS25HBInit->AutoZero = (LPS25HB_State_et)((tmp & LPS25HB_RESET_AZ_MASK) >> LPS25HB_AUTO_ZERO_BIT);
  
  return LPS25HB_OK;
}

/**
* @brief   Set Interrupt Configuration
* @param  *B_Addr Device B_Addr.
* @param  LPS25HB Interrupt configuration structure
* @retval  Status [LPS25HB_ERROR, LPS25HB_OK]
*/
LPS25HB_Error_et LPS25HB_Set_InterruptConfig(uint8_t B_Addr, LPS25HB_InterruptTypeDef_st* pLPS25HBInt)
{
  if(LPS25HB_Set_InterruptActiveLevel(B_Addr, pLPS25HBInt->INT_H_L))
    return LPS25HB_ERROR;
    
  if(LPS25HB_Set_InterruptOutputType(B_Addr, pLPS25HBInt->PP_OD))
    return LPS25HB_ERROR;
    
  if(LPS25HB_Set_InterruptControlConfig(B_Addr, pLPS25HBInt->OutputSignal_INT1))
    return LPS25HB_ERROR;
    
  if(pLPS25HBInt->OutputSignal_INT1 == LPS25HB_DATA)
  {
  
    if(LPS25HB_Set_InterruptDataConfig(B_Addr, pLPS25HBInt->DataInterrupt_INT1))
      return LPS25HB_ERROR;
  }
  
  if(LPS25HB_LatchInterruptRequest(B_Addr, pLPS25HBInt->LatchIRQ))
    return LPS25HB_ERROR;
    
  if(LPS25HB_Set_PressureThreshold(B_Addr, pLPS25HBInt->fP_threshold))
    return LPS25HB_ERROR;
    
  /*DIFF_EN bit is used to enable the circuitry for the computing of differential pressure output.*/
  /*It is suggested to turn on the circuitry only after the configuration of REF_P_x and THS_P_x.*/
  
  if(LPS25HB_Set_InterruptDifferentialConfig(B_Addr, pLPS25HBInt->PressureInterrupt))
    return LPS25HB_ERROR;
    
  return LPS25HB_OK;
}

/**
* @brief   Get Interrupt Configuration
* @param  *B_Addr Device B_Addr.
* @param  LPS25HB Interrupt configuration structure
* @retval  Status [LPS25HB_ERROR, LPS25HB_OK]
*/
LPS25HB_Error_et LPS25HB_Get_InterruptConfig(uint8_t B_Addr, LPS25HB_InterruptTypeDef_st* pLPS25HBInt)
{
  uint8_t tmp;
  
  if(LPS25HB_ReadReg(B_Addr, LPS25HB_CTRL_REG3, 1, &tmp))
    return LPS25HB_ERROR;
    
  pLPS25HBInt->INT_H_L = (LPS25HB_State_et)((tmp & LPS25HB_INT_H_L_MASK) >> LPS25HB_INT_H_L_BIT);
  
  pLPS25HBInt->PP_OD = (LPS25HB_OutputType_et)(tmp & LPS25HB_PP_OD_MASK);
  pLPS25HBInt->OutputSignal_INT1 = (LPS25HB_OutputSignalConfig_et)((tmp & 0x03));
  
  if(pLPS25HBInt->OutputSignal_INT1 == LPS25HB_DATA)
  {
    if(LPS25HB_ReadReg(B_Addr, LPS25HB_CTRL_REG4, 1, &tmp))
      return LPS25HB_ERROR;
      
    pLPS25HBInt->DataInterrupt_INT1 = (LPS25HB_DataSignalType_et)(tmp &= 0x0F);
    
  }
  if(LPS25HB_ReadReg(B_Addr, LPS25HB_INTERRUPT_CFG_REG, 1, &tmp))
    return LPS25HB_ERROR;
    
  pLPS25HBInt->LatchIRQ = (LPS25HB_State_et)((tmp & LPS25HB_LIR_MASK) >> LPS25HB_LIR_BIT);
  pLPS25HBInt->PressureInterrupt = (LPS25HB_InterruptDiffConfig_et)(tmp & LPS25HB_PE_MASK);
  if(LPS25HB_Get_PressureThreshold(B_Addr, &pLPS25HBInt->fP_threshold))
    return LPS25HB_ERROR;
    
  return LPS25HB_OK;
}

/**
* @brief   Set Fifo Configuration
* @param  *B_Addr Device B_Addr.
* @param  LPS25HB FIFO configuration structure
* @retval  Status [LPS25HB_ERROR, LPS25HB_OK]
*/
LPS25HB_Error_et LPS25HB_Set_FifoConfig(uint8_t B_Addr, LPS25HB_FIFOTypeDef_st* pLPS25HBFIFO)
{
  if(pLPS25HBFIFO->FIFO_MODE == LPS25HB_FIFO_BYPASS_MODE)
  {
    /* FIFO Disable-> FIFO_EN bit=0 in CTRL_REG2*/
    if(LPS25HB_Set_FifoModeUse(B_Addr, LPS25HB_DISABLE))
      return LPS25HB_ERROR;
  }
  else
  {
    /* FIFO Enable-> FIFO_EN bit=1 in CTRL_REG2*/
    if(LPS25HB_Set_FifoModeUse(B_Addr, LPS25HB_ENABLE))
      return LPS25HB_ERROR;
      
    if(pLPS25HBFIFO->FIFO_MODE == LPS25HB_FIFO_MEAN_MODE)
    {
      if(LPS25HB_Set_FifoSampleSize(B_Addr, pLPS25HBFIFO->MEAN_MODE_SAMPLE))
        return LPS25HB_ERROR;
      if(pLPS25HBFIFO->FIFO_MEAN_DEC)
        if(LPS25HB_Set_FifoMeanDecUse(B_Addr, LPS25HB_ENABLE))
          return LPS25HB_ERROR;
    }
    else
    {
      if (pLPS25HBFIFO->WTM_INT)
      {
        if(LPS25HB_Set_FifoWatermarkLevelUse(B_Addr, LPS25HB_ENABLE))
          return LPS25HB_ERROR;
        if(LPS25HB_Set_FifoWatermarkLevel(B_Addr, pLPS25HBFIFO->WTM_LEVEL))
          return LPS25HB_ERROR;
      }
    }
  }
  
  if(LPS25HB_Set_FifoMode(B_Addr, pLPS25HBFIFO->FIFO_MODE))
    return LPS25HB_ERROR;
    
  return LPS25HB_OK;
}

/**
* @brief   Get Fifo Configuration
* @param  *B_Addr Device B_Addr.
* @param  LPS25HB FIFO configuration structure
* @retval  Status [LPS25HB_ERROR, LPS25HB_OK]
*/
LPS25HB_Error_et LPS25HB_Get_FifoConfig(uint8_t B_Addr, LPS25HB_FIFOTypeDef_st* pLPS25HBFIFO)
{
  uint8_t tmp;
  
  if(LPS25HB_ReadReg(B_Addr, LPS25HB_CTRL_FIFO_REG, 1, &tmp))
    return LPS25HB_ERROR;
    
    
  pLPS25HBFIFO->FIFO_MODE = (LPS25HB_FifoMode_et)(tmp & LPS25HB_FMODE_MASK);
  
  if(pLPS25HBFIFO->FIFO_MODE == LPS25HB_FIFO_MEAN_MODE)
  {
  
    pLPS25HBFIFO->MEAN_MODE_SAMPLE = (LPS25HB_FifoMeanModeSample_et)(tmp & LPS25HB_WTM_POINT_MASK);
    
    if(LPS25HB_ReadReg(B_Addr, LPS25HB_CTRL_REG2, 1, &tmp))
      return LPS25HB_ERROR;
      
    pLPS25HBFIFO->FIFO_MEAN_DEC = (LPS25HB_State_et)((tmp & LPS25HB_FIFO_MEAN_MASK) >> LPS25HB_FIFO_MEAN_BIT);
    
  }
  else
  {
    if(pLPS25HBFIFO->FIFO_MODE != LPS25HB_FIFO_BYPASS_MODE)
    {
      if(LPS25HB_ReadReg(B_Addr, LPS25HB_CTRL_REG2, 1, &tmp))
        return LPS25HB_ERROR;
        
      pLPS25HBFIFO->WTM_INT = (LPS25HB_State_et)((tmp & LPS25HB_WTM_EN_MASK) >> LPS25HB_WTM_EN_BIT);
      
      if (pLPS25HBFIFO->WTM_INT)
      {
        if(LPS25HB_ReadReg(B_Addr, LPS25HB_CTRL_FIFO_REG, 1, &tmp))
          return LPS25HB_ERROR;
        pLPS25HBFIFO->WTM_LEVEL = (uint8_t)(tmp & LPS25HB_WTM_POINT_MASK);
        
      }
    }
  }
  
  return LPS25HB_OK;
}

/**
* @brief   Get the Reference Pressure tmp that is sum to the sensor output pressure
* @param  *B_Addr Device B_Addr.
* @param  Buffer to fill with reference pressure tmp
* @retval  Status [LPS25HB_ERROR, LPS25HB_OK]
*/
LPS25HB_Error_et LPS25HB_Get_ReferencePressure(uint8_t B_Addr, int32_t* RefP)
{
  uint8_t buffer[3];
  uint32_t tempVal = 0;
  int32_t raw_press;
  uint8_t i;
  
  if(LPS25HB_ReadReg(B_Addr, LPS25HB_REF_P_XL_REG, 3, buffer))
    return LPS25HB_ERROR;
    
  /* Build the raw data */
  for(i = 0; i < 3; i++)
    tempVal |= (((uint32_t)buffer[i]) << (8 * i));
    
  /* convert the 2's complement 24 bit to 2's complement 32 bit */
  if(tempVal & 0x00800000)
    tempVal |= 0xFF000000;
    
  raw_press = ((int32_t)tempVal);
  *RefP = (raw_press * 100) / 4096;
  
  return LPS25HB_OK;
}

/**
* @brief  Check if the single measurement has completed.
* @param  *B_Addr Device B_Addr.
* @param  tmp is set to 1, when the measure is completed
* @retval Status [LPS25HB_ERROR, LPS25HB_OK]
*/
LPS25HB_Error_et LPS25HB_IsMeasurementCompleted(uint8_t B_Addr, uint8_t* Is_Measurement_Completed)
{
  uint8_t tmp;
  LPS25HB_DataStatus_st datastatus;
  
  if(LPS25HB_ReadReg(B_Addr, LPS25HB_STATUS_REG, 1, &tmp))
    return LPS25HB_ERROR;
    
  datastatus.TempDataAvailable = (uint8_t)(tmp & 0x01);
  datastatus.PressDataAvailable = (uint8_t)((tmp & 0x02) >> LPS25HB_PDA_BIT);
  
  *Is_Measurement_Completed = (uint8_t)((datastatus.PressDataAvailable) & (datastatus.TempDataAvailable));
  
  return LPS25HB_OK;
}

/**
* @brief  Get the values of the last single measurement.
* @param  *B_Addr Device B_Addr.
* @param  Pressure and temperature tmp
* @retval Status [LPS25HB_ERROR, LPS25HB_OK]
*/
LPS25HB_Error_et LPS25HB_Get_Measurement(uint8_t B_Addr, LPS25HB_MeasureTypeDef_st *Measurement_Value)
{
  int16_t Tout;
  int32_t Pout;
  
  if(LPS25HB_Get_Temperature(B_Addr, &Tout))
    return LPS25HB_ERROR;
    
  Measurement_Value->Tout = Tout;
  
  if(LPS25HB_Get_Pressure(B_Addr, &Pout))
    return LPS25HB_ERROR;
    
  Measurement_Value->Pout = Pout;
  
  return LPS25HB_OK;
}

/**
* @brief  De initialization function for LPS25HB.
*         This function put the LPS25HB in power down, make a memory boot and clear the data output flags.
* @param  *B_Addr Device B_Addr.
* @retval Error code [LPS25HB_OK, LPS25HB_ERROR].
*/
LPS25HB_Error_et LPS25HB_DeInit(uint8_t B_Addr)
{
  LPS25HB_MeasureTypeDef_st Measurement_Value;
  
  /* LPS25HB in power down */
  if(LPS25HB_Set_PowerDownMode(B_Addr, LPS25HB_RESET))
    return LPS25HB_ERROR;
    
  /* Make LPS25HB Reset and Reboot */
  if(LPS25HB_SwResetAndMemoryBoot(B_Addr))
    return LPS25HB_ERROR;
    
  /* Dump of data output */
  if(LPS25HB_Get_Measurement(B_Addr, &Measurement_Value))
    return LPS25HB_ERROR;
    
  return LPS25HB_OK;
}

#ifdef  USE_FULL_ASSERT_LPS25HB
/**
* @brief  Reports the name of the source file and the source line number
*         where the assert_param error has occurred.
* @param file: pointer to the source file name
* @param line: assert_param error line source number
* @retval : None
*/
void LPS25HB_assert_failed(uint8_t* file, uint32_t line)
{
  /* User can add his own implementation to report the file name and line number */
  printf("Wrong parameters tmp: file %s on line %d\r\n", file, (int)line);
  
  /* Infinite loop */
  while (1)
  {
  }
}
#endif

/**
* @}
*/

/**
* @}
*/

/**
* @}
*/

/******************* (C) COPYRIGHT 2013 STMicroelectronics *****END OF FILE****/
