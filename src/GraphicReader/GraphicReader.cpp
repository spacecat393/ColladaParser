#include "stdafx.h"

std::string GraphicReader::repaste(std::string& char_star1, const std::string& char_star2, const std::string& char_star3)
{
	std::string char_star0;

	for (int i = 0; i < char_star1.size(); ++i)
	{
		if (char_star1[i] == char_star2[0])
		{
			char_star0.push_back(char_star3[0]);
		}
		else
		{
			char_star0.push_back(char_star1[i]);
		}
	}

	return char_star0;
}

int GraphicReader::getSpace(std::string& string)
{
	int value = 0;

	for (int i = 0; i < string.size(); ++i)
	{
		if (string[i] == ' ')
		{
			++value;
		}
	}

	return value;
}

void GraphicReader::makeModelOffset(SourceDataType& sourcedatatype)
{
	int i_offset = 0;

	for (int x = 0; x < sourcedatatype.p_offset.size(); ++x)
	{
		sourcedatatype.positions_offset.push_back({});
		sourcedatatype.normals_offset.push_back({});
		sourcedatatype.texcoord_offset.push_back({});

		if (SourceDataType::CREATE_COLOR)
		{
			sourcedatatype.color_offset.push_back({});

			for (int i : sourcedatatype.p_offset[x])
			{
				if (i_offset == 0)
				{
					sourcedatatype.positions_offset[x].push_back(i);
				}
				else if (i_offset == 1)
				{
					sourcedatatype.normals_offset[x].push_back(i);
				}
				else if (i_offset == 2)
				{
					sourcedatatype.texcoord_offset[x].push_back(i);
				}
				else if (i_offset == 3)
				{
					sourcedatatype.color_offset[x].push_back(i);

					i_offset = -1;
				}

				++i_offset;
			}
		}
		else
		{
			for (int i : sourcedatatype.p_offset[x])
			{
				if (i_offset == 0)
				{
					sourcedatatype.positions_offset[x].push_back(i);
				}
				else if (i_offset == 1)
				{
					sourcedatatype.normals_offset[x].push_back(i);
				}
				else if (i_offset == 2)
				{
					sourcedatatype.texcoord_offset[x].push_back(i);

					i_offset = -1;
				}

				++i_offset;
			}
		}
	}
}

// void GraphicReader::makeAnimation(SourceDataType& sourcedatatype)
// {
// 	for (int x = 0; x < sourcedatatype.joints.size(); ++x)
// 	{
// 		sourcedatatype.vertex_offset.push_back({});
// 		sourcedatatype.joints_offset.push_back({});
// 		sourcedatatype.weights_offset.push_back({});

// 		{
// 			int i_offset = 0;

// 			for (int i : sourcedatatype.vcount_offset[x])
// 			{
// 				i *= 2;

// 				for (int l = 0; l < i; ++l)
// 				{
// 					sourcedatatype.vertex_offset[x].push_back(sourcedatatype.v_offset[x][i_offset]);

// 					++i_offset;
// 				}
// 			}
// 		}

// 		int max = 0;

// 		for (int i : sourcedatatype.vcount_offset[x])
// 		{
// 			if (max < i)
// 			{
// 				max = i;
// 			}
// 		}

// 		{
// 			int id = 0;
// 			int i_offset = 0;
// 			int check_id = 0;
// 			int reload = 0;

// 			for (int i : sourcedatatype.v_offset[x])
// 			{
// 				int vc = sourcedatatype.vcount_offset[x][id];

// 				if (i_offset == 0)
// 				{
// 					sourcedatatype.joints_offset[x].push_back(i);
// 				}
// 				else if (i_offset == 1)
// 				{
// 					sourcedatatype.weights_offset[x].push_back(i);
// 				}

// 				if (i_offset == 1)
// 				{
// 					++reload;

// 					i_offset = 0;

// 					if (max != vc)
// 					{
// 						++id;
// 					}
// 					else
// 					{
// 						if (max == check_id)
// 						{
// 							++id;
// 							check_id = 0;
// 						}
// 						else
// 						{
// 							++check_id;
// 						}
// 					}
// 				}
// 				else
// 				{
// 					++i_offset;
// 					++reload;
// 				}

// 				if (reload == 2)
// 				{
// 					reload = 0;
// 				}
// 			}
// 		}
// 	}
// }

void GraphicReader::makeBonesSpace(SourceDataType& sourcedatatype)
{
	std::string node_string = " ";
	std::vector<BoneData>& bonedata_vector = sourcedatatype.bonedata_vector;

	for (int x = 0; x < bonedata_vector.size(); ++x)
	{
		BoneData& bonedata = bonedata_vector[x];
		std::vector<std::string>& bones_name_string = bonedata.bones_name_string;

		int index = GraphicReader::matchString(node_string, bones_name_string);
		if (index != -1)
		{
			int value = GraphicReader::getSpace(bones_name_string[index]);
			bonedata.space_int = value;
		}
	}
}

void GraphicReader::repasteBonesName(std::vector<std::string>& string_vector, const std::string& string0, const std::string& string1)
{
	for (int i = 0; i < string_vector.size(); ++i)
	{
		string_vector[i] = GraphicReader::repaste(string_vector[i], string0, string1);
	}
}

void GraphicReader::switchBones(SourceDataType& sourcedatatype)
{
	//sourcedatatype.visual_bones_bonedata_vector.assign(sourcedatatype.joints.size(), BoneData{});
	sourcedatatype.visual_bones_bonedata_vector_vector.assign(sourcedatatype.joints.size(), {});

	for (int z = 0; z < sourcedatatype.joints.size(); ++z)
	{
		sourcedatatype.visual_bones_bonedata_vector_vector[z].assign(sourcedatatype.joints[z].size(), BoneData{});
	}

	std::vector<BoneData>& bonedata_vector = sourcedatatype.bonedata_vector;

	for (int x = 0; x < bonedata_vector.size(); ++x)
	{
		BoneData& bonedata = bonedata_vector[x];
		std::vector<std::string>& bones_name_string = bonedata.bones_name_string;

		for (int z = 0; z < sourcedatatype.joints.size(); ++z)
		{
			for (int w = 0; w < sourcedatatype.joints[z].size(); ++w)
			{
				int index = GraphicReader::matchString(sourcedatatype.joints[z][w], bones_name_string);
				if (index != -1)
				{
					BoneData& visual_bones_bonedata = sourcedatatype.visual_bones_bonedata_vector_vector[z][w];
					visual_bones_bonedata.bones_name_string.push_back(sourcedatatype.joints[z][w]);
					visual_bones_bonedata.space_int = bonedata.space_int;
					visual_bones_bonedata.visual_bones_transform_float_vector = bonedata.visual_bones_transform_float_vector;
					// bonedata.bones_name_string.clear();
					// bonedata.bones_name_string.push_back(sourcedatatype.joints[z][w]);
				}
			}
		}
	}
}

void GraphicReader::switchAnimationBones(SourceDataType& sourcedatatype)
{
	std::vector<std::string>& armature_string_vector = sourcedatatype.armature_string_vector;

	for (int y = 0; y < sourcedatatype.joints.size(); ++y)
	{
		for (int z = 0; z < sourcedatatype.joints[y].size(); ++z)
		{
			int index = GraphicReader::matchString(sourcedatatype.joints[y][z], armature_string_vector);
			if (index != -1)
			{
				armature_string_vector[index] = sourcedatatype.joints[y][z];
			}
		}
	}
}

// void GraphicReader::makeBonesSpaces(SourceDataType& sourcedatatype)
// {
// 	for (int i = 0; i < sourcedatatype.bonedata_vector.size(); ++i)
// 	{
// 		bool result = true;

// 		for (int l = 0; l < sourcedatatype.bones_spaces_int_vector.size(); ++l)
// 		{
// 			if (sourcedatatype.bonedata_vector[i].space_int == sourcedatatype.bones_spaces_int_vector[l])
// 			{
// 				result = false;
// 				break;
// 			}
// 		}

// 		if (result)
// 		{
// 			sourcedatatype.bones_spaces_int_vector.push_back(sourcedatatype.bonedata_vector[i].space_int);
// 		}
// 	}
// }

void GraphicReader::makeBones(SourceDataType& sourcedatatype)
{
	std::vector<BoneData>& bonedata_vector = sourcedatatype.bonedata_vector;

	for (int x = 0; x < sourcedatatype.joints.size(); ++x)
	{
		sourcedatatype.bones_string_vector_vector_vector.push_back({});

		for (int w = 0; w < sourcedatatype.joints[x].size(); ++w)
		{
			for (int y = 0; y < bonedata_vector.size(); ++y)
			{
				BoneData& bonedata = bonedata_vector[y];

				int index = GraphicReader::matchString(sourcedatatype.joints[x][w], bonedata.bones_name_string);
				if (index != -1)
				{
					std::vector<std::string> bones_string_vector;
					bones_string_vector.push_back(bonedata.bones_name_string[index]);
					int max_z = bonedata.space_int;

					for (int z = y; z - 1 > -2; --z)
					{
						if (max_z > bonedata_vector[z].space_int)
						{
							max_z = bonedata_vector[z].space_int;
							bones_string_vector.push_back(bonedata_vector[z].bones_name_string[0]);
						}
					}

					sourcedatatype.bones_string_vector_vector_vector[x].push_back(bones_string_vector);
				}
			}
		}
	}
}

void GraphicReader::addParent(SourceDataType& sourcedatatype)
{
	for (int x = 0; x < sourcedatatype.joints.size(); ++x)
	{
		for (int y = 0; y < sourcedatatype.bones_string_vector_vector_vector[x].size(); ++y)
		{
			for (int z = 0; z < sourcedatatype.bones_string_vector_vector_vector[x][y].size(); ++z)
			{
				int index = GraphicReader::matchString(sourcedatatype.bones_string_vector_vector_vector[x][y][z], sourcedatatype.joints[x]);
				if (index == -1)
				{
					for (int w = 0; w < sourcedatatype.joints[x].size(); ++w)
					{
						if (sourcedatatype.joints[x][w] == sourcedatatype.bones_string_vector_vector_vector[x][y][z])
						{
							break;
						}
					}

					sourcedatatype.joints[x].push_back(sourcedatatype.bones_string_vector_vector_vector[x][y][z]);
					sourcedatatype.weights[x].push_back(1.0F);
					for (int i = 0; i < sourcedatatype.bonedata_vector.size(); ++i)
					{
						BoneData& bonedata = sourcedatatype.bonedata_vector[i];
						int index = GraphicReader::matchString(sourcedatatype.bones_string_vector_vector_vector[x][y][z], bonedata.bones_name_string);
						if (index != -1)
						{
							for (int l = 0; l < 16; ++l)
							{
								sourcedatatype.bind_poses[x].push_back(bonedata.visual_bones_transform_float_vector[l]);
							}

							break;
						}
					}
				}
			}
		}
	}
}

void GraphicReader::compressVertex(SourceDataType& sourcedatatype)
{
	std::vector<std::vector<float>> positions(sourcedatatype.positions_offset.size());
	std::vector<std::vector<float>> normals(sourcedatatype.positions_offset.size());
	std::vector<std::vector<float>> texcoord(sourcedatatype.positions_offset.size());

    for (int x = 0; x < sourcedatatype.positions_offset.size(); ++x)
	{
		sourcedatatype.pack_positions.push_back({});
		sourcedatatype.pack_normals.push_back({});
		sourcedatatype.pack_texcoord.push_back({});

		for (int y = 0; y < sourcedatatype.positions_offset[x].size(); ++y)
		{
			int xv = sourcedatatype.positions_offset[x][y] * 3;
			int yv = sourcedatatype.positions_offset[x][y] * 3 + 1;
			int zv = sourcedatatype.positions_offset[x][y] * 3 + 2;
			int xn = sourcedatatype.normals_offset[x][y] * 3;
			int yn = sourcedatatype.normals_offset[x][y] * 3 + 1;
			int zn = sourcedatatype.normals_offset[x][y] * 3 + 2;
			int ut = sourcedatatype.texcoord_offset[x][y] * 2;
			int vt = sourcedatatype.texcoord_offset[x][y] * 2 + 1;

			positions[x].push_back(sourcedatatype.positions[x][xv]);
			positions[x].push_back(sourcedatatype.positions[x][yv]);
			positions[x].push_back(sourcedatatype.positions[x][zv]);
			normals[x].push_back(sourcedatatype.normals[x][xn]);
			normals[x].push_back(sourcedatatype.normals[x][yn]);
			normals[x].push_back(sourcedatatype.normals[x][zn]);
			texcoord[x].push_back(sourcedatatype.texcoord[x][ut]);
			texcoord[x].push_back(sourcedatatype.texcoord[x][vt]);
		}
	}

	if (sourcedatatype.create_animation)
	{
		std::vector<std::vector<int>> joints(sourcedatatype.positions_offset.size());
		std::vector<std::vector<float>> weights(sourcedatatype.positions_offset.size());

		for (int x = 0; x < sourcedatatype.positions_offset.size(); ++x)
		{
			sourcedatatype.pack_joints.push_back({});
			sourcedatatype.pack_weights.push_back({});

			for (int y = 0; y < sourcedatatype.positions_offset[x].size(); ++y)
			{
				{
					int jxyzw[sourcedatatype.max_joint_vector[x]];
					for (int j = 0; j < sourcedatatype.max_joint_vector[x]; ++j)
					{
						jxyzw[j] = -1;
					}

					int v_offset_by_p = 0;

					for (int i = 0; i < sourcedatatype.positions_offset[x][y]; ++i)
					{
						v_offset_by_p += sourcedatatype.vcount_offset[x][i];
					}

					v_offset_by_p *= 2;

					int vc = sourcedatatype.vcount_offset[x][sourcedatatype.positions_offset[x][y]];

					int vc_in = 0;
					int vc_out = 0;

					while (vc_out < vc)
					{
						jxyzw[vc_out] = sourcedatatype.v_offset[x][v_offset_by_p + vc_in];

						++vc_out;
						vc_in += 2;
					}

					for (int j = 0; j < sourcedatatype.max_joint_vector[x]; ++j)
					{
						joints[x].push_back(jxyzw[j]);
					}
				}

				{
					float wxyzw[sourcedatatype.max_joint_vector[x]];
					for (int j = 0; j < sourcedatatype.max_joint_vector[x]; ++j)
					{
						wxyzw[j] = 0.0F;
					}

					int v_offset_by_p = 0;

					for (int i = 0; i < sourcedatatype.positions_offset[x][y]; ++i)
					{
						v_offset_by_p += sourcedatatype.vcount_offset[x][i];
					}

					v_offset_by_p *= 2;

					int vc = sourcedatatype.vcount_offset[x][sourcedatatype.positions_offset[x][y]];

					int vc_in = 0;
					int vc_out = 0;

					while (vc_out < vc)
					{
						wxyzw[vc_out] = sourcedatatype.weights[x][sourcedatatype.v_offset[x][v_offset_by_p + vc_in + 1]];

						++vc_out;
						vc_in += 2;
					}

					for (int j = 0; j < sourcedatatype.max_joint_vector[x]; ++j)
					{
						weights[x].push_back(wxyzw[j]);
					}
				}
			}
		}

		sourcedatatype.indexdata.joints = joints;
		sourcedatatype.indexdata.weights = weights;
	}

	sourcedatatype.indexdata.positions = positions;
	sourcedatatype.indexdata.normals = normals;
	sourcedatatype.indexdata.texcoord = texcoord;

	if (SourceDataType::CREATE_COLOR)
	{
		std::vector<std::vector<float>> color(sourcedatatype.positions_offset.size());

		for (int x = 0; x < sourcedatatype.positions_offset.size(); ++x)
		{
			sourcedatatype.pack_color.push_back({});

			for (int y = 0; y < sourcedatatype.positions_offset[x].size(); ++y)
			{
				int xv = sourcedatatype.color_offset[x][y] * 4;
				int yv = sourcedatatype.color_offset[x][y] * 4 + 1;
				int zv = sourcedatatype.color_offset[x][y] * 4 + 2;
				int wv = sourcedatatype.color_offset[x][y] * 4 + 3;

				color[x].push_back(sourcedatatype.color[x][xv]);
				color[x].push_back(sourcedatatype.color[x][yv]);
				color[x].push_back(sourcedatatype.color[x][zv]);
				color[x].push_back(sourcedatatype.color[x][wv]);
			}
		}

		sourcedatatype.indexdata.color = color;
	}

	for (int x = 0; x < positions.size(); ++x)
	{
		sourcedatatype.index.push_back({});

		for (int y = 0; y < positions[x].size() / 3; ++y)
		{
			if (canPackNew(sourcedatatype, x, y))
			{
				sourcedatatype.index[x].push_back({});
				sourcedatatype.pack_positions[x].push_back(positions[x][y * 3]);
				sourcedatatype.pack_positions[x].push_back(positions[x][y * 3 + 1]);
				sourcedatatype.pack_positions[x].push_back(positions[x][y * 3 + 2]);
				sourcedatatype.pack_normals[x].push_back(normals[x][y * 3]);
				sourcedatatype.pack_normals[x].push_back(normals[x][y * 3 + 1]);
				sourcedatatype.pack_normals[x].push_back(normals[x][y * 3 + 2]);
				sourcedatatype.pack_texcoord[x].push_back(texcoord[x][y * 2]);
				sourcedatatype.pack_texcoord[x].push_back(texcoord[x][y * 2 + 1]);

				if (SourceDataType::CREATE_COLOR)
				{
					sourcedatatype.pack_color[x].push_back(sourcedatatype.indexdata.color[x][y * 4]);
					sourcedatatype.pack_color[x].push_back(sourcedatatype.indexdata.color[x][y * 4 + 1]);
					sourcedatatype.pack_color[x].push_back(sourcedatatype.indexdata.color[x][y * 4 + 2]);
					sourcedatatype.pack_color[x].push_back(sourcedatatype.indexdata.color[x][y * 4 + 3]);
				}

				if (sourcedatatype.create_animation)
				{
					for (int z = 0; z < sourcedatatype.max_joint_vector[x]; ++z)
					{
						sourcedatatype.pack_joints[x].push_back(sourcedatatype.indexdata.joints[x][y * sourcedatatype.max_joint_vector[x] + z]);
						sourcedatatype.pack_weights[x].push_back(sourcedatatype.indexdata.weights[x][y * sourcedatatype.max_joint_vector[x] + z]);
					}
				}

				for (int z = 0; z < positions[x].size() / 3; ++z)
				{
					if (canPack(sourcedatatype, x, y, z))
					{
						sourcedatatype.index[x][sourcedatatype.index[x].size() - 1].push_back(z);
					}
				}
			}
		}
	}
}

bool GraphicReader::canPackNew(SourceDataType& sourcedatatype, int& x, int& y)
{
	for (int z = 0; z < sourcedatatype.index[x].size(); ++z)
	{
		for (int w = 0; w < sourcedatatype.index[x][z].size(); ++w)
		{
			if (y == sourcedatatype.index[x][z][w])
			{
				return false;
			}
		}
	}

	return true;
}

bool GraphicReader::canPack(SourceDataType& sourcedatatype, int& x, int& y, int& z)
{
	if (SourceDataType::CREATE_COLOR)
	{
		if
		(
			sourcedatatype.indexdata.color[x][y * 4] != sourcedatatype.indexdata.color[x][z * 4] ||
			sourcedatatype.indexdata.color[x][y * 4 + 1] != sourcedatatype.indexdata.color[x][z * 4 + 1] ||
			sourcedatatype.indexdata.color[x][y * 4 + 2] != sourcedatatype.indexdata.color[x][z * 4 + 2] ||
			sourcedatatype.indexdata.color[x][y * 4 + 3] != sourcedatatype.indexdata.color[x][z * 4 + 3]
		)
		{
			return false;
		}
	}

	if
	(
		sourcedatatype.indexdata.positions[x][y * 3] == sourcedatatype.indexdata.positions[x][z * 3] &&
		sourcedatatype.indexdata.positions[x][y * 3 + 1] == sourcedatatype.indexdata.positions[x][z * 3 + 1] &&
		sourcedatatype.indexdata.positions[x][y * 3 + 2] == sourcedatatype.indexdata.positions[x][z * 3 + 2] &&
		sourcedatatype.indexdata.texcoord[x][y * 2] == sourcedatatype.indexdata.texcoord[x][z * 2] &&
		sourcedatatype.indexdata.texcoord[x][y * 2 + 1] == sourcedatatype.indexdata.texcoord[x][z * 2 + 1] &&
		sourcedatatype.indexdata.normals[x][y * 3] == sourcedatatype.indexdata.normals[x][z * 3] &&
		sourcedatatype.indexdata.normals[x][y * 3 + 1] == sourcedatatype.indexdata.normals[x][z * 3 + 1] &&
		sourcedatatype.indexdata.normals[x][y * 3 + 2] == sourcedatatype.indexdata.normals[x][z * 3 + 2]
	)
	{
		if (sourcedatatype.create_animation)
		{
			for (int w = 0; w < sourcedatatype.max_joint_vector[x]; ++w)
			{
				if
				(
					sourcedatatype.indexdata.joints[x][y * sourcedatatype.max_joint_vector[x] + w] != sourcedatatype.indexdata.joints[x][z * sourcedatatype.max_joint_vector[x] + w] ||
					sourcedatatype.indexdata.weights[x][y * sourcedatatype.max_joint_vector[x] + w] != sourcedatatype.indexdata.weights[x][z * sourcedatatype.max_joint_vector[x] + w]
				)
				{
					return false;
				}
			}

			return true;
		}
		else
		{
			return true;
		}

	}
	else
	{
		return false;
	}
}

void GraphicReader::fixAnimation(SourceDataType& sourcedatatype)
{
	for (int x = 0; x < sourcedatatype.bonedata_vector.size(); ++x)
	{
		for (int y = 0; y < sourcedatatype.armature_string_vector.size(); ++y)
		{
			if (sourcedatatype.bonedata_vector[x].bones_name_string[0].find(sourcedatatype.armature_string_vector[y]) != std::string::npos)
			{
				int y_index = y * sourcedatatype.max_frame * 16;

				for (int z = 0; z < sourcedatatype.max_frame; ++z)
				{
					int z_index = z * 16;

					M4x4::inverse(sourcedatatype.armature_transform_vector, y_index + z_index);
					M4x4::inverse(sourcedatatype.armature_transform_vector, y_index + z_index);
					sourcedatatype.armature_transform_vector[y_index + 3 + z_index] -= sourcedatatype.bonedata_vector[x].visual_bones_transform_float_vector[3];
					sourcedatatype.armature_transform_vector[y_index + 7 + z_index] -= sourcedatatype.bonedata_vector[x].visual_bones_transform_float_vector[7];
					sourcedatatype.armature_transform_vector[y_index + 11 + z_index] -= sourcedatatype.bonedata_vector[x].visual_bones_transform_float_vector[11];
					M4x4::inverse(sourcedatatype.armature_transform_vector, y_index + z_index);
				}

				break;
			}
		}
	}
}

void GraphicReader::unPackIndex(SourceDataType& sourcedatatype)
{
	for (int x = 0; x < sourcedatatype.object_name_vector.size(); ++x)
	{
		sourcedatatype.unpack_index.push_back({});

		for (int y = 0; y < sourcedatatype.indexdata.positions[x].size() / 3; ++y)
		{
			for (int z = 0; z < sourcedatatype.index[x].size(); ++z)
			{
				for (int w = 0; w < sourcedatatype.index[x][z].size(); ++w)
				{
					if (sourcedatatype.index[x][z][w] == y)
					{
						sourcedatatype.unpack_index[x].push_back(z);
						break;
					}
				}
			}
		}
	}
}

void GraphicReader::unPackVisualBones(SourceDataType& sourcedatatype)
{
	for (int x = 0; x < sourcedatatype.object_name_vector.size(); ++x)
	{
		sourcedatatype.un_pack_visual_bones.push_back({});

		for (int y = 0; y < sourcedatatype.visual_bones_bonedata_vector_vector[x].size(); ++y)
		{
			std::vector<float>& visual_bones_transform_float_vector = sourcedatatype.visual_bones_bonedata_vector_vector[x][y].visual_bones_transform_float_vector;

			for (int z = 0; z < visual_bones_transform_float_vector.size(); ++z)
			{
				sourcedatatype.un_pack_visual_bones[x].push_back(visual_bones_transform_float_vector[z]);
			}
		}
	}
}

void GraphicReader::updateBones(SourceDataType& sourcedatatype)
{
	for (int x = 0; x < sourcedatatype.object_name_vector.size(); ++x)
	{
		sourcedatatype.skinning_bones.push_back({});
		sourcedatatype.animation_bones.push_back({});

		for (int y = 0; y < sourcedatatype.armature_string_vector.size(); ++y)
		{
			for (int z = 0; z < sourcedatatype.joints[x].size(); ++z)
			{
				if (sourcedatatype.armature_string_vector[y].find(sourcedatatype.joints[x][z]) != std::string::npos)
				{
					sourcedatatype.skinning_bones[x].push_back(z * 16);
					sourcedatatype.animation_bones[x].push_back(y * sourcedatatype.max_frame);
					break;
				}
			}
		}
	}
}

int GraphicReader::matchString(const std::string& string, std::vector<std::string>& string_vector)
{
    int size = string_vector.size();
    std::vector<std::string> new_string_vector(size);
    std::vector<int> index_vector(size);
	int index = -1;

    for (auto& c : string)
    {
        for (int i = 0; i < size; ++i)
        {
			for (int l = 0; l < string_vector[i].size(); ++l)
			{
				if (c == string_vector[i][l + index_vector[i]])
				{
					new_string_vector[i] += c;
					index_vector[i] += l + 1;

					if (string == new_string_vector[i])
					{
						index = i;
					}

					break;
				}
				else
				{
					new_string_vector[i].clear();
					index_vector[i] = 0;
				}
			}
        }
    }

    return index;
}
