#pragma once
#include<iostream>

/// @brief Csvfileからマップの配列を取得
/// @param  ファイルの名前
void load_csvfile(std::string filepath);

/// @brief マップの座標の初期化
void InitializeMap();

/// @brief カメラの座標からマップの座標を更新
/// @param camera_X カメラのX座標
void UpdateMapPos(int camera_X);

/// @brief マップの描画
void DrawMap();
