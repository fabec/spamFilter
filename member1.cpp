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

bool comparePhrase(string phrase, string keyword)
{
    int levenshteinDistance = 1;
    int counter = 0;

    for(int i=0; i<keyword.length(); i++)
    {
        if(keyword[i] == phrase[i]) counter++;
    }

    if(counter == keyword.length() && keyword.length() == 1) return true;
    else if((counter >= keyword.length() - levenshteinDistance) && (keyword.length() > levenshteinDistance)) return true;
    else return false;
}

int rateEmail(string email, string keyword)
{
    int counter = 0;
    for(int i=0; i<email.length(); i++)
    {
        string phrase = email.substr(i, keyword.length());
        bool isGood = comparePhrase(phrase, keyword);

        cout << phrase << " " << keyword << " " << isGood << " " << counter <<endl;
        if(isGood)
        {
            counter++;
            i += keyword.length();
        } 
    }

    return counter;
}

void readKeys(vector<string> strVector, vector<int> intVector)
{
    string filename="keywords.txt";
    ifstream readKey;
    readKey.open(filename);
    ifstream readValue;;
    readValue.open(filename);

    string key;
    int value;
    while(readKey >> key)
    {
        readValue >> value;
        strVector.push_back(key);
        intVector.push_back(value);
    }

    readValue.close();
    readKey.close();
}

string cleanString(string str)
{
    // for (int i=0; i<str.length(); i++)
    // {
    //     if(ispunct(str[i])) str.erase(i--, 1);
    // }

    str = convertToLowerCase(str);

    return str;
}

string readEmail(string filename)
{
    ifstream fin;
    fin.open(filename);
    string word;
    string email;

    while (fin >> word)
    {
        word = cleanString(word);
        email += word + " ";
    }

    fin.close();
    return email.substr(0, email.length()-1);
    
}

string isSpam(int score)
{
    if(score < 10) return "NOT SPAM.";
    if(score < 50) return "MAYBE SPAM";
    if(score >= 50) return "DEFINITELY SPAM";
}

int main()
{
    string filename = "email7.txt";
    string email = readEmail(filename);

    vector<string> keywords = {"$", "earn per week", "double your", "income in one week", "trial that lasts forever",  "opportunity", "income", "cash", "month free trial", "your love life"};
    vector<int> values = {10, 20, 20, 15, 30, 10, 10, 20, 15, 25};

    unsigned long long int result=0;
    cout << email << endl;
    for(int i=0; i<keywords.size(); i++)
    {
        int num = rateEmail(email, keywords[i]);
        result = result + (num * values[i]);
    }

    cout << result << endl;
    cout << "Email is: " << isSpam(result) << endl;

}