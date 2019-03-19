/// @author Sam Kenyon <sam@metadevo.com>
#ifndef NODEDATA_HPP
#define NODEDATA_HPP

#include <memory>

#include <QHash>
#include <QImage>
#include <QObject>
#include <QString>
#include <QVariant>
#include <QVector>

#include "FlowGraph.hpp"
#include "NodeBehavior.hpp"

class NodeData : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int uniqueId READ uniqueId)
    Q_PROPERTY(int inputId READ inputId WRITE setInputId NOTIFY inputIdChanged)
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(QVariant defaultValue READ defaultValue WRITE setDefaultValue NOTIFY defaultValueChanged)
    Q_PROPERTY(QString stackLabel READ stackLabel WRITE setStackLabel NOTIFY stackLabelChanged)
    Q_PROPERTY(QString typeNickname READ typeNickname WRITE setTypeNickname NOTIFY typeNicknameChanged)

public:
    using ValueType = QMetaType::Type;

    explicit NodeData(const int schematicId = 0);
    NodeData(const QString& name, const QVariant value, const int schematicId = 0);
    ~NodeData();

    int uniqueId() const { return m_uniqueId; }
    int schematicId() const { return m_schematicId; }
    int inputId(const int index = 0) const { return m_inputId[index]; }
    QString name() const { return m_name; }
    QVariant defaultValue() const { return m_defaultValue; }
    QString stackLabel() const { return m_stackLabel; }
    Q_INVOKABLE QVariant nodeProperty(const QString& key) const { return m_properties[key]; }

    virtual ValueType defaultType() const { return m_defaultType; }
    virtual QString typeNickname() const { return m_typeNickname; }

    virtual QImage glimpse() const;
    virtual QString glimpseText() const;
    virtual QVariant result(const int index = 0) const;

    Q_INVOKABLE void run();
    void setInputId(const int inputId, const int index = 0) { m_inputId[index] = inputId; emit inputIdChanged();}
    void setName(const QString& name) { m_name = name; emit nameChanged(); }
    void setDefaultValue(const QVariant& value) { m_defaultValue = value; emit defaultValueChanged(); }
    void setStackLabel(const QString& label) { m_stackLabel = label; emit stackLabelChanged(); }
    void setTypeNickname(const QString& nickname) { m_typeNickname = nickname; emit typeNicknameChanged(); }

    Q_INVOKABLE void setNodeProperty(const QString& key, const QVariant& value) { m_properties[key] = value; }
    void setBehavior(std::shared_ptr<NodeBehavior> behavior) { m_behavior = behavior; }

signals:
    void inputIdChanged();
    void nameChanged();
    void defaultValueChanged();
    void typeNicknameChanged();
    void stackLabelChanged();
    void glimpseChanged(const int schematicId, const int id, const QImage& image);
    void resultChanged();

private:
    QString m_name = "node";
    QString m_typeNickname = "+";
    int m_uniqueId = -1;
    int m_schematicId = 0;
    QHash<int, int> m_inputId;
    std::vector<QVariant> m_result;
    QVariant m_defaultValue = 0;
    ValueType m_defaultType = QMetaType::Int;
    QHash<QString, QVariant> m_properties;
    std::shared_ptr<NodeBehavior> m_behavior;
    bool m_isStackOp = false;
    QString m_stackLabel;
};

#endif // NODEDATA_HPP
