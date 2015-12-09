#include <iostream>
#include <fstream>
#include <sstream> //istringstream
#include <string>
using namespace std;
int main(){
    istringstream t1("12345,6778976,ewertyuytre");
    string* s1 = new string[3];
    for(int i = 0; !getline(t1, s1[i], ',').eof(); i++);
    cout<<s1[0]<<endl
        <<s1[1]<<endl
        <<s1[2]<<endl;
    delete [] s1;
    return 0;
    /**
    ifstream input("./CSession_01", ifstream::in);
    int i = 10;
    string test;
    while(!getline(input, test, '|').eof() && i > 0){
        cout<<i<<"th round"<<endl;
        cout<<test<<endl;
        getline(input, test, '|');
        cout<<test<<endl;
        getline(input, test, '|');
        cout<<test<<endl;
        getline(input, test, '|');
        cout<<test<<endl;
        getline(input, test);
        cout<<test<<endl;
        i--;
    }
    input.close();
    return 0;
    */

}
