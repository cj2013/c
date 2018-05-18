#include <iostream>
#include <cstdlib>
#include <string.h>
using namespace std;

int main()
{
	string str;
	while(getline(cin, str)){
		if(str == ""){
			cout << 0 << endl;
			continue;
		}
		int nLen = strlen(str.c_str());
		int i = nLen - 1;
		for(; i >= 0 && (str[i] != ' '); i--){
			
		}
		
		if(i == 0){
			cout << 0 << endl;
		}else{
			cout << nLen - 1 - i << endl;
		}
	}
	system("pause");
}