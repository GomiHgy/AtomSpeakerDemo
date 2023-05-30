/// AtomSpeakerに接続されたPIRセンサーが人を発見した際
/// SDカード内のログファイルに書き込みを行い、音声再生を行うサンプル。

#include <SD.h>
#include <M5Unified.h>

// ESP8266Audioライブラリ(https://github.com/earlephilhower/ESP8266Audio/)
#include <AudioFileSourceSD.h>
#include <AudioFileSourceID3.h>
#include <AudioGeneratorMP3.h>
#include <AudioOutputM5Speaker.h>

// SDカードピン
#define PIN_SD_SCK 23
#define PIN_SD_MISO 33
#define PIN_SD_MOSI 19

// PIRシグナルピン
#define PIN_PIR_SIGNAL 32

// ファイル関係
#define FILEPATH_MUSIC "/file.mp3" // 再生する音楽ファイル
#define FILEPATH_LOG "/log.csv"    // ログファイル

// 音声再生関連
static AudioFileSourceSD file;
static AudioOutputM5Speaker out(&M5.Speaker, 0);
static AudioGeneratorMP3 mp3;
static AudioFileSourceID3 *id3 = nullptr;

/// 音楽再生を停止する
void stopMusic(void)
{
  if (id3 == nullptr)
    return;
  out.stop();
  mp3.stop();
  id3->RegisterMetadataCB(nullptr, nullptr);
  id3->close();
  file.close();
  delete id3;
  id3 = nullptr;
}

/// [ fname ] で指定したパスの音楽ファイルを再生する
void playMusic(const char *fname)
{
  if (id3 != nullptr)
  {
    stopMusic();
  }
  M5.Display.setCursor(0, 8);
  file.open(fname);
  id3 = new AudioFileSourceID3(&file);
  id3->open(fname);
  mp3.begin(id3, &out);
}

/// SDカードに起動時からの時間(ミリ秒)と起動時からの回数のログを書き込む
void writeLog()
{
  static uint32_t count = 1; // カウントした人数

  File logFile = SD.open(FILEPATH_LOG, FILE_APPEND);
  logFile.print(millis());
  logFile.print(",");
  logFile.println(count++);
  file.close();
}

/// trueの場合PIRセンサーによって人がいる判定をされた場合
bool existsHuman()
{
  return digitalRead(PIN_PIR_SIGNAL) == HIGH;
}

void setup(void)
{
  // M5Stack初期化処理
  auto cfg = M5.config();
  cfg.external_speaker.atomic_spk = true;
  M5.begin(cfg);

  // スピーカー初期化処理
  M5.Speaker.begin();
  M5.Speaker.setVolume(255);
  M5.Speaker.setAllChannelVolume(255);

  // PIRセンサー初期化処理
  pinMode(PIN_PIR_SIGNAL, INPUT);

  // SDカード初期化処理
  SPI.begin(PIN_SD_SCK, PIN_SD_MISO, PIN_SD_MOSI, -1);
  while (false == SD.begin(-1, SPI, 25000000))
  {
    // 初期化に失敗した場合低い音を1秒間隔で鳴らす(確認用)
    M5.Speaker.tone(300, 200);
    delay(1000);
  }

  // 初期化に成功した場合高い音を短く鳴らす(確認用)
  M5.Speaker.tone(1000, 200);
  delay(200);
}

void loop(void)
{
  // 再生時は他の処理は行わない
  if (mp3.isRunning())
  {
    if (!mp3.loop())
    {
      mp3.stop();
    }
  }
  // 停止時
  else
  {
    // 人がいる場合
    if (existsHuman())
    {
      // ログに書き出し音楽を再生する
      writeLog();
      playMusic(FILEPATH_MUSIC);
    }
    delay(1);
  }
  M5.update();
}