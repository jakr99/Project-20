#include <iostream>
#include <fstream>
#include <regex>
#include <cstdlib>

int main() {
    std::ifstream htmlFile("sample.html");

    if (!htmlFile.is_open()) {
        std::cerr << "Error opening file!\n";
        return 1;
    }

    std::string line;
    std::regex linkRegex("<a\\s+.*?href=['\"](.*?)['\"].*?>(.*?)</a>");
    std::regex imgRegex("<img\\s+.*?src=['\"](.*?)['\"].*?alt=['\"](.*?)['\"].*?>");

    while (std::getline(htmlFile, line)) {
        std::smatch match;

        if (std::regex_search(line, match, linkRegex)) {
            std::cout << "Link Text: " << match[2].str() << "\n";
            std::cout << "URL: " << match[1].str() << "\n";
        }

        if (std::regex_search(line, match, imgRegex)) {
            std::cout << "Alt Text: " << match[2].str() << "\n";
            std::cout << "Image URL: " << match[1].str() << "\n";

            std::string downloadCommand = "wget -O " + match[2].str() + ".jpg " + match[1].str();
            std::system(downloadCommand.c_str());
        }
    }

    htmlFile.close();

    return 0;
}
