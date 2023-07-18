#include "stdafx.h"

void FolderWriter::name(const std::string& string)
{
    if (!std::filesystem::create_directories(string))
    {
        std::printf("FolderWriter %s\n", string.c_str());
    }
}
