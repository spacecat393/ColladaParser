#include "stdafx.h"

int work_int = 0;

void work(std::filesystem::directory_entry directory_entry)
{
	SourceDataType sourcedatatype{};

	printf("Load %s%s", directory_entry.path().c_str(), "\n");
	std::fstream file(directory_entry.path());

	std::istreambuf_iterator<char> char_pointer(file);
	FileReader::find(char_pointer, "<library_geometries>");

	{
		std::vector<std::string> string_vector
		{
			"</library_geometries>",
			"<geometry"
		};

		int v_index = 0;

		while (int state = FileReader::matchString(char_pointer, string_vector))
		{
			FileReader::find(char_pointer, "\"");
			FileReader::getString(char_pointer, '-', "-", sourcedatatype.object_name_vector);

			sourcedatatype.positions.push_back({});
			sourcedatatype.normals.push_back({});
			sourcedatatype.texcoord.push_back({});
			sourcedatatype.p_offset.push_back({});

			FileReader::find(char_pointer, "positions-array");
			FileReader::find(char_pointer, ">");
			FileReader::getFloat(char_pointer, "</float_array>", sourcedatatype.positions[v_index]);

			FileReader::find(char_pointer, "normals-array");
			FileReader::find(char_pointer, ">");
			FileReader::getFloat(char_pointer, "</float_array>", sourcedatatype.normals[v_index]);

			FileReader::find(char_pointer, "map-0-array");
			FileReader::find(char_pointer, ">");
			FileReader::getFloat(char_pointer, "</float_array>", sourcedatatype.texcoord[v_index]);

			if (SourceDataType::CREATE_COLOR)
			{
				sourcedatatype.color.push_back({});

				FileReader::find(char_pointer, "colors-Attribute-array");
				FileReader::find(char_pointer, ">");
				FileReader::getFloat(char_pointer, "</float_array>", sourcedatatype.color[v_index]);
			}

			FileReader::find(char_pointer, "<p>");
			FileReader::getInt(char_pointer, "</p>", sourcedatatype.p_offset[v_index]);

			++v_index;
		}

		GraphicReader::repasteBonesName(sourcedatatype.object_name_vector);

		GraphicReader::makeModelOffset(sourcedatatype);
	}

	// Skinning / Animation

	if (SourceDataType::CREATE_ANIMATION)
	{
		FileReader::find(char_pointer, "<library_controllers>");

		std::vector<std::string> string_vector
		{
			"</library_controllers>",
			"<controller"
		};

		int v_index = 0;

		while (int state = FileReader::matchString(char_pointer, string_vector))
		{
			sourcedatatype.joints.push_back({});
			sourcedatatype.bind_poses.push_back({});
			sourcedatatype.weights.push_back({});
			sourcedatatype.vcount_offset.push_back({});
			sourcedatatype.v_offset.push_back({});
			sourcedatatype.max_joint_vector.push_back(0);

			FileReader::find(char_pointer, "joints-array");
			FileReader::find(char_pointer, ">");
			FileReader::getString(char_pointer, ' ', "</Name_array>", sourcedatatype.joints[v_index]);

			FileReader::find(char_pointer, "bind_poses-array");
			FileReader::find(char_pointer, ">");
			FileReader::getFloat(char_pointer, "</float_array>", sourcedatatype.bind_poses[v_index]);

			FileReader::find(char_pointer, "weights-array");
			FileReader::find(char_pointer, ">");
			FileReader::getFloat(char_pointer, "</float_array>", sourcedatatype.weights[v_index]);

			FileReader::find(char_pointer, "<vcount>");
			FileReader::getMaxInt(char_pointer, "</vcount>", sourcedatatype.vcount_offset[v_index], sourcedatatype.max_joint_vector[v_index]);
			std::printf("MaxJoint %s : %d\n", sourcedatatype.object_name_vector[v_index].c_str(), sourcedatatype.max_joint_vector[v_index]);

			FileReader::find(char_pointer, "<v>");
			FileReader::getInt(char_pointer, "</v>", sourcedatatype.v_offset[v_index]);

			// Remove library_visual_scenes and unused action
			//
			GraphicReader::repasteBonesName(sourcedatatype.joints[v_index]);
			//

			++v_index;
		}

		FileReader::find(char_pointer, "<animation");
		std::istreambuf_iterator<char> empty_pointer;

		// for (int i = 0; i < 15; ++i)//14
		// {
		// 	FileReader::findText(char_pointer, sourcedatatype.armature_name);
		// }

		if (SourceDataType::DECOMPOSED)
		{
			for (int i = 0; i < 135; ++i)
			{
				FileReader::find(char_pointer, sourcedatatype.armature_name);
			}
		}
		else
		{
			for (int i = 0; i < 15; ++i)
			{
				FileReader::find(char_pointer, sourcedatatype.armature_name);
			}
		}

		for (int l = 0; l < sourcedatatype.max_animation_bones * (SourceDataType::DECOMPOSED ? 9 : 1); ++l)
		{
			for (int i = 0; i < 3; ++i)
			{
				FileReader::find(char_pointer, sourcedatatype.armature_name);
			}
			FileReader::find(char_pointer, ">");
			FileReader::getFloat(char_pointer, "</float_array>", sourcedatatype.armature_time_vector);

			for (int i = 0; i < 3; ++i)
			{
				FileReader::find(char_pointer, sourcedatatype.armature_name);
			}
			FileReader::find(char_pointer, ">");
			FileReader::getFloat(char_pointer, "</float_array>", sourcedatatype.armature_transform_vector);

			FileReader::find(char_pointer, "source=\"#");
			FileReader::getString(char_pointer, '\"', "\"", sourcedatatype.armature_string_vector);
			for (int i = 0; i < 9; ++i)//8
			{
				FileReader::find(char_pointer, sourcedatatype.armature_name);
			}
		}

		//
		GraphicReader::repasteBonesName(sourcedatatype.armature_string_vector);
		//
		// GraphicReader::makeAnimation(sourcedatatype);
		GraphicReader::switchAnimationBones(sourcedatatype);
		// GraphicReader::repasteBonesName(sourcedatatype.armature_string_vector);
	}

	// VisualBones
	FileReader::find(char_pointer, "<library_visual_scenes>");

	if (SourceDataType::DECOMPOSED)
	{
		FileReader::find(char_pointer, "</translate>");
	}
	else
	{
		FileReader::find(char_pointer, "</matrix>");
	}

	for (int l = 0; l < sourcedatatype.max_animation_bones; ++l)
	{
		FileReader::getNode(char_pointer, sourcedatatype.bonedata_vector);
	}
	//GraphicReader::repasteBonesName(sourcedatatype.joints);
	//
	for (int l = 0; l < sourcedatatype.bonedata_vector.size(); ++l)
	{
		GraphicReader::repasteBonesName(sourcedatatype.bonedata_vector[l].bones_name_string);
	}
	//
	GraphicReader::makeBonesSpace(sourcedatatype);
	GraphicReader::switchBones(sourcedatatype);
	// GraphicReader::makeBonesSpaces(sourcedatatype);
	GraphicReader::makeBones(sourcedatatype);

	if (SourceDataType::CREATE_ANIMATION && SourceDataType::FIX_ANIMATION)
	{
		GraphicReader::fixAnimation(sourcedatatype);
	}

	if (SourceDataType::COMPRESS)
	{
		GraphicReader::compressVertex(sourcedatatype);
		GraphicReader::unPackIndex(sourcedatatype);
		GraphicReader::unPackVisualBones(sourcedatatype);
		GraphicReader::updateBones(sourcedatatype);
	}

	FileWriter::modelFile(sourcedatatype, directory_entry.path().stem());

	file.close();

	--work_int;
}

int main()
{
	FolderWriter::name("Objects");
	FolderWriter::name("Results");

    std::ios::sync_with_stdio(false);

	{
		FolderWriter::name("Results/Bones");

		std::vector<std::vector<int>> bones_int_2d_vector;

		FileReader::readRawIntFile("Objects/Bones", bones_int_2d_vector);

		for (int i = 0; i < bones_int_2d_vector.size(); ++i)
		{
			FileWriter::intPack(bones_int_2d_vector[i], "Results/Bones/" + std::to_string(i));
		}
	}

	for (const auto& directory_entry : std::filesystem::directory_iterator("Objects"))
	{
		if (directory_entry.is_regular_file() && directory_entry.path() != "Objects/Bones")
		{
			std::thread thread(work, directory_entry);

			thread.detach();
			++work_int;
		}
	}

	while (work_int){}
	// std::cin.get();
}
