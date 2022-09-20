/*
  cpu_map.hpp - Machine dependent code for the ESP8266 and family
  Part of Grbl

  Copyright (c) 2012-2016 Sungeun K. Jeon for Gnea Research LLC

  Grbl is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  Grbl is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with Grbl.  If not, see <http://www.gnu.org/licenses/>.
*/

/* The cpu_map.h files serve as a central pin mapping selection file for different
   processor types or alternative pin layouts. This version of Grbl officially supports
   only the Arduino Mega328p. */

#ifndef cpu_map_h
#define cpu_map_h

#define save_SREG() xt_rsil(2); // this routine will allow level 3 and above (returns an uint32_t)
#define restore_SREG(state) \
  xt_wsr_ps(state);         \
  sei(); // restore the state (uint32_t)

#ifdef  CPU_MAP_ESP8266
  #include "esp8266cpu_map.hpp"
#endif


/*
#ifdef CPU_MAP_CUSTOM_PROC
  // For a custom pin map or different processor, copy and edit one of the available cpu
  // map files and modify it to your needs. Make sure the defined name is also changed in
  // the config.h file.
#endif
*/

#endif /* CPU_MAP_H_ */
