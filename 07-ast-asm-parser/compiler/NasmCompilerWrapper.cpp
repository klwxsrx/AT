#include "NasmCompilerWrapper.h"

void NasmCompilerWrapper::Compile(std::string const &code, std::string const &executableName) {
    try {
        auto fileName = CreateSourceCodeFile(executableName, code);
        ExecuteSystemCommand("nasm -f elf " + fileName);
        ExecuteSystemCommand("gcc -m32 -o " + executableName + " " + GetObjectFileFromExecutableName(executableName));
        RemoveTempFiles(executableName);
    }
    catch (std::exception const &e) {
        throw std::runtime_error(std::string("Error while compile source code at: ") + e.what());
    }
}

std::string NasmCompilerWrapper::CreateSourceCodeFile(std::string const &executableName, std::string const &code) {
    std::string sourceFile = GetAsmSourceFileFromExecutableName(executableName);

    try {
        std::ofstream outfile(sourceFile);
        outfile << code << std::endl;
        outfile.close();
        return sourceFile;
    }
    catch (std::exception const &e) {
        throw std::runtime_error("Can't create source file " + sourceFile);
    }

}

void NasmCompilerWrapper::ExecuteSystemCommand(std::string const &cmd) {
    if (std::system(cmd.c_str()) != 0)
    {
        throw std::runtime_error("Command '" + cmd + "' failed!");
    }
}

void NasmCompilerWrapper::RemoveTempFiles(std::string const &executableName) {
    TryRemoveFile(GetAsmSourceFileFromExecutableName(executableName));
    TryRemoveFile(GetObjectFileFromExecutableName(executableName));
}

std::string NasmCompilerWrapper::GetAsmSourceFileFromExecutableName(std::string const& executableName)
{
    return executableName + ".asm";
}

std::string NasmCompilerWrapper::GetObjectFileFromExecutableName(std::string const& executableName)
{
    return executableName + ".o";
}

void NasmCompilerWrapper::TryRemoveFile(std::string const& fileName)
{
    if (!std::remove(fileName.c_str()))
    {
        throw std::runtime_error("Can't remove file " + fileName);
    }
}