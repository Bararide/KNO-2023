#include "RPN.h"

namespace RPN
{
    int RPN_Creator::precedence(char op)
    {
        switch (op)
        {
            case '+':
            case '-':
                return 2;
            case '#':
            case '$':
            case '&':
            case '~':
                return 3;
            case '*':
            case '/':
            case '%':
                return 4;
            case '^':
                return 5;
            case '<':
            case '>':
            case ':': //<=
            case '?': //>=
            case '@': //==
            case '!': //!=
                return 1;
        }
        return -1;
    }

    void RPN_Creator::CheckLibFunctionCall(std::string& line, std::stack<std::pair<std::string, char>> brackets, const int& str_number, const int& pos, std::string& word, IdTable& idTable)
    {
        std::regex pattern("\\((.*)\\)");
        std::regex functionRegex("\\b([a-zA-Z_][a-zA-Z0-9_]*)\\((.*)\\)");
        std::smatch match;
        std::vector<int> vecArgs;

        std::string args;
        std::string func;
        std::string subFunc;

        std::string signature;
        std::string funcArgs;

        for(char c : line)
        {
            if(c != ' ')
                signature += c;
            else break;
        }

        if(signature == "str")
        {
            signature = "string";
        }
        else if(signature == "byte")
        {
            signature = "uint8_t";
        }

        signature += '(';

        std::sregex_iterator funcIter(line.begin(), line.end(), functionRegex);
        std::sregex_iterator endFuncIter;

        std::atomic<bool> isEmpty(true);

        while(funcIter != endFuncIter)
        {
            match = *funcIter;

            ++funcIter;

            args = match[2].str();
            subFunc = match[1].str();

            std::regex argumentRegex(R"(\s*,\s*)");
            std::regex wordRegex("\\b\\w+\\b");
            std::regex numberRegex("\\b\\d+\\.?\\d*\\b");

            std::sregex_token_iterator iter(args.begin(), args.end(), argumentRegex, -1);
            std::sregex_token_iterator endIter;

            int argumentIndex = 1;
            while (iter != endIter) 
            {
                std::string argument = *iter++;
                if(std::regex_search(argument, match, wordRegex))
                {
                    auto iter = std::find_if(idTable.table.begin(), idTable.table.end(), [&argument, parent_function = brackets.top().first](const auto& v) {
                        return v.id == argument && v.idtype == static_cast<IDTYPE>(4) && v.parrent_function == parent_function;
                    });

                    if (iter == idTable.table.end()) 
                    {
                        while (brackets.top().first != "glob") 
                        {
                            removedBrackets.push(brackets.top());
                            brackets.pop();
                            iter = std::find_if(idTable.table.begin(), idTable.table.end(), [&argument, parent_function = brackets.top().first](const auto& v) {
                                return v.id == argument && v.idtype == static_cast<IDTYPE>(4) && v.parrent_function == parent_function;
                            });
                            if (iter != idTable.table.end())
                                break;
                        }
                    }

                    while (!removedBrackets.empty()) 
                    {
                        brackets.push(removedBrackets.top());
                        removedBrackets.pop();
                    }

                    if (iter != idTable.table.end())
                    {
                        if (iter->idtype == static_cast<IDTYPE>(3))
                            return;
                        
                        std::visit([&vecArgs, &isEmpty, str_number, pos, &signature, &funcArgs, &iter](const auto& v) {
                            if constexpr (std::is_same_v<std::decay_t<decltype(v)>, std::string>)
                            {
                                if (!v.empty())
                                {
                                    isEmpty = false;
                                    signature += "string, ";
                                    funcArgs += v + ' ';
                                }
                            }
                            else
                            {
                                funcArgs += boost::lexical_cast<std::string>(v) + ' ';
                                isEmpty = false;
                                if(iter->iddatatype == 1)
                                {
                                    signature += "int, ";
                                }
                                else if(iter->iddatatype == 2)
                                {
                                    signature += "string, ";
                                }
                                else if(iter->iddatatype == 4)
                                {
                                    signature += "bool, ";
                                }
                                else if(iter->iddatatype == 5)
                                {
                                    signature += "uint8_t, ";
                                }
                            }
                        }, iter->value);
                    }
                    else if(std::regex_search(argument, match, numberRegex))
                    {
                        signature += "int, ";
                        funcArgs += boost::lexical_cast<std::string>(argument) + ' ';
                        isEmpty = false;
                    }

                    if (isEmpty.load())
                    {
                        throw ERROR_THROW_IN(611, str_number, pos);
                    }
                    isEmpty = true;
                }
            }

            if(signature.find(',') != std::string::npos)
            {
                signature = signature.substr(0, signature.length() - 2);
            }
            signature += ')';

            for (auto it = vecArgs.begin(); it != vecArgs.end(); ++it)
            {
                func += *it;
                if (it != std::prev(vecArgs.end()))
                {
                    func += ", ";
                }

                if (it == std::prev(vecArgs.end()))
                    break;
            }

            bool found = false;
            std::string result;

            for (const auto& lib : libraries) 
            {
                if (lib.first.has(subFunc)) 
                {
                    if (sign.count(subFunc) > 0 && sign[subFunc] == signature) 
                    {
                        const std::string& functionSignature = sign[subFunc];
                        if (functionSignature == "int()" && functionSignature == signature) 
                        {
                            auto myFunctionPtr = lib.first.get<int()>(subFunc);
                            found = true;
                            
                            result = boost::lexical_cast<std::string>(myFunctionPtr());
                        } 
                        else if (functionSignature == "int(int)" && functionSignature == signature) 
                        {
                            auto myFunctionPtr = lib.first.get<int(int)>(subFunc);
                            found = true;

                            std::istringstream iss(funcArgs);
                            std::vector<int> args;
                            int arg;
                            while (iss >> arg) {
                                args.push_back(arg);
                            }

                            if (args.size() == 1) 
                            {
                                result = boost::lexical_cast<std::string>(myFunctionPtr(args[0]));
                            } 
                            else 
                            {
                                throw ERROR_THROW_IN(619, str_number, pos);
                            }
                        } 
                        else if (functionSignature == "std::string()" && functionSignature == signature) 
                        {
                            auto myFunctionPtr = lib.first.get<std::string()>(subFunc);
                            found = true;
                            
                            result = myFunctionPtr();
                        }
                    }
                }
            }

            if(!found)
            {
                throw ERROR_THROW_IN(631, str_number, pos);
            }
            else
            {
                std::size_t subFuncPos = line.find(subFunc);
                if (subFuncPos != std::string::npos) 
                {
                    std::size_t closingBracketPos = line.find(")", subFuncPos);
                    if (closingBracketPos != std::string::npos) 
                    {
                        line.replace(subFuncPos, closingBracketPos - subFuncPos + 1, result);
                    }
                }
            }

            vecArgs.clear();
        }
    }

    bool isHexNumber(const std::string& number) {
        if (number.size() > 18) {
            return false;
        }

        if (number.substr(0, 2) != "0x") {
            return false;
        }

        for (char ch : number.substr(2)) {
            if (!std::isxdigit(ch)) {
                return false;
            }
        }

        return true;
    }

    bool isBinaryNumber(const std::string& word)
    {
        if (word.substr(0, 2) != "bx") {
            return false;
        }

        for (char c : word.substr(2))
        {
            if (c != '0' && c != '1')
            {
                return false;
            }
        }
        return true;
    }

    void transformFromHex(std::string& word, std::string& line, const int& str_number, const int& pos)
    {
        std::string hexValue = word.substr(2);

        if (hexValue.length() > std::to_string(std::numeric_limits<int>::max()).length()) throw ERROR_THROW_IN(622, str_number, pos);

        int num = boost::lexical_cast<int>(hexValue);

        std::string newWord = boost::lexical_cast<std::string>(num);

        size_t start = line.find(word);
        if (start != std::string::npos && newWord.size() < word.size())
        {
            line.replace(start, word.size(), newWord);
            start += newWord.size();
            line.insert(start, std::string(word.size() - newWord.size(), ' '));
        }        
    }

    void transformFromBinary(std::string& word, std::string& line)
    {
        std::string binaryValue = word.substr(2);

        int num = std::bitset<32>(binaryValue).to_ulong();

        std::string newWord = boost::lexical_cast<std::string>(num);

        size_t start = line.find(word);
        if (start != std::string::npos)
        {
            line.replace(start, word.size(), newWord);
        }            
    }

    void replaceVariable(const std::string& variableName, const std::string& word, std::string& actionDescription) {
        std::regex regex("\\b" + variableName + "\\b");
        std::smatch match;
        std::string::const_iterator searchStart(actionDescription.cbegin());

        while (std::regex_search(searchStart, actionDescription.cend(), match, regex)) {
            std::string matchStr = match[0].str();
            std::size_t startPos = std::distance(actionDescription.cbegin(), match[0].first);
            std::size_t endPos = std::distance(actionDescription.cbegin(), match[0].second) - 1;

            actionDescription.replace(startPos, matchStr.length(), word);
            searchStart = actionDescription.begin() + startPos + word.length();
        }
    }

    void RPN_Creator::replaceFunctionCall(std::string& line, const int& str_number, const int& pos, const std::string& func_name, std::stack<std::pair<std::string, char>> brackets, const Function& function, const IdTable& idTable) 
    {
        std::string expr;
        std::string word;
        std::string actionDescription = function.actionDescription;
        if(actionDescription == "") throw ERROR_THROW(623);

        size_t start = line.find(func_name);
        size_t func  = line.find(func_name);
        int i = 0;

        if (start != std::string::npos) 
        {
            start += func_name.size() + 1;
            size_t block = std::distance(line.begin(), std::find(line.begin() + start, line.end(), ')'));
            expr = line.substr(0, block);
            expr = expr.substr(start);
            line.erase(func, block - func + 1);

            boost::regex pattern("\\b(\\w+)");
            boost::regex regex("\\(([^()]*?)\\)");

            boost::smatch match;

            std::istringstream iss(expr);

            while (iss >> word) 
            {
                if (boost::regex_search(word, match, pattern)) 
                {
                    word = match[1];
                    if(i >= function.arguments.size()) throw ERROR_THROW_IN(619, str_number, pos);

                    std::string variableName = function.arguments[i].second;
                    int variableType = function.arguments[i].first;

                    auto iter = std::find_if(idTable.table.begin(), idTable.table.end(), [&word, parent_function = brackets.top().first](const auto& v) {
                        return v.id == word && v.idtype == static_cast<IDTYPE>(4) && v.parrent_function == parent_function;
                    });

                    if (iter == idTable.table.end()) 
                    {
                        while (brackets.top().first != "glob") 
                        {
                            removedBrackets.push(brackets.top());
                            brackets.pop();
                            iter = std::find_if(idTable.table.begin(), idTable.table.end(), [&word, parent_function = brackets.top().first](const auto& v) {
                                return v.id == word && v.idtype == static_cast<IDTYPE>(4) && v.parrent_function == parent_function;
                            });
                            if (iter != idTable.table.end())
                                break;
                        }
                    }

                    while (!removedBrackets.empty()) 
                    {
                        brackets.push(removedBrackets.top());
                        removedBrackets.pop();
                    }

                    boost::sregex_iterator it(actionDescription.begin(), actionDescription.end(), regex);
                    boost::sregex_iterator end;

                    while (it != end) 
                    {
                        std::string parameters = (*it)[0].str();

                        size_t pos = parameters.find(variableName);

                        if (pos != std::string::npos) {
                            replaceVariable(variableName, word, actionDescription);
                        }

                        ++it;
                    }
                    ++i;
                }
            }

            line.insert(func, actionDescription);

            if (actionDescription.length() > expr.length()) {
                line.resize(line.length() + (actionDescription.length() - expr.length()));
            }
        }
    }

    bool isValidOperator(const std::unordered_set<char>& operators, const std::string& op) 
    {
        return operators.find(op[0]) != operators.end();
    }

    bool checkOperators(const std::string& line, const std::unordered_set<char>& operators) 
    {
        for (std::size_t i = 0; i < line.length(); ++i) 
        {
            if (operators.count(line[i]) > 0) 
            {
                if (i + 1 < line.length() && operators.count(line[i + 1]) > 0) {
                    return false;
                }
            }
        }
        return true;
    }

    void RPN_Creator::transform(std::string& line, std::stack<std::pair<std::string, char>> brackets, const int& type, const int& pos, const int& str_number, LT::LexTable& lexTable, IdTable& idTable)
    {
        size_t start;
        size_t poss = 0;

        std::string result;
        std::string variable;

        bool is_number   = false;
        bool is_variable = false;
        bool is_function = false;
        bool is_chain    = false;

        std::string function_name;
        std::string number;


        replaceSubstring(line, "<<", "#");
        replaceSubstring(line, ">>", "$");
        replaceSubstring(line, "==", "@");
        replaceSubstring(line, "<=", ":");
        replaceSubstring(line, "!=", "!");
        replaceSubstring(line, ">=", "?");

        if(!checkOperators(line, operators))
        {
            throw ERROR_THROW_IN(632, str_number, pos);
        }

        std::istringstream iss(line);

        std::string func_call;

        while (iss >> word)
        {
            if(isHexNumber(word)) transformFromHex(word, line, str_number, poss);

            if (isBinaryNumber(word)) transformFromBinary(word, line);

            if (word.find('\'') != std::string::npos)
                return;

            boost::regex pattern("\\b(\\w+)");

            boost::smatch match;
            if (boost::regex_search(word, match, pattern)) 
            {
                word = match[1];
                if (FST::execute<TRUE>(word) && word.size() == TRUE::states)
                    replaceSubstring(line, word.c_str(), "1");
                else if (FST::execute<FALSE>(word) && word.size() == FALSE::states)
                    replaceSubstring(line, word.c_str(), "0");

                auto func = std::find_if(functions.begin(), functions.end(), [this](const auto& func){
                    return func.name == word && func.actionDescription.find(word) != std::string::npos;
                });

                if(func != functions.end() && !is_chain)
                {
                    is_chain = true;
                }
                else func = std::find_if(functions.begin(), functions.end(), [this](const auto& func){
                    return func.name == word && func.actionDescription.find(word) == std::string::npos;
                });


                if(func != functions.end())
                {
                    replaceFunctionCall(line, str_number, pos, word, brackets, *func, idTable);
                    if(is_chain)
                    {
                        if(std::find_if(functions.begin(),functions.end(), [this](const auto& func){
                            return func.name == word && func.actionDescription.find(word) == std::string::npos;
                        }) == functions.end()) {
                            throw ERROR_THROW_IN(624, str_number, pos);
                        }
                    }
                    iss = std::istringstream(line);
                }
                else if(sign.count(word) != 0)
                {
                    CheckLibFunctionCall(line, brackets, str_number, pos, word, idTable);
                }
            }   
        }

        start = line.find('=') + 1;

        for (auto it = std::next(line.begin() + start); it != line.end(); ++it)
        {
            if (!std::isspace(*it))
            {
                if (std::isdigit(*it) || *it == '.')
                {
                    number += *it;
                    is_number = true;
                }
                else if (std::isalpha(*it))
                {
                    variable += *it;
                    is_variable = true;
                }
                else if (operators.count(*it) != 0)
                {
                    if (is_number)
                    {
                        result += number;
                        result += ' ';
                        number.clear();
                        is_number = false;
                    }
                    if (is_variable)
                    { 
                        std::atomic<bool> isEmpty(true);
                        if (variable.find('\'') != std::string::npos)
                        {
                            variable = boost::lexical_cast<std::string>(variable.size() - 2);
                        }

                        auto iter = std::find_if(idTable.table.begin(), idTable.table.end(), [&variable, parent_function = brackets.top().first](const auto& v) {
                            return v.id == variable && v.idtype == static_cast<IDTYPE>(4) && v.parrent_function == parent_function;
                        });

                        if (iter == idTable.table.end()) 
                        {
                            while (brackets.top().first != "glob") 
                            {
                                removedBrackets.push(brackets.top());
                                brackets.pop();
                                iter = std::find_if(idTable.table.begin(), idTable.table.end(), [&variable, parent_function = brackets.top().first](const auto& v) {
                                    return v.id == variable && v.idtype == static_cast<IDTYPE>(4) && v.parrent_function == parent_function;
                                });
                                if (iter != idTable.table.end())
                                    break;
                            }
                        }

                        while (!removedBrackets.empty()) 
                        {
                            brackets.push(removedBrackets.top());
                            removedBrackets.pop();
                        }

                        if (iter != idTable.table.end())
                        {
                            if (iter->idtype == static_cast<IDTYPE>(3))
                                return;
                            
                            std::visit([&result, &isEmpty](const auto& v) {
                                if constexpr (std::is_same_v<std::decay_t<decltype(v)>, std::string>)
                                {
                                    if (!v.empty())
                                    {
                                        isEmpty = false;
                                        result += v;
                                        result += ' ';
                                    }
                                }
                                else
                                {
                                    isEmpty = false;
                                    result += boost::lexical_cast<std::string>(v);
                                    result += ' ';
                                }
                            }, iter->value);
                        }

                        if (isEmpty.load())
                        {
                            throw ERROR_THROW(611);
                        }

                        variable.clear();
                        is_variable = false;
                    }

                    while (!oper_stack.empty() && oper_stack.top() != '(' &&
                           precedence(*it) <= precedence(oper_stack.top()))
                    {
                        result += oper_stack.top();
                        result += ' ';
                        oper_stack.pop();
                    }
                    oper_stack.push(*it);
                }
                else if (*it == '(')
                {
                    oper_stack.push(*it);
                }
                else if (*it == ')')
                {
                    if (is_number)
                    {
                        if (number.length() > std::to_string(std::numeric_limits<int>::max()).length()) throw ERROR_THROW_IN(622, str_number, pos);
                        result += number;
                        result += ' ';
                        number.clear();
                        is_number = false;
                    }

                    if (is_variable)
                    {
                        std::atomic<bool> isEmpty(true);

                        auto iter = std::find_if(idTable.table.begin(), idTable.table.end(), [&variable, parent_function = brackets.top().first](const auto& v) {
                            return v.id == variable && (v.idtype == static_cast<IDTYPE>(4) || v.idtype == static_cast<IDTYPE>(3)) && v.parrent_function == parent_function;
                        });

                        if (iter == idTable.table.end()) 
                        {
                            while (brackets.top().first != "glob") 
                            {
                                removedBrackets.push(brackets.top());
                                brackets.pop();
                                iter = std::find_if(idTable.table.begin(), idTable.table.end(), [&variable, parent_function = brackets.top().first](const auto& v) {
                                    return v.id == variable && v.idtype == static_cast<IDTYPE>(4) && v.parrent_function == parent_function;
                                });
                                if (iter != idTable.table.end())
                                    break;
                            }
                        }

                        while (!removedBrackets.empty()) 
                        {
                            brackets.push(removedBrackets.top());
                            removedBrackets.pop();
                        }

                        if (iter != idTable.table.end())
                        {
                            if (iter->idtype == static_cast<IDTYPE>(3))
                                return;
                            
                            std::visit([&result, &isEmpty](const auto& v) {
                                if constexpr (std::is_same_v<std::decay_t<decltype(v)>, std::string>)
                                {
                                    if (!v.empty())
                                    {
                                        isEmpty = false;
                                        result += v;
                                        result += ' ';
                                    }
                                }
                                else
                                {
                                    isEmpty = false;
                                    result += boost::lexical_cast<std::string>(v);
                                    result += ' ';
                                }
                            }, iter->value);
                        }

                        if (isEmpty.load())
                        {
                            throw ERROR_THROW_IN(611, str_number, pos);
                        }

                        variable.clear();
                        is_variable = false;
                    }
                    
                    while (!oper_stack.empty() && oper_stack.top() != '(')
                    {
                        result += oper_stack.top();
                        result += ' ';
                        oper_stack.pop();
                    }
                    
                    if (!oper_stack.empty() && oper_stack.top() == '(')
                    {
                        oper_stack.pop();
                    }
                    else
                    {
                        throw ERROR_THROW_IN(622, str_number, pos);
                    }
                }
            }
        }
        
        if (is_number)
        {
            if (number.length() > std::to_string(std::numeric_limits<int>::max()).length()) throw ERROR_THROW_IN(622, str_number, pos);
            result += number;
            result += ' ';
        }
        
        if (is_variable)
        {
            std::atomic<bool> isEmpty(true);

            auto iter = std::find_if(idTable.table.begin(), idTable.table.end(), [&variable, parent_function = brackets.top().first](const auto& v) {
                return v.id == variable && (v.idtype == static_cast<IDTYPE>(4) || v.idtype == static_cast<IDTYPE>(3)) && v.parrent_function == parent_function;
            });

            if (iter == idTable.table.end()) 
            {
                while (brackets.top().first != "glob") 
                {
                    removedBrackets.push(brackets.top());
                    brackets.pop();
                    iter = std::find_if(idTable.table.begin(), idTable.table.end(), [&variable, parent_function = brackets.top().first](const auto& v) {
                        return v.id == variable && v.idtype == static_cast<IDTYPE>(4) && v.parrent_function == parent_function;
                    });
                    if (iter != idTable.table.end())
                        break;
                }
            }

            while (!removedBrackets.empty()) 
            {
                brackets.push(removedBrackets.top());
                removedBrackets.pop();
            }

            if (iter != idTable.table.end())
            {
                if (iter->idtype == static_cast<IDTYPE>(3))
                    return;
                
                std::visit([&result, &isEmpty](const auto& v) {
                    if constexpr (std::is_same_v<std::decay_t<decltype(v)>, std::string>)
                    {
                        if (!v.empty())
                        {
                            isEmpty = false;
                            result += v;
                            result += ' ';
                        }
                    }
                    else
                    {
                        isEmpty = false;
                        result += boost::lexical_cast<std::string>(v);
                        result += ' ';
                    }
                }, iter->value);
            }

            if (isEmpty.load())
            {
                throw ERROR_THROW_IN(611, str_number, pos);
            }
        }
        
        while (!oper_stack.empty())
        {
            if (oper_stack.top() == '(')
            {
                throw ERROR_THROW_IN(611, str_number, pos);
            }
            
            result += oper_stack.top();
            result += ' ';
            oper_stack.pop();
        }

        get_polish_value(result);
    
        //std::cout << "result " << result << "\tval " << val_stack.top() << std::endl;
        line.erase(start);

        if (type == 1)
        {
            //std::cout << "TYPE 1 " << result << std::endl;
            line += ' ' + boost::lexical_cast<std::string>(boost::lexical_cast<int>(val_stack.top())) + ';';
        }
        else if (type == 4)
        {
            //std::cout << "TYPE 4 " << result << std::endl;
            bool boolValue = (val_stack.top() != 0.0);
            line += ' ' + std::to_string(boolValue) + ';';
        }
        else if (type == 5)
        {
            //std::cout << "TYPE 5 " << word << std::endl;
            uint8_t uintValue = static_cast<uint8_t>(std::round(val_stack.top()));
            line += ' ' + std::to_string(uintValue) + ';';
        }
        else line += ' ' + boost::lexical_cast<std::string>(static_cast<int>(val_stack.top())) + ';';
        //std::cout << line << std::endl;
    }

	void RPN_Creator::get_polish_value(const std::string& line)
	{
        auto pop_stack([&](){
            auto r(val_stack.top());
            val_stack.pop();
            return r;
        });

        std::istringstream iss(line);
        std::vector<std::string> words;

        std::string word;
        while (iss >> word) 
        {
            words.push_back(word);
        }


        for (const auto& word : words) 
        {
            std::stringstream ss(word);
            if (double val; ss >> val) 
            {
                val_stack.push(val);
            } 
            else 
            {
                const auto r{pop_stack()};
                const auto l{pop_stack()};
                try 
                {
                    const auto& op (ops.at(word));
                    const double result {op(l, r)};
                    val_stack.push(result);
                } 
                catch(const std::out_of_range&) 
                {
                    throw std::invalid_argument(word);
                }
            }
        }
	}
}