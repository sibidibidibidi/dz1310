#include<iostream>
#include<string>
#include<vector>
#include<fstream>
using namespace std;

string LoadFileContent(string filename)
{
    ifstream file(filename);
    string currentLine = "", content = "";
    while (!file.eof())
    {
        getline(file, currentLine);
        content += currentLine + '\n';
    }
    return content;
}

void RemoveComments()
{
    string fileContent = LoadFileContent("File.txt");
    int endOfLine;
    int commentPos = fileContent.find("//");

    while (commentPos != string::npos)
    {
        endOfLine = fileContent.find('\n');
        fileContent.erase(commentPos, endOfLine - commentPos + 1);
        commentPos = fileContent.find("//");
    }

    commentPos = fileContent.find("/*");
    while (commentPos != string::npos)
    {
        endOfLine = fileContent.find("*/");
        fileContent.erase(commentPos, endOfLine - commentPos + 2);  // include "*/"
        commentPos = fileContent.find("/*");
    }

    cout << fileContent << endl;
}

int PerformOperation(int operand1, int operand2, char operatorSymbol)
{
    int result = 0;
    switch (operatorSymbol)
    {
    case '+':
        result = operand1 + operand2;
        break;
    case '-':
        result = operand1 - operand2;
        break;
    case '*':
        result = operand1 * operand2;
        break;
    case '/':
        result = operand1 / operand2;
        break;
    default:
        break;
    }
    return result;
}

string EvaluateExpression(string expression)
{
    string modexp = expression;
    string number = "";
    vector<int> numbers;
    string operators = "";
    string currentExpr = "";
    int exprIndex = 0;

    for (size_t i = 0; i < modexp.length(); i++)
    {
        if (isdigit(modexp[i]))
        {
            number += modexp[i];
        }
        if (!isdigit(modexp[i]) || i == modexp.length() - 1)
        {
            if (!number.empty())
            {
                numbers.push_back(stoi(number));
                number.clear();
            }
        }
        if (modexp[i] == '+' || modexp[i] == '-' || modexp[i] == '*' || modexp[i] == '/')
        {
            operators += modexp[i];
        }
    }

    if (numbers.size() % operators.length() != 0)
    {
        return "Error!";
    }

    int j = 0;
    for (size_t i = 0; i < operators.length(); i++)
    {
        currentExpr = to_string(numbers[j]) + operators[i] + to_string(numbers[j + 1]);
        exprIndex = modexp.find(currentExpr);
        if (exprIndex != string::npos)
        {
            modexp.erase(exprIndex, currentExpr.length());
            modexp.insert(exprIndex, to_string(PerformOperation(numbers[j], numbers[j + 1], operators[i])));
        }
        j += 2;
    }
    return modexp;
}

void AddParentheses()
{
    string baseString = "abaracadabra";
    string substrfind;
    string modstr;

    cout << "Enter substring to modify: ";
    cin >> substrfind;

    int prevPos = 0;
    int pos = baseString.find(substrfind);
    modstr.append(baseString.substr(0, pos));

    while (pos != string::npos)
    {
        pos = baseString.find(substrfind, prevPos);
        if (pos == -1) break;
        modstr.append("(");
        modstr.append(baseString.substr(pos, substrfind.length()));
        modstr.append(")");
        prevPos = pos + substrfind.length();
    }

    modstr.append(baseString.substr(prevPos, baseString.length() - prevPos));
    cout << modstr;
}

int main()
{
    cout << "Task 1" << endl << endl;
    RemoveComments();

    cout << "Task 2" << endl << endl;
    AddParentheses();

    cout << endl << endl;

    cout << "Task 3" << endl << endl;
    string sampleStr = "alpha 5+26 beta 72-35 gamma 32+45 etc";
    string resultStr = EvaluateExpression(sampleStr);
    cout << resultStr << endl;

    return 0;
}