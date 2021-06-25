#include Monitor.h



    void OpenDirectory(vector<string>& Directory, string Path)
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