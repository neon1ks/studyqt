#ifndef CONVERT_H
#define CONVERT_H

#include <QString>

class Convert
{
public:
    Convert();

    void setText(const QString &text, int currentPos);
    [[nodiscard]] bool isChanged() const;
    [[nodiscard]] int getPos() const;
    const QString &getTest();

private:
    QString cache;
    bool update = false;
    int pos = 0;
};

#endif // CONVERT_H
