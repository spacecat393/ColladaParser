#ifndef SPACEENGINE_FILEREADER_H
#define SPACEENGINE_FILEREADER_H

#pragma once

class FileReader
{
public:
    static void find(std::istreambuf_iterator<char>& c, const std::string& string);
    static bool matchString(std::istreambuf_iterator<char>& c, std::vector<std::string>& string_vector);
    static void getString(std::istreambuf_iterator<char>& c, const char& newline, const std::string& end_string, std::vector<std::string>& string_vector);
    static void getFloat(std::istreambuf_iterator<char>& c, const std::string& end_string, std::vector<float>& float_vector);
    static void getInt(std::istreambuf_iterator<char>& c, const std::string& end_string, std::vector<int>& int_vector);
    static void getMaxInt(std::istreambuf_iterator<char>& c, const std::string& end_string, std::vector<int>& int_vector, int& max_int);
    static void getNode(std::istreambuf_iterator<char>& c, std::vector<BoneData>& bonedata_vector);
    // static void stringFloat(std::string string, float* value);
    static void readRawIntFile(const std::string& filename, std::vector<std::vector<int>>& int_2d_vector);
};

#endif
