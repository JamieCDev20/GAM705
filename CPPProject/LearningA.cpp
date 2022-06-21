// LearningA.cpp : This file contains the 'main' function. Program execution begins and ends there.
//


#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <iostream>

int main()
{
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile("SHO_EX_1.fbx", 0);

	if (!scene) {
		std::cerr << "didn't load" << std::endl;
	}
	
	unsigned int n = scene->mAnimations[0]->mNumChannels;

	for (unsigned int i = 0; i < n; ++i)
	{
		aiAnimation* anim = scene->mAnimations[0];
		aiNodeAnim** nodeChannels = anim->mChannels;
		
		unsigned int numRotKeys = nodeChannels[i]->mNumRotationKeys;
		unsigned int numPosKeys = nodeChannels[i]->mNumPositionKeys;

		std::cout << "Rotation data" << std::endl;
		for (unsigned int j = 0; j < numRotKeys; j++)
		{
			aiQuaternion quat = nodeChannels[i]->mRotationKeys[j].mValue;
			std::cout << "(" << quat.x << "," << quat.y << "," << quat.z << "," << quat.w << ")" << " ";
			if (j % 5 == 0 && j > 0)
			{
				std::cout << std::endl;
			}
		}

		std::cout << std::endl << "Position data" << std::endl;

		for (unsigned int j = 0; j < numPosKeys; j++)
		{
			aiVector3D vec = nodeChannels[i]->mPositionKeys[j].mValue;
			std::cout << "(" << vec.x << "," << vec.y << "," << vec.z << ")" << " ";
			if (j % 5 == 0 && j > 0)
			{
				std::cout << std::endl;
			}
		}
		
		std::cout << std::endl;
		std::cout << nodeChannels[i]->mPostState << std::endl;
		std::cout << "\n\n" << std::endl;

	}

}