#pragma once
#include <string>
#include <stdexcept>
#include <fstream>
#include <cstring>

class NasmCompilerWrapper {
public:
    static void Compile(std::string const& code, std::string const& executableName);

private:
    static std::string CreateSourceCodeFile(std::string const& executableName, std::string const& code);
    static void ExecuteSystemCommand(std::string const& cmd);
    static void RemoveTempFiles(std::string const& executableName);
    static std::string GetAsmSourceFileFromExecutableName(std::string const& executableName);
    static std::string GetObjectFileFromExecutableName(std::string const& executableName);
    static void TryRemoveFile(std::string const& fileName);
};
