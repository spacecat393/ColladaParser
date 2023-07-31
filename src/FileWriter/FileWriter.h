#ifndef SPACEENGINE_FILEWRITER_H
#define SPACEENGINE_FILEWRITER_H

#pragma once

class FileWriter
{
public:
    static void modelFile(SourceDataType& sourcedatatype, const std::string& string);
    static void floatPack(std::vector<float>& float_vector, const std::string& string);
    static void intPack(std::vector<int>& int_vector, const std::string& string);
    static void stringPack(std::vector<std::string>& string_vector, const std::string& string);
    static void bytePack(std::vector<unsigned char>& unsigned_char_vector, const std::string& string);
    static void unPackBones(SourceDataType& sourcedatatype, const std::string& string, const int& x);
    // static void unPackBonesM4x4(SourceDataType& sourcedatatype, const std::string& string, const int& x);
};

#endif
