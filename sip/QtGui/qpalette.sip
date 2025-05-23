// qpalette.sip generated by MetaSIP
//
// This file is part of the QtGui Python extension module.
//
// Copyright (c) 2025 Riverbank Computing Limited <info@riverbankcomputing.com>
// 
// This file is part of PyQt6.
// 
// This file may be used under the terms of the GNU General Public License
// version 3.0 as published by the Free Software Foundation and appearing in
// the file LICENSE included in the packaging of this file.  Please review the
// following information to ensure the GNU General Public License version 3.0
// requirements will be met: http://www.gnu.org/copyleft/gpl.html.
// 
// If you do not wish to use this file under the terms of the GPL version 3.0
// then you may purchase a commercial license.  For more information contact
// info@riverbankcomputing.com.
// 
// This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
// WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.


class QPalette
{
%TypeHeaderCode
#include <qpalette.h>
%End

public:
    QPalette();
    QPalette(const QColor &button);
    QPalette(Qt::GlobalColor button);
    QPalette(const QColor &button, const QColor &background);
    QPalette(const QBrush &foreground, const QBrush &button, const QBrush &light, const QBrush &dark, const QBrush &mid, const QBrush &text, const QBrush &bright_text, const QBrush &base, const QBrush &background);
    QPalette(const QPalette &palette);
    QPalette(const QVariant &variant /GetWrapper/) /NoDerived/;
%MethodCode
        if (a0->canConvert<QPalette>())
            sipCpp = new QPalette(a0->value<QPalette>());
        else
            sipError = sipBadCallableArg(0, a0Wrapper);
%End

    ~QPalette();

    enum ColorGroup
    {
        Active,
        Disabled,
        Inactive,
        NColorGroups,
        Current,
        All,
        Normal,
    };

    enum ColorRole
    {
        WindowText,
        Button,
        Light,
        Midlight,
        Dark,
        Mid,
        Text,
        BrightText,
        ButtonText,
        Base,
        Window,
        Shadow,
        Highlight,
        HighlightedText,
        Link,
        LinkVisited,
        AlternateBase,
        ToolTipBase,
        ToolTipText,
        PlaceholderText,
%If (Qt_6_6_0 -)
        Accent,
%End
        NoRole,
        NColorRoles,
    };

    QPalette::ColorGroup currentColorGroup() const;
    void setCurrentColorGroup(QPalette::ColorGroup cg);
    const QColor &color(QPalette::ColorGroup cg, QPalette::ColorRole cr) const;
    const QBrush &brush(QPalette::ColorGroup cg, QPalette::ColorRole cr) const;
    void setBrush(QPalette::ColorGroup cg, QPalette::ColorRole cr, const QBrush &brush);
    void setColorGroup(QPalette::ColorGroup cr, const QBrush &foreground, const QBrush &button, const QBrush &light, const QBrush &dark, const QBrush &mid, const QBrush &text, const QBrush &bright_text, const QBrush &base, const QBrush &background);
    bool isEqual(QPalette::ColorGroup cr1, QPalette::ColorGroup cr2) const;
    const QColor &color(QPalette::ColorRole cr) const;
    const QBrush &brush(QPalette::ColorRole cr) const;
    const QBrush &windowText() const;
    const QBrush &button() const;
    const QBrush &light() const;
    const QBrush &dark() const;
    const QBrush &mid() const;
    const QBrush &text() const;
    const QBrush &base() const;
    const QBrush &alternateBase() const;
    const QBrush &window() const;
    const QBrush &midlight() const;
    const QBrush &brightText() const;
    const QBrush &buttonText() const;
    const QBrush &shadow() const;
    const QBrush &highlight() const;
    const QBrush &highlightedText() const;
    const QBrush &link() const;
    const QBrush &linkVisited() const;
    const QBrush &toolTipBase() const;
    const QBrush &toolTipText() const;
    const QBrush &placeholderText() const;
    bool operator==(const QPalette &p) const;
    bool operator!=(const QPalette &p) const;
    bool isCopyOf(const QPalette &p) const;
    QPalette resolve(const QPalette &) const;
    void setColor(QPalette::ColorGroup acg, QPalette::ColorRole acr, const QColor &acolor);
    void setColor(QPalette::ColorRole acr, const QColor &acolor);
    void setBrush(QPalette::ColorRole acr, const QBrush &abrush);
    bool isBrushSet(QPalette::ColorGroup cg, QPalette::ColorRole cr) const;
    qint64 cacheKey() const;
    void swap(QPalette &other /Constrained/);
%If (Qt_6_6_0 -)
    const QBrush &accent() const;
%End
};

QDataStream &operator<<(QDataStream &s, const QPalette &p) /ReleaseGIL/;
QDataStream &operator>>(QDataStream &ds, QPalette &p /Constrained/) /ReleaseGIL/;
