#include <iostream>
#include <cstring>
#include <list>
#include <algorithm>
#include <windows.h>

int main(int argc, char *argv[])
{
    std::string path;

    char *buff = new (std::nothrow) char[2048];
    if (buff)
    {
        memset(buff, 0, 2048);
        if (!GetEnvironmentVariable("PATH", buff, 2048))
        {
            DWORD dwLastError = GetLastError();
            if (dwLastError == ERROR_ENVVAR_NOT_FOUND)
            {
                std::cerr << "Error! Environment variable was not found.\n";
            }
            else
            {
                std::cerr << "Error! Code: " << dwLastError << "\n";
            }
            delete []buff;
            return 1;
        }
        path = buff;
        delete []buff;
    }
    else
    {
        std::cerr << "Error! Failed to allocate memory.\n";
        return 1;
    }

    std::list<std::string> vlist;

    if (!path.empty())
    {
        size_t pos = -1;
        size_t last_pos = 0;
        while ((pos = path.find(';', pos + 1)) != std::string::npos)
        {
            vlist.push_back(path.substr(last_pos, pos - last_pos));
            last_pos = pos + 1;
        }
        if (last_pos != path.size())
        {
            vlist.push_back(path.substr(last_pos, path.size() - last_pos));
        }
    }

    std::cout << "Counter: " << vlist.size() << "\n";
    
    if (vlist.size() > 0)
    {
	    std::cout << "List: \n";

	    int counter = 0;
	    for (std::list<std::string>::const_iterator i = vlist.begin(); i != vlist.end(); i++)
	    {
	        std::cout << "#" << (counter++) << " " << (*i) << "\n";
	    }
	}
    return 0;
}
