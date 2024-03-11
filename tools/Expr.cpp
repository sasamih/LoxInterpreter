#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <utility>
#include <algorithm>

#include "../lox/error_handler.hpp"

static void createHeaderFile(std::string outputDir, std::string baseName,
                             std::vector<std::string> members,
                             std::string membersStr)
{
    std::string headerPath = outputDir + "/" + baseName + ".hpp";
    std::ofstream headerFile(headerPath, std::ios::out);

    headerFile << "#ifndef " + baseName + "_HPP" << std::endl;
    headerFile << "#define " + baseName + "_HPP" << std::endl;
    headerFile << std::endl;

    headerFile << "#include \"../Lox.hpp\"" << std::endl;
    headerFile << "#include \"../expressions.hpp\"" << std::endl;
    headerFile << std::endl;

    headerFile << "class " + baseName + " : public Expr" << std::endl;
    headerFile << "{" << std::endl;
    headerFile << "    protected: "<< std::endl;
    for (auto& member : members)
    {
        headerFile << "        " + member + ";"<< std::endl;
    }
    headerFile << "    public: "<< std::endl;
    headerFile << "        " + baseName + "(" + membersStr + ");";
    headerFile << std::endl;

    headerFile << "};" << std::endl;

    headerFile << "#endif" << std::endl;
    headerFile << std::endl;
}

static void createSourceFile(std::string outputDir, std::string baseName,
                             std::vector<std::string> members,
                             std::string membersStr)
{
    std::string sourcePath = outputDir + "/" + baseName + ".cpp";
    std::ofstream sourceFile(sourcePath, std::ios::out);

    sourceFile << "#include \"" + baseName << ".hpp\"" << std::endl;

    sourceFile << std::endl;
    sourceFile << baseName + "::" + baseName + "(" + membersStr + ") : ";
    for (auto it = members.begin(); it != members.end(); it++)
    {
        std::string argName;
        auto argPosition = it->find(" ");
        if (argPosition != std::string::npos)
        {
            argName = it->substr(argPosition+1, std::string::npos);
        }
        sourceFile << argName + "(" + argName + ")";
        if (it + 1 != members.end())
        {
            sourceFile << ", ";
        }
        else
        {
            sourceFile << std::endl << "{ }";
        }
    }
    sourceFile << std::endl;
}

void defineAst(std::string outputDir, 
               std::vector<std::pair<std::string, std::string>> types)
{
    for (auto it = types.begin(); it != types.end(); it++)
    {
        auto baseName = it->first;
        std::istringstream dataMembers(it->second);
        std::vector<std::string> members;
        std::string m;
        while(getline(dataMembers, m, ','))
        {
            m.erase(m.begin(), 
                    std::find_if(m.begin(), m.end(), [](unsigned char ch)
                                 { return !std::isspace(ch); }));
            members.push_back(m);            
        }
        
        createHeaderFile(outputDir, baseName, members, dataMembers.str());
        createSourceFile(outputDir, baseName, members, dataMembers.str());
    }
}

std::vector<std::pair<std::string, std::string>> getClasses()
{
    std::vector<std::pair<std::string, std::string>> sV;
    std::vector<std::string> descriptors = 
    { "Binary", "Expr left, Token op, Expr right",
      "Grouping","Expr expression",
      "Literal","Object value",
      "Unary","Token op, Expr right" };

    for (auto it = descriptors.begin(); it != descriptors.end(); it += 2)
    {
        auto temp_pair = std::make_pair(*it, *(it+1));
        sV.push_back(temp_pair);
    }
    return sV;    
}

int main(int argc, char* argv[])
{
    if (argc != 2)
    {
        error(__LINE__, "Usage: generate_ast <output directory>");
        return -1;
    }

    std::string outputDir = argv[1];

    auto sV = getClasses();

    defineAst(outputDir, sV);

    return 0;
}
