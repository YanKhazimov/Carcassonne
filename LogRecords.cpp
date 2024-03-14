#include "LogRecords.h"
#include "DataRoles.h"
#include <QDebug>

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
    qWarning() << "accessing abstract color data of LogRecord";
    return "black";
}

QString LogRecord::name() const
{
    qWarning() << "accessing abstract name data of LogRecord";
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

int LogRecord::objectId() const
{
    qWarning() << "accessing abstract ObjectId data of LogRecord";
    return -1;
}

QmlEnums::MeepleType LogRecord::meeple() const
{
    qWarning() << "accessing abstract meeple data of LogRecord";
    return QmlEnums::MeepleType::MeepleNone;
}

QmlEnums::BonusType LogRecord::resourceType() const
{
    qWarning() << "accessing abstract resourceType data of LogRecord";
    return QmlEnums::BonusType::None;
}

Tile *LogRecord::tile() const
{
    qWarning() << "accessing abstract tile data of LogRecord";
    return nullptr;
}

MeepleInfoModel* LogRecord::meeples()
{
    qWarning() << "accessing abstract meeples data of LogRecord";
    return nullptr;
}

ScoringLogRecord::ScoringLogRecord(QColor color, QString name, int points, QObject *parent)
    : PlayerSpecificLogRecord(QmlEnums::LogRecordType::LogScoring, color, name, parent), m_points(points)
{
}

int ScoringLogRecord::points() const
{
    return m_points;
}

CompletionLogRecord::CompletionLogRecord(QColor color, QString name, ObjectType objectType, int objectSize, int objectId, QObject *parent)
    : PlayerSpecificLogRecord(QmlEnums::LogRecordType::LogObjectCompletion, color, name, parent),
    m_objectType(objectType), m_objectSize(objectSize), m_objectId(objectId)
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

int CompletionLogRecord::objectId() const
{
    return m_objectId;
}

FreeTurnLogRecord::FreeTurnLogRecord(QColor color, QString name, ObjectType objectType, int objectId, QObject *parent)
    : PlayerSpecificLogRecord(QmlEnums::LogRecordType::LogFreeTurn, color, name, parent), m_objectType(objectType), m_objectId(objectId)
{
}

QString FreeTurnLogRecord::objectType() const
{
    return objectStrings.value("acc").value(m_objectType);
}

int FreeTurnLogRecord::objectId() const
{
    return m_objectId;
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

MeeplePlaceLogRecord::MeeplePlaceLogRecord(QColor color, QString name, ObjectType objectType, QmlEnums::MeepleType meeple, int objectId, QObject *parent)
    : PlayerSpecificLogRecord(QmlEnums::LogRecordType::LogMeeplePlaced, color, name, parent),
    m_objectType(objectType), m_meeple(meeple), m_objectId(objectId)
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

int MeeplePlaceLogRecord::objectId() const
{
    return m_objectId;
}

FieldMeepleReleaseLogRecord::FieldMeepleReleaseLogRecord(QColor color, QString name,
                                                         const std::vector<TileObject::MeepleInfo>& meeples, QObject *parent)
    : PlayerSpecificLogRecord(QmlEnums::LogRecordType::LogMeeplesReleased, color, name, parent)
{
    m_meeplesModel.add(meeples);
}

MeepleInfoModel *FieldMeepleReleaseLogRecord::meeples()
{
    return &m_meeplesModel;
}

int MeepleInfoModel::rowCount(const QModelIndex &parent) const
{
    return m_meeples.size();
}

QVariant MeepleInfoModel::data(const QModelIndex &index, int role) const
{
    if (role == DataRoles::EventMeepleType)
        return m_meeples.at(index.row()).meepleType;

    if (role == DataRoles::EventMeeplePlayer)
        return m_meeples.at(index.row()).playerIndex;

    return QVariant();
}

QHash<int, QByteArray> MeepleInfoModel::roleNames() const
{
    return {
        { DataRoles::EventMeepleType, "MEEPLE_TYPE" },
        { DataRoles::EventMeeplePlayer, "MEEPLE_PLAYER" }
    };
}

void MeepleInfoModel::add(const std::vector<TileObject::MeepleInfo>& meeples)
{
    beginResetModel();
//    beginInsertRows(QModelIndex(), m_meeples.size(), m_meeples.size() + meeples.size() - 1);
    m_meeples.insert(m_meeples.end(), meeples.begin(), meeples.end());
//    endInsertRows();
    endResetModel();
}

NewTurnLogRecord::NewTurnLogRecord(QColor color, QString name, int turn, QObject *parent)
    : PlayerSpecificLogRecord(QmlEnums::LogRecordType::LogNewTurn, color, name, parent), m_turn(turn)
{
}

int NewTurnLogRecord::objectSize() const
{
    return m_turn;
}

ResourceLeadLogRecord::ResourceLeadLogRecord(QColor color, QString name, int total, int extra, QmlEnums::BonusType resourceType, QObject *parent)
    : PlayerSpecificLogRecord(QmlEnums::LogRecordType::LogResourceLeadChange, color, name, parent),
    m_total(total), m_extra(extra), m_resourceType(resourceType)
{
}

int ResourceLeadLogRecord::objectSize() const
{
    return m_total;
}

int ResourceLeadLogRecord::points() const
{
    return m_extra;
}

QmlEnums::BonusType ResourceLeadLogRecord::resourceType() const
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

ResourceLogRecord::ResourceLogRecord(QColor color, QString name, int extra, QmlEnums::BonusType resourceType, QObject *parent)
    : PlayerSpecificLogRecord(QmlEnums::LogRecordType::LogResource, color, name, parent), m_extra(extra), m_resourceType(resourceType)
{
}

int ResourceLogRecord::points() const
{
    return m_extra;
}

QmlEnums::BonusType ResourceLogRecord::resourceType() const
{
    return m_resourceType;
}

TilePlaceLogRecord::TilePlaceLogRecord(QColor color, QString name, Tile *tile, QObject *parent)
    : PlayerSpecificLogRecord(QmlEnums::LogRecordType::LogTilePlaced, color, name, parent), m_tile(tile)
{
}

Tile *TilePlaceLogRecord::tile() const
{
    return m_tile;
}

MeepleInfoModel::MeepleInfoModel(QObject *parent) : QAbstractListModel(parent)
{
}
