#include <iostream>
#include <fstream>
#include <string.h>
#include <stack>
#include <vector>
#include <stdio.h>

#include "tags.h"
#include "tags.cpp"

using namespace std;

int main(void)
{
        char ans = 'x';
        vector<FLDCLA001::TagStruct> tags;
        //a vector of TagStruct objects
        vector<string> file;
        //file will contain every tag/word in order in separate indices
        vector<string> boolArr;
        //vector of booleans displaying which position in the (old) file is a tag and which is a word
        vector<string> tagOrder;
        //a vector containing the tags in the correct order


    while(ans!='q')
    {
        cout<<" 1. r - read and parse input file \n 2. p - print all tags \n 3. d - write tags and data to file \n 4. l = list tag data \n 5. q - quit"<<endl;
        cin>>ans;
        ans = tolower(ans);

        switch(ans) {

    case 'r':
    {
        //read in data from file
        ifstream indata;

        string filename;
        cout<<"\nSPECIFY NAME OF INPUT FILE:"<<endl;
        cin>>filename;
        indata.open(filename);

        string str;
        int count = 0;

        if(!indata)
        {
            cout<<"ERROR! FILE COULD NOT BE OPENED!\n";
            return 1;
        }

        while(!indata.eof())
        {
            getline(indata, str, '\n');
            //store tags & words in file vector
            FLDCLA001::storeData(str, file);
        }

        indata.close();

        //parse the file
        cout<<"\nPARSING YOUR FILE . . ."<<endl;
        FLDCLA001::P(file, boolArr, tagOrder, tags);
        cout<<"\nFILE PARSED SUCCESSFULLY, PICK ANOTHER OPTION: \n"<<endl;
        break;
    }

    case 'p':
    {
        cout<<"\nPRINTING ALL TAGS . . .\n"<<endl;

        FLDCLA001::printTags(tags);
        cout<<"\nALL TAGS PRINTED SUCCESSFULLY, PICK ANOTHER OPTION: \n"<<endl;
        break;

    }

    case 'd':
    {
        cout<<"\nWRITING YOUR TAGS TO FILE 'tags.txt' . . ."<<endl;

        ofstream outdata;
        outdata.open("tag.txt");

        if(!outdata)
        {
            cout<<"ERROR! FILE COULD NOT BE OPENED!\n";
            return 1;
        }

        FLDCLA001::printToFile(tags, outdata);

        cout<<"\nTAGS WRITTEN SUCCESSFULLY TO FILE, PICK ANOTHER OPTION: \n"<<endl;

        break;
    }

    case 'l':
    {
        string tn;
        cout<<"\nSPECIFY THE TAG FOR WHICH DATA IS NEEDED:"<<endl;
        cin>>tn;
        cout<<"\n"<<endl;
        FLDCLA001::findTag(tags, tn);
        break;
    }

    }
    }
    cout<<"\n\nProgram terminated!"<<endl;
    return 0;
}
