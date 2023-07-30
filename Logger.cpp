#include "Logger.h"
#include "DataRoles.h"
#include <QDebug>

Logger* Logger::m_instance = nullptr;
int Logger::m_turn = 0;

Logger::Logger(QObject *parent) : QAbstractListModel(parent)
{
}

int Logger::incrementTurn()
{
    return ++Logger::m_turn;
}

Logger *Logger::instance()
{
    if (!m_instance)
    {
        m_instance = new Logger();
    }

    return m_instance;
}

void Logger::log(const std::shared_ptr<LogRecord> &record)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    m_messages.append(record);
    endInsertRows();
}

int Logger::rowCount(const QModelIndex &parent) const
{
    return m_messages.size();
}

QVariant Logger::data(const QModelIndex &index, int role) const
{
    if (role == DataRoles::EventType)
        return int(m_messages.at(index.row())->type());

    if (role == DataRoles::PlayerName)
        return m_messages.at(index.row())->name();

    if (role == DataRoles::PlayerColor)
        return m_messages.at(index.row())->color();

    if (role == DataRoles::EventPoints)
        return m_messages.at(index.row())->points();

    if (role == DataRoles::EventObjectType)
        return m_messages.at(index.row())->objectType();

    if (role == DataRoles::EventObjectSize)
        return m_messages.at(index.row())->objectSize();

    if (role == DataRoles::EventMeepleType)
        return m_messages.at(index.row())->meeple();

    if (role == DataRoles::EventMeepleTypes) {
        QVariantList meeples;
        for (auto meeple: m_messages.at(index.row())->meeples())
        {
            meeples.push_back(meeple.meepleType);
        }
        return meeples;
    }

    return QVariant();
}

QHash<int, QByteArray> Logger::roleNames() const
{
    return {
        { DataRoles::EventType, "TYPE" },
        { DataRoles::PlayerName, "NAME" },
        { DataRoles::PlayerColor, "COLOR" },
        { DataRoles::EventPoints, "POINTS" },
        { DataRoles::EventObjectType, "OBJECT_TYPE" },
        { DataRoles::EventObjectSize, "OBJECT_SIZE" },
        { DataRoles::EventMeepleType, "MEEPLE_TYPE" },
        { DataRoles::EventMeepleTypes, "MEEPLE_TYPES" }
    };
}

LogRecord::LogRecord(QmlEnums::LogRecordType type, QObject *parent)
    : QObject(parent), m_type(type)
{
}

QmlEnums::LogRecordType LogRecord::type()
{
    return m_type;
}

QColor LogRecord::color() const
{
    return "black";
}

QString LogRecord::name() const
{
    return "-";
}

int LogRecord::points() const
{
    qWarning() << "accessing abstract points data of LogRecord";
    return -1;
}

QString LogRecord::objectType() const
{
    qWarning() << "accessing abstract ObjectType data of LogRecord";
    return objectStrings.value("acc").value(ObjectType::None);
}

int LogRecord::objectSize() const
{
    qWarning() << "accessing abstract ObjectSize data of LogRecord";
    return -1;
}

QmlEnums::MeepleType LogRecord::meeple() const
{
    return QmlEnums::MeepleType::MeepleNone;
}

QList<MapObjectData::MeepleInfo> LogRecord::meeples() const
{
    return {};
}

ScoringLogRecord::ScoringLogRecord(QColor color, QString name, int points, QObject *parent)
    : PlayerSpecificLogRecord(QmlEnums::LogRecordType::LogScoring, color, name, parent), m_points(points)
{
}

int ScoringLogRecord::points() const
{
    return m_points;
}

CompletionLogRecord::CompletionLogRecord(QColor color, QString name, ObjectType objectType, int objectSize, QObject *parent)
    : PlayerSpecificLogRecord(QmlEnums::LogRecordType::LogObjectCompletion, color, name, parent),
    m_objectType(objectType), m_objectSize(objectSize)
{
}

QString CompletionLogRecord::objectType() const
{
    return objectStrings.value("acc").value(m_objectType);
}

int CompletionLogRecord::objectSize() const
{
    return m_objectSize;
}

FreeTurnLogRecord::FreeTurnLogRecord(QColor color, QString name, QObject *parent)
    : PlayerSpecificLogRecord(QmlEnums::LogRecordType::LogFreeTurn, color, name, parent)
{
}

RoadLeadLogRecord::RoadLeadLogRecord(QColor color, QString name, int objectSize, QObject *parent)
    : PlayerSpecificLogRecord(QmlEnums::LogRecordType::LogRoadLeadChange, color, name, parent), m_objectSize(objectSize)
{
}

int RoadLeadLogRecord::objectSize() const
{
    return m_objectSize;
}

TownLeadLogRecord::TownLeadLogRecord(QColor color, QString name, int objectSize, QObject *parent)
    : PlayerSpecificLogRecord(QmlEnums::LogRecordType::LogTownLeadChange, color, name, parent), m_objectSize(objectSize)
{
}

int TownLeadLogRecord::objectSize() const
{
    return m_objectSize;
}

MeeplePlaceLogRecord::MeeplePlaceLogRecord(QColor color, QString name, ObjectType objectType, QmlEnums::MeepleType meeple, QObject *parent)
    : LogRecord(QmlEnums::LogRecordType::LogMeeplePlaced, parent), m_objectType(objectType), m_meeple(meeple), m_color(color), m_name(name)
{
}

QString MeeplePlaceLogRecord::objectType() const
{
    return objectStrings.value("acc").value(m_objectType);
}

QmlEnums::MeepleType MeeplePlaceLogRecord::meeple() const
{
    return m_meeple;
}

FieldMeepleReleaseLogRecord::FieldMeepleReleaseLogRecord(QColor color, QString name,
                                                         QList<MapObjectData::MeepleInfo> meeples, QObject *parent)
    : PlayerSpecificLogRecord(QmlEnums::LogRecordType::LogMeepleReleased, color, name, parent), m_meeples(meeples)
{
}

QList<MapObjectData::MeepleInfo> FieldMeepleReleaseLogRecord::meeples() const
{
    return m_meeples;
}

NewTurnLogRecord::NewTurnLogRecord(QColor color, QString name, int turn, QObject *parent)
    : PlayerSpecificLogRecord(QmlEnums::LogRecordType::LogNewTurn, color, name, parent), m_turn(turn)
{
}

int NewTurnLogRecord::objectSize() const
{
    return m_turn;
}

ResourceLeadLogRecord::ResourceLeadLogRecord(QColor color, QString name, int amount, QString resourceType, QObject *parent)
    : PlayerSpecificLogRecord(QmlEnums::LogRecordType::LogResourceLeadChange, color, name, parent),
    m_amount(amount), m_resourceType(resourceType)
{
}

int ResourceLeadLogRecord::objectSize() const
{
    return m_amount;
}

QString ResourceLeadLogRecord::objectType() const
{
    return m_resourceType;
}

GameEndLogRecord::GameEndLogRecord(QObject *parent)
    : LogRecord(QmlEnums::LogRecordType::LogGameEnd, parent)
{
}

PlayerSpecificLogRecord::PlayerSpecificLogRecord(QmlEnums::LogRecordType type, QColor color, QString name, QObject *parent)
    : LogRecord(type, parent), m_color(color), m_name(name)
{
}

QColor PlayerSpecificLogRecord::color() const
{
    return m_color;
}

QString PlayerSpecificLogRecord::name() const
{
    return m_name;
}
