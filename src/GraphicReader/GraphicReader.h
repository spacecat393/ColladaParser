#ifndef SPACEENGINE_GRAPHICREADER_H
#define SPACEENGINE_GRAPHICREADER_H

#pragma once

class GraphicReader
{
public:
	static std::string repaste(std::string& char_star1, const std::string& char_star2, const std::string& char_star3);
	static int getSpace(std::string& string);
	static void makeModelOffset(SourceDataType& sourcedatatype);
	// static void makeAnimation(SourceDataType& sourcedatatype);
	static void makeBonesSpace(SourceDataType& sourcedatatype);
	static void repasteBonesName(std::vector<std::string>& string_vector, const std::string& string0, const std::string& string1);
	static void switchBones(SourceDataType& sourcedatatype);
	static void switchAnimationBones(SourceDataType& sourcedatatype);
	// static void makeBonesSpaces(SourceDataType& sourcedatatype);
	static void makeBones(SourceDataType& sourcedatatype);
	static void addParent(SourceDataType& sourcedatatype);
	static void compressVertex(SourceDataType& sourcedatatype);
	static bool canPackNew(SourceDataType& sourcedatatype, int& x, int& y);
	static bool canPack(SourceDataType& sourcedatatype, int& x, int& y, int& z);
	static void fixAnimation(SourceDataType& sourcedatatype);
	static void unPackIndex(SourceDataType& sourcedatatype);
	static void unPackVisualBones(SourceDataType& sourcedatatype);
	static void updateBones(SourceDataType& sourcedatatype);
	static int matchString(const std::string& string, std::vector<std::string>& string_vector, const char& end);
};

#endif
