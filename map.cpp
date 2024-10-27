#include"camera.h"
#include"map.h"
#include"Vector.h"
#include"DxLib.h"
#include"Screen.h"
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

std::vector<std::vector<int>>map;          // マップの2次元配列
Vector2D mapPos[27][60];   //マップの座標


const int MapChipSize = 40;

void load_csvfile(std::string filepath)
{
    std::string linebuf;                       // 1行読み込みバッファ
    std::string data;                          // カンマ区切りで切り出したデータ格納用

    //ファイルオープン
    std::ifstream csvFile(filepath);
    if (csvFile.fail())
    {
        printfDx("ファイルのオープンに失敗しました\n");
        return;
    }

    // ファイルからCSV読み込み
    int line = 0;
    while (getline(csvFile, linebuf))
    {
        // map配列の行を追加
        map.emplace_back();
        //カンマ区切りで読みやすいように istringstream型に変換
        std::istringstream iStream(linebuf);

        // カンマ区切り単位でdataに文字列格納
        while (getline(iStream, data, ','))
        {
            // 文字列データを数値に変換して、map[line][]の末尾に追加
            map[line].emplace_back(stoi(data));
        }
        line++;
    }
}

void InitializeMap()
{
    //マップの座標をいつも通りに並べてる
    for (int iy = 0; iy < map.size(); iy++)
    {
        for (int ix = 0; ix < map[iy].size(); ix++)
        {
            mapPos[iy][ix] = { ix * MapChipSize,iy * MapChipSize };
        }
    }
}

void UpdateMapPos(int camera_X)
{
    //マップの座標にカメラの座標を足すことでマップを動かしていく
    for (int iy = 0; iy < map.size(); iy++)
    {
        for (int ix = 0; ix < map[iy].size(); ix++)
        {
            mapPos[iy][ix].x += camera_X;
        }
    }
}

void DrawMap()
{
    for (int iy = 0; iy < map.size(); iy++)
    {
        for (int ix = 0; ix < map[iy].size(); ix++)
        {
            //マップチップの座標が画面内だった時
            if (0 - MapChipSize <= mapPos[iy][ix].x && mapPos[iy][ix].x <= SCREEN_X)
            {
                //マップチップが0だった時はグレー、1だった時は白
                if (map[iy][ix] == 0)
                {
                    DrawBox(mapPos[iy][ix].x, mapPos[iy][ix].y, mapPos[iy][ix].x + MapChipSize, mapPos[iy][ix].y + MapChipSize, GetColor(127, 127, 127), FALSE);
                }
                else
                {
                    DrawBox(mapPos[iy][ix].x, mapPos[iy][ix].y, mapPos[iy][ix].x + MapChipSize, mapPos[iy][ix].y + MapChipSize, GetColor(255, 255, 255), FALSE);
                }
            }
        }
    }
}
