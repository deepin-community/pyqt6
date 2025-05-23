#include <QCoreApplication>
#include <QFile>
#include <QLibraryInfo>
#include <QTextStream>

#include <qhostaddress.h>


int main(int argc, char **argv)
{
    QCoreApplication app(argc, argv);
    QFile outf(argv[1]);

    if (!outf.open(QIODevice::WriteOnly|QIODevice::Truncate|QIODevice::Text))
        return 1;

    QTextStream out(&outf);

    // The link test.
    new QHostAddress();

    // Determine which features should be disabled.

#if !QT_CONFIG(ssl)
    out << "PyQt_SSL\n";
#endif

#if !QT_CONFIG(dtls)
    out << "PyQt_DTLS\n";
#endif

    return 0;
}
