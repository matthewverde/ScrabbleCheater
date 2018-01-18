//Made by: Matthew Green

#include <iostream>
#include <string>
#include <stdlib.h>
#include <fstream>
#include <unordered_map>
#include <vector>

using namespace std;

string letters =  "qwertyuiopasdfghjklzxcvbnm";
string alphabet = "abcdefghijklmnopqrstuvwxyz";
string startingLetters = "";
unordered_map<string,bool> dict;
bool repeats = false;
vector<int> letterLoc;

int len;
int totalNodes;
int wordsFound;

vector<int> getLetterLoc(string input)
{
    vector<int> toRet;
    for(int i = 0; i < input.size(); i++)
    {
        if(input[i] != '-')
        {
            toRet.push_back(i);
        }
    }
    return toRet;
}

//this function is used to determine if a specific spot within the tree being produced has a defined charcter as
//defined by the user
bool hasDefinedLetter(int level)
{
    for(auto num : letterLoc)
    {
        if(num == level)
        {
            return true;
        }
    }
    
    return false;
}

//loads the computers predefined dictionary into a hash table
unordered_map<string,bool> getDict()
{
    ifstream input("/usr/share/dict/words");
    string line;
    unordered_map<string,bool> toRet;
    
    cout << "Loading Dictionary" << endl;
    while(getline(input, line))
    {
        toRet[line] = true;
    }
    cout << "Done Loading" << endl;
    input.close();
    
    return toRet;
}

//Removes the first instance of a character within a string
//returns the string without the first character found
string removeChar(string input, char c)
{
    int loc = input.find_first_of(c,0);
    string front, end;
    
    if(loc != -1)
    {
        front = input.substr(0,loc);
        end = input.substr(loc + 1);
        input = front + end;
    }
    
    return input;
}

//removes a character by location within the string
string removeChar(string input, int pos)
{
    string front, end;
    
    if(pos < input.size())
    {
        front = input.substr(0,pos);
        end = input.substr(pos + 1);
        input = front + end;
    }
    
    return input;
}

//simple bubble sort to sort the letters produced by the user
string sortLetters(string input)
{
    char temp;
    for(int i = 0; i < input.size(); i++)
    {
        for(int j = i + 1; j < input.size(); j++)
        {
            if((int)input[i] > (int)input[j])
            {
                temp = input[i];
                input[i] = input[j];
                input[j] = temp;
            }
        }
    }
    return input;
}

//recusive function to produce all combinations of characters provided by the user
void rec(string toPrint, string remaining)
{
    int curSize = toPrint.size();
    string nextRemaining = "";
    totalNodes++;
    //terminating statement for recusive function
    //if the size of our string is the length of required print length, check to see if it is a real word
    if(toPrint.size() == len)
    {
        if(dict.find(toPrint) != dict.end())
        {
            if(dict[toPrint] == true)
            {
                cout << toPrint << endl;
                dict[toPrint] = false;
                wordsFound++;
            }
        }
    }
    else
    {
        if(hasDefinedLetter(toPrint.size()))
        {
            toPrint += startingLetters[curSize];
            
            if(!repeats)
            {
                nextRemaining = removeChar(remaining, startingLetters[curSize]);
            }
            else
            {
                nextRemaining = letters;
            }
            
            rec(toPrint, nextRemaining);
        }
        else
        {
            //for every remaining letter that can be used, start a new DFS
            for(int i = 0; i < remaining.size(); i++)
            {
                //if(toPrint.find(letters[i]) == string::npos)
            
                if(toPrint.size() == curSize)
                {
                    toPrint += remaining[i];
                }
                else
                {
                    toPrint[curSize] = remaining[i];
                }
            
                if(!repeats)
                {
                    nextRemaining = removeChar(remaining, i);
                }
                else
                {
                    nextRemaining = letters;
                }
            
                rec(toPrint, nextRemaining);
            }
        }
    }
}

int main(int argc, char *argv[])
{
    int pos = 0;
    string start = "";
    
    if(argc < 3)
    {
        cout << "The order of required inputs are\n1.Letters to make words from (Or '-' to use all characters)\n2.Requested length of words to find\n3.(Optional) Location of known letters ex. a--b-d would find all words with 'a' as the first character 'b' as the fourth character, and 'd' as the sixth character." << endl;
        return 0;
    }
    
    totalNodes = 0;
    wordsFound = 0;
    letters = argv[1];
    len = atoi(argv[2]);
    string remaining = "";
    
    letters = sortLetters(letters);
    if(letters == "-")
    {
        repeats = true;
        letters = alphabet;
    }
    
    if(argc > 3)
    {
        startingLetters = argv[3];
        letterLoc = getLetterLoc(startingLetters);
    }
    
    dict = getDict();
    
    for(int i = 0; i < letters.size(); i++)
    {
        //this if statement makes it so we dont start a new "tree" starting with a letter we have already checked
        //if(start.find(letters[i]) == string::npos)
        //{
        totalNodes++;
        start = "";//startingLetters;
        
        if(hasDefinedLetter(0))
        {
            start += startingLetters[0];
        }
        else
        {
            start += letters[i];
        }
        
        if(!repeats)
        {
            remaining = removeChar(letters, letters[i]);
        }
        else
        {
            remaining = letters;
        }
        rec(start,remaining);
        
        if(hasDefinedLetter(0))
        {
            break;
        }
        //}
    }
    
    
    cout << "Total Nodes Made: \t" << totalNodes << endl;
    cout << "Total Words Found: \t" << wordsFound << endl;
    return 0;
}
