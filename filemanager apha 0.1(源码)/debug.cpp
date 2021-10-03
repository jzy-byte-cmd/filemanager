#include "standard.h"

int main()
{
    ifstream in;
    string a[10]={""};
    in.open("1.txt",ios::in|ios::binary);
    getline(in,a[1]);
    in.close();
    for(int k=0;k<a[1].size();k++)
    {
        if(a[1][k]=='\r')
        {
            cout<<"yes"<<endl;
            a[1].erase(k,1);
        }
    }
    cout<<a[1].compare("true")<<endl;
    system("pause");
    return 0;
}