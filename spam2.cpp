#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <vector>

using namespace std;

string convertToLowerCase(string str)
{
    for (int i = 0; i < str.length(); i++)
    {
        str[i] = tolower(str[i]);
    }

    return str;
}

bool comparePhrase(string &phrase, string keyword)
{
    int levenshteinDistance = 1;
    int counter = 0;

    for (int i = 0; i < keyword.length(); i++)
    {
        if (isspace(keyword[i]))
            levenshteinDistance++;
        if (keyword[i] == phrase[i])
            counter++;
    }

    if (counter == keyword.length() && keyword.length() == 1)
    {
        phrase = keyword;
        return true;
    }
    else if ((counter >= keyword.length() - levenshteinDistance) && phrase.length() <= keyword.length() + 1 && phrase.length() >= keyword.length() - 1)
    {
        phrase = keyword;
        return true;
    }
    else
    {
        return false;
    }
}

void rateEmail(string &email, vector<string> keywords, map<string, int> &numOfInstances)
{
    for (int i = 0; i < email.length(); i++)
    {
        for (int j = 0; j < keywords.size(); j++)
        {
            string phrase = email.substr(i, keywords[j].length());
            bool isGood = comparePhrase(phrase, keywords[j]);

            if (isGood && (keywords[j].length() != 1 || (phrase.length() == 1 && ((isspace(email[i + 1]) || i == email.length() - 1) && (isspace(email[i - 1]) || i == 0)))))
            {
                numOfInstances.at(keywords[j])++;
                email.erase(i, keywords[j].length());
            }
        }
    }
}

string readEmail(string filename, int &counter)
{
    ifstream fin;
    fin.open(filename);
    string word;
    string email;

    while (fin >> word)
    {
        counter++;
        word = convertToLowerCase(word);
        email += word + " ";
    }

    fin.close();
    return email.substr(0, email.length() - 1);
}

string isSpam(int score)
{
    if (score < 10)
        return "NOT SPAM.";
    if (score < 50)
        return "MAYBE SPAM";
    if (score >= 50)
        return "DEFINITELY SPAM";
}

double relativeSpam(double numberOfWords_spam, double numberOfWords_email)
{
    return 100.0 * (numberOfWords_spam / numberOfWords_email);
}

map<string, int> initialiseMap(vector<string> vec)
{
    map<string, int> newMap;
    for (int i = 0; i < vec.size(); i++)
    {
        newMap[vec[i]] = 0;
    }

    return newMap;
}

int main()
{
    string filename = "email9.txt";
    int numOfWordsInEmail = 0;
    string email = readEmail(filename, numOfWordsInEmail);

    vector<string> keywords = {"$", "earn per week", "double your", "income in one week", "trial that lasts forever", "opportunity", "income", "cash", "month free trial", "your love life"};
    vector<int> values = {10, 20, 20, 15, 30, 10, 10, 20, 15, 25};
    map<string, int> instanceCounter = initialiseMap(keywords);
    int result = 0;
    int numOfSpamWords = 0;

    rateEmail(email, keywords, instanceCounter);

    for (int i = 0; i < instanceCounter.size(); i++)
    {
        result += instanceCounter.at(keywords[i]) * values[i];
        numOfSpamWords += instanceCounter.at(keywords[i]);
    }

    double relativeResult = relativeSpam(numOfSpamWords, numOfWordsInEmail);
    ofstream output;
    output.open("output_s2.txt");
    string absResult = "Absolute score is: " + to_string(result) + " (" + isSpam(result) + ") ";
    string relResult = "Relative score is: " + to_string(relativeResult) + " (" + isSpam(relativeResult) + ") ";
    output << absResult << endl;
    output << relResult << endl;
    output.close();
    cout << absResult << endl;
    cout << relResult << endl;
}
