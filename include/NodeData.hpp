/// @author Sam Kenyon <sam@metadevo.com>
#ifndef NODEDATA_HPP
#define NODEDATA_HPP

#include <QHash>
#include <QImage>
#include <QObject>
#include <QString>
#include <QVariant>
#include <QVector>

#include "FlowGraph.hpp"

class NodeData : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int uniqueId READ uniqueId)
    Q_PROPERTY(int inputId READ inputId WRITE setInputId NOTIFY inputIdChanged)
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(QVariant defaultValue READ defaultValue WRITE setDefaultValue NOTIFY defaultValueChanged)
    Q_PROPERTY(QString typeNickname READ typeNickname NOTIFY typeNicknameChanged)

public:
    using ValueType = QMetaType::Type;

    NodeData();
    NodeData(QString name, QVariant value);
    ~NodeData();

    int uniqueId() const { return m_uniqueId; }
    int inputId(const int index = 0) const { return m_inputId[index]; }
    QString name() const { return m_name; }
    QVariant defaultValue() const { return m_defaultValue; }
    Q_INVOKABLE QVariant nodeProperty(const QString& key) const { return m_properties[key]; }

    virtual ValueType defaultType() const { return m_defaultType; }
    virtual QString typeNickname() const { return "+"; }

    virtual QImage glimpse() const { return QImage(); }
    virtual QString glimpseText() const { return QString::number(m_defaultValue.toInt()); }
    virtual QVariant result(const int index = 0) const { return m_result[index]; }

    void setInputId(const int inputId, const int index = 0) { m_inputId[index] = inputId; }
    void setName(const QString& name) { m_name = name; }
    void setDefaultValue(const QVariant& value) { m_defaultValue = value; }
    Q_INVOKABLE void setNodeProperty(const QString& key, const QVariant& value) { m_properties[key] = value; }

signals:
    void inputIdChanged();
    void nameChanged();
    void defaultValueChanged();
    void typeNicknameChanged();
    void glimpseChanged(const QImage& image);
    void resultChanged();

private:
    QString m_name = "node";
    int m_uniqueId = -1;
    std::vector<int> m_inputId;
    std::vector<QVariant> m_result;
    QVariant m_defaultValue = 0;
    ValueType m_defaultType = QMetaType::Int;
    QHash<QString, QVariant> m_properties;

    //std::shared_ptr<NodeBehavior> m_behavior;
};

#endif // NODEDATA_HPP
