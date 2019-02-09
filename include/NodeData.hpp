/// @author Sam Kenyon <sam@metadevo.com>
#ifndef NODEDATA_HPP
#define NODEDATA_HPP

#include <QObject>
#include <QString>
#include <QVariant>
#include <QVector>

#include "FlowGraph.hpp"

class NodeData : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int id READ getId)
    Q_PROPERTY(int inputId READ getInputId WRITE setInputId)
    Q_PROPERTY(QString name READ getName WRITE setName)
    Q_PROPERTY(QVariant value READ getValue WRITE setValue)
//    Q_PROPERTY(bool defaultType READ getDefaultType)

public:
    NodeData();
    NodeData(QString name, QVariant value);
    ~NodeData();

    int getId() const { return m_id; }
    int getInputId() const { return m_inputId; }
    QString getName() const { return m_name; }
    QVariant getValue() const { return m_value; }
    //char getDefaultType() const { return defaultType; }

    void setInputId(const int inputId) { m_inputId = inputId; }
    void setName(const QString& name) { m_name = name; }
    void setValue(QVariant value) { m_value = value; }

private:
    QString m_name = "node";
    int m_id;
    int m_inputId = -1;
    QVariant m_value = 0; //test
    //char defaultType;

    //std::shared_ptr<NodeBehavior> m_behavior;
};


#endif // NODEDATA_HPP
