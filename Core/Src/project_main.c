/* ==========================================================
 * project_main.c - 
 * Project : Disk91 SDK
 * ----------------------------------------------------------
 * Created on: 22 July 2024
 *     Author: Paul Pinault aka Disk91
 * ----------------------------------------------------------
 * Copyright (C) 2024 Disk91
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU LESSER General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Lesser Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 * ----------------------------------------------------------
 * 
 * Demo program for Seeed E5 module running sigfox communication
 *
 * ==========================================================
 */
#include <it_sdk/config.h>
#include <it_sdk/itsdk.h>
#include <it_sdk/time/time.h>
#include <it_sdk/logger/logger.h>
#include <it_sdk/sched/scheduler.h>

#include <it_sdk/lowpower/lowpower.h>
#include <it_sdk/sigfox/sigfox.h>

void task() {
	static uint16_t counter = 299;
	static uint8_t bytes[4] = { 0x00, 0x00, 0x00, 0x00 };
	static uint8_t down[8];

	// make the board led blinking
	gpio_toggle(__BANK_B, LED_Pin);

	// fire a Sigfox communication on every 10 minutes
	if ( counter == 300 ) {
		log_info("Fire Sigfox message\r\n");
		counter = 0;

		int16_t t = adc_getTemperature();
		log_debug("Temp : %d\r\n",t);
		uint16_t v = adc_getVdd();
		log_debug("Volt : %d\r\n",v);

		bytes[0] = (t & 0xFF00) >> 8;
		bytes[1] = t & 0xFF;
		bytes[2] = (v & 0xFF00) >> 8;
		bytes[3] = v & 0xFF;

		itdsk_sigfox_txrx_t ret = itsdk_sigfox_sendFrame(
				bytes,						// data buffer containing the temperature and the MCU voltage
				sizeof(bytes),				// data size
				2,							// 2 repeats eq N = 3
				SIGFOX_SPEED_DEFAULT,		// 100bps EU
				SIGFOX_POWER_DEFAULT,		// 14dBm EU
				PAYLOAD_ENCRYPT_NONE,		// No encryption
				true,						// ack / downlink
				down
		);

		if ( ret == SIGFOX_TXRX_DOWLINK_RECEIVED ) {
			log_info("Received downlink with value [%02X,%02X,%02X,%02X,%02X,%02X,%02X,%02X]",
					down[0],down[1],down[2],down[3],
					down[4],down[5],down[6],down[7]
			);
		}


	} else counter++;

}


void project_setup() {
	log_info("Booting \r\n");

	// This delay is just to make sure we are not imedialty low power for
	// on reset programming
	itsdk_delayMs(6000);

	// Board led for blinking
	gpio_toggle(__BANK_B, LED_Pin);

	// Schedule a task on every 2 seconds
	itdt_sched_registerSched(2000,ITSDK_SCHED_CONF_IMMEDIATE, &task);

	// init sigfox lib
	itsdk_sigfox_setup();

}

void project_loop() {

}

