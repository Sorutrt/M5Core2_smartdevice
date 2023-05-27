#include <M5Core2.h>
#include <SD.h>

#define MaxPicturesCount 256

File dir; //ディレクトリオブジェクト
String imageFolder_str = "/img"; //フォルダの名前
int imageCount = 0; //jpgファイルの数
int image_showing = 0;
String MyPictures_string[MaxPicturesCount];
const char* MyPictures[MaxPicturesCount];

void setup() {
  M5.begin(true, true, true, true);
  M5.Lcd.setTextSize(2);

  dir = SD.open(imageFolder_str);
  if (!dir) {
    M5.Lcd.println("Photo directory not found\n");
    return;
  }
  
  // ディレクトリ内のファイルを1つずつチェックして、jpgファイルの数と名前を配列に格納する
  while (true) {
    File file = dir.openNextFile();
    if (!file) {
      // ファイルがなくなったら終了する
      break;
    }
    String fileName = file.name();
    if (fileName.endsWith(".jpg")) {
      MyPictures_string[imageCount] = "/img/" + fileName;
      imageCount++;
    }
    file.close();
  }

  //MyPictures_stringの内容をconst char*型の配列に変換し入れる
  for (int i = 0; i < imageCount; i++) {
    MyPictures[i] = MyPictures_string[i].c_str();
  }

  //確認作業
  M5.Lcd.printf("imageCount: %d\n", imageCount);
  
  for(int i=0; i<imageCount; i++) {
    M5.Lcd.printf("%s\n", MyPictures[i]);
  }
  delay(2000);
}

void loop() {

  //画像遷移
  if (M5.BtnA.wasPressed() && 0 < image_showing ) {
    image_showing--;
  }
  if (M5.BtnC.wasPressed() && image_showing < imageCount-1) {
    image_showing++;
  }

  M5.Lcd.drawJpgFile(SD, MyPictures[image_showing]);

  M5.update(); //ボタン操作の際必須
}
