/*
    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.
    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.
    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/


/*
|****************************************************************************
|****************************************************************************
* Project                                         :<Soft_PLC>
* Programm name                                   :soft_plc_compiler.c
* Author                                          :Shults1981
* Data create                                     :01/06/2019
* Purpose                                         :

|***************************************************************************
|***************************************************************************
*/




#define _windows_

#ifdef _windows_

    #define test_prog  "E:\\SOFT_PLC\\soft_plc_compiler\\prg1.splc"

#endif

#ifdef _linux_
    #define test_prog  "//home//alex//programing//SOFT_PLC//soft_plc_compiler//prg1.splc"
#endif



#include <iostream>
#include <string>
#include <cstring>
#include <fstream>
#include <vector>
#include <ctype.h>







using namespace std;

int main()
{
    fstream in_file;

    string buf_str="";
    string buf_str_sc="";
//    vector <string> _prg_;
    vector <string> _tok_;

    char *rch=new char;
    char *rch_sc=new char;
    long long readpos=0;
    bool tok_bild=false;


    in_file.open(test_prog,ios::in);

    if (!in_file)
        cerr<<"Can`t open input file"<<endl;
    else{
        in_file.seekg(readpos,ios::beg);
        while (!in_file.eof())
        {
            in_file.read(rch,1);
            cout<<*rch;
            if (!tok_bild){

                if (isalpha(*rch) || isdigit(*rch)|| (*rch=='_'))
                    buf_str.push_back(*rch);
                if (*rch==':')
                {
                   *rch_sc=*rch;
                   buf_str_sc.push_back(*rch);
                   tok_bild=true;
                }
                if (*rch=='.')
                {
                   *rch_sc=*rch;
                   buf_str_sc.push_back(*rch);
                   tok_bild=true;
                }

                //-----token is bild
                if (*rch=='\n')
                {
                    tok_bild=true;
                }
                if (isspace(*rch))
                {
                    tok_bild=true;
                }

            }


            if (tok_bild) // ading in to array of tokens
            {
                if (!buf_str.empty())
                {
                _tok_.push_back(buf_str);
                buf_str.clear();
                }
                if (!buf_str_sc.empty())
                {
                _tok_.push_back(buf_str_sc);
                buf_str_sc.clear();
                }

                tok_bild=false;
            }

        }
    }

    cout<<"================================="<<endl;
        for (unsigned int i=0; i<_tok_.size(); i++)
            cout<<"(tok#"<<i<<"-"<<_tok_.at(i)<<")"<<std::endl;



    in_file.close();
    delete rch;


    return 0;
}


