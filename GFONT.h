
#ifndef _GFONT_h
#define _GFONT_h

#include "type.h" 







/**************************************************************************/
/*! 
    @brief Describes a single character's display information
*/
/**************************************************************************/
typedef struct
{
  const uint8_t widthBits;              // width, in bits (or pixels), of the character
  const uint16_t offset;                // offset of the character's bitmap, in bytes, into the the FONT_INFO's data array
} FONT_CHAR_INFO;	

/**************************************************************************/
/*! 
    @brief Describes a single font
*/
/**************************************************************************/
typedef struct
{
  const uint8_t           heightPages;  // height, in pages (8 pixels), of the font's characters
  const uint8_t           startChar;    // the first character in the font (e.g. in charInfo and data)
  const FONT_CHAR_INFO*	  charInfo;     // pointer to array of char information
  const uint8_t*          data;         // pointer to generated array of character visual representation
} FONT_INFO;

// Font data for Kristen ITC 20pt
extern const uint8_t kristenITC_20ptBitmaps[];
extern const FONT_INFO kristenITC_20ptFontInfo;
extern const FONT_CHAR_INFO kristenITC_20ptDescriptors[];


// Font data for Arial 24pt
extern const uint8_t arial_24ptBitmaps[];
extern const FONT_INFO arial_24ptFontInfo;
extern const FONT_CHAR_INFO arial_24ptDescriptors[];

// Font data for Arial 56pt
extern const uint8_t arial_56ptBitmaps[];
extern const FONT_INFO arial_56ptFontInfo;
extern const FONT_CHAR_INFO arial_56ptDescriptors[];



// Bitmap info for tMCLogo
extern const uint8_t tMCLogoBitmaps[];
extern const uint8_t tMCLogoWidthPages;
extern const uint16_t tMCLogoHeightPixels;

// Bitmap info for nasb2
extern const uint8_t nasb2Bitmaps[];
extern const uint8_t nasb2WidthPages;
extern const uint16_t nasb2HeightPixels;



// Bitmap info for tMCLogo_Small
extern const uint8_t tMCLogo_SmallBitmaps[];
extern const uint8_t tMCLogo_SmallWidthPages;
extern const uint8_t tMCLogo_SmallHeightPixels;


// Font data for Arial 32pt
extern const uint8_t arial_32ptBitmaps[];
extern const FONT_INFO arial_32ptFontInfo;
extern const FONT_CHAR_INFO arial_32ptDescriptors[];



// Bitmap info for pAYVAND
extern const uint8_t pAYVANDBitmaps[];
extern const uint8_t pAYVANDWidthPages;
extern const uint8_t pAYVANDHeightPixels;

// Bitmap info for pAYVAND2
extern const uint8_t pAYVAND2Bitmaps[];
extern const uint8_t pAYVAND2WidthPages;
extern const uint16_t pAYVAND2HeightPixels;

// Bitmap info for sIMOCO
extern const uint8_t sIMOCOBitmaps[];
extern const uint8_t sIMOCOWidthPages;
extern const uint16_t sIMOCOHeightPixels;


// Bitmap info for vIBROTECHS2
extern const uint8_t vIBROTECHSBitmaps[];
extern const uint8_t vIBROTECHSWidthPages;
extern const uint16_t vIBROTECHSHeightPixels;


// Bitmap info for tADBIRGARAN_5
extern const uint8_t tADBIRGARAN_4Bitmaps[];
extern const uint8_t tADBIRGARAN_4WidthPages;
extern const uint16_t tADBIRGARAN_4HeightPixels;

// Font data for Swis721 Blk BT 32pt
extern const uint8_t swis721BlkBT_32ptBitmaps[];
extern const FONT_INFO swis721BlkBT_32ptFontInfo;
extern const FONT_CHAR_INFO swis721BlkBT_32ptDescriptors[];


// Font data for MS Reference Sans Serif 48pt
extern const uint8_t mSReferenceSansSerif_48ptBitmaps[];
extern const FONT_INFO mSReferenceSansSerif_48ptFontInfo;
extern const FONT_CHAR_INFO mSReferenceSansSerif_48ptDescriptors[];


// Font data for Times New Roman 24pt
extern const uint8_t timesNewRoman_24ptBitmaps[];
extern const FONT_INFO timesNewRoman_24ptFontInfo;
extern const FONT_CHAR_INFO timesNewRoman_24ptDescriptors[];


// Font data for Arial Narrow 26pt
extern const uint8_t arialNarrow_26ptBitmaps[];
extern const FONT_INFO arialNarrow_26ptFontInfo;
extern const FONT_CHAR_INFO arialNarrow_26ptDescriptors[];

// Font data for Times New Roman 26pt
extern const uint8_t timesNewRoman_26ptBitmaps[];
extern const FONT_INFO timesNewRoman_26ptFontInfo;
extern const FONT_CHAR_INFO timesNewRoman_26ptDescriptors[];

// Font data for Arial Rounded MT Bold 26pt
extern const uint8_t arialRoundedMTBold_26ptBitmaps[];
extern const FONT_INFO arialRoundedMTBold_26ptFontInfo;
extern const FONT_CHAR_INFO arialRoundedMTBold_26ptDescriptors[];

// Font data for Arial Rounded MT Bold 24pt
extern const uint8_t arialRoundedMTBold_24ptBitmaps[];
extern const FONT_INFO arialRoundedMTBold_24ptFontInfo;
extern const FONT_CHAR_INFO arialRoundedMTBold_24ptDescriptors[];





// Font data for Arial Rounded MT Bold 48pt
extern const uint8_t arialRoundedMTBold_48ptBitmaps[];
extern const FONT_INFO arialRoundedMTBold_48ptFontInfo;
extern const FONT_CHAR_INFO arialRoundedMTBold_48ptDescriptors[];

// Font data for Arial Rounded MT Bold 72pt
extern const uint8_t arialRoundedMTBold_72ptBitmaps[];
extern const FONT_INFO arialRoundedMTBold_72ptFontInfo;
extern const FONT_CHAR_INFO arialRoundedMTBold_72ptDescriptors[];

// Font data for Verdana 72pt
extern const uint8_t verdana_72ptBitmaps[];
extern const FONT_INFO verdana_72ptFontInfo;
extern const FONT_CHAR_INFO verdana_72ptDescriptors[];

// Font data for Arial Rounded MT Bold 28pt
extern const uint8_t arialRoundedMTBold_28ptBitmaps[];
extern const FONT_INFO arialRoundedMTBold_28ptFontInfo;
extern const FONT_CHAR_INFO arialRoundedMTBold_28ptDescriptors[];

// Font data for Arial Rounded MT Bold 20pt
extern const uint8_t arialRoundedMTBold_20ptBitmaps[];
extern const FONT_INFO arialRoundedMTBold_20ptFontInfo;
extern const FONT_CHAR_INFO arialRoundedMTBold_20ptDescriptors[];

// Font data for Webdings 26pt
extern const uint8_t webdings_26ptBitmaps[];
extern const FONT_INFO webdings_26ptFontInfo;
extern const FONT_CHAR_INFO webdings_26ptDescriptors[];

// Font data for Arial Narrow 20pt
extern const uint8_t arialNarrow_20ptBitmaps[];
extern const FONT_INFO arialNarrow_20ptFontInfo;
extern const FONT_CHAR_INFO arialNarrow_20ptDescriptors[];

// Font data for Arial Narrow 14pt
extern const uint8_t arialNarrow_14ptBitmaps[];
extern const FONT_INFO arialNarrow_14ptFontInfo;
extern const FONT_CHAR_INFO arialNarrow_14ptDescriptors[];

// Font data for Arial Rounded MT Bold 16pt
extern const uint8_t arialRoundedMTBold_16ptBitmaps[];
extern const FONT_INFO arialRoundedMTBold_16ptFontInfo;
extern const FONT_CHAR_INFO arialRoundedMTBold_16ptDescriptors[];


// Font data for Arial Rounded MT Bold 30pt
extern const uint8_t arialRoundedMTBold_30ptBitmaps[];
extern const FONT_INFO arialRoundedMTBold_30ptFontInfo;
extern const FONT_CHAR_INFO arialRoundedMTBold_30ptDescriptors[];



// Font data for Arial Rounded MT Bold 18pt
extern const uint8_t arialRoundedMTBold_18ptBitmaps[];
extern const FONT_INFO arialRoundedMTBold_18ptFontInfo;
extern const FONT_CHAR_INFO arialRoundedMTBold_18ptDescriptors[];










#endif
