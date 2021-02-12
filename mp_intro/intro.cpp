#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"

#include <cmath>
#include <string>
#include <ctime>

void rotate(std::string inputFile, std::string outputFile) {
  // TODO: Part 2

  // Load in.png
  cs225::PNG* before = new cs225::PNG();
  before->readFromFile(inputFile);
  unsigned width = before->width();
  unsigned height = before->height();

  // Create out.png
  cs225::PNG* after = new cs225::PNG(width, height);

  cs225::HSLAPixel* currOutPixel = new cs225::HSLAPixel();
  cs225::HSLAPixel* currInPixel = new cs225::HSLAPixel();
  for (unsigned y = 0; y <= height - 1; y++)
  {
    for (unsigned x = 0; x <= width - 1; x++)
    {
      currInPixel = & before->getPixel(width - x - 1, height - y - 1);
      currOutPixel = & after->getPixel(x, y);
      *currOutPixel = *currInPixel;      
    }
  }
  after->writeToFile(outputFile);

  delete before;
  delete after;
  // delete currInPixel;
  // delete currOutPixel;
}

cs225::PNG myArt(unsigned int width, unsigned int height) {
  cs225::PNG png(width, height);
  // TODO: Part 3
  for (unsigned y = 0; y <= height - 1; y++)
  {
    for (unsigned x = 0; x <= width - 1; x++)
    {
      cs225::HSLAPixel & curPixel = png.getPixel(x, y);
      
      curPixel.h = 240 - (y * 40 / height);
      curPixel.s = 1;
      curPixel.l = 0.5;
      curPixel.a = 1;

      if (y >= height * 0.67)
      {
        curPixel.h = 31;
        curPixel.s = 0.11;
      }

      double distance = std::abs(std::sqrt((width * 0.67 - x) * (width * 0.67 - x) + (height * 0.67 - y) * (height * 0.67 - y)));
      if (distance <= width * 0.2 && x >= y)
      {
        curPixel.h = 55;
        curPixel.s = 1;
      }
      
      if (x <= y && y - x <= 0.4 * width && ((x + y <= 1.36 * width && x + y >= 1.32 * width) 
        || (x + y <= 1.30 * width && x + y >= 1.26 * width && y - x >= 0.32 * width) 
        || (x + y <= 1.36 * width && x + y >= 1.26 * width && y - x >= 0.36 * width)))
      {
        curPixel.l = 0.05;
      }

      if (x - y >= 0.28 * width && x - y <= 0.30 * width && x + y <= 1.35 * width && x + y >= 1.33 * width)
      {
        curPixel.l = 0.05;
      }

      srand((int)time(0));
      for (int i = 0; i <= 100; i++)
      {
        int centerX = rand() % width;
        int centerY = rand() % height;
        double distance = std::abs(std::sqrt((centerX - x) * (centerX - x) + (centerY - y) * (centerY - y)));
        if (distance <= width * 0.001 * (rand() % 10))
        {
          curPixel.l = 1;
        }
      }
    }
  }
  return png;
}
//