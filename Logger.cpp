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

int Logger::currentTurn() const
{
    return Logger::m_turn;
}

void Logger::logNewTurn(const std::shared_ptr<NewTurnLogRecord> &record)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    m_turnLogs.push_back({ record, std::make_shared<TurnLog>() });
    endInsertRows();
}

void Logger::logAction(const std::shared_ptr<LogRecord> &record)
{
    m_turnLogs.back().second->logAction(record);
}

void Logger::logEffect(const std::shared_ptr<LogRecord> &record)
{
    m_turnLogs.back().second->logEffect(record);
}

int Logger::rowCount(const QModelIndex &parent) const
{
    return m_turnLogs.size();
}

QVariant Logger::data(const QModelIndex &index, int role) const
{
    if (role == DataRoles::TurnIndex)
        return int(m_turnLogs.at(index.row()).first->objectSize());

    if (role == DataRoles::TurnActions)
        return QVariant::fromValue(m_turnLogs.at(index.row()).second.get());

    if (role == DataRoles::PlayerColor)
        return m_turnLogs.at(index.row()).first->color();

//    if (role == DataRoles::EventPoints)
//        return m_messages.at(index.row())->points();

//    if (role == DataRoles::EventMeepleType)
//        return m_messages.at(index.row())->meeple();

//    if (role == DataRoles::EventMeepleTypes) {
//        QVariantList meeples;
//        for (auto meeple: m_messages.at(index.row())->meeples())
//        {
//            meeples.push_back(meeple.meepleType);
//        }
//        return meeples;
//    }

    return QVariant();
}

QHash<int, QByteArray> Logger::roleNames() const
{
    return {
//        { DataRoles::PlayerName, "NAME" },
        { DataRoles::PlayerColor, "COLOR" },
//        { DataRoles::EventPoints, "POINTS" },
//        { DataRoles::EventObjectType, "OBJECT_TYPE" },
//        { DataRoles::EventObjectSize, "OBJECT_SIZE" },
//        { DataRoles::EventMeepleType, "MEEPLE_TYPE" },
//        { DataRoles::EventMeeples, "MEEPLE_TYPES" },
        { DataRoles::TurnIndex, "TURN" },
        { DataRoles::TurnActions, "ACTIONS" }
    };
}

TurnLog::TurnLog(QObject *parent) : QAbstractListModel(parent)
{
}

void TurnLog::logAction(std::shared_ptr<LogRecord> actionRecord)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    actionRecords.push_back({ actionRecord, std::make_shared<EffectsModel>() });
    endInsertRows();
}

void TurnLog::logEffect(std::shared_ptr<LogRecord> effectRecord)
{
    if (actionRecords.empty())
    {
        logAction(effectRecord);
    }
    actionRecords.back().second->logEffect(effectRecord);
}

int TurnLog::rowCount(const QModelIndex &parent) const
{
    return actionRecords.size();
}

QVariant TurnLog::data(const QModelIndex &index, int role) const
{
    if (role == DataRoles::PlayerColor)
        return actionRecords.at(index.row()).first->color();

    if (role == DataRoles::PlayerName)
        return actionRecords.at(index.row()).first->name();

    if (role == DataRoles::EventType)
        return int(actionRecords.at(index.row()).first->type());

    if (role == DataRoles::EventObjectType)
        return actionRecords.at(index.row()).first->objectType();

    if (role == DataRoles::EventObjectSize)
        return actionRecords.at(index.row()).first->objectSize();

    if (role == DataRoles::EventObjectId)
        return actionRecords.at(index.row()).first->objectId();

    if (role == DataRoles::EventMeepleType)
        return actionRecords.at(index.row()).first->meeple();

    if (role == DataRoles::ActionEffects)
        return QVariant::fromValue(actionRecords.at(index.row()).second.get());

    if (role == DataRoles::EventTile)
        return QVariant::fromValue(actionRecords.at(index.row()).first->tile());

    return QVariant();
}

QHash<int, QByteArray> TurnLog::roleNames() const
{
    return {
        { DataRoles::EventType, "EVENT_TYPE" },
        { DataRoles::PlayerName, "NAME" },
        { DataRoles::PlayerColor, "COLOR" },
        { DataRoles::EventObjectType, "OBJECT_TYPE" },
        { DataRoles::EventObjectSize, "OBJECT_SIZE" },
        { DataRoles::EventObjectId, "OBJECT_ID" },
        { DataRoles::EventMeepleType, "MEEPLE_TYPE" },
        { DataRoles::ActionEffects, "EFFECTS" },
        { DataRoles::EventTile, "TILE" }
    };
}

EffectsModel::EffectsModel(QObject *parent) : QAbstractListModel(parent)
{
}

void EffectsModel::logEffect(std::shared_ptr<LogRecord> effectRecord)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    effectRecords.push_back(effectRecord);
    endInsertRows();
}

int EffectsModel::rowCount(const QModelIndex &parent) const
{
    return effectRecords.size();
}

QVariant EffectsModel::data(const QModelIndex &index, int role) const
{
    if (role == DataRoles::EventType)
        return int(effectRecords.at(index.row())->type());

    if (role == DataRoles::PlayerColor)
        return effectRecords.at(index.row())->color();

    if (role == DataRoles::EventPoints)
        return effectRecords.at(index.row())->points();

    if (role == DataRoles::EventObjectType)
        return effectRecords.at(index.row())->objectType();

    if (role == DataRoles::EventObjectSize)
        return effectRecords.at(index.row())->objectSize();

    if (role == DataRoles::EventResourceType)
        return effectRecords.at(index.row())->resourceType();

    if (role == DataRoles::EventMeeples)
        return QVariant::fromValue(effectRecords.at(index.row())->meeples());

    return QVariant();
}

QHash<int, QByteArray> EffectsModel::roleNames() const
{
    return {
        { DataRoles::EventType, "EVENT_TYPE" },
        { DataRoles::PlayerColor, "COLOR" },
        { DataRoles::EventPoints, "POINTS" },
        { DataRoles::EventObjectType, "OBJECT_TYPE" },
        { DataRoles::EventObjectSize, "OBJECT_SIZE" },
        { DataRoles::EventResourceType, "RESOURCE_TYPE" },
        { DataRoles::EventMeeples, "MEEPLES" }
    };
}
