#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <vector>

using namespace std;

string convertToLowerCase(string str)
{
    for(int i=0; i<str.length(); i++)
    {
        str[i] = tolower(str[i]);
    }

    return str;
}

int rateEmail(string email, string keyword, int value)
{
    int counter = 0;
    for(int i=0; i<email.length(); i++){
        if(keyword == email.substr(i, keyword.length()))
        {
            counter++;
        }
    }
    
    return counter*value;
}

void readKeywords(map<string, int>& hashMap, vector<string>& strVector)
{
    string filenameKey="keywords.txt";
    ifstream readKey;
    readKey.open(filenameKey);
    ifstream readValue;
    string filenameValue="values.txt";
    readValue.open(filenameValue);

    string key;
    int value;
    while(getline(readKey, key))
    {
        readValue >> value;
        strVector.push_back(key);
        hashMap.insert(pair<string, int>(key, value));
    }

    readValue.close();
    readKey.close();
}

string readEmail(string filename)
{
    ifstream fin;
    fin.open(filename);
    string line;
    string email;

    while (getline(fin, line))
    {
        email += line;
        cout << endl;
    }

    fin.close();
    return email;
    
}

string isSpam(int score)
{
    if(score < 10) return "NOT SPAM.";
    if(score < 50) return "MAYBE SPAM";
    if(score >= 50) return "DEFINITELY SPAM";
}

int main()
{
    string filename = "email.txt";
    string email = readEmail(filename);

    map<string, int> keywords;
    vector<string> phrases;
    readKeywords(keywords, phrases);
    email = convertToLowerCase(email);

    int result=0;
    for(int i=0; i<phrases.size()-1; i++)
    {
        int num = rateEmail(email, phrases.at(i), keywords.at(phrases.at(i)));
        // cout << num << endl;
        result += num;
    }

    cout << result << endl;
    cout << "Email is: " << isSpam(result) << endl;

}