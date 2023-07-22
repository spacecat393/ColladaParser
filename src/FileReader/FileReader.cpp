#include "stdafx.h"

void FileReader::find(std::istreambuf_iterator<char>& c, const std::string& string)
{
	std::istreambuf_iterator<char> e;

    std::string new_string;
    int index = 0;

    while (c != e)
    {
        if (string == new_string)
        {
            return;
        }

        if (*c == string[index])
        {
            new_string += *c;
            ++index;
        }
        else
        {
            new_string.clear();
            index = 0;
        }

        ++c;
    }
}

int FileReader::matchString(std::istreambuf_iterator<char>& c, std::vector<std::string>& string_vector)
{
    std::istreambuf_iterator<char> e;

    int size = string_vector.size();
    std::vector<std::string> new_string_vector(size);
    std::vector<int> index_vector(size);

    while (c != e)
    {
        for (int i = 0; i < size; ++i)
        {
            if (string_vector[i] == new_string_vector[i])
            {
                return i;
            }

            if (*c == string_vector[i][index_vector[i]])
            {
                new_string_vector[i] += *c;
                ++index_vector[i];
            }
            else
            {
                new_string_vector[i].clear();
                index_vector[i] = 0;
            }
        }

        ++c;
    }

    return -1;
}

void FileReader::getString(std::istreambuf_iterator<char>& c, const char& newline, const std::string& end_string, std::vector<std::string>& string_vector)
{
    std::istreambuf_iterator<char> e;

    std::string new_string;
    std::string text_string;
    int index = 0;

    while (c != e)
    {
        if (end_string == new_string)
        {
            if (text_string != "")
            {
                string_vector.push_back(text_string);
            }

            return;
        }

        if (*c == newline)
        {
            string_vector.push_back(text_string);
            text_string.clear();
        }

        if (*c == end_string[index])
        {
            new_string += *c;
            ++index;
        }
        else
        {
            text_string += new_string;

            if (*c != newline)
            {
                text_string += *c;
            }

            new_string.clear();
            index = 0;
        }

        ++c;
    }
}

void FileReader::getFloat(std::istreambuf_iterator<char>& c, const std::string& end_string, std::vector<float>& float_vector)
{
    std::istreambuf_iterator<char> e;

    std::string new_string;
    std::string number_string;
    int index = 0;

    while (c != e)
    {
        if (end_string == new_string)
        {
            if (number_string != "")
            {
                // float value;
                // FileReader::stringFloat(number_string, &value);
                // float_vector.push_back(value);
                float_vector.push_back(std::stof(number_string));
            }

            return;
        }

        if (*c == ' ')
        {
            // float value;
            // FileReader::stringFloat(number_string, &value);
            // float_vector.push_back(value);
            float_vector.push_back(std::stof(number_string));
            number_string.clear();
        }

        if (*c == end_string[index])
        {
            new_string += *c;
            ++index;
        }
        else
        {
            if (*c != ' ')
            {
                number_string += *c;
            }

            new_string.clear();
            index = 0;
        }

        ++c;
    }
}

void FileReader::getInt(std::istreambuf_iterator<char>& c, const std::string& end_string, std::vector<int>& int_vector)
{
    std::istreambuf_iterator<char> e;

    std::string new_string;
    std::string number_string;
    int index = 0;

    while (c != e)
    {
        if (end_string == new_string)
        {
            if (number_string != "")
            {
                int_vector.push_back(std::stoi(number_string));
            }

            return;
        }

        if (*c == ' ')
        {
            int_vector.push_back(std::stoi(number_string));
            number_string.clear();
        }

        if (*c == end_string[index])
        {
            new_string += *c;
            ++index;
        }
        else
        {
            if (*c != ' ')
            {
                number_string += *c;
            }

            new_string.clear();
            index = 0;
        }

        ++c;
    }
}

void FileReader::getMaxInt(std::istreambuf_iterator<char>& c, const std::string& end_string, std::vector<int>& int_vector, int& max_int)
{
    std::istreambuf_iterator<char> e;

    std::string new_string;
    std::string number_string;
    int index = 0;

    while (c != e)
    {
        if (end_string == new_string)
        {
            if (number_string != "")
            {
                int value = std::stoi(number_string);

                if (max_int < value)
                {
                    max_int = value;
                }

                int_vector.push_back(value);
            }

            return;
        }

        if (*c == ' ')
        {
            int value = std::stoi(number_string);

            if (max_int < value)
            {
                max_int = value;
            }

            int_vector.push_back(value);
            number_string.clear();
        }

        if (*c == end_string[index])
        {
            new_string += *c;
            ++index;
        }
        else
        {
            if (*c != ' ')
            {
                number_string += *c;
            }

            new_string.clear();
            index = 0;
        }

        ++c;
    }
}

void FileReader::getNode(std::istreambuf_iterator<char>& c, std::vector<BoneData>& bonedata_vector)
{
    BoneData bonedata{};
    FileReader::find(c, "name=\"");
    FileReader::getString(c, '\n', "\"", bonedata.bones_name_string);
	FileReader::find(c, "\n");
    FileReader::getString(c, '\n', "<matrix sid=", bonedata.bones_name_string);
	FileReader::find(c, ">");
    FileReader::getFloat(c, "</matrix>", bonedata.visual_bones_transform_float_vector);
    bonedata_vector.push_back(bonedata);
}

// void FileReader::stringFloat(std::string string, float* value)
// {
//     auto result = std::from_chars(string.data(), string.data() + string.size(), *value);

//     if (result.ec != std::errc())
//     {
//         std::printf("std::from_chars");
//     }
// }

void FileReader::readRawIntFile(const std::string& filename, std::vector<std::vector<int>>& int_2d_vector)
{
    std::istreambuf_iterator<char> e;

    std::fstream file(filename);
    std::istreambuf_iterator<char> c(file);
    std::vector<char> char_vector;
    std::vector<int> int_vector;

    while (c != e)
    {
        if (*c == '\n')
        {
            std::string numbertext(char_vector.begin(), char_vector.end());
            int_vector.push_back(atoi(numbertext.c_str()));
            char_vector.clear();

            int_2d_vector.push_back(int_vector);
            int_vector.clear();
        }
        else if (*c != ' ')
        {
            char_vector.push_back(*c);
        }
        else
        {
            std::string numbertext(char_vector.begin(), char_vector.end());
            int_vector.push_back(atoi(numbertext.c_str()));

            char_vector.clear();
        }

        ++c;
    }

    std::string numbertext(char_vector.begin(), char_vector.end());
    int_vector.push_back(atoi(numbertext.c_str()));
    int_2d_vector.push_back(int_vector);
}
