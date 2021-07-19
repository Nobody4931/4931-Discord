#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>

#define SOURCE_DIR "src"
#define BUILD_DIR "bin"

#define SASS_FLAGS ""
#define POSTCSS_FLAGS "--no-map --use autoprefixer cssnano"

namespace fs = std::filesystem;

int main() {
	fs::path working_dir = fs::current_path();

	fs::path source_dir = working_dir / SOURCE_DIR;
	fs::path build_dir = working_dir / BUILD_DIR;

	if ( !fs::is_directory( source_dir ) ) {
		std::cerr << "source directory not found, make sure the working directory is the project folder" << std::endl;
		return 1;
	}

	if ( !fs::is_directory( build_dir ) ) {
		std::cerr << "build directory not found, make sure the working directory is the project folder" << std::endl;
		return 1;
	}

	for ( const fs::directory_entry& entry : fs::directory_iterator( source_dir ) ) {
		if ( entry.is_regular_file() == false ) continue;
		if ( entry.path().has_extension() && entry.path().extension().string() != ".scss" ) continue;

		fs::path infile = entry.path();
		fs::path outfile = build_dir / infile.filename();

		outfile.replace_extension( "css" );

		std::string command_sass = "sass ";
		std::string command_postcss = "postcss ";

		command_sass += SASS_FLAGS + infile.string() + ':' + outfile.string();
		command_postcss += outfile.string() + " " POSTCSS_FLAGS + " --output " + outfile.string();

		std::cout << "compiling " << infile.filename().string() << '\n';
		std::system( command_sass.c_str() );
		std::system( command_postcss.c_str() );
		std::cout << "compiled " << infile.filename().string() << '\n';
	}

	std::cout << "\ncompilation finished" << std::endl;
	return 0;
}
