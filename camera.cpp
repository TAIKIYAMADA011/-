#include"camera.h"
#include"DxLib.h"

//横スクロールなのでX座標しか用意してない
int camera_X = 0;					//カメラのX座標

const int Velocity_X = 300;		//カメラのX方向移動速度

void CamerainputMove(float dt)
{
	if (CheckHitKey(KEY_INPUT_A))
	{
		camera_X -= Velocity_X * dt;
	}
	if (CheckHitKey(KEY_INPUT_D))
	{
		camera_X += Velocity_X * dt;
	}
}

void CameraInitalize()
{
	camera_X = 0;
}

int GetCamera_X()
{
	return camera_X;
}
