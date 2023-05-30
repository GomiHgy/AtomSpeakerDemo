# M5呼び込みくん

![349271429_1104366760519824_6152396647276172695_n](https://github.com/GomiHgy/M5YobikomiKun/assets/10735253/16450f71-5be4-43a9-822f-c14f0289b462)

M5Stack社の[Atom SPK](https://docs.m5stack.com/en/atom/atom_spk)を用いた呼びこみシステムです。  
Atom SPKに接続された[PIR Unit](https://docs.m5stack.com/ja/unit/pir)が人を発見した際、microSDカード内のログファイルに書き込みを行い、音声再生を行います。

## 開発・検証環境

- 開発環境
  - VSCode(Version:1.78.2) PlatformIO(Version:Core 6.1.7,Home 3.4.4)
- OS
  - Windows 11 Home(Version:22H2)
- ライブラリ
  - m5stack/M5Unified(Version:0.1.6)
  - earlephilhower/ESP8266Audio(Version:1.9.7) 

## 材料

![image](https://github.com/GomiHgy/M5YobikomiKun/assets/10735253/ef1dc959-7838-4a01-bb58-0bcc94f90615)

- [Atom SPK](https://docs.m5stack.com/en/atom/atom_spk)
- [PIR Unit](https://docs.m5stack.com/ja/unit/pir)
- [Accessory GROVE Cable(5cm)](https://docs.m5stack.com/ja/accessory/cable/grove_cable)
- microSDカード
- レゴテクニックピン

## カスタマイズ

デフォルトのソースコードでは音声ファイル及びログファイルをdefine定義しています。  
ファイル名を変更する場合はmain.cppの下記内容を変更してください。

```
// ファイル関係
#define FILEPATH_MUSIC "/file.mp3" // 再生する音楽ファイル
#define FILEPATH_LOG "/log.csv" // ログファイル
```

## UIFlow版

![image](https://github.com/GomiHgy/M5YobikomiKun/assets/10735253/a0df0800-a4a4-45c6-a822-00b9f5b7d54d)

uiflowディレクトリ内にUIFlow用プログラムが入っています。  
UIFlow Version 1.11.8現在、Atom SPKはwavファイルしか再生出来ないため、file.wavを再生するようにしています。
