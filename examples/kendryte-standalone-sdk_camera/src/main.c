/* Copyright 2018 Canaan Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#include <stdio.h>
#include <string.h>
#include "dvp.h"
#include "fpioa.h"
#include "lcd.h"
#include "ov5640.h"
#include "ov2640.h"
#include "plic.h"
#include "sysctl.h"
#include "uarths.h"
#include "nt35310.h"
#include "board_config.h"
#include "unistd.h"

uint32_t g_lcd_gram0[38400] __attribute__((aligned(64)));
uint32_t g_lcd_gram1[38400] __attribute__((aligned(64)));

volatile uint8_t g_dvp_finish_flag;
volatile uint8_t g_ram_mux;

static int on_irq_dvp(void* ctx)
{
    if (dvp_get_interrupt(DVP_STS_FRAME_FINISH))
    {
        /* switch gram */
        dvp_set_display_addr(g_ram_mux ? (uint32_t)g_lcd_gram0 : (uint32_t)g_lcd_gram1);

        dvp_clear_interrupt(DVP_STS_FRAME_FINISH);
        g_dvp_finish_flag = 1;
    }
    else
    {
        if(g_dvp_finish_flag == 0)
            dvp_start_convert();
        dvp_clear_interrupt(DVP_STS_FRAME_START);
    }

    return 0;
}

static void io_mux_init(void)
{
    /* Init DVP IO map and function settings */
    fpioa_set_function(DVP_RST_IO, FUNC_CMOS_RST);
    fpioa_set_function(DVP_PWDN_IO, FUNC_CMOS_PWDN);
    fpioa_set_function(DVP_XCLK_IO, FUNC_CMOS_XCLK);
    fpioa_set_function(DVP_VSYNC_IO, FUNC_CMOS_VSYNC);
    fpioa_set_function(DVP_HREF_IO, FUNC_CMOS_HREF);
    fpioa_set_function(DVP_PCLK_IO, FUNC_CMOS_PCLK);
    fpioa_set_function(DVP_SCLK_IO, FUNC_SCCB_SCLK);
    fpioa_set_function(DVP_SDA_IO, FUNC_SCCB_SDA);

    /* Init TFT SPI IO map and function settings */
    fpioa_set_function(LCD_DCX_IO, FUNC_GPIOHS0 + DCX_GPIONUM); 
    fpioa_set_function(LCD_CS_IO, FUNC_SPI0_SS3);
    fpioa_set_function(LCD_WR_IO, FUNC_SPI0_SCLK);
    //fpioa_set_function(LCD_RST_IO, FUNC_GPIOHS0 + RST_GPIONUM);

    sysctl_set_spi0_dvp_data(1);

}

int main(void)
{
    /* Set CPU and dvp clk */
    sysctl_pll_set_freq(SYSCTL_PLL0, 800000000UL);
    sysctl_pll_set_freq(SYSCTL_PLL1, 160000000UL);
    sysctl_pll_set_freq(SYSCTL_PLL2, 45158400UL);
    uarths_init();

    plic_init();

    /* LCD init */
    printf("LCD init\n");
	
	io_mux_init();
    lcd_init();
    lcd_set_direction(DIR_XY_LRDU);

    lcd_clear(BLACK);

    /* DVP init */
    printf("DVP init\n");

	/* ov5640 configuration */
    dvp_init(16);
    dvp_set_xclk_rate(50000000);
    dvp_enable_burst();
    dvp_set_output_enable(0, 1);
    dvp_set_output_enable(1, 1);
    dvp_set_image_format(DVP_CFG_RGB_FORMAT);
    dvp_set_image_size(LCD_X_MAX, LCD_Y_MAX);
    ov5640_init();

    dvp_set_ai_addr((uint32_t)0x40600000, (uint32_t)0x40612C00, (uint32_t)0x40625800);
    dvp_set_display_addr((uint32_t)g_lcd_gram0);
    dvp_config_interrupt(DVP_CFG_START_INT_ENABLE | DVP_CFG_FINISH_INT_ENABLE, 0);
    dvp_disable_auto();

    /* DVP interrupt config */
    printf("DVP interrupt config\n");
    plic_set_priority(IRQN_DVP_INTERRUPT, 1);
    plic_irq_register(IRQN_DVP_INTERRUPT, on_irq_dvp, NULL);
    plic_irq_enable(IRQN_DVP_INTERRUPT);

    /* enable global interrupt */
    sysctl_enable_irq();

    /* system start */
    printf("system start\n");
    g_ram_mux = 0;
    g_dvp_finish_flag = 0;
    dvp_clear_interrupt(DVP_STS_FRAME_START | DVP_STS_FRAME_FINISH);
    dvp_config_interrupt(DVP_CFG_START_INT_ENABLE | DVP_CFG_FINISH_INT_ENABLE, 1);

    while (1)
    {
        /* ai cal finish*/
        while (g_dvp_finish_flag == 0)
            ;
        g_dvp_finish_flag = 0;
        /* display pic*/
        g_ram_mux ^= 0x01;
        lcd_draw_picture(0, 0, LCD_X_MAX, LCD_Y_MAX, g_ram_mux ? g_lcd_gram0 : g_lcd_gram1);
    }

    return 0;
}
