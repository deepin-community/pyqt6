// qcommandlineoption.sip generated by MetaSIP
//
// This file is part of the QtCore Python extension module.
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


class QCommandLineOption
{
%TypeHeaderCode
#include <qcommandlineoption.h>
%End

public:
    explicit QCommandLineOption(const QString &name);
    explicit QCommandLineOption(const QStringList &names);
    QCommandLineOption(const QString &name, const QString &description, const QString &valueName = QString(), const QString &defaultValue = QString());
    QCommandLineOption(const QStringList &names, const QString &description, const QString &valueName = QString(), const QString &defaultValue = QString());
    QCommandLineOption(const QCommandLineOption &other);
    ~QCommandLineOption();
    void swap(QCommandLineOption &other /Constrained/);
    QStringList names() const;
    void setValueName(const QString &name);
    QString valueName() const;
    void setDescription(const QString &description);
    QString description() const;
    void setDefaultValue(const QString &defaultValue);
    void setDefaultValues(const QStringList &defaultValues);
    QStringList defaultValues() const;

    enum Flag /BaseType=Flag/
    {
        HiddenFromHelp,
        ShortOptionStyle,
%If (Qt_6_9_0 -)
        IgnoreOptionsAfter,
%End
    };

    typedef QFlags<QCommandLineOption::Flag> Flags;
    QCommandLineOption::Flags flags() const;
    void setFlags(QCommandLineOption::Flags aflags);
};
