#include <BNO055.h>
#include <mbed.h>

double gyro_test(double cnt);

double nowyaw = 0;       //現在の角度を最終的に代入する変数
double yaw = 0;          //角度
double rawyaw[2] = {0};  //比べる用の変数
double taryaw = 0;       //基準角度
double cnt = 0;          //タイマー
double con = 0;          //補正値

int main() {
  yawCnt.start();
  yawCnt.reset();

  while (1) {
    cnt = yawCnt.read_ms();
    nowyaw = gyro_test(cnt);
  }
}

// cnt=yawCnt_ms()を入力することでyawを返り値として返す
double gyro_test(double cnt) {
  //目標の角度（yaw）を取得  基準を新しくする  １秒待ってもとに戻る
  if (cnt < 1000) taryaw = yaw;
  bno.setmode(OPERATION_MODE_IMUPLUS);
  bno.get_angles();  //角度を取得 angles=角度

  // bno.euler.yawにはジャイロから送られてきた角度が入っている
  rawyaw[1] = rawyaw[0];
  rawyaw[0] = bno.euler.yaw;
  if (rawyaw[0] != 0) {  //角度が０度じゃないとき
    // 180～-180をまたいだ時
    if (rawyaw[1] < 90 && rawyaw[0] > 270)
      rawyaw[1] += 360;  // 20度を取得していた場合 380度
    else if (rawyaw[1] > 270 && rawyaw[0] < 90)
      rawyaw[1] -= 360;
    yaw -= rawyaw[0] - rawyaw[1];
  }
  cor = (taryaw - yaw) * 4;  //補正値
  return yaw;
}