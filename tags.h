#ifndef _TAGS_H
#define _TAGS_H

using namespace std;

namespace FLDCLA001 {

struct TagStruct {
    string tagName;
    int num = 0;
    vector<string> conc;
};

void storeData(string line, vector<string> &file);

void createBooleanArray(vector<string> &boolArr, vector<string> &file);

    //create an array of booleans
    //opening tag = O
    //closing tag = C
    //word = W
    //so if it is stored as a struct, must be in format OWC


void createTagOrder(vector<string>&file, vector<string>&tagOrder);
   //STEP 1: Create a new file with all the opening tags
   //STEP 2: Remove all repeats


void findRepeats(vector<TagStruct> &tags);
    //finding repeated tags & putting them into one instance
    //add the nums
    //add the words from the repeated tag to the prior tag
    //delete the repeated tag

void printFile(vector<string> file);

vector<string> removeFromFile(int x, int y, int z, vector<string> &file);

void removeNesting(vector<string> &file, vector<TagStruct> &tags, vector<string> boolArr);
    //go through each element in the file
    //if it is not a tag
    //if the tag before the one word is an opening tag and the tag after is a closing tag
    //add to tags vector as a tag struct
    //add the tag to the TagStruct vector
    //now we must delete the whole instance from the file
    //start searching from top of file again

    //if there is a tag before & another word after
    //concatenate & search from top of file again
    //set the string to the current word
    //add the next word to the string
    //set the current position in the file to the concatenate strings
    //delete the word that came after it
    //start searching from top of file again

vector<TagStruct> sortTags(vector<TagStruct> &tags, vector<string> &tagOrder);

void printTags(vector<TagStruct> &tags);

void printToFile(vector<TagStruct> &tags, ofstream &outfile);

void findTag(vector<TagStruct> &tags, string name);
    //create a new TagStruct vector to store the one tag in

void P(vector<string> &file, vector<string> &boolArr, vector<string> &tagOrder, vector<TagStruct> &tags);
}

#endif /* TAGS_H */
