// Lexical Analyzer.cpp 
#include <iostream>
#include <string>
#include <vector>
#include <cctype>
#include <fstream>
#include <sstream>
#include <iomanip>


// create gobal scope enum variable to define token types
enum tokenType
{
    keyWord,
    identifier,
    num,
    addOp,
    mulOp,
    relOp,
    andType,
    orType,
    notType,
    lPar,
    rPar,
    lBrack,
    rBrack,
    lBrace,
    rBrace,
    equal,
    semiCol,
    undefined
};

// create a structure to hold token values these will be used for function reading
struct token
{
    tokenType analyzedToken;
    std::string actualToken; // used to print out what we parsed
};

// function used to analyze tokens
  tokenType tokenAnalyzer(const std::string& token)
{
    // we will begin by checking for all the different token types we want
    // using if/else beginning with keyword

    if (token == "while" || token == "if" || token == "else" || token == "return"
        || token == "break" || token == "continue" || token == "int" || token ==
        "float" || token == "void")
    {
        return keyWord;
    }
    // identifier requires the first character to be letter or underscore
    else if (std::isalpha(token[0]) || token[0] == '_')
    {
        return identifier;
    }
    // num requires unsigned numbers, optional fraction, optional exponent
    else if (std::isdigit(token[0]) || token[0] == '.' || token[0] == 'E')
    {
        return num;
    }
    // rinse and repeat for the rest of the token types i.e add/sub
    else if (token == "+" || token == "-")
    {
        return addOp;
    }
    // mult/divide
    else if (token == "*" || token == "/")
    {
        return mulOp;
    }
    // relational
    else if (token == "<" || token == ">" || token == "<=" || token == ">="
        || token == "==" || token == "!=")
    {
        return relOp;
    }
    // and
    else if (token == "&&")
    {
        return andType;
    }
    // or
    else if (token == "||")
    {
        return orType;
    }
    // not
    else if (token[0] == '!')
    {
        return notType;
    }
    // left parentheses
    else if (token[0] == '(')
    {
        return lPar;
    }
    // right parentheses
    else if (token[0] == ')')
    {
        return rPar;
    }
    // right brace
    else if (token[0] == '}')
    {
        return rBrace;
    }
    // left brace
    else if (token[0] == '{')
    {
        return lBrace;
    }
    // right bracket 
    else if (token[0] == ']')
    {
        return rBrack;
    }
    // left bracket
    else if (token[0] == '[')
    {
        return lBrack;
    }
    // equal
    else if (token[0] == '=')
    {
        return equal;
    }
    else if (token[0] == ';')
    {
        return semiCol;
    }
    // accounting for unrecognizable token 
    else
    {
        return undefined;
    }
}

int main()
{
    // create necessary variables and vectors
    std::string inputLine;     // for reading input.txt
    std::vector<token> tokens; // used to store input.txt

    // begin with reading in input.txt file with error if can't read
    std::ifstream file("input.txt");

    if (!file.is_open()) 
    {
        std::cout << "error cannot open file try again." << std::endl;
        return 1;
    }

    // push input file into vector
    // figure out parsing
    while (getline(file, inputLine))
    {
        std::istringstream iss(inputLine);
        std::string token;

        while (iss >> token) 
        {
            tokenType type = tokenAnalyzer(token);
            tokens.push_back({ type, token });
            token.clear();
        }
    }

    // cout tokens and proper format using switch/case
    for (int i = 0; i < tokens.size(); ++i) 
    {
        const token& token = tokens[i];
        std::string typeName;

        switch (token.analyzedToken) 
        {
        case keyWord: typeName = "keyword"; break;
        case identifier: typeName = "identifier"; break;
        case num: typeName = "num"; break;
        case addOp:
            if (token.actualToken == "+")
            {
                typeName = "+";
            }
            else if (token.actualToken == "-")
            {
                typeName = "-";
            }
            break;
        // use actualTokem to get the symbol necessary
        case mulOp:
            if (token.actualToken == "*")
            {
                typeName = "*";
            }
            else if (token.actualToken == "/")
            {
                typeName = "/";
            }
            
            break;
        case relOp: 
            if (token.actualToken == "<")
            {
                typeName = "<";
            }
            else if (token.actualToken == ">")
            {
                typeName = ">";
            }
            else if (token.actualToken == "<=")
            {
                typeName = "<=";
            }
            else if (token.actualToken == ">=")
            {
                typeName = ">=";
            }
            else if (token.actualToken == "==")
            {
                typeName = "==";
            }
            else if (token.actualToken == "!=")
            {
                typeName = "!=";
            }
            break;
        case andType: typeName = "&&"; break;
        case orType: typeName = "||"; break;
        case notType: typeName = "!"; break;
        case lPar: typeName = '('; break;
        case rPar: typeName = ')'; break;
        case rBrace: typeName = "}"; break;
        case lBrace: typeName = "{"; break;
        case rBrack: typeName = "["; break;
        case lBrack: typeName = "]"; break;
        case equal: typeName = "="; break;
        case semiCol: typeName = ";"; break;
        case undefined: typeName = "Unknown"; break;
        }

        std::cout << std::setw(10) << typeName << " : " << token.actualToken << std::endl;
    }

    // exit and close the file
    file.close();

    return 0;
}

