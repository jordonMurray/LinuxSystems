#include <iostream>
#include <dirent.h>
#include <vector> 
#include <string>

using std::cout; using std::cin;
using std::endl; using std::vector;
using std::string;

   DIR *dir; struct dirent *diread;

    void OpenDirectory(vector<string>& Directory, const char* Path)
    {
   //vect.push_back(30);
    if ((dir = opendir(Path)) != nullptr) {
        while ((diread = readdir(dir)) != nullptr) {
            //
            Directory.push_back(diread->d_name);
        }
        closedir (dir);
    } else {
        perror ("opendir");
        throw EXIT_FAILURE;
     }
    }
    
    

bool is_digits(const std::string &str)
{
    return str.find_first_not_of("0123456789") == std::string::npos;
}