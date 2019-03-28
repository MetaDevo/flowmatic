/// @author Sam Kenyon <sam@metadevo.com>
#ifndef PROPERTYACCESS_HPP
#define PROPERTYACCESS_HPP

#include <memory>
#include <QList>
#include <QObject>
#include <QString>
#include <QQmlListProperty>
#include <QVariant>

class NodeData;

class NodeProperty : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString name READ getName CONSTANT)
    Q_PROPERTY(QVariant value READ getValue CONSTANT)

public:
    NodeProperty() {}
    NodeProperty(QString name, QVariant value) :
        name(name), value(value) {}
    QString getName() { return name; }
    QVariant getValue() { return value; }

    QString name;
    QVariant value;
};


/// Wrapper for QML access to get properties for any node
class PropertyAccess : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QQmlListProperty<NodeProperty> nodeProperties READ getNodeProperties)

public:
    /// Singleton
    static PropertyAccess& instance() {
        static PropertyAccess instance;
        return instance;
    }

    Q_INVOKABLE void setNode(const int schematicId, const int nodeId);

    QQmlListProperty<NodeProperty> getNodeProperties();
    int nodePropertiesCount() const;
    NodeProperty* nodePropertyAt(int index);

signals:

private:
    PropertyAccess() {}
    ~PropertyAccess() {}

    static int nodePropertiesCount(QQmlListProperty<NodeProperty>* list);
    static NodeProperty* nodePropertyAt(QQmlListProperty<NodeProperty>* list, int i);

    int m_nodeId = 0;
    int m_schematicId = 0;
    NodeData* m_node = nullptr;
    std::vector<NodeProperty*> m_currentProperties;
};

#endif // PROPERTYACCESS_HPP
