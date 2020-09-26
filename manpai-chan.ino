#define LED_PIN 1 // LED出力するピン
#define TRIGGER_PIN 3 // 超音波センサに送るトリガー信号
#define ECHO_PIN 2 // やまびこが帰ってくるピン
#define DETECTION_DISTANCE 40 // cm単位の検知距離

double duration = 0; // 受信した間隔
double distance = 0; // 距離
boolean prevState = false; // 前の状態

/**
 * 超音波の結果から満杯か判定する
 */
boolean isFull(){
  digitalWrite(TRIGGER_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite( TRIGGER_PIN, HIGH ); //超音波を出力
  delayMicroseconds( 10 );
  digitalWrite( TRIGGER_PIN, LOW );
  Duration = pulseIn( ECHO_PIN, HIGH ); //センサからの入力
  if (Duration >= 0) {
    Duration = Duration/2; // 往復距離を半分にする
    Distance = Duration*340*100/1000000; // 音速を340m/sに設定し、ディスタンスをcm単位で出力する
  }
  delay(500);
  if(Distance < DETECTION_DISTANCE ){
    return true;
  }
  return false;
}

/**
 * 点滅する関数
 */
void blink(){
  for(int i = 0;i <= 2 ; i++){
    digitalWrite(LED_PIN, HIGH);
    delay(500);
    digitalWrite(LED_PIN, LOW);
    delay(500);
  }
}

/**
 * セットアップ関数
 */
void setup() {
  // ピンの入出力設定
  pinMode(LED_PIN, OUTPUT);
  pinMode(TRIGGER_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
}

/**
 * メインループ
 */
void loop() {
    if(isFull()){
      if(prevState == false) {
        blink();
      }
      digitalWrite(LED_PIN, HIGH);
      prevState = true;
    }else{
      digitalWrite(LED_PIN, LOW);
      prevState = false;
    }
}
