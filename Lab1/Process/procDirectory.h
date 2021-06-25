#include "Monitor.h"



class ProcessDirectory{
            vector<string> rootDirectory; 
            vector<string> ProcDirectory; 
    public:

   vector<string>&  getRoot() { return rootDirectory; }
   vector<string>&  getProc() { return ProcDirectory; }
   
   //Get all the files 
  void GetProcFiles()
  {
     OpenDirectory(getProc(), "/proc");
      }
      
  // Show all files in the /proc directory
   void ShowProcFiles()
   {
       cout << "These are all the files in the Proc Directory" << endl;
          for (auto i : getProc()) {
        /* code */
      cout << i << endl;
         }
   }
    //Show all pid Files 
    void ShowPidFiles()
    {
     for (auto i : getProc()) {
        /* code */
      if(is_digits(i))
      cout << i << endl;
         }   
        
    }
    
    
    
    
};


