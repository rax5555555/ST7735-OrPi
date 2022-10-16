// Section ::  libraries 
#include <wiringPi.h>
#include <wiringPiSPI.h> //include spi library
#include <stdio.h> // for printf
#include "ST7735_TFT.h"

// Section :: Globals 
ST7735_TFT myTFT;

//  Section ::  Function Headers 

void Setup(void);  // setup + user options
void Test0(void);  // Print out all fonts 1-5
void EndTests(void);

//  Section ::  MAIN loop

int main(void) 
{
	/*if(!bcm2835_init())
	{
		printf("Error 1201 : Problem with init bcm2835 library\r\n");
		return -1;
	}*/
	
	Setup();

	Test0();

	EndTests();
	return 0;
}
// *** End OF MAIN **


//  Section ::  Function Space 

void Setup(void)
{
// ****** USER OPTION 1 Screen Setup ****** 
	uint8_t OFFSET_COL = 0;  // 2, These offsets can be adjusted for any issues->
	uint8_t OFFSET_ROW = 0 ; // 3, with manufacture tolerance/defects
	uint16_t TFT_WIDTH = 128;// Screen width in pixels
	uint16_t TFT_HEIGHT = 128; // Screen height in pixels
// ******************************************

// ******** USER OPTION 2 GPIO/SPI TYPE *************************
	int8_t RST_TFT = 25;
	int8_t DC_TFT = 24;
	int8_t SCLK_TFT = -1; // 11,  change to GPIO no for software spi
	int8_t SDIN_TFT = -1; // 10, change to GPIO no for software spi
	int8_t CS_TFT = -1 ;  // 8, change to GPIO no for software spi
//**********************************************************
	delay(1000);
	printf("TFT Start\r\n");
	myTFT.TFTSetupGPIO(RST_TFT, DC_TFT ,CS_TFT , SCLK_TFT, SDIN_TFT);
	myTFT.TFTInitScreenSize(OFFSET_COL, OFFSET_ROW , TFT_WIDTH , TFT_HEIGHT);
// ******** USER OPTION 3 PCB_TYPE **************************
// init PCB type , pass enum 4 choices, see readme
	myTFT.TFTInitPCBType(TFT_ST7735R_Red);
//**********************************************************

}

void Test0(void) {

	char teststr1[] = "Default 1";
	char teststr2[] = "THICK 2";
	char teststr3[] = "Seven 3";
	char teststr4[] = "WIDE 4";
	char teststr5[] = "Tiny 5";
	
	myTFT.TFTfillScreen(ST7735_BLACK);
	
	myTFT.TFTFontNum(TFTFont_Default);
	myTFT.TFTdrawText(0, 5, teststr1, ST7735_WHITE, ST7735_BLACK, 2);
	myTFT.TFTFontNum(TFTFont_Thick);
	myTFT.TFTdrawText(0, 35, teststr2, ST7735_GREEN, ST7735_BLACK, 2);
	myTFT.TFTFontNum(TFTFont_Seven_Seg);
	myTFT.TFTdrawText(0, 55, teststr3, ST7735_BLUE, ST7735_BLACK, 2);
	myTFT.TFTFontNum(TFTFont_Wide);
	myTFT.TFTdrawText(0, 75, teststr4, ST7735_CYAN, ST7735_BLACK, 2);
	myTFT.TFTFontNum(TFTFont_Tiny);
	myTFT.TFTdrawText(0, 100, teststr5, ST7735_RED, ST7735_BLACK, 2);
	bcm2835_delay(TEST_DELAY5);
	myTFT.TFTfillScreen(ST7735_BLACK);
	myTFT.TFTFontNum(TFTFont_Default);
}

void EndTests(void)
{
	char teststr1[] = "Tests over";
	myTFT.TFTfillScreen(ST7735_BLACK);
	myTFT.TFTdrawText(5, 50, teststr1, ST7735_GREEN, ST7735_BLACK, 2);
	//bcm2835_delay(TEST_DELAY5);
	delay(1000);
	myTFT.TFTPowerDown(); // Power down device
	//bcm2835_close(); // Close the bcm2835 library
	printf("TFT End\r\n");
}
// *************** EOF ****************
