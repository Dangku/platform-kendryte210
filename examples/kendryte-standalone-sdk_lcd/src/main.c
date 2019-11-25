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
#include <bsp.h>
#include "fpioa.h"
#include "lcd.h"
#include "sysctl.h"
#include "nt35310.h"
#include "board_config.h"

uint32_t g_lcd_gram[LCD_X_MAX * LCD_Y_MAX / 2] __attribute__((aligned(128)));

static void io_mux_init(void)
{
    fpioa_set_function(LCD_DCX_IO, FUNC_GPIOHS0 + DCX_GPIONUM);
    fpioa_set_function(LCD_CS_IO, FUNC_SPI0_SS3);
    fpioa_set_function(LCD_WR_IO, FUNC_SPI0_SCLK);
    //fpioa_set_function(LCD_RST_IO, FUNC_GPIOHS0 + RST_GPIONUM);
	
    sysctl_set_spi0_dvp_data(1);
}

int main(void)
{
    printf("lcd test\n");
	
    io_mux_init();
    lcd_init();
    lcd_set_direction(DIR_XY_LRDU);

    lcd_clear(RED);  //blue
    sleep(1);
    lcd_clear(BLUE);  //red
    sleep(1);
    lcd_clear(GREEN);  //green
    sleep(1);

    lcd_draw_picture(0, 0, 240, 160, g_lcd_gram);
	sleep(1);
	lcd_draw_string(16, 40, "Kendryte K210(Red)", RED);
    lcd_draw_string(16, 80, "Kendryte K210(Blue)", BLUE);
	lcd_draw_string(16, 120, "Kendryte K210(Green)", GREEN);
    
    while (1);
}
