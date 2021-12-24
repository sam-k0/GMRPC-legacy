/**
        This Header file contains useful functions for GameMaker Dll export.

        <!-- Feel free to use this in your projects-->

        - GameMaker Booleans              : gmtrue and gmfalse
        - GameMaker Boolean Return value  : gmbool
        - GameMaker Integer Return value  : gmint
        - GameMaker Strings:
            -> When passing a string to a dll function from GameMaker, use stringToDLL as param value
            -> When passing a string from the dll (as a return value) back to GameMaker, use stringFromDLL

        And the most important:

        To expose functions from the DLL to GameMaker, use the keyword "gmx"

        Example:

        - Non exposed function (Only accessible from within the C++ Code):

            -> void doSometing();

        - GameMaker exposed DLL function (Callable from GM):

            -> gmx gmbool doSomething(gmint myNumber)
            {
                return myNumber*2
            }

            (All functions in GM must return something...)
            (In this case, it just returns double the value it got.)
*/

#ifndef GMS_H_INCLUDED
#define GMS_H_INCLUDED
#define gmx extern "C" __declspec(dllexport)
#define gmtrue 1.0;
#define gmfalse 0.0;
typedef double gmint;
typedef const char* stringToDLL; // Pass to dll
typedef char* stringFromDLL;      // return from dll
typedef double gmbool;

#include <string>
#include <string.h>
#include <iostream>
using namespace std;

class gmu {

public:

	static char* string_to_charptr(string s)
	{
		return _strdup(s.c_str());
	}

	static const char* string_to_constcharptr(string s)
	{
		return s.c_str();
	}

	static string constcharptr_to_string(const char* p)
	{
		return string(p);
	}

	static void debugmessage(string s)
	{
		std::cout << s << std::endl;
	}

private:
    gmu(){}
};
#endif // AMOGUS_H_INCLUDED
