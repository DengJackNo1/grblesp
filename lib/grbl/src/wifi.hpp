/*
  wifi.cpp - Handles connection to wifi and makes web, websockets and telnet
  connections available
*/

#ifndef wifi_h
#define wifi_h

#include "grbl.hpp"

void wifi_init();
void wifi_handle();  //放在定时器中执行,arduino ota 在定时器中不起作用
void wifi_loop();   //放在loop中执行

#endif
