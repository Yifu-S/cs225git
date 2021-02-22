/**
 * @file StickerSheet.cpp
 * @author Yifu Song at Illinois
 * @brief Implementation of the StickerSheet class using the Image class I constructed
 * @version 1.0
 * @date 2021-02-21
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include <cmath>
#include <cstdlib>
#include "StickerSheet.h"
#include "cs225/PNG.h"
using cs225::PNG;
using cs225::HSLAPixel;

void StickerSheet::_copy(StickerSheet const & other)
{
    // Clear self
    delete baseIMG;
    for (unsigned i = 0; i < curLevel_; i++)
    {
        delete arr_[i];
    }
    baseIMG = nullptr;
    arr_ = {};

    // Copy 'other' to self
    baseIMG = new Image(*other.baseIMG);
    maxLevel_ = other.maxLevel_;
    curLevel_ = other.curLevel_;
    arr_ = std::vector<Image *>(other.maxLevel_);
    xCoordinates_ = std::vector<unsigned>(other.maxLevel_);
    yCoordinates_ = std::vector<unsigned>(other.maxLevel_);
    for (unsigned i = 0; i < other.curLevel_; i++)
    {
        arr_[i] = new Image(*other.arr_[i]);
        xCoordinates_[i] = other.xCoordinates_[i];
        yCoordinates_[i] = other.yCoordinates_[i];
    }
}

StickerSheet::StickerSheet(const Image &picture, unsigned max)
{
    baseIMG = new Image(picture);
    arr_ = std::vector<Image *>(max);
    curLevel_ = 0;
    maxLevel_ = max;
    xCoordinates_ = std::vector<unsigned>(max);
    yCoordinates_ = std::vector<unsigned>(max);
}

StickerSheet::~StickerSheet()
{
    delete baseIMG;
    for (unsigned i = 0; i < curLevel_; i++)
    {
        delete arr_[i];
    }
    baseIMG = nullptr;
    curLevel_ = 0;
    maxLevel_ = 0;
    arr_ = {};
    xCoordinates_ = {};
    yCoordinates_ = {};
}

StickerSheet::StickerSheet(const StickerSheet & other)
{
    baseIMG = nullptr;
    curLevel_ = 0;
    maxLevel_ = 0;
    arr_ = {};
    xCoordinates_ = {};
    yCoordinates_ = {};
    _copy(other);
}

int StickerSheet::addSticker(Image & sticker, unsigned x, unsigned y)
{
    if (curLevel_ >= maxLevel_)
        return -1;
    arr_[curLevel_] = new Image(sticker);
    xCoordinates_[curLevel_] = x;
    yCoordinates_[curLevel_] = y;
    curLevel_ = curLevel_ + 1;
    return curLevel_-1;
}

void StickerSheet::changeMaxStickers(unsigned max)
{
    // arr_.resize(max);
    // curLevel_ = max < curLevel_ ? max : curLevel_;
    unsigned loop_max = max < curLevel_ ? max : curLevel_;
    std::vector<Image *>temp_arr = std::vector<Image *>(loop_max);
    std::vector<unsigned>temp_x = std::vector<unsigned>(loop_max);
    std::vector<unsigned>temp_y = std::vector<unsigned>(loop_max);

    for (unsigned i = 0; i < loop_max; i++)
    {
        temp_arr[i] = new Image(*arr_[i]);
        temp_x[i] = xCoordinates_[i];
        temp_y[i] = yCoordinates_[i];
    }
    for (unsigned i = 0; i < curLevel_; i++)
    {
        delete arr_[i];
    }
    arr_ = std::vector<Image *>(max);
    xCoordinates_ = std::vector<unsigned>(max);
    yCoordinates_ = std::vector<unsigned>(max);
    for (unsigned i = 0; i < loop_max; i++)
    {
        arr_[i] = new Image(*temp_arr[i]);
        xCoordinates_[i] = temp_x[i];
        yCoordinates_[i] = temp_y[i];
    }
    curLevel_ = loop_max;
    maxLevel_ = max;

    for (unsigned i = 0; i < loop_max; i++)
    {
        delete temp_arr[i];
    }
}

Image * StickerSheet::getSticker(unsigned index)
{
    if (index >= curLevel_)
        return nullptr;
    return arr_[index];
}

const StickerSheet & StickerSheet::operator=(const StickerSheet & other)
{
    if (this != &other) { _copy(other); }
    return *this;
}

void StickerSheet::removeSticker(unsigned index)
{
    if (curLevel_ == 1)
    {
        delete arr_[0];
        arr_ = {};
        xCoordinates_ = {};
        yCoordinates_ = {};
    }
    else
    {
        for(unsigned i = index; i+1 < curLevel_; i++)
        {
            delete arr_[i];
            arr_[i] = new Image(*arr_[i+1]);
            xCoordinates_[i] = xCoordinates_[i+1];
            yCoordinates_[i] = yCoordinates_[i+1];
        }
        delete arr_[curLevel_-1];
    }
    curLevel_ = curLevel_ - 1;
}

Image StickerSheet::render() const
{
    unsigned new_wid = baseIMG->width();
    unsigned new_hei = baseIMG->height();
    for (unsigned i = 0; i < curLevel_; i++)
    {
        if(new_wid < arr_[i]->width() + xCoordinates_[i])
            new_wid = arr_[i]->width() + xCoordinates_[i];
        if(new_hei < arr_[i]->height() + yCoordinates_[i])
            new_hei = arr_[i]->height() + yCoordinates_[i];
    }

    Image output(new_wid, new_hei);
    for(unsigned x = 0; x < baseIMG->width(); x++)
    {
        for(unsigned y = 0; y < baseIMG->height(); y++)
        {
            HSLAPixel & Pixel = output.getPixel(x, y);
            Pixel = baseIMG->getPixel(x, y);
        }
    }

    for (unsigned loop = 0; loop < curLevel_; loop++)
    {
        for (unsigned x = xCoordinates_[loop]; x < xCoordinates_[loop] + arr_[loop]->width(); x++)
        {
            for (unsigned y = yCoordinates_[loop]; y < yCoordinates_[loop] + arr_[loop]->height(); y++)
            {
                HSLAPixel & Pixel = output.getPixel(x, y);
                if (arr_[loop]->getPixel(x - xCoordinates_[loop], y - yCoordinates_[loop]).a != 0.0)
                    Pixel = arr_[loop]->getPixel(x - xCoordinates_[loop], y - yCoordinates_[loop]);
            }
        }
    }
    return output;
}

bool StickerSheet::translate(unsigned index, unsigned x, unsigned y)
{
    if (index >= curLevel_)
        return false;
    xCoordinates_[index] = x;
    yCoordinates_[index] = y;
    return true;
}