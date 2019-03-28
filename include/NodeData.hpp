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
    Q_PROPERTY(bool isRunning READ isRunning WRITE setIsRunning NOTIFY isRunningChanged)
    Q_PROPERTY(int seqStart READ seqStart WRITE setSeqStart NOTIFY seqChanged)
    Q_PROPERTY(int seqEnd READ seqEnd WRITE setSeqEnd NOTIFY seqChanged)
    Q_PROPERTY(int seqPos READ seqPos NOTIFY seqPosChanged)
    Q_PROPERTY(bool isSelected READ isSelected NOTIFY isSelectedChanged)
    Q_PROPERTY(QString behavior WRITE setBehaviorByName)

public:
    using ValueType = QMetaType::Type;

    explicit NodeData(const int schematicId = 0);
    NodeData(const QString& name, const QVariant value, const int schematicId = 0);
    ~NodeData();

    Q_INVOKABLE QVariant nodeProperty(const QString& key) const { return m_properties[key]; }
    int propertiesSize() const { return m_properties.size(); }
    QHash<QString, QVariant> properties() const { return m_properties; }
    int uniqueId() const { return m_uniqueId; }
    int schematicId() const { return m_schematicId; }
    int inputId(const int index = 0) const { return m_inputId[index]; }
    QString name() const { return m_name; }
    QVariant defaultValue() const { return m_defaultValue; }
    QString stackLabel() const { return m_stackLabel; }
    bool isRunning() { return m_isRunning; }
    int seqStart() { return m_seqStart; }
    int seqEnd() { return m_seqEnd; }
    int seqPos() { return m_seqPos; }
    bool isSelected() { return m_selected; }

    virtual ValueType defaultType() const { return m_defaultType; }
    virtual QString typeNickname() const { return m_typeNickname; }

    virtual QImage glimpse() const;
    virtual QString glimpseText() const;
    virtual QVariant result(const int outputIndex = 0) const;

    Q_INVOKABLE virtual void preview();
    Q_INVOKABLE virtual void previewAll();
    Q_INVOKABLE virtual void run();
    Q_INVOKABLE virtual void runAll();

    Q_INVOKABLE void setNodeProperty(const QString& key, const QVariant& value) { m_properties[key] = value; }
    void setInputId(const int inputId, const int index = 0);
    void setName(const QString& name) { m_name = name; emit nameChanged(); }
    void setDefaultValue(const QVariant& value) { m_defaultValue = value; emit defaultValueChanged(); }
    void setStackLabel(const QString& label) { m_stackLabel = label; emit stackLabelChanged(); }
    void setTypeNickname(const QString& nickname) { m_typeNickname = nickname; emit typeNicknameChanged(); }
    void setIsRunning(bool flag) { m_isRunning = flag; emit isRunningChanged(m_isRunning); }
    void setSeqStart(const int index) { if (index <= m_seqEnd) { m_seqStart = index; emit seqChanged(); } }
    void setSeqEnd(const int index) { if (index >= m_seqStart) { m_seqEnd = index; emit seqChanged(); } }
    void setBehaviorByName(const QString& behaviorName);
    Q_INVOKABLE bool scrub(const int position);
    Q_INVOKABLE void select(const int oldNodeId);
    Q_INVOKABLE void unselect() const;

    void setBehavior(std::shared_ptr<NodeBehavior> behavior) { m_behavior = behavior; }

public slots:
    void updatePreview(const int nodeId, const int position, QVariant* result);
    void updateRun(const int nodeId, const int position, QVariant* result);

signals:
    void inputIdChanged();
    void nameChanged();
    void defaultValueChanged();
    void typeNicknameChanged();
    void stackLabelChanged();
    void glimpseChanged(const int schematicId, const int id, const QImage& image);
    void previewResultChanged(const int nodeId, const int position, QVariant* result);
    void runResultChanged(const int nodeId, const int position, QVariant* result);
    void seqChanged();
    void seqPosChanged(int);
    void isRunningChanged(bool);
    void isSelectedChanged(bool) const;

private:
    QString m_name = "node";
    QString m_typeNickname = "+";
    int m_uniqueId = -1;
    int m_schematicId = 0;
    QHash<int, int> m_inputId;
    QHash<int, QVariant*> m_inputs;
    //QHash<int, QVariant> m_result;
    QVariant m_defaultValue = 0;
    ValueType m_defaultType = QMetaType::Int;
    QHash<QString, QVariant> m_properties;
    std::shared_ptr<NodeBehavior> m_behavior;
    bool m_isStackOp = false;
    QString m_stackLabel;
    int m_seqStart = 0;
    int m_seqEnd = 0;
    int m_seqPos = 0;
    bool m_isRunning = false;
    mutable bool m_selected = false;
};

#endif // NODEDATA_HPP
