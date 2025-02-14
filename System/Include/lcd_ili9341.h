//! @file    lcd_ili9341.h
//! @brief   Komunikacija s krmilnikom Ili9341
//! @author  nbert, februar-marec 2022
#ifndef LCD_ILI9341_H_
#define LCD_ILI9341_H_



// Vključimo definicije registrov vmesnika ILI9341.
#include "lcd_ili9341_registers.h"




// -------------- User-defined parameters ----------------
//
// Tu uporabnik modula specificira parametre za delo s krmilnikom LCD zaslona ILI9341.


// Potrebno je vključiti zglavno .h datoteko, kjer so definirani registri mikrokrmilnika,
// ki ga uporabljamo.
#include "stm32g4xx.h"


// DOPOLNI: Odkomentirati je potrebno ustrezno definicijo makroja. S tem povzročimo, da bo obstajal
// makro s točno določenim imenom, zaradi česar se bo s pomočjo pred-procesorskega stavka
// "#ifdef" nato izvedla ustrezna koda.
#define ILI9341_INTERFACE_WIDTH_16                // 16 bit
//#define ILI9341_INTERFACE_WIDTH_8                	// 8 bit


// Potrebno je specificirati resolucijo LCD zaslona.
#define ILI9341_WIDTH  		240		// širina zaslona v številu pikslov
#define ILI9341_HEIGHT 		320		// višina zaslona v številu pikslov


// -------------------------------------------------------------



// Definicija ustreznega podatkovnega tipa za komunikacijo z LCD zaslonom.
#ifdef ILI9341_INTERFACE_WIDTH_16
typedef uint16_t ILI9341_Data_t;
#endif

#ifdef ILI9341_INTERFACE_WIDTH_8
	typedef uint8_t ILI9341_Data_t;
#endif



// ----------- Definicije makro parametrov ----------

#define ILI9341_ID     0x9341U

// Pikselska površina
#define ILI9341_AREA   (ILI9341_WIDTH * ILI9341_HEIGHT)

/* Timing configuration  (Typical configuration from ILI9341 datasheet)
   HSYNC   =  10 (9+1)
   HBP     =  20 (29-10+1)
   ActiveW = 240 (269-20-10+1)
   HFP     =  10 (279-240-20-10+1)

   VSYNC   =   2 (1+1)
   VBP     =   2 (3-2+1)
   ActiveH = 320 (323-2-2+1)
   VFP     =   4 (327-320-2-2+1)
*/
#define ILI9341_HSYNC  ((uint32_t)9)   /* Horizontal synchronization */
#define ILI9341_HBP    ((uint32_t)29)  /* Horizontal back porch      */
#define ILI9341_HFP    ((uint32_t)2)   /* Horizontal front porch     */
#define ILI9341_VSYNC  ((uint32_t)1)   /* Vertical synchronization   */
#define ILI9341_VBP    ((uint32_t)3)   /* Vertical back porch        */
#define ILI9341_VFP    ((uint32_t)2)   /* Vertical front porch       */

//! @brief Zasuk zaslona na platformi Miško 3 (v smeri urinega kazalca)
#define ILI9341_MISKO_ROTATE_0    0x03U
#define ILI9341_MISKO_ROTATE_90   0x01U
#define ILI9341_MISKO_ROTATE_180  0x02U
#define ILI9341_MISKO_ROTATE_270  0x00U

//! @brief Možni barvni prostori zaslona (pixel format)
#define ILI9341_COLORSPACE_RBG565  0x55U           /* RGB565: 16 bpp */
#define ILI9341_COLORSPACE_RBG666  0x66U           /* RGB666: 18 bpp */

/**
 * @brief LCD constroller REG and RAM addresses
 */
#define FMC_BANK1_REG  ((uint16_t *)  0x60000000)
#define FMC_BANK1_MEM  ((uint16_t *) (0x60000000 | 0x0010000))

#ifdef ILI9341_INTERFACE_WIDTH_16
	#define LCD_IO_DATA_WRITE_CYCLES 1
	typedef uint16_t LCD_IO_Data_t;
#endif

#define SCROLL_LEFT  0
#define SCROLL_RIGHT 1

// #ifdef ILI9341_INTERFACE_WIDTH_8
// 	#define LCD_IO_DATA_WRITE_CYCLES 2
//  	typedef uint8_t LCD_IO_Data_t;
// #endif

typedef enum LCD_Param
{
	LCD_WIDTH,
	LCD_HEIGHT,
	LCD_AREA,
	LCD_ORIENTATION
} LCD_Param_t;

/**
 * @brief LCD DMA Configuration
 */
extern  DMA_HandleTypeDef hdma_memtomem_dma1_channel1;
#define hLCDDMA           hdma_memtomem_dma1_channel1



void    ILI9341_SetAddress (LCD_IO_Data_t *address);
void    ILI9341_SendData(LCD_IO_Data_t *data, uint32_t length);
void    ILI9341_SendRepeatedData(LCD_IO_Data_t data, uint32_t num_copies);
int32_t ILI9341_SendDataDMA(LCD_IO_Data_t *data, uint32_t length);
void    ILI9341_RecvData(LCD_IO_Data_t *address, uint32_t length);

void ILI9341_SetOrientation(uint32_t Orientation);
void ILI9341_SetDisplayWindow(uint32_t Xpos, uint32_t Ypos, uint32_t Width, uint32_t Height);
void ILI9341_Init(uint32_t color_space, uint32_t orientation);
void ILI9341_WaitTransfer();

void ILI9341_DisplayOn();
void ILI9341_DisplayOff();
void ILI9341_InvertDisplay(uint8_t invert);
void ILI9341_SetSleep(uint8_t state);
void ILI9341_SetScrollArea(uint16_t start_pos, uint16_t end_pos);
void ILI9341_ScrollScreen(uint16_t position, uint8_t direction);
uint32_t ILI9341_GetParam(LCD_Param_t param);


#endif /* LCD_ILI9341_H_ */
