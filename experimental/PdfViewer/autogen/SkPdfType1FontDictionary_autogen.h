#ifndef __DEFINED__SkPdfType1FontDictionary
#define __DEFINED__SkPdfType1FontDictionary

#include "SkPdfUtils.h"
#include "SkPdfEnums_autogen.h"
#include "SkPdfArray_autogen.h"
#include "SkPdfFontDictionary_autogen.h"

// Entries in a Type 1 font dictionary
class SkPdfType1FontDictionary : public SkPdfFontDictionary {
public:
  virtual SkPdfObjectType getType() const { return kType1FontDictionary_SkPdfObjectType;}
  virtual SkPdfObjectType getTypeEnd() const { return kType1FontDictionary__End_SkPdfObjectType;}
public:
  virtual SkPdfType1FontDictionary* asType1FontDictionary() {return this;}
  virtual const SkPdfType1FontDictionary* asType1FontDictionary() const {return this;}

private:
  virtual SkPdfType0FontDictionary* asType0FontDictionary() {return NULL;}
  virtual const SkPdfType0FontDictionary* asType0FontDictionary() const {return NULL;}

public:
private:
public:
  SkPdfType1FontDictionary(const PdfMemDocument* podofoDoc = NULL, const PdfObject* podofoObj = NULL) : SkPdfFontDictionary(podofoDoc, podofoObj) {}

  SkPdfType1FontDictionary(const SkPdfType1FontDictionary& from) : SkPdfFontDictionary(from.fPodofoDoc, from.fPodofoObj) {}

  virtual bool valid() const {return true;}

  SkPdfType1FontDictionary& operator=(const SkPdfType1FontDictionary& from) {this->fPodofoDoc = from.fPodofoDoc; this->fPodofoObj = from.fPodofoObj; return *this;}

/** (Required) The type of PDF object that this dictionary describes; must be
 *  Font for a font dictionary.
**/
  bool has_Type() const {
    return (ObjectFromDictionary(fPodofoDoc, fPodofoObj->GetDictionary(), "Type", "", NULL));
  }

  std::string Type() const;
/** (Required) The type of font; must be Type1 for a Type 1 font.
**/
  bool has_Subtype() const {
    return (ObjectFromDictionary(fPodofoDoc, fPodofoObj->GetDictionary(), "Subtype", "", NULL));
  }

  std::string Subtype() const;
/** (Required in PDF 1.0; optional otherwise) The name by which this font is ref-
 *  erenced in the Font subdictionary of the current resource dictionary.
 *  Note: This entry is obsolescent and its use is no longer recommended. (See
 *  implementation note 42 in Appendix H.)
**/
  bool has_Name() const {
    return (ObjectFromDictionary(fPodofoDoc, fPodofoObj->GetDictionary(), "Name", "", NULL));
  }

  std::string Name() const;
/** (Required) The PostScript name of the font. For Type 1 fonts, this is usually
 *  the value of the FontName entry in the font program; for more information,
 *  see Section 5.2 of the PostScript Language Reference, Third Edition. The Post-
 *  Script name of the font can be used to find the font's definition in the viewer
 *  application or its environment. It is also the name that will be used when
 *  printing to a PostScript output device.
**/
  bool has_BaseFont() const {
    return (ObjectFromDictionary(fPodofoDoc, fPodofoObj->GetDictionary(), "BaseFont", "", NULL));
  }

  std::string BaseFont() const;
/** (Required except for the standard 14 fonts) The first character code defined in
 *  the font's Widths array.
**/
  bool has_FirstChar() const {
    return (ObjectFromDictionary(fPodofoDoc, fPodofoObj->GetDictionary(), "FirstChar", "", NULL));
  }

  long FirstChar() const;
/** (Required except for the standard 14 fonts) The last character code defined in
 *  the font's Widths array.
**/
  bool has_LastChar() const {
    return (ObjectFromDictionary(fPodofoDoc, fPodofoObj->GetDictionary(), "LastChar", "", NULL));
  }

  long LastChar() const;
/** (Required except for the standard 14 fonts; indirect reference preferred) An array
 *  of (LastChar - FirstChar + 1) widths, each element being the glyph width for
 *  the character whose code is FirstChar plus the array index. For character
 *  codes outside the range FirstChar to LastChar, the value of MissingWidth from
 *  the FontDescriptor entry for this font is used. The glyph widths are measured
 *  in units in which 1000 units corresponds to 1 unit in text space. These widths
 *  must be consistent with the actual widths given in the font program itself.
 *  (See implementation note 43 in Appendix H.) For more information on
 *  glyph widths and other glyph metrics, see Section 5.1.3, "Glyph Positioning
 *  and Metrics."
**/
  bool has_Widths() const {
    return (ObjectFromDictionary(fPodofoDoc, fPodofoObj->GetDictionary(), "Widths", "", NULL));
  }

  SkPdfArray* Widths() const;
/** (Required except for the standard 14 fonts; must be an indirect reference) A font
 *  descriptor describing the font's metrics other than its glyph widths (see Sec-
 *  tion 5.7, "Font Descriptors").
 *     Note: For the standard 14 fonts, the entries FirstChar, LastChar, Widths, and
 *     FontDescriptor must either all be present or all absent. Ordinarily, they are ab-
 *     sent; specifying them enables a standard font to be overridden (see "Standard
 *     Type 1 Fonts," below).
**/
  bool has_FontDescriptor() const {
    return (ObjectFromDictionary(fPodofoDoc, fPodofoObj->GetDictionary(), "FontDescriptor", "", NULL));
  }

  SkPdfFontDescriptorDictionary* FontDescriptor() const;
/** (Optional) A specification of the font's character encoding, if different from
 *  its built-in encoding. The value of Encoding may be either the name of a pre-
 *  defined encoding (MacRomanEncoding, MacExpertEncoding, or WinAnsi-
 *  Encoding, as described in Appendix D) or an encoding dictionary that
 *  specifies differences from the font's built-in encoding or from a specified pre-
 *  defined encoding (see Section 5.5.5, "Character Encoding").
**/
  bool has_Encoding() const {
    return (ObjectFromDictionary(fPodofoDoc, fPodofoObj->GetDictionary(), "Encoding", "", NULL));
  }

  bool isEncodingAName() const {
    SkPdfObject* ret = NULL;
    if (!ObjectFromDictionary(fPodofoDoc, fPodofoObj->GetDictionary(), "Encoding", "", &ret)) return false;
    return ret->podofo()->GetDataType() == ePdfDataType_Name;
  }

  std::string getEncodingAsName() const;
  bool isEncodingADictionary() const {
    SkPdfObject* ret = NULL;
    if (!ObjectFromDictionary(fPodofoDoc, fPodofoObj->GetDictionary(), "Encoding", "", &ret)) return false;
    return ret->podofo()->GetDataType() == ePdfDataType_Dictionary;
  }

  SkPdfDictionary* getEncodingAsDictionary() const;
/** (Optional; PDF 1.2) A stream containing a CMap file that maps character
 *  codes to Unicode values (see Section 5.9, "ToUnicode CMaps").
**/
  bool has_ToUnicode() const {
    return (ObjectFromDictionary(fPodofoDoc, fPodofoObj->GetDictionary(), "ToUnicode", "", NULL));
  }

  SkPdfStream* ToUnicode() const;
};

#endif  // __DEFINED__SkPdfType1FontDictionary
