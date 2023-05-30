# M5呼び込みくん

M5Stack社の[Atom SPK](https://docs.m5stack.com/en/atom/atom_spk)に接続された[PIR Unit](https://docs.m5stack.com/ja/unit/pir)が人を発見した際、microSDカード内のログファイルに書き込みを行い、音声再生を行います。

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
