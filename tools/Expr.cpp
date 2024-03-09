#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "../lox/error_handler.hpp"

void defineAst(std::string outputDir, std::string baseName, 
               std::vector<std::string> types)
{
    std::string path = outputDir + "/" + baseName + ".hpp";
    std::ofstream outputFile(path, std::ios::out);

    outputFile << "#ifndef " + baseName + "_HPP" << std::endl;
    outputFile << "#define " + baseName + "_HPP" << std::endl;
    outputFile << std::endl;

    outputFile << "#include \"Lox.hpp\"" << std::endl;
    outputFile << std::endl;

    outputFile << "class " + baseName + " : public Expr" << std::endl;
    outputFile << "{" << std::endl;
    outputFile << "    protected: "<< std::endl;
    outputFile << std::endl;
    outputFile << std::endl;
    outputFile << "    public: "<< std::endl;
    outputFile << std::endl;

    outputFile << "};" << std::endl;

    outputFile << "#endif" << std::endl;

}

int main(int argc, char* argv[])
{
    if (argc != 2)
    {
        error(__LINE__, "Usage: generate_ast <output directory>");
        return -1;
    }
    std::string outputDir = argv[1];
    std::vector<std::string> sV;
    defineAst(".", "example", sV);

    return 0;
}