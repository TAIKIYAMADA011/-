#include"DxLib.h"
#include"camera.h"
#include"Screen.h"
#include"map.h"


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	ChangeWindowMode(TRUE);//Windowsの画面をアクティブにする
	DxLib_Init();//DxLibの初期化
	SetDrawScreen(DX_SCREEN_BACK);//画面の背景は黒
	SetGraphMode(SCREEN_X, SCREEN_Y, 32);
	//DxLibの初期化処理
	if (DxLib_Init() == -1)
	{
		//エラーが起きたら直ちに終了
		return -1;
	}

	float nowtime;
	float prevtime;
	float deltatime;
	

	//csvファイルの読み込み
	load_csvfile("TestMap.csv");
	//マップの座標の初期化
	InitializeMap();

	nowtime = prevtime = GetNowCount();

	while (ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0 && !CheckHitKey(KEY_INPUT_ESCAPE))
	{
		nowtime = GetNowCount();

		deltatime = (nowtime - prevtime) / 1000.0f;

		//カメラの位置を変える
		CamerainputMove(deltatime);

		////カメラの座標からマップの位置を更新
		UpdateMapPos(GetCamera_X());

		//カメラの座標を足したので元に戻す
		CameraInitalize();

		//マップの描画
		DrawMap();

		prevtime = nowtime;
	}
	DxLib_End();
	return -1;
}