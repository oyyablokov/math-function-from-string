#pragma once
#include <string>


/**
 * @brief A class for storing settings for GetFunctionFromString.
 */
struct FunctionFromStringSettings
{
    std::string command;                    /**< The command which will be executed for compiling a function. */
    std::string function_source_filename;
    std::string function_source_code;

    /**
     * Filename of the target linked library.
     * Note that if the file with this filename exists and is used for linking, the actual filename will be augmented with an ordinal number, e.g. "libFunction3.so" (to avoid collisions).
     * If the previous condition is true, the lib_filename variable is changed to the augmented one.
     */
    std::string lib_filename;

    /**
     * Function name of the target library function.
     * Note that the actual name will be augmented with the lib_filename's ordinal number, e.g. "function3" (to avoid collisions).
     * If the previous condition is true, the function_name variable is changed to the augmented one.
     */
    std::string function_name;

    std::string RET_TYPE;                   /**< Initialize it explicitly if compilation fails. */
    std::string ARG_TYPE;                   /**< Initialize it explicitly if compilation fails. */
    std::string DIM;                        /**< Initialize it explicitly if compilation fails. */

    void *handle = nullptr;                 /**< Handle for library. If you want to manually close the library, call dlclose(handle); */

    FunctionFromStringSettings()
    {
        function_source_filename = "function.cpp";
        function_name = "function";

#ifdef _WIN32
        lib_filename = "libFunction.dll";
        function_source_code = ""
            "#include <array>\n"
            "#include <functional>\n"
            "#include <cmath>\n"
            "\n"
            "extern RET_TYPE fun(const std::array<ARG_TYPE, DIM>& arg)\n"
            "{\n"
            "    return BODY;\n"
            "}";
        command = "\"gcc -std=c++17 -shared -o libFunction.so -fPIC ";
        function_header = "function_linux.h";

#elif __linux__
        lib_filename = "libFunction.so";
        function_source_code = ""
            "#include <array>\n"
            "#include <functional>\n"
            "#include <cmath>\n"
            "\n\n"
            "using namespace std;\n"
            "#ifdef __cplusplus\n"
            "extern \"C\" {\n"
            "#endif\n"
            ""
            "RET_TYPE FUNCTION_NAME(const std::array<ARG_TYPE, DIM>& arg)\n"
            "{\n"
            "    return BODY;\n"
            "}\n"
            "\n"
            "#ifdef __cplusplus\n"
            "}\n"
            "#endif";
        command = "g++ -std=c++17 -shared -o <lib_filename> -fPIC <function_source_filename>";
#endif
    }
};
