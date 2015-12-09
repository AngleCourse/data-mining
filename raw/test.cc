#include <iostream>
#include <fstream>
#include <string>
using namespace std;
int main(){
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

}
