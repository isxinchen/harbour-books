#include "MGConfItem.h"

// MGConfItem stubs
struct MGConfItemPrivate
{
    QString key;
    QVariant value;
};

QMap<QString, MGConfItem*> gMGConfItems;

MGConfItem::MGConfItem(const QString &key, QObject *parent)
    : QObject (parent)
{
    priv = new MGConfItemPrivate;
    priv->key = key;
    priv->value = QVariant(false);

    gMGConfItems.insert(key, this);
}

MGConfItem::~MGConfItem()
{
    gMGConfItems.remove(priv->key);
    delete priv;
}

QList<QString> MGConfItem::listEntries() const
{
    return QList<QString>();
}

QVariant MGConfItem::value() const
{
    return priv->value;
}

QVariant MGConfItem::value(const QVariant &def) const
{
    if(!priv->value.isNull() && priv->value.isValid()){
        return priv->value;
    }
    return def;
}

void MGConfItem::set(const QVariant &val)
{
    priv->value = val;
    emit valueChanged();
}

void MGConfItem::unset()
{
    priv->value = QVariant();
}
