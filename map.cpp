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

void DrawMap(int camera_x)
{
    for (int iy = 0; iy < map.size(); iy++)
    {
        for (int ix = 0; ix < map[iy].size(); ix++)
        {
            Vector2D map_chip_pos = mapPos[iy][ix];
            // マップチップの位置にカメラの位置を追加する
            map_chip_pos.x += camera_x;
            
            //マップチップの座標が画面内だった時
            if (0 - MapChipSize <= map_chip_pos.x && map_chip_pos.x <= SCREEN_X)
            {
                //マップチップが0だった時はグレー、1だった時は白
                if (map[iy][ix] == 0)
                {
                    DrawBox(map_chip_pos.x, map_chip_pos.y,map_chip_pos.x + MapChipSize, map_chip_pos.y + MapChipSize,GetColor(127, 127, 127), FALSE);
                }
                else
                {
                    DrawBox(map_chip_pos.x, map_chip_pos.y, map_chip_pos.x + MapChipSize, map_chip_pos.y + MapChipSize, GetColor(255, 255, 255), FALSE);
                }
            }
        }
    }
}
