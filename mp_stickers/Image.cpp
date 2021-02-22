/**
 * @file Image.cpp
 * Implementation of the Image class using based on the given PNG class.
 *
 * @author Yifu Song from Illinois
 */

#include <cmath>
#include <cstdlib>
#include "Image.h"
using cs225::PNG;
using cs225::HSLAPixel;

void Image::lighten()
{
    for (unsigned x = 0; x <= this->width()-1; x++)
    {
        for (unsigned y = 0; y <= this->height()-1; y++)
        {
            HSLAPixel & pixel = this->getPixel(x, y);
            pixel.l += 0.1;
            if (pixel.l >= 1)
            {
                pixel.l = 1;
            }
        }
    }
}
    
void Image::lighten(double amount)
{
    for (unsigned x = 0; x <= this->width()-1; x++)
    {
        for (unsigned y = 0; y <= this->height()-1; y++)
        {
            HSLAPixel & pixel = this->getPixel(x, y);
            pixel.l += amount;
            if (pixel.l >= 1)
            {
                pixel.l = 1;
            }
            if (pixel.l <= 0)
            {
                pixel.l = 0;
            }
        }
    }
}

void Image::darken()
{
    for (unsigned x = 0; x <= this->width()-1; x++)
    {
        for (unsigned y = 0; y <= this->height()-1; y++)
        {
            HSLAPixel & pixel = this->getPixel(x, y);
            pixel.l -= 0.1;
            if (pixel.l <= 0)
            {
                pixel.l = 0;
            }
        }
    }
}

void Image::darken(double amount)
{
    for (unsigned x = 0; x <= this->width()-1; x++)
    {
        for (unsigned y = 0; y <= this->height()-1; y++)
        {
            HSLAPixel & pixel = this->getPixel(x, y);
            pixel.l -= amount;
            if (pixel.l >= 1)
            {
                pixel.l = 1;
            }
            if (pixel.l <= 0)
            {
                pixel.l = 0;
            }
        }
    }
}

void Image::saturate()
{
    for (unsigned x = 0; x <= this->width()-1; x++)
    {
        for (unsigned y = 0; y <= this->height()-1; y++)
        {
            HSLAPixel & pixel = this->getPixel(x, y);
            pixel.s += 0.1;
            if (pixel.s >= 1)
            {
                pixel.s = 1;
            }
        }
    }
}

void Image::saturate(double amount)
{
    for (unsigned x = 0; x <= this->width()-1; x++)
    {
        for (unsigned y = 0; y <= this->height()-1; y++)
        {
            HSLAPixel & pixel = this->getPixel(x, y);
            pixel.s += amount;
            if (pixel.s >= 1)
            {
                pixel.s = 1;
            }
            if (pixel.s <= 0)
            {
                pixel.s = 0;
            }
        }
    }
}

void Image::desaturate()
{
    for (unsigned x = 0; x <= this->width()-1; x++)
    {
        for (unsigned y = 0; y <= this->height()-1; y++)
        {
            HSLAPixel & pixel = this->getPixel(x, y);
            pixel.s -= 0.1;
            if (pixel.s <= 0)
            {
                pixel.s = 0;
            }
        }
    }
}

void Image::desaturate (double amount)
{
    for (unsigned x = 0; x <= this->width()-1; x++)
    {
        for (unsigned y = 0; y <= this->height()-1; y++)
        {
            HSLAPixel & pixel = this->getPixel(x, y);
            pixel.s -= amount;
            if (pixel.s >= 1)
            {
                pixel.s = 1;
            }
            if (pixel.s <= 0)
            {
                pixel.s = 0;
            }
        }
    }
}

void Image::grayscale()
{
    for (unsigned x = 0; x <= this->width()-1; x++) 
    {
        for (unsigned y = 0; y <= this->height()-1; y++) 
        {
            HSLAPixel & pixel = this->getPixel(x, y);
            pixel.s = 0;
        }
    }
}

void Image::rotateColor(double degrees)
{
    for (unsigned x = 0; x <= this->width()-1; x++) 
    {
        for (unsigned y = 0; y <= this->height()-1; y++) 
        {
            HSLAPixel & pixel = this->getPixel(x, y);
            pixel.h += degrees;
            while (pixel.h < 0)
            {
                pixel.h += 360;
            }
            
            while (pixel.h >= 360)
            {
                pixel.h -= 360;
            }
        }
    }
}

void Image::illinify()
{
    for (unsigned x = 0; x <= this->width()-1; x++) 
    {
        for (unsigned y = 0; y <= this->height()-1; y++) 
        {
            HSLAPixel & pixel = this->getPixel(x, y);
            // if closer to orange (11)
            if (std::abs((double)pixel.h - 11.0) <= std::abs((double)pixel.h - 216.0) || 
                std::abs((double)pixel.h - (11.0 + 360.0)) <= std::abs((double)pixel.h - 216.0))
                pixel.h = 11.0;

            else // which means closer to blue (216)
                pixel.h = 216.0;
        }
    }
}

void Image::scale(double factor)
{
    PNG temp = PNG(this->width()*factor, this->height()*factor);
    PNG &p = *this;
    for (unsigned x = 0; x <= this->width()*factor-1; x++) 
    {
        for (unsigned y = 0; y <= this->height()*factor-1; y++) 
        {
            
            HSLAPixel & pixel = temp.getPixel(x, y);
            pixel = this->getPixel(x / factor, y / factor);
        }
    }
    p = temp;
}

void Image::scale(unsigned w, unsigned h)
{
    double factor = std::min(w / this->width(), h / this->height());
    PNG temp = PNG(this->width()*factor, this->height()*factor);
    PNG &p = *this;
    for (unsigned x = 0; x <= this->width()*factor-1; x++) 
    {
        for (unsigned y = 0; y <= this->height()*factor-1; y++) 
        {
            
            HSLAPixel & pixel = temp.getPixel(x, y);
            pixel = this->getPixel(x / factor, y / factor);
        }
    }
    p = temp;
}