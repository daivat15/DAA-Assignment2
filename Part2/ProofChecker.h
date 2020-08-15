#include <bits/stdc++.h>
using namespace std;

class ProofChecker {
    public:
        /**
         * Core function
         * @param n The number of lines in proof.
         * @return The value if the proof is valid or not.
         */
        static int checker(int n) {
            int flag = 1;
            vector<string> box;     //box is vector of strings where all valid statements are stored.
            while(n-- && flag==1)
            {
                string x;
                cin>>x;
                int count=0;
                for(int i=0;i<x.size()-1;i++)
                {   /**
             * This will check if the statement entered is a Premise.
             * If it is a premise then then it is stored in temp which is then pushed in box*/
                    if(x[i]=='/' && x[i+1]=='P' && flag==1)
                    {
                        string temp;
                        for(int j=0;j<i;j++)
                        {
                            temp.push_back(x[j]);
                        }
                        box.push_back(temp);

                        count++;
                    }
                    /**
                     * This will check if the statement is a AND introduction.
                     * If it is then i1 and i2 will be the two sub statements from which and is derived. We make temp2 from the substatements
                     * and then compare it with the given statement.If both are equal we can continue further and analyse other statements otherwise directly make flag 0*/
                    if(x[i]=='/' && x[i+1]=='^'  && x[i+2]=='i' && flag==1)
                    {
                        string temp1,temp2;

                        string q;
                        int y=i+4;
                        while(x[y]!='/')
                        {
                            q.push_back(x[y]);
                            y++;
                        }
                        int i1=stoi(q);
                        string w;
                        int r=y+1;

                        while(r!=x.size())
                        {
                            w.push_back(x[r]);
                            r++;
                        }
                        int i2=stoi(w);
                        for(int j=0;j<i;j++)
                        {
                            temp1.push_back(x[j]);
                        }
                        temp2.push_back('(');
                        for(int z=0;z<box[i1-1].size();z++)
                            temp2.push_back(box[i1-1][z]);
                        temp2.push_back('^');
                        for(int z=0;z<box[i2-1].size();z++)
                            temp2.push_back(box[i2-1][z]);
                        temp2.push_back(')');
                        if(temp1 == temp2)
                        {
                            box.push_back(temp1);
                            count++;
                        }
                        else
                        {
                            flag=0;
                            break;
                        }

                    }
                        /**
                         * This will check if the statement is AND elimination 1. temp1 will have the given statement.
                         * If it is then i1 will be the statement from which this given statement is derived. We then push the statement corresponding to i1 in stack s.
                         * Then temp2 is found out which is obtained from ^e1 from the i1 statement.If both are equal we can continue further and analyse other statements
                         * otherwise directly make flag 0*/
                    else if(x[i]=='/' && x[i+1]=='^' && x[i+2]=='e' && x[i+3]=='1' && flag==1)
                    {   string temp1;
                        stack <char> s;
                        for(int j=0;j<i;j++)
                        {
                            temp1.push_back(x[j]);
                        }

                        string q;
                        int y=i+5;
                        while(x[y]!='/')
                        {
                            q.push_back(x[y]);
                            y++;
                        }
                        int i1=stoi(q);
                        for(int j=box[i1-1].size()-1;j>=0;j--)
                        {
                            s.push(box[i1-1][j]);
                        }
                        int parenthesis=0;
                        int alphabet=0;
                        int sign=0;
                        int doublecheck=0;
                        int doublecheck2=0;
                        string temp2;
                        while(!s.empty())
                        {
                            char ele=s.top();
                            if(ele=='(' && doublecheck==0 && doublecheck2==0) /*double check will ensure only the part before and is pushed in temp2*/
                            {   /*parenthesis, alphabet and sign will ensure that desired part is only pushed in temp2*/
                                parenthesis++;
                                alphabet++;
                                sign++;
                                if(parenthesis>1)
                                    temp2.push_back(ele);
                            }
                            else if(ele==')')
                            {

                                parenthesis--;
                                if(parenthesis>0)
                                    temp2.push_back(ele);
                                if(parenthesis==1)
                                {
                                    doublecheck=1;
                                    break;
                                }
                            }
                            else if((ele>='a' && ele<='u')|| (ele>='w' && ele<='z') || (ele>='A' && ele<='Z'))
                            {
                                if(alphabet>0)
                                {
                                    temp2.push_back(ele);
                                    alphabet--;
                                }
                            }
                            else if(ele=='~')   /*not symbol*/
                            {

                                temp2.push_back(ele);
                            }
                            else
                            {
                                if(sign==1)
                                {
                                    doublecheck2=1;
                                }
                                else if(sign>1)
                                {
                                    temp2.push_back(ele);
                                    sign--;
                                }

                            }

                            s.pop();

                        }
                        /*We compare temp1 and temp2 and if both  are equal then it is put on box vector otherwise flag is made 0 and proof is invalid*/
                        if(temp1 == temp2)
                        {
                            box.push_back(temp1);
                            count++;
                        }
                        else
                        {
                            flag=0;
                            break;
                        }
                    }
                        /**
                         * This will check if the statement is AND elimination 2. temp1 will have the given statement.
                         * i1 will be the statement from which this given statement is derived. We then push the statement corresonding to i1 in stack s.
                         * Then temp2 is found out which is obtained from ^e2 from the i1 statement.If both are equal we can continue further and analyse other statements
                         * otherwise directly make flag 0*/
                    else if(x[i]=='/' && x[i+1]=='^' && x[i+2]=='e' && x[i+3]=='2' && flag==1)
                    {
                        stack <char> s;
                        string temp1,permanent;
                        for(int j=0;j<i;j++)
                        {
                            temp1.push_back(x[j]);
                        }
                        string q;
                        int y=i+5;
                        while(x[y]!='/')
                        {
                            q.push_back(x[y]);
                            y++;
                        }
                        int i1=stoi(q);
                        for(int j=0;j<box[i1-1].size();j++)
                        {
                            s.push(box[i1-1][j]);
                        }
                        int parenthesis=0;
                        int alphabet=0;
                        int sign=0;
                        string temp2;
                        int doublecheck=0;
                        int doublecheck2=0;
                        while(!s.empty())
                        {
                            char ele=s.top();
                            if(ele==')' && doublecheck==0 && doublecheck2==0)
                            {
                                parenthesis++;
                                alphabet++;
                                sign++;
                                if(parenthesis>1)
                                    temp2.push_back(ele);

                            }
                            else if(ele=='(')
                            {
                                parenthesis--;
                                if(parenthesis>0)
                                    temp2.push_back(ele);
                                if(parenthesis==1)
                                {
                                    doublecheck=1;
                                    break;
                                }
                            }
                            else if((ele>='a' && ele<='u')|| (ele>='w' && ele<='z') || (ele>='A' && ele<='Z'))
                            {
                                if(alphabet>0)
                                {
                                    temp2.push_back(ele);
                                    alphabet--;
                                }
                            }
                            else if(ele=='~')
                            {
                                temp2.push_back(ele);
                            }
                            else
                            {
                                if(sign==1)
                                {
                                    doublecheck2=1;
                                }
                                else if(sign>1)
                                {
                                    temp2.push_back(ele);
                                    sign--;
                                }

                            }

                            s.pop();

                        }

                        reverse(temp2.begin(),temp2.end()); /*to reverse temp2*/
                        /*We compare temp1 and temp2 and if both  are equal then it is put on box vector*/
                        if(temp1 == temp2)
                        {
                            box.push_back(temp1);
                            count++;
                        }
                        else
                        {
                            flag=0;
                            break;
                        }
                    }
                        /**
                         * This will check if the statement is OR introduction 1. permanent will have the given statement.
                         * i1 will be the statement from which this given statement is derived.
                         * temp1 will have the statement from box which corresponds to i1. We then push the permanent statement in stack s.
                         * Then temp2 is found out which is the part from which permanent is obtined by v i1.
                         * If both temp1 and temp2 are equal we can continue further and analyse other statements
                         * otherwise directly make flag 0*/
                    else if(x[i]=='/' && x[i+1]=='v' && x[i+2]=='i' && x[i+3]=='1' && flag==1)
                    {   string temp1,permanent,temp2;

                        stack <char> s;
                        for(int j=0;j<i;j++)
                        {
                            permanent.push_back(x[j]);
                        }

                        string q;
                        int y=i+5;
                        while(y!=x.size())
                        {
                            q.push_back(x[y]);
                            y++;
                        }
                        int i1=stoi(q);
                        for(int j=0;j<box[i1-1].size();j++)
                        {
                            temp1.push_back(box[i1-1][j]);
                        }
                        for(int i=permanent.size()-1;i>=0;i--)
                        {
                            s.push(permanent[i]);
                        }
                        int parenthesis=0;
                        int alphabet=0;
                        int sign=0;
                        int doublecheck=0;
                        int doublecheck2=0;
                        while(!s.empty())
                        {
                            char ele=s.top();


                            if(ele=='('&& doublecheck==0 && doublecheck2==0)
                            {
                                parenthesis++;
                                alphabet++;
                                sign++;
                                if(parenthesis>1)
                                    temp2.push_back(ele);

                            }
                            else if(ele==')')
                            {
                                parenthesis--;
                                if(parenthesis>0)
                                    temp2.push_back(ele);
                                if(parenthesis==1)
                                {
                                    doublecheck=1;
                                    break;
                                }
                            }
                            else if((ele>='a' && ele<='u')|| (ele>='w' && ele<='z') || (ele>='A' && ele<='Z'))
                            {
                                if(alphabet>0)
                                {
                                    temp2.push_back(ele);
                                    alphabet--;
                                }
                            }
                            else if(ele=='~')
                            {
                                temp2.push_back(ele);
                            }
                            else
                            {
                                if(sign==1)
                                {
                                    doublecheck2=1;
                                }
                                else if(sign>1)
                                {
                                    temp2.push_back(ele);
                                    sign--;
                                }

                            }

                            s.pop();

                        }
                        /*We compare temp1 and temp2 and if both  are equal then it is put on box vector*/
                        if(temp1 == temp2)
                        {
                            box.push_back(permanent);
                            count++;
                        }
                        else
                        {
                            flag=0;
                            break;
                        }
                    }
                        /**
                         * This will check if the statement is OR introduction 2. permanent will have the given statement.
                         * i1 will be the statement from which this given statement is derived.
                         * temp1 will have the statement from box which corresponds to i1. We then push the permanent statement in stack s.
                         * Then temp2 is found out which is the part from which permanent is obtained by v i1.
                         * If both temp1 and temp2 are equal we can continue further and analyse other statements
                         * otherwise directly make flag 0*/
                    else if(x[i]=='/' && x[i+1]=='v' && x[i+2]=='i' && x[i+3]=='2' && flag==1)
                    {   string temp1,permanent;
                        stack <char> s;
                        for(int j=0;j<i;j++)
                        {
                            permanent.push_back(x[j]);
                        }
                        string q;
                        int y=i+5;
                        while(y!=x.size())
                        {
                            q.push_back(x[y]);
                            y++;
                        }
                        int i1=stoi(q);

                        for(int j=0;j<box[i1-1].size();j++)
                        {
                            temp1.push_back(box[i1-1][j]);
                        }
                        for(int i=0;i<permanent.size();i++)
                        {
                            s.push(permanent[i]);
                        }
                        int parenthesis=0;
                        int alphabet=0;
                        int sign=0;
                        int doublecheck=0;
                        int doublecheck2=0;
                        string temp2;
                        while(!s.empty())
                        {
                            char ele=s.top();
                            if(ele==')' && doublecheck==0 && doublecheck2==0)
                            {
                                parenthesis++;
                                alphabet++;
                                sign++;
                                if(parenthesis>1)
                                    temp2.push_back(ele);

                            }
                            else if(ele=='(')
                            {
                                parenthesis--;
                                if(parenthesis>0)

                                    temp2.push_back(ele);
                            }
                            else if((ele>='a' && ele<='u')|| (ele>='w' && ele<='z') || (ele>='A' && ele<='Z'))
                            {
                                if(alphabet>0)
                                {
                                    temp2.push_back(ele);
                                    alphabet--;
                                }
                            }
                            else if(ele=='~')
                            {
                                temp2.push_back(ele);
                            }
                            else
                            {
                                if(sign==1)
                                {
                                    doublecheck2=1;
                                }
                                else if(sign>1)
                                {
                                    temp2.push_back(ele);
                                    sign--;
                                }

                            }
                            s.pop();

                        }
                        reverse(temp2.begin(),temp2.end());
                        /*We compare temp1 and temp2 and if both  are equal then it is put on box vector otherwise flag is made 0 and proof is invalid*/
                        if(temp1 == temp2)
                        {
                            box.push_back(permanent);
                            count++;
                        }
                        else
                        {flag=0;
                            break;
                        }
                    }

                        /**
                         * This will check if the statement is implication elimination. temp1 will have the given statement.
                         * i1 and i2 are the statement from which this given statement is derived.
                         * If i1 has implication symbol then interchange i1 and i2. i2 should have implication symbol. Also implication symbol used is "->"
                         * temp2 will form an implication statement. temp3 will be statement corresponding to i2.
                         * If both temp2 and temp3 are equal we can continue further and analyse other statements
                         * otherwise directly make flag 0*/
                    else if(x[i]=='/' && x[i+1]=='-' && x[i+3]=='e' && flag==1)
                    {   string temp1,temp3;
                        stack <char> s;

                        string q;
                        int y=i+5;
                        while(x[y]!='/')
                        {
                            q.push_back(x[y]);
                            y++;
                        }
                        int i1=stoi(q);
                        string w;
                        int r=y+1;

                        while(r!=x.size())
                        {
                            w.push_back(x[r]);
                            r++;
                        }
                        int i2=stoi(w);
                        for(int j=0;j<i;j++)
                        {
                            temp1.push_back(x[j]);
                        }
                        int check=1;
                        for(int i=0;i<box[i1-1].size()-1;i++)
                        {
                            if(box[i1-1][i]=='-')
                                check=0;

                        }
                        if(check==0)
                        {
                            int z;
                            z=i1;
                            i1=i2;
                            i2=z;
                        }
                        string temp2;
                        temp2.push_back('(');
                        for(int z=0;z<box[i1-1].size();z++)
                            temp2.push_back(box[i1-1][z]);
                        temp2.push_back('-');
                        temp2.push_back('>');
                        for(int z=0;z<temp1.size();z++)
                            temp2.push_back(temp1[z]);
                        temp2.push_back(')');

                        for(int z=0;z<box[i2-1].size();z++)
                        {
                            temp3.push_back(box[i2-1][z]);
                        }


                        if(temp2 == temp3)
                        {
                            box.push_back(temp1);
                            count++;
                        }

                        else
                        {
                            flag=0;
                            break;
                        }
                    }
                        /**
                         * This will check if the statement follows MT rule or not. temp1 will have the given statement.
                         * i1 and i2 are the statement from which this given statement is derived.
                         * If i1 has implication symbol then interchange i1 and i2. i2 should have implication symbol. Also implication symbol used is "->"
                         * temp2 will form an implication statement. temp3 will be statement corresponding to i2.
                         * If both temp2 and temp3 are equal we can continue further and analyse other statements
                         * otherwise directly make flag 0*/
                    else if(x[i]=='/' && x[i+1]=='M' && x[i+2]=='T' && flag==1)
                    {   string temp1,temp3;
                        stack <char> s;

                        string q;
                        int y=i+4;
                        while(x[y]!='/')
                        {
                            q.push_back(x[y]);
                            y++;
                        }
                        int i1=stoi(q);
                        string w;
                        int r=y+1;

                        while(r!=x.size())
                        {
                            w.push_back(x[r]);
                            r++;
                        }
                        int i2=stoi(w);

                        for(int j=0;j<i;j++)
                        {
                            temp1.push_back(x[j]);
                        }
                        int check=1;
                        for(int i=0;i<box[i1-1].size()-1;i++)
                        {
                            if(box[i1-1][i]=='-')
                                check=0;

                        }
                        if(check==0)
                        {
                            int z;
                            z=i1;
                            i1=i2;
                            i2=z;
                        }
                        string temp2;
                        temp2.push_back('(');

                        for(int z=1;z<temp1.size();z++) //z=1 to ignore initial ~
                            temp2.push_back(temp1[z]);
                        temp2.push_back('-');
                        temp2.push_back('>');
                        for(int z=1;z<box[i1-1].size();z++) //z=1 to ignore initial ~
                            temp2.push_back(box[i1-1][z]);
                        temp2.push_back(')');

                        for(int z=0;z<box[i2-1].size();z++)
                        {
                            temp3.push_back(box[i2-1][z]);
                        }

                        if(temp2 == temp3)
                        {
                            box.push_back(temp1);
                            count++;
                        }

                        else
                        {
                            flag=0;
                            break;
                        }
                    }


                }
            }
            return flag;
        }

};