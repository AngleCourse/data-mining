
#include "./include/loadlog.h"
#include "./include/fpphasea.h"
#include "./include/fpphaseb.h"

using namespace std;

void testing();

int main(){
    testing();
    return 0;
}
void testing(){

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
    delete [] filenames;
    cout<<"Test loading module done\n";

    cout<<"Starting to test Precomputing module...\n";
    map<string, int> ip_map;
    vector<  vector<int>  > tran_ip = trans_ip_int((loglists[0]->getLogs()), ip_map);   
    vector<int>  order, count;
    count_sort_ip(tran_ip, order, count);
    sort_transaction(tran_ip, order); 
    cout<<"Testing done.\n";

    cout<<"Starting to test FP-Tree building module...\n";
    testfptree(tran_ip);
     
    cout<<"Testing done.\n";
    
}
