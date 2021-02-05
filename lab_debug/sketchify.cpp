/**
 * @file sketchify.cpp
 * Implementation of the sketchify function.
 */
#pragma GCC diagnostic ignored "-Wuninitialized"
#include <cstdlib>
#include <cmath>

#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"
using namespace cs225;

/**
 * Creates a new output image.

 * @param w width of the image
 * @param h height of the image

 * @return a pointer to the newly-created image
 */
PNG* setupOutput(unsigned w, unsigned h) {
    PNG* image = new PNG(w, h);
    return image;
}

/**
 * Used to customize the color of the sketchified image.

 * @return a pointer to the color to use when sketchifying
 */
HSLAPixel* myFavoriteColor() {
    return new HSLAPixel(169, 0.8, 0.5); // I chose something like teal?
    // HSLAPixel p(280, 0.8, 0.5); return &p;
}

void sketchify(std::string inputFile, std::string outputFile) {
    // Load in.png
    PNG* original = new PNG(); // PNG* original = NULL
    // std::cout << "Reached line " << __LINE__ << std::endl;
    original->readFromFile(inputFile);  // std::cout << "Reached line " << __LINE__ << std::endl;
    unsigned width = original->width(); // std::cout << "Reached line " << __LINE__ << std::endl;
    unsigned height = original->height();   // std::cout << "Reached line " << __LINE__ << std::endl;
    // std::cout << "Reached line " << __LINE__ << std::endl;
    // Create out.png
    /*
    PNG* output;
    setupOutput(width, height);
    */
    PNG* output = setupOutput(width, height);

    // Load our favorite color to color the outline
    HSLAPixel* myPixel = myFavoriteColor();
    // Go over the whole image, and if a pixel differs from that to its upper
    // left, color it my favorite color in the output
    HSLAPixel* currOutPixel = new HSLAPixel();
    for (unsigned y = 1; y < height; y++) {
        for (unsigned x = 1; x < width; x++) {
            // Calculate the pixel difference
            HSLAPixel& prev = original->getPixel(x - 1, y - 1); 
            HSLAPixel& curr = original->getPixel(x, y);
            double diff = std::fabs(curr.h - prev.h);

            // If the pixel is an edge pixel,
            // color the output pixel with my favorite color
            currOutPixel = & output->getPixel(x, y); // HSLAPixel currOutPixel = (*output).getPixel(x, y);
            if (diff > 20) {
                *currOutPixel = *myPixel; // currOutPixel = *myPixel;
            }
        }
    }
    // std::cout << "Reached line " << __LINE__ << std::endl;
    // Save the output file
    output->writeToFile(outputFile);

    // Clean up memory
    // delete myPixel;
    // delete output;
    delete original;
}

/**
 * Debug Trail:
 * 
 * Segmentation fault
 * line32: select my favorate color (169)
 * line38~43: initiallize original to a new PNG
 * 
 * Segmentation fault
 * line45~49: output point to the return value of setupOutput
 * 
 * Warning: try to access somewhere outside of the image
 * line56~57: change from 0 < y < height and 0 < x < width to the thing without the 0 <
 * 
 * double free or corruption (out)
 * Aborted (core dumped)
 * line71: check if reach this line -> reach, which means free something twice
 * line76~77: remove delete
 * 
 * no bug but the output doesn't match (output.png is blank)
 * line65~68: use pointer instead of value
 * line55: initialize using new
 * 
 * no bug but the output doesn't match (I can't quite describe but something is wrong) yet I passed the test you provided =_=, 
 * while comparison.png says the difference is huge O_O
 * line32~33: use new to initialize a pointer, because I think if not this way, p will be deleted after function call
 * 
 * all pass! Hurray!
 * 
 */