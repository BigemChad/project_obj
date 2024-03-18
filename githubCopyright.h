#ifdef _WIN32
#include <windows.h>
#elif __linux__
#include <cstdlib>
#endif

//Maybe wariant na maca

void openLink(const std::string& link) {
#ifdef _WIN32
    //Windows
    ShellExecuteA(NULL, "open", link.c_str(), NULL, NULL, SW_SHOWNORMAL);
#elif __linux__
    //Linux
    std::string command = "xdg-open " + link;
    system(command.c_str());
#elif __APPLE__
    std::string command = "open " + link;
    system(command.c_str());
#endif
}
