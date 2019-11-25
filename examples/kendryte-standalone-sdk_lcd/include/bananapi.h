#ifndef _BANANAPI_
#define _BANANAPI_

#define LCD_X_MAX	320
#define LCD_Y_MAX	240

/* dvp io */
#define DVP_RST_IO	45
#define DVP_PWDN_IO	43
#define DVP_XCLK_IO	41
#define DVP_VSYNC_IO	44
#define DVP_HREF_IO	42
#define DVP_PCLK_IO	40
#define DVP_SCLK_IO	46
#define DVP_SDA_IO	47

/* tft lcd io */
#define LCD_DCX_IO	38
#define LCD_CS_IO	36
#define LCD_WR_IO	37
#define LCD_RST_IO	39

/* led io */
#define GREEN_LED_IO	16

/* key io */
#define KEY_IO		26

/* mic io */
#define MIC_DATA0_IO	12
#define MIC_WS0_IO	13
#define MIC_SCLK0_IO	14

/* jack io */
#define I2S_DA_IO	33
#define I2S_WS_IO	34
#define I2S_BCK_IO	35

/* speaker io */
#define SPEAKER_EN_IO	0

/* pwm io */
#define PWM_IO		24

/* sdcard io */
#define SD_SCLK_IO	29
#define SD_MOSI_IO	30
#define SD_MISO_IO	31
#define SD_TFCS_IO	32

/* uart demo */
#define UART_TX_IO	24
#define UART_RX_IO	10

/* WIFI io */
#define WIFI_TX_IO	27
#define WIFI_RX_IO	28
#define WIFI_RESET_IO	16

/* external pin io 
 * phy num 1, 2, 3, ..., 26 
 */
#define EXT_PIN_NUM	19

#define EXT_P0_IO		24
#define EXT_P1_IO		25
#define EXT_P2_IO		26
#define EXT_P3_IO		2
#define EXT_P4_IO		3
#define EXT_P5_IO		6
#define EXT_P6_IO		7
#define EXT_P7_IO		8
#define EXT_P8_IO		9
#define EXT_P9_IO		10
#define EXT_P10_IO		11
#define EXT_P11_IO		18
#define EXT_P12_IO		21
#define EXT_P13_IO		22
#define EXT_P14_IO		19
#define EXT_P15_IO		20
#define EXT_P16_IO		23
#define EXT_P19_IO		17
#define EXT_P20_IO		15

/*-----------------------------------------------------------------------------------*/

/* gpiohs num 0-31 */

/* lcd io gpionum */
#define DCX_GPIONUM     	0
#define RST_GPIONUM     	1

/* green led io gpionum */
#define GREEN_LED_GPIONUM       2

/* key io gpionum */
#define KEY_GPIONUM		3

#define EXT_P0_GPIONUM		4
#define EXT_P1_GPIONUM		5
#define EXT_P2_GPIONUM		6
#define EXT_P3_GPIONUM		7
#define EXT_P4_GPIONUM		8
#define EXT_P5_GPIONUM		9
#define EXT_P6_GPIONUM		10
#define EXT_P7_GPIONUM		11
#define EXT_P8_GPIONUM		12
#define EXT_P9_GPIONUM		13
#define EXT_P10_GPIONUM		14
#define EXT_P11_GPIONUM		15
#define EXT_P12_GPIONUM		16
#define EXT_P13_GPIONUM		17
#define EXT_P14_GPIONUM		18
#define EXT_P15_GPIONUM		19
#define EXT_P16_GPIONUM		20
#define EXT_P19_GPIONUM		21
#define EXT_P20_GPIONUM		22

#define SD_TFCS_GPIONUM		23

#define WIFI_RESET_GPIONUM	24

#define SPEAKER_EN_GPIONUM	25

/*-----------------------------------------------------------------------------------*/

static const int ext_pin[] =
{
	EXT_P0_IO,
	EXT_P1_IO,
	EXT_P2_IO,
	EXT_P3_IO,
	EXT_P4_IO,
	EXT_P5_IO,
	EXT_P6_IO,
	EXT_P7_IO,
	EXT_P8_IO,
	EXT_P9_IO,
	EXT_P10_IO,
	EXT_P11_IO,
	EXT_P12_IO,
	EXT_P13_IO,
	EXT_P14_IO,
	EXT_P15_IO,
	EXT_P16_IO,
	EXT_P19_IO,
	EXT_P20_IO
};

static const int ext_gpionum[] =
{
	EXT_P0_GPIONUM,
	EXT_P1_GPIONUM,
	EXT_P2_GPIONUM,
	EXT_P3_GPIONUM,
	EXT_P4_GPIONUM,
	EXT_P5_GPIONUM,
	EXT_P6_GPIONUM,
	EXT_P7_GPIONUM,
	EXT_P8_GPIONUM,
	EXT_P9_GPIONUM,
	EXT_P10_GPIONUM,
	EXT_P11_GPIONUM,
	EXT_P12_GPIONUM,
	EXT_P13_GPIONUM,
	EXT_P14_GPIONUM,
	EXT_P15_GPIONUM,
	EXT_P16_GPIONUM,
	EXT_P19_GPIONUM,
	EXT_P20_GPIONUM
};


#endif

