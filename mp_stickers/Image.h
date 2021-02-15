/**
 * @file Image.h
 * Contains your declaration of the interface for the Image class.
 * 
 * @author Yifu Song from Illinois
 */

#pragma once

#include "cs225/PNG.h"

class Image : public cs225::PNG
{
    public:

        /**
         * @brief Lighten an Image by increasing the luminance of every pixel by 0.1.
         * This function ensures that the luminance remains in the range [0, 1].
         */
        void lighten();
            
        /**
         * @brief Lighten an Image by increasing the luminance of every pixel by amount.
         * This function ensures that the luminance remains in the range [0, 1].
         * @param amount The desired increase in luminance.
         */
        void lighten(double amount);
        
        /**
         * @brief Darken an Image by decreasing the luminance of every pixel by 0.1.
         * This function ensures that the luminance remains in the range [0, 1].
         */
        void darken();                
        
        /**
         * @brief Darkens an Image by decreasing the luminance of every pixel by amount.
         * This function ensures that the luminance remains in the range [0, 1].
         * 
         * @param amount The desired decrease in luminance.
         */
        void darken(double amount);
                
        /**
         * @brief Saturates an Image by increasing the saturation of every pixel by 0.1.
         * This function ensures that the saturation remains in the range [0, 1].
         */
        void saturate();
        
        /**
         * @brief Saturates an Image by increasing the saturation of every pixel by amount.
         * This function ensures that the saturation remains in the range [0, 1].
         * @param amount The desired increase in saturation.
         */
        void saturate(double amount);
        
        /**
         * @brief Desaturates an Image by decreasing the saturation of every pixel by 0.1.
         * 
         */
        void desaturate();
        
        /**
         * @brief Desaturates an Image by decreasing the saturation of every pixel by amount.
         * This function ensures that the saturation remains in the range [0, 1].
         * @param amount The desired decrease in saturation.
         */
        void desaturate (double amount);
        
        /**
         * @brief Turns the image grayscale.
         * This function ensures that the saturation remains in the range [0, 1].
         */
        void grayscale();
        
        /**
         * @brief Rotates the color wheel by degrees.
         * Rotating in a positive direction increases the degree of the hue. This function ensures that the hue remains in the range [0, 360].
         * @param degrees The desired amount of rotation.
         */
        void rotateColor(double degrees);
        
        /**
         * @brief Illinify the image.
         * 
         */
        void illinify();
        
        /**
         * @brief Scale the Image by a given factor.
         * 
         * @param factor Scale factor.
         */
        void scale(double factor);
        
        /**
         * @brief Scales the image to fit within the size (w x h)
         * 
         * @param w 
         * @param h 
         */
        void scale(unsigned w, unsigned h);

    private:

};