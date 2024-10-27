#include"DxLib.h"
#include"camera.h"
#include"Screen.h"
#include"map.h"


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	ChangeWindowMode(TRUE);//Windows�̉�ʂ��A�N�e�B�u�ɂ���
	DxLib_Init();//DxLib�̏�����
	SetDrawScreen(DX_SCREEN_BACK);//��ʂ̔w�i�͍�
	SetGraphMode(SCREEN_X, SCREEN_Y, 32);
	//DxLib�̏���������
	if (DxLib_Init() == -1)
	{
		//�G���[���N�����璼���ɏI��
		return -1;
	}

	float nowtime;
	float prevtime;
	float deltatime;
	

	//csv�t�@�C���̓ǂݍ���
	load_csvfile("TestMap.csv");
	//�}�b�v�̍��W�̏�����
	InitializeMap();

	nowtime = prevtime = GetNowCount();

	while (ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0 && !CheckHitKey(KEY_INPUT_ESCAPE))
	{
		nowtime = GetNowCount();

		deltatime = (nowtime - prevtime) / 1000.0f;

		//�J�����̈ʒu��ς���
		CamerainputMove(deltatime);

		//�}�b�v�̕`��
		DrawMap(GetCamera_X());

		prevtime = nowtime;
	}
	DxLib_End();
	return -1;
}