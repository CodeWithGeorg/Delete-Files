// simple_delete_fixed.cpp
#include <iostream>
#include <filesystem>
#include <string>
#include <algorithm>
using namespace std;
namespace fs = std::filesystem;

string to_lower(string s) {
    transform(s.begin(), s.end(), s.begin(), ::tolower);
    return s;
}

int main() {
    string ext;
    char confirm;
    int count = 0;

    cout << "Enter extension (e.g. png, jpg, txt): ";
    cin >> ext;

    // Clean & normalize extension
    ext = to_lower(ext);
    if (ext.empty()) {
        cout << "No extension entered.\n";
        return 1;
    }
    if (ext[0] != '.') ext = "." + ext;

    cout << "\nScanning current folder for *" << ext << " files...\n";
    cout << "Type 'y' to DELETE them: ";
    cin >> confirm;

    if (confirm != 'y' && confirm != 'Y') {
        cout << "Cancelled.\n";
        return 0;
    }

    // Scan current directory
    for (const auto& entry : fs::directory_iterator(".")) {
        if (!entry.is_regular_file()) continue;

        string file_ext = to_lower(entry.path().extension().string());
        if (file_ext == ext) {
            try {
                fs::remove(entry.path());
                cout << "Deleted: " << entry.path().filename() << "\n";
                count++;
            } catch (const exception& e) {
                cout << "Failed: " << entry.path().filename() << " (" << e.what() << ")\n";
            }
        }
    }

    cout << "\nDone. " << count << " file(s) deleted.\n";

    if (count == 0) {
        cout << "Tip: Make sure you're in the right folder and files have the correct extension.\n";
        cout << "Run: ls *." << ext.substr(1) << "  to check.\n";
    }

    return 0;
}