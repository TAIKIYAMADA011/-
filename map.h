#pragma once
#include<iostream>

/// @brief Csvfile����}�b�v�̔z����擾
/// @param  �t�@�C���̖��O
void load_csvfile(std::string filepath);

/// @brief �}�b�v�̍��W�̏�����
void InitializeMap();

/// @brief �}�b�v�̕`��
/// @param camera_X �J������X���W
void DrawMap(int camera_X);
