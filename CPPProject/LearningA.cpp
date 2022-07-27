// LearningA.cpp : This file contains the 'main' function. Program execution begins and ends there.
//


#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <iostream>
#include <fstream>
#include <string>


int main()
{
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile("AlxWalk1.fbx", 0);

	if (!scene) {
		std::cerr << "didn't load" << std::endl;
		return 0;
	}

	std::string nam = scene->mAnimations[0]->mName.C_Str();
	nam += ".txt";

	std::ofstream file;
	file.open(nam, std::ios::out);

	unsigned int n = scene->mAnimations[0]->mNumChannels;

	for (unsigned int i = 0; i < n; ++i)
	{
		aiAnimation* anim = scene->mAnimations[0];
		aiNodeAnim** nodeChannels = anim->mChannels;

		unsigned int numRotKeys = nodeChannels[i]->mNumRotationKeys;
		unsigned int numPosKeys = nodeChannels[i]->mNumPositionKeys;
		file << "SS";

		std::string curLine = "";

		for (unsigned int j = 0; j < numRotKeys; j++)
		{
			aiQuaternion quat = nodeChannels[i]->mRotationKeys[j].mValue;
			curLine += ":" + std::to_string(quat.x) + "," + std::to_string(quat.y) + "," + std::to_string(quat.z) + "," + std::to_string(quat.w);
			if (j % 5 == 0 && j > 0)
			{
				file << curLine;

				curLine = "";
			}
		}

		file << "#";
		curLine = "";

		for (unsigned int j = 0; j < numPosKeys; j++)
		{
			aiVector3D vec = nodeChannels[i]->mPositionKeys[j].mValue;
			file << ":" << std::to_string(vec.x) << "," << std::to_string(vec.y) << "," << std::to_string(vec.z);
			if (j % 5 == 0 && j > 0)
			{
				file << curLine;

				curLine = "";
			}
		}


	}

	std::cerr << "Done writing to file" << std::endl;

}