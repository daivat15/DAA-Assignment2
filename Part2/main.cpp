#include<bits/stdc++.h>
#include "ProofChecker.h"

using namespace std;

/**
 * Boiler plate code
 * @return default value
 */
int main()
{
    int n;      //no. of lines in proof rule
    cin>>n;
    int flag = ProofChecker::checker(n);


    if(flag==0)
        cout<<"Invalid";
    else
        cout<<"Valid";
    return 0;
}