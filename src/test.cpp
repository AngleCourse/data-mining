
#include <iostream>
#include <fstream>
#include "./include/loadlog.h"
#include "./include/fields.h"
using std::cout;
using std::ifstream;
extern LogList ** loadfiles(string *files, int num);
void testloading();
int main(){
    testloading();
    return 0;
}

void testloading(){
    cout<< "Starting to test loading module...\n";
    const int num_files = 7;
    string* filenames = new string[num_files];
    filenames[0].assign("../raw/CSession_01");
    filenames[1].assign("../raw/CSession_02");
    filenames[2].assign("../raw/CSession_03");
    filenames[3].assign("../raw/CSession_28");
    filenames[4].assign("../raw/CSession_29");
    filenames[5].assign("../raw/CSession_30");
    filenames[6].assign("../raw/CSession_31");
    LogList ** loglists = loadfiles(filenames, num_files);
    /**
    for(int i = 0; ((i <num_files) && (!filenames[i].empty())); i++){
        cout<<"File: "<<filenames[i]
            <<" Loads " << (*loglists[i]).getNumofLogs()
            <<" logs\n";       
    }*/
    delete [] filenames;
    cout<< "Testing done.\n";
}
