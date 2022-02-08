#include "hashmap.h"
#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;

/** 
  * Assignment 3 for COSE213 Data Structures
  *
  * 2021. 11. 1   Won-Ki Jeong
  *
  */

MapElem<std::string,int> mapElem;
HashMap<MapElem<std::string,int>> map;
char alphabet[26] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};

void spellcheck(std::string s)
{
    if (map.find(s) != NULL) {
        std::cout << "> " << s + " is in the dictionary" << std::endl;
    } else {
        std::cout << "> " << s + " is NOT in the dictionary" << std::endl;
        bool first = true;
        unsigned long length = s.length();
        char *p = new char[length + 1];
        p[length] = '\0';
        
        for (int i = 0; i < length; i++) {
            for (int j = 0; j < length; j++) {
                p[j] = s[j];
            }
            
            for (int j = 0; j < 26; j++) {
                p[i] = alphabet[j];
                if (map.find(p)) {
                    if (first) {
                        std::cout << "> " << s + " : " + map.find(p)->key;
                        first = false;
                    } else {
                        std::cout << ", " + map.find(p)->key;
                    }
                }
            }
        }
        
        if (first) {
            std::cout << "> " << s + " : no suggestion";
        }
        std::cout << std::endl;
        free(p);
    }
}

int main()
{
    // load dictionary
    char filename[] = "dictionary.txt";
    std::ifstream ifs(filename, std::ifstream::in);
    std::string s((std::istreambuf_iterator<char>(ifs)), std::istreambuf_iterator<char>());
    std::transform(s.begin(), s.end(),
                   s.begin(), ::tolower);

    std::string token;
    unsigned int len = s.length();
        
    for(int i=0; i<len; i++)
    {
        int ascii = s[i];
        if(ascii < 97 || ascii > 127)
        {
            if(token.length() > 0)
            {
                // ToDo
                // Insert token to hash map
                map.insert(token, 1);
                token.clear();
            }
            continue;
        }
        token.push_back(s[i]);
    }
    map.insert(token, 1);
    token.clear();
    
    //
    // infinite loop to accept user input word
    //
    while(1)
    {
        std::string s;
        std::cout << "> ";
        std::cin >> s;
        
        if(s.compare("q") == 0) break;
        
        spellcheck( s );
    }
    
    return 0;
}
