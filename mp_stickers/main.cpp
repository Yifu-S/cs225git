#include "Image.h"
#include "StickerSheet.h"

int main() {

  //
  // Reminder:
  //   Before exiting main, save your creation to disk as myImage.png
  //

  Image CT; CT.readFromFile("CT.png");
  Image Gs; Gs.readFromFile("Gs.png");
  Image STS; STS.readFromFile("STS.png");

  StickerSheet sheet(CT, 10);
  sheet.addSticker(Gs, 300, 1800);
  sheet.addSticker(Gs, 100, 2000);
  sheet.addSticker(Gs, 500, 2200);
  sheet.addSticker(Gs, 1000, 2400);
  sheet.addSticker(STS, 1500, 0);
  sheet.render().writeToFile("myImage.png");
  return 0;
}
