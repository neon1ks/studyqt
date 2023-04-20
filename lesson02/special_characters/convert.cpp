#include "convert.h"

#include <QDebug>
#include <QStringRef>

Convert::Convert() = default;

void Convert::setText(const QString &text, int currentPos)
{
    if (cache == text) {
        update = false;
        return;
    }

    QString buff;
    auto ref = text.splitRef(QChar('@'));

    if (ref.size() < 3) {
        cache = text;
        return;
    }

    int editPos = 0;

    int index = 0;
    for (index = 0; index + 2 < ref.size(); ++index) {
        const auto &first = ref[index];
        if (first.isEmpty()) {
            buff.append("@");
            ++editPos;
            continue;
        }
        buff.append(first);
        editPos += first.size();

        if (first[first.size() - 1] == QChar('#')) {
            bool status = true;
            const auto &second = ref[index + 1];
            if (second == "COP") {
                buff[buff.size() - 1] = QString::fromUtf8("©")[0];
            } else if (second == "PRO") {
                buff[buff.size() - 1] = QString::fromUtf8("‰")[0];
            } else if (second == "EUR") {
                buff[buff.size() - 1] = QString::fromUtf8("€")[0];
            } else if (second == "RUB") {
                buff[buff.size() - 1] = QString::fromUtf8("₽")[0];
            } else {
                buff.append("@");
                ++editPos;
                status = false;
            }
            if (status) {
                pos = editPos;
                ++index;
            }
        } else {
            ++editPos;
            buff.append("@");
        }
    }
    if (index == ref.size() - 2) {
        buff.append(ref[index]);
        buff.append("@");
        ++index;
    }
    if (index == ref.size() - 1) {
        buff.append(ref[index]);
    }

    update = buff != text;
    if (update) {
        cache = buff;
    } else {
        pos = currentPos;
    }
}

bool Convert::isChanged() const
{
    return update;
}

int Convert::getPos() const
{
    return pos;
}

const QString &Convert::getTest()
{
    update = false;
    return cache;
}
