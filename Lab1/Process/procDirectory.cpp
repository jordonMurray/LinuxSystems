#include "procDirectory.h"


int main(){
    
  
ProcessDirectory ProcessD;
    
    
    
    //  if ((dir = opendir("/")) != nullptr) {
    //     while ((diread = readdir(dir)) != nullptr) {
    //         //
    //         ProcessD.getRoot().push_back(diread->d_name);
    //     }
    //     closedir (dir);
    // } else {
    //     perror ("opendir");
    //     return EXIT_FAILURE;
    // }
    OpenDirectory(ProcessD.getRoot(),"/");
    
    
    // for (auto i : ProcessD.getRoot()) {
    //     /* code */
    //   if(i == "proc")
    //   {
    //      OpenDirectory(ProcessD.getProc(), "/proc");
         
    //   }
    // }
    
    ProcessD.GetProcFiles();
  //  ProcessD.ShowProcFiles();
  ProcessD.ShowPidFiles();
    
    
   
}