#ifndef LOGGER_H
#define LOGGER_H

#include <QAbstractListModel>
#include <QColor>
#include <memory>
#include "DataTypes.h"
#include "MapObjectData.h"

class LogRecord : public QObject
{
    Q_OBJECT

    QmlEnums::LogRecordType m_type = QmlEnums::LogRecordType::LogNone;
    QColor m_color;
    QString m_name;

public:
    explicit LogRecord(QmlEnums::LogRecordType type, QColor color, QString name, QObject* parent = nullptr);

    virtual QmlEnums::LogRecordType type();
    virtual QColor color() const;
    virtual QString name() const;
    virtual int points() const;
    virtual QString objectType() const;
    virtual int objectSize() const;
    virtual QmlEnums::MeepleType meeple() const;
    virtual QList<MapObjectData::MeepleInfo> meeples() const;
};

class NewTurnLogRecord : public LogRecord
{
    Q_OBJECT

    int m_turn;

public:
    explicit NewTurnLogRecord(QColor color, QString name, int turn, QObject* parent = nullptr);

    virtual int objectSize() const override;
};

class GameEndLogRecord : public LogRecord
{
    Q_OBJECT

public:
    explicit GameEndLogRecord(QColor color, QString name, QObject* parent = nullptr);
};

class ScoringLogRecord : public LogRecord
{
    Q_OBJECT

    int m_points;

public:
    explicit ScoringLogRecord(QColor color, QString name, int points, QObject* parent = nullptr);

    virtual int points() const override;
};

class CompletionLogRecord : public LogRecord
{
    Q_OBJECT

    ObjectType m_objectType;
    int m_objectSize;

public:
    explicit CompletionLogRecord(QColor color, QString name, ObjectType objectType, int objectSize, QObject* parent = nullptr);

    virtual QString objectType() const override;
    virtual int objectSize() const override;
};

class FreeTurnLogRecord : public LogRecord
{
    Q_OBJECT

public:
    explicit FreeTurnLogRecord(QColor color, QString name, QObject* parent = nullptr);
};

class MeeplePlaceLogRecord : public LogRecord
{
    Q_OBJECT

    ObjectType m_objectType;
    QmlEnums::MeepleType m_meeple = QmlEnums::MeepleType::MeepleNone;

public:
    explicit MeeplePlaceLogRecord(QColor color, QString name, ObjectType objectType, QmlEnums::MeepleType meeple, QObject* parent = nullptr);

    virtual QString objectType() const override;
    virtual QmlEnums::MeepleType meeple() const override;
};

class FieldMeepleReleaseLogRecord : public LogRecord
{
    Q_OBJECT

    QList<MapObjectData::MeepleInfo> m_meeples;

public:
    explicit FieldMeepleReleaseLogRecord(QColor color, QString name, QList<MapObjectData::MeepleInfo> meeples, QObject* parent = nullptr);

    virtual QList<MapObjectData::MeepleInfo> meeples() const override;
};

class RoadLeadLogRecord : public LogRecord
{
    Q_OBJECT

    int m_objectSize;

public:
    explicit RoadLeadLogRecord(QColor color, QString name, int objectSize, QObject* parent = nullptr);

    virtual int objectSize() const override;
};

class TownLeadLogRecord : public LogRecord
{
    Q_OBJECT

    int m_objectSize;

public:
    explicit TownLeadLogRecord(QColor color, QString name, int objectSize, QObject* parent = nullptr);

    virtual int objectSize() const override;
};

class ResourceLeadLogRecord : public LogRecord
{
    Q_OBJECT

    int m_amount;
    QString m_resourceType;

public:
    explicit ResourceLeadLogRecord(QColor color, QString name, int amount, QString resourceType, QObject* parent = nullptr);

    virtual int objectSize() const override;
    virtual QString objectType() const override;
};

class Logger: public QAbstractListModel
{
    Q_OBJECT

    QList<std::shared_ptr<LogRecord>> m_messages;
    static Logger* m_instance;
    explicit Logger(QObject* parent = nullptr);
    static int m_turn;

public:
    static int incrementTurn();
    static Logger* instance();
    void log(const std::shared_ptr<LogRecord> &record);
    Q_INVOKABLE int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    Q_INVOKABLE QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    virtual QHash<int,QByteArray> roleNames() const override;
};

#endif // LOGGER_H
