/**
 * @file StickerSheet.h
 * Contains your declaration of the interface for the StickerSheet class.
 * 
 * @author Yifu Song from Illinois
 */

#pragma once

#include <vector>

#include "Image.h"

class StickerSheet
{
    public:
        /**
         * @brief Initializes this StickerSheet with a deep copy of the base picture 
         * and the ability to hold a max number of stickers (Images) with indices 0 through max - 1.
         * 
         * @param picture The base picture to use in the StickerSheet
         * @param max The maximum number of stickers (Images) on this StickerSheet
         */
        StickerSheet(const Image &picture, unsigned max);

        /**
         * @brief Frees all space that was dynamically allocated by this StickerSheet.
         * 
         */
        ~StickerSheet();

        /**
         * @brief The copy constructor makes this StickerSheet an independent copy of the source.
         * Hint: Code is likely shared between all of the "Rule of Three" functions. 
         * Would a helper function (or two) make your life easier?
         * 
         * @param other The other StickerSheet object to copy data from
         */
        StickerSheet(const StickerSheet & other);	

        /**
         * @brief Adds a sticker to the StickerSheet, so that the top-left of the sticker's Image is at (x, y) on the StickerSheet.
         * The sticker must be added to the lowest possible layer available.
         * 
         * @param sticker The Image of the sticker.
         * @param x The x location of the sticker on the StickerSheet
         * @param y The y location of the sticker on the StickerSheet
         * 
         * @return The zero-based layer index the sticker was added to, or -1 if the sticker cannot be added.
         */
        int addSticker(Image & sticker, unsigned x, unsigned y);

        /**
         * @brief Modifies the maximum number of stickers that can be stored on this StickerSheet 
         * without changing existing stickers' indices.
         * If the new maximum number of stickers is smaller than the current number number of stickers, 
         * the stickers with indices above max - 1 will be lost.
         * 
         * @param max The new value for the maximum number of Images in the StickerSheet.
         */
        void changeMaxStickers(unsigned max);

        /**
         * @brief Returns a pointer to the sticker at the specified index, not a copy of it.
         * That way, the user can modify the Image.
         * If the index is invalid, return NULL.
         * 
         * @param index The layer in which to get the sticker.
         * @return Image* A pointer to a specific Image in the StickerSheet
         */
        Image * getSticker(unsigned index);

        /**
         * @brief The assignment operator for the StickerSheet class.
         * Hint: Code is likely shared between all of the "Rule of Three" functions. 
         * Would a helper function (or two) make your life easier?
         * 
         * @param other The other Scene object to copy data from
         * @return a constant Scene reference
         */
        const StickerSheet & operator=(const StickerSheet & other);	

        /**
         * @brief Removes the sticker at the given zero-based layer index.
         * Make sure that the other stickers don't change order.
         * 
         * @param index The layer in which to delete the png
         */
        void removeSticker(unsigned index);

        /**
         * @brief Renders the whole StickerSheet on one Image and returns that Image.
         * The base picture is drawn first and then each sticker is drawn in order starting with layer zero (0), 
         * then layer one (1), and so on.
         * 
         * If a pixel's alpha channel in a sticker is zero (0), no pixel is drawn for that sticker at that pixel. 
         * If the alpha channel is non-zero, a pixel is drawn. (Alpha blending is awesome, but not required.)
         * 
         * The returned Image always includes the full contents of the picture and all stickers. 
         * This means that the size of the result image may be larger than the base picture 
         * if some stickers go beyond the edge of the picture.
         * 
         * @return Image an Image object representing the drawn scene
         */
        Image render() const;

        /**
         * @brief Changes the x and y coordinates of the Image in the specified layer.
         * If the layer is invalid or does not contain a sticker, 
         * this function must return false. Otherwise, this function returns true.
         * 
         * @param index Zero-based layer index of the sticker.
         * @param x The new x location of the sticker on the StickerSheet
         * @param y The new y location of the sticker on the StickerSheet
         * @return true if the translate was successful; otherwise false.
         */
        bool translate(unsigned index, unsigned x, unsigned y);

    // private:
        Image* baseIMG;
        std::vector<Image *> arr_;
        unsigned curLevel_;
        unsigned maxLevel_;
        std::vector<unsigned> xCoordinates_;
        std::vector<unsigned> yCoordinates_;

        /**
         * @brief copies the contents of 'other' to selfs
         * 
         * @param other to be copied
         */
        void _copy(StickerSheet const & other);
};