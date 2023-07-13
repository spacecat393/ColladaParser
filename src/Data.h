#ifndef SPACEENGINE_SOURCEDATATYPE_H
#define SPACEENGINE_SOURCEDATATYPE_H

#pragma once

struct IndexData
{
	std::vector<std::vector<float>> positions;
	std::vector<std::vector<float>> normals;
	std::vector<std::vector<float>> texcoord;
	std::vector<std::vector<float>> color;
	std::vector<std::vector<int>> joints;
	std::vector<std::vector<float>> weights;
};

struct BoneData
{
	int space_int = 0;
	std::vector<std::string> bones_name_string;
	std::vector<float> visual_bones_transform_float_vector; // M4x4
};

struct SourceDataType
{
	const int max_animation_bones = 149;//0
	const int max_frame = 175;//+1
	static const bool COMPRESS = true;
	static const bool CREATE_ANIMATION = true;
	static const bool FIX_ANIMATION = true;
	static const bool DECOMPOSED = false;
	static const bool CREATE_COLOR = false;
	const char* armature_name = "Armature_";
	const char* vertices_name = "/Vertices";
	const char* normals_name = "/Normals";
	const char* texcoord_name = "/Texcoord";
	const char* color_name = "/Color";
	const char* joints_name = "/Joints";
	const char* weights_name = "/Weights";
	const char* bindposes_name = "/BindPoses";
	const char* jointsidentity_name = "/JointsIdentity";
	const char* index_name = "/Index";
	const char* animation_name = "/Animation";
	const char* bones_name = "/Bones";
	const char* bones_m4x4_name = "/BonesM4x4";
	const char* skinning_bones_name = "/SkinningBones";
	const char* animation_bones_name = "/AnimationBones";
	const char* times_name = "/Times";
	const char* transforms_name = "/Transforms";
	const char* visualbones_name = "/VisualBones";

	std::vector<int> max_joint_vector;

	std::vector<std::string> object_name_vector;

	std::vector<std::vector<float>> positions; // V3
	std::vector<std::vector<float>> normals; // V3
	std::vector<std::vector<float>> texcoord; // V2
	std::vector<std::vector<float>> color; // V4

	std::vector<std::vector<int>> positions_offset;
	std::vector<std::vector<int>> normals_offset;
	std::vector<std::vector<int>> texcoord_offset;
	std::vector<std::vector<int>> color_offset;
	std::vector<std::vector<int>> p_offset; // V[]

	std::vector<std::vector<std::string>> joints;
	std::vector<std::vector<float>> weights; // V1-V4
	std::vector<std::vector<float>> bind_poses; // M4x4

	std::vector<std::vector<int>> v_offset; // V[]
	std::vector<std::vector<int>> vcount_offset; // V[]
	// std::vector<std::vector<int>> joints_offset;
	// std::vector<std::vector<int>> weights_offset;
	// std::vector<std::vector<int>> vertex_offset; // V[]

	IndexData indexdata;

	std::vector<std::vector<std::vector<int>>> index; // V1
	// std::vector<M4x4> bones_m4x4_vector;
	std::vector<std::vector<int>> unpack_index;
	std::vector<std::vector<float>> pack_positions; // V3
	std::vector<std::vector<float>> pack_normals; // V3
	std::vector<std::vector<float>> pack_texcoord; // V2
	std::vector<std::vector<float>> pack_color; // V4
	std::vector<std::vector<int>> pack_joints; // V1-V4
	std::vector<std::vector<float>> pack_weights; // V1-V4
	std::vector<std::vector<float>> un_pack_visual_bones;
	std::vector<std::vector<int>> skinning_bones;
	std::vector<std::vector<int>> animation_bones;

	std::vector<std::string> armature_string_vector;
	std::vector<float> armature_time_vector;
	std::vector<float> armature_transform_vector; // V1 : M4x4 | DECOMPOSED : samples

	std::vector<BoneData> bonedata_vector;
	std::vector<std::vector<BoneData>> visual_bones_bonedata_vector_vector;

	// std::vector<int> bones_spaces_int_vector;
	std::vector<std::vector<std::vector<std::string>>> bones_string_vector_vector_vector;
};

#endif
