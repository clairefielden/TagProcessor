#include <iostream>
#include <fstream>
#include <string.h>
#include <stack>
#include <vector>
#include <stdio.h>

#include "tags.h"

using namespace std;

namespace FLDCLA001 {

struct TagStruct tag;

void storeData(string line, vector<string> &file)
{
    string element = "";
    int i = 0;
    while(i<line.length())
    {
        if(line.at(i)=='<')
        {
            while(line.at(i)!='>')
            {
                element = element+line.at(i);
                i++;
            }
            element = element+line.at(i);
            file.push_back(element);
            element = "";
            i++;
        }
        else
        {
            while(i<line.length())
            {
                if(line.substr(i,2)=="</")
                {
                    break;
                }
                else if(line[i]=='<' && line[i+1]!=' ')
                {
                    break;
                }
                else
                {
                    element = element+line.at(i);
                    i++;
                }
            }

            file.push_back(element);
            element = "";

        }
    }
}

void createBooleanArray(vector<string> &boolArr, vector<string> &file)
{
    //create an array of booleans
    //opening tag = O
    //closing tag = C
    //word = W
    //so if it is stored as a struct, must be in format OWC

    for(int i = 0; i<file.size(); i++)
    {
        if(file.at(i).at(0)=='<' && file.at(i).at(1)=='/')
        {
            boolArr.push_back("C");
        }
        else if(file.at(i).at(0)=='<' && file.at(i).at(1)!='/')
        {
            boolArr.push_back("O");
        }
        else
        {
            boolArr.push_back("W");
        }
    }
}

void createTagOrder(vector<string>&file, vector<string>&tagOrder)
{
   //STEP 1: Create a new file with all the opening tags
   vector<string> tagsOnly;
   for(int i = 0; i<file.size(); i++)
   {
       if(file.at(i).at(0)=='<' && file.at(i).at(1)!='/')
       {
           tagsOnly.push_back(file.at(i).substr(1,file.at(i).length()-2));
       }
   }

   //STEP 2: Remove all repeats
   for(int j = 0; j<tagsOnly.size()-1; j++)
    {
        for(int k = j+1; k<tagsOnly.size(); k++)
        {
            if(tagsOnly.at(j) == tagsOnly.at(k))
            {
                tagsOnly.erase(tagsOnly.begin()+k);
                j = 0;
            }
        }
    }
    tagOrder = tagsOnly;
}


void findRepeats(vector<TagStruct> &tags)
{
    //finding repeated tags & putting them into one instance
    for(int t = 0; t<tags.size()-1; t++)
    {
        for(int u = t+1; u<tags.size(); u++)
        {
            if(tags.at(t).tagName == tags.at(u).tagName)
            {
                //add the nums
                tags.at(t).num = tags.at(t).num+1;
                //add the words from the repeated tag to the prior tag
                for(int v = 0; v<tags.at(u).conc.size(); v++)
                {
                    tags.at(t).conc.push_back(tags.at(u).conc.at(v));
                }
                //delete the repeated tag
                tags.erase(tags.begin()+u);
                t = 0;
            }
        }

    }

}

void printFile(vector<string> file)
{
   for(int i = 0; i<file.size(); i++)
   {
           cout<<file.at(i)<<endl;
   }
}

vector<string> removeFromFile(int x, int y, int z, vector<string> &file)
{
    //file = removeFromFile(i-1, i, i+1);
    vector<string> newFile;

    for(int i = 0; i<file.size(); i++)
    {
        if(i!=x && i!=y && i!=z)
        {
            newFile.push_back(file.at(i));
        }
    }

    return newFile;
}

void removeNesting(vector<string> &file, vector<TagStruct> &tags, vector<string> boolArr)
{
    string concatenate = "";
    while(file.empty()==false)
    {
        for(int i = 0; i<file.size(); i++)
        {
            //go through each element in the file
            if(boolArr.at(i)=="W")
            {
                //if it is not a tag
                if(boolArr.at(i-1)=="O" && boolArr.at(i+1)=="C")
                {
                        //if the tag before the one word is an opening tag and the tag after is a closing tag
                        //add to tags vector as a tag struct
                        struct TagStruct t;
                        t.tagName = file.at(i-1).substr(1,file.at(i-1).length()-2);
                        t.num = t.num+1;
                        t.conc.push_back(file.at(i));
                        //add the tag to the TagStruct vector
                        tags.push_back(t);
                        //now we must delete the whole instance from the file
                        file = removeFromFile(i-1, i, i+1, file);
                        boolArr = removeFromFile(i-1, i, i+1, boolArr);
                        //start searching from top of file again
                        break;
                }
                else if(boolArr.at(i-1)=="O" && boolArr.at(i+1)=="W")
                {
                    //if there is a tag before & another word after
                    //concatenate & search from top of file again
                    //set the string to the current word
                    concatenate = file.at(i) +" "+file.at(i+1);
                    //add the next word to the string
                    file[i] = concatenate;
                    //set the current position in the file to the concatenate strings
                    file.erase(file.begin()+i+1);
                    boolArr.erase(boolArr.begin()+i+1);
                    concatenate = "";
                    //delete the word that came after it
                    //start searching from top of file again
                    break;
                }
            }
        }
    }
 }


vector<TagStruct> sortTags(vector<TagStruct> &tags, vector<string> &tagOrder)
{
    vector<TagStruct> newFile;

        for(int i = 0; i<tagOrder.size(); i++)
        {
            for(int j = 0; j<tags.size(); j++)
            {
                if(tagOrder.at(i) == tags.at(j).tagName)
                {
                    newFile.push_back(tags.at(j));
                }
            }
        }

    return newFile;
}


void printTags(vector<TagStruct> &tags)
{
    for(int i = 0; i<tags.size(); i++)
    {
        cout<<"\""<<tags.at(i).tagName<<"\","<<tags.at(i).num<<",\"";

        if(tags.at(i).num>1)
        {
            for(int x=0; x<tags.at(i).conc.size(); x++)
            {
                if(x==0)
                {
                    cout<<tags.at(i).conc.at(x);
                }
                else
                {
                    cout<<":"<<tags.at(i).conc.at(x);
                }

            }
        }
        else
        {
           for(int x=0; x<tags.at(i).conc.size(); x++)
            {
                if(x==0)
                {
                    cout<<tags.at(i).conc.at(x);
                }
                else
                {
                    cout<<" "<<tags.at(i).conc.at(x);
                }

            }
        }
        cout<<"\""<<endl;

    }
}

void printToFile(vector<TagStruct> &tags, ofstream &outfile)
{
    for(int i = 0; i<tags.size(); i++)
    {
        outfile<<"\""<<tags.at(i).tagName<<"\","<<tags.at(i).num<<",\"";

        if(tags.at(i).num>1)
        {
            for(int x=0; x<tags.at(i).conc.size(); x++)
            {
                if(x==0)
                {
                    outfile<<tags.at(i).conc.at(x);
                }
                else
                {
                    outfile<<":"<<tags.at(i).conc.at(x);
                }

            }
        }
        else
        {
           for(int x=0; x<tags.at(i).conc.size(); x++)
            {
                if(x==0)
                {
                    outfile<<tags.at(i).conc.at(x);
                }
                else
                {
                    outfile<<" "<<tags.at(i).conc.at(x);
                }

            }
        }
        outfile<<"\""<<endl;

    }
}

void findTag(vector<TagStruct> &tags, string name)
{
    //create a new TagStruct vector to store the one tag in
    vector<TagStruct> single;
    bool found = false;
    //finding the tag
    for(int t = 0; t<tags.size(); t++)
    {
        if(tags.at(t).tagName == name)
        {
            single.push_back(tags.at(t));
            found = true;
        }
    }

    if(found == true)
    {
        printTags(single);
        cout<<"\nTAG DATA PRINTED SUCCESSFULLY, PICK ANOTHER OPTION:\n"<<endl;
    }
    else
    {
        cout<<"TAG DOES NOT EXIST, PICK ANOTHER OPTION:\n"<<endl;
    }

}

void P(vector<string> &file, vector<string> &boolArr, vector<string> &tagOrder, vector<TagStruct> &tags)
{
    createBooleanArray(boolArr, file);
    createTagOrder(file, tagOrder);
    removeNesting(file, tags, boolArr);
    findRepeats(tags);
    tags = sortTags(tags, tagOrder);
}
}
