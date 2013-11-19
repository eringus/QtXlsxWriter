/****************************************************************************
** Copyright (c) 2013 Debao Zhang <hello@debao.me>
** All right reserved.
**
** Permission is hereby granted, free of charge, to any person obtaining
** a copy of this software and associated documentation files (the
** "Software"), to deal in the Software without restriction, including
** without limitation the rights to use, copy, modify, merge, publish,
** distribute, sublicense, and/or sell copies of the Software, and to
** permit persons to whom the Software is furnished to do so, subject to
** the following conditions:
**
** The above copyright notice and this permission notice shall be
** included in all copies or substantial portions of the Software.
**
** THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
** EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
** MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
** NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
** LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
** OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
** WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
**
****************************************************************************/
#ifndef XLSXFORMAT_P_H
#define XLSXFORMAT_P_H
#include "xlsxformat.h"
#include <QSharedData>
#include <QHash>

namespace QXlsx {

struct XlsxFormatFontData
{
    XlsxFormatFontData() :
        size(11), italic(false), strikeOut(false), color(QColor()), bold(false)
      , scirpt(Format::FontScriptNormal), underline(Format::FontUnderlineNone)
      , outline(false), shadow(false), name(QStringLiteral("Calibri")), family(2), charset(0)
      , scheme(QStringLiteral("minor")), condense(0), extend(0)
      , _dirty(true), _indexValid(false), _index(-1)

    {}

    int size;
    bool italic;
    bool strikeOut;
    QColor color;
    QString themeColor;
    bool bold;
    Format::FontScript scirpt;
    Format::FontUnderline underline;
    bool outline;
    bool shadow;
    QString name;
    int family;
    int charset;
    QString scheme;
    int condense;
    int extend;

    QByteArray key() const
    {
        if (_dirty) {
            QByteArray key;
            QDataStream stream(&key, QIODevice::WriteOnly);
            stream<<bold<<charset<<color<<themeColor<<condense
                 <<extend<<family<<italic<<name
                <<outline<<scheme<<scirpt<<shadow
               <<size<<strikeOut<<underline;

            const_cast<XlsxFormatFontData*>(this)->_key = key;
            const_cast<XlsxFormatFontData*>(this)->_dirty = false;
            const_cast<XlsxFormatFontData*>(this)->_indexValid = false;//dirty flag can not be simply cleared.
        }
        return _key;
    }

    bool indexValid() const
    {
        return !_dirty && _indexValid;
    }

    int index() const
    {
        return _index;
    }

    void setIndex(int index)
    {
        _index = index;
        _indexValid = true;
    }

    //helper member
    bool _dirty; //key re-generated and proper index assign is need.

private:
    QByteArray _key;
    bool _indexValid;  //has a valid index, so no need to assign a new one
    int _index; //index in the Font list
};

struct XlsxFormatAlignmentData
{
    XlsxFormatAlignmentData() :
        alignH(Format::AlignHGeneral), alignV(Format::AlignBottom)
      , wrap(false), rotation(0), indent(0), shinkToFit(false)
    {}

    Format::HorizontalAlignment alignH;
    Format::VerticalAlignment alignV;
    bool wrap;
    int rotation;
    int indent;
    bool shinkToFit;
};

struct XlsxFormatBorderData
{
    XlsxFormatBorderData() :
        left(Format::BorderNone), right(Format::BorderNone), top(Format::BorderNone)
      ,bottom(Format::BorderNone), diagonal(Format::BorderNone)
      ,diagonalType(Format::DiagonalBorderNone)
      ,_dirty(true), _indexValid(false), _index(-1)
    {}

    Format::BorderStyle left;
    Format::BorderStyle right;
    Format::BorderStyle top;
    Format::BorderStyle bottom;
    Format::BorderStyle diagonal;
    QColor leftColor;
    QColor rightColor;
    QColor topColor;
    QColor bottomColor;
    QColor diagonalColor;
    QString leftThemeColor;
    QString rightThemeColor;
    QString topThemeColor;
    QString bottomThemeColor;
    QString diagonalThemeColor;
    Format::DiagonalBorderType diagonalType;

    QByteArray key() const
    {
        if (_dirty) {
            QByteArray key;
            QDataStream stream(&key, QIODevice::WriteOnly);
            stream << bottom << bottomColor << bottomThemeColor << top << topColor << topThemeColor
                 << diagonal << diagonalColor << diagonalThemeColor << diagonalType
                << left << leftColor << leftThemeColor << right << rightColor << rightThemeColor;
            const_cast<XlsxFormatBorderData*>(this)->_key = key;
            const_cast<XlsxFormatBorderData*>(this)->_dirty = false;
            const_cast<XlsxFormatBorderData*>(this)->_indexValid = false;
        }
        return _key;
    }

    bool indexValid() const
    {
        return !_dirty && _indexValid;
    }

    int index() const
    {
        return _index;
    }

    void setIndex(int index)
    {
        _index = index;
        _indexValid = true;
    }

    //helper member
    bool _dirty; //key re-generated and proper index assign is need.

private:
    QByteArray _key;
    bool _indexValid;  //has a valid index, so no need to assign a new one
    int _index; //index in the border list
};

struct XlsxFormatFillData {
    XlsxFormatFillData() :
        pattern(Format::PatternNone)
      ,_dirty(true), _indexValid(false), _index(-1)
    {}

    Format::FillPattern pattern;
    QColor bgColor;
    QColor fgColor;
    QString bgThemeColor;
    QString fgThemeColor;

    QByteArray key() const
    {
        if (_dirty) {
            QByteArray key;
            QDataStream stream(&key, QIODevice::WriteOnly);
            stream<< bgColor << bgThemeColor
                  << fgColor << fgThemeColor
                  << pattern;
            const_cast<XlsxFormatFillData*>(this)->_key = key;
            const_cast<XlsxFormatFillData*>(this)->_dirty = false;
            const_cast<XlsxFormatFillData*>(this)->_indexValid = false;
        }
        return _key;
    }

    bool indexValid() const
    {
        return !_dirty && _indexValid;
    }

    int index() const
    {
        return _index;
    }

    void setIndex(int index)
    {
        _index = index;
        _indexValid = true;
    }

    //helper member
    bool _dirty; //key re-generated and proper index assign is need.

private:
    QByteArray _key;
    bool _indexValid;  //has a valid index, so no need to assign a new one
    int _index; //index in the border list
};

struct XlsxFormatProtectionData {
    XlsxFormatProtectionData() :
        locked(false), hidden(false)
    {}

    bool locked;
    bool hidden;
};

class FormatPrivate : public QSharedData
{
public:
    enum FormatType
    {
        FT_Invalid = 0,
        FT_NumFmt = 0x01,
        FT_Font = 0x02,
        FT_Alignment = 0x04,
        FT_Border = 0x08,
        FT_Fill = 0x10,
        FT_Protection = 0x20
    };

    enum Property {
        //numFmt
        P_NumFmt_Id,
        P_NumFmt_FormatCode,

        //font
        P_Font_,

        //alignment
        P_Alignment_,

        //border
        P_Border_,

        //fill
        P_Fill_,

        //protection
        P_Protection_,
    };

    FormatPrivate();
    FormatPrivate(const FormatPrivate &other);
    ~FormatPrivate();

    XlsxFormatFontData fontData;
    XlsxFormatAlignmentData alignmentData;
    XlsxFormatBorderData borderData;
    XlsxFormatFillData fillData;
    XlsxFormatProtectionData protectionData;

    mutable bool dirty; //The key re-generation is need.
    mutable QByteArray formatKey;

    int xf_index;
    mutable bool xf_indexValid;

    bool is_dxf_fomat;
    int dxf_index;
    mutable bool dxf_indexValid;

    int theme;

    QHash<int, QVariant> property;
};

}

#endif // XLSXFORMAT_P_H
