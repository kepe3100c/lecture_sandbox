#include <iostream>
using namespace std;
int main(void){
    string M1,M2;
    // int M1[10];
    // int M2[10]
    int iN,iM1,iM2;
    int listN[1000];
    int needM[1000],matchM[1000];
    bool emp;
    int i,j;
    
    getline(cin,iN);
    getline(cin,iM1);
    getilne(cin,M1);
    getline(cin.iM2);
    getline(cin.M2);
    
    for(i = 0; i < iN; i++)
    {
        listN[i] = i + 1;
    }
    
    for(size_t c = M1.find_first_of(" "); c != string::npos; c = c = M1.find_first_of(" ")){
      M1.erase(c,1);
    }
    
    for(size_t c = M2.find_first_of(" "); c != string::npos; c = c = M2.find_first_of(" ")){
      M2.erase(c,1);
    }
    
    for(i = 0; i < iN; i++)
    {
        for(j = 0; j < iM1; j++)
        {
            if(listN[i] != iM1[j])
            {
                needM[i] = atoi(iM1[j]);
            }
        }
    }
    
    for(i = 0; i < iM1; i++)
    {
        for(j = 0; j < iM2; j++)
        {
            if(needM[i] != iM2[j])
            {
                matchM[i] = atoi(iM2[j]);
                emp = true;
            }
        }
    }
    
    if(emp)
    {
        for(i = 0; i < ; i++)
        {
            
        }
        
    }
    
    return 0;
}
