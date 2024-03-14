#ifndef LOGRECORDS_H
#define LOGRECORDS_H

#include <QObject>
#include "DataTypes.h"
#include "Tile.h"
#include <QAbstractListModel>
#include <QJsonObject>

class MeepleInfoModel;

class LogRecord : public QObject
{
    Q_OBJECT

    QmlEnums::LogRecordType m_type = QmlEnums::LogRecordType::LogNone;

protected:
    void include(QJsonObject& main, const QJsonObject& part) const;

public:
    explicit LogRecord(QmlEnums::LogRecordType type, QObject* parent = nullptr);

    virtual QmlEnums::LogRecordType type();
    virtual QColor color() const;
    virtual QString name() const;
    virtual int points() const;
    virtual QString objectType() const;
    virtual int objectSize() const;
    virtual int objectId() const;
    virtual QmlEnums::MeepleType meeple() const;
    virtual QmlEnums::BonusType resourceType() const;
    virtual Tile* tile() const;
    virtual MeepleInfoModel* meeples();

    virtual QJsonObject serialize() const;
};

class PlayerSpecificLogRecord : public LogRecord
{
    Q_OBJECT

    QColor m_color;
    QString m_name;

public:
    explicit PlayerSpecificLogRecord(QmlEnums::LogRecordType type, QColor color, QString name, QObject* parent = nullptr);

    virtual QColor color() const override;
    virtual QString name() const override;

    QJsonObject serialize() const override;
};

class NewTurnLogRecord : public PlayerSpecificLogRecord
{
    Q_OBJECT

    int m_turn;

public:
    explicit NewTurnLogRecord(QColor color, QString name, int turn, QObject* parent = nullptr);

    virtual int objectSize() const override;

    QJsonObject serialize() const override;
};

class GameEndLogRecord : public LogRecord
{
    Q_OBJECT

public:
    explicit GameEndLogRecord(QObject* parent = nullptr);
};

class ScoringLogRecord : public PlayerSpecificLogRecord
{
    Q_OBJECT

    int m_points;

public:
    explicit ScoringLogRecord(QColor color, QString name, int points, QObject* parent = nullptr);

    virtual int points() const override;

    QJsonObject serialize() const override;
};

class CompletionLogRecord : public PlayerSpecificLogRecord
{
    Q_OBJECT

    ObjectType m_objectType;
    int m_objectSize;
    int m_objectId;

public:
    explicit CompletionLogRecord(QColor color, QString name, ObjectType objectType, int objectSize, int objectId, QObject* parent = nullptr);

    virtual QString objectType() const override;
    virtual int objectSize() const override;
    virtual int objectId() const override;

    QJsonObject serialize() const override;
};

class FreeTurnLogRecord : public PlayerSpecificLogRecord
{
    Q_OBJECT

    ObjectType m_objectType;
    int m_objectId;

public:
    explicit FreeTurnLogRecord(QColor color, QString name, ObjectType objectType, int objectId, QObject* parent = nullptr);

    virtual QString objectType() const override;
    virtual int objectId() const override;

    QJsonObject serialize() const override;
};

class MeeplePlaceLogRecord : public PlayerSpecificLogRecord
{
    Q_OBJECT

    ObjectType m_objectType;
    QmlEnums::MeepleType m_meeple = QmlEnums::MeepleType::MeepleNone;
    int m_objectId;

public:
    explicit MeeplePlaceLogRecord(QColor color, QString name, ObjectType objectType, QmlEnums::MeepleType meeple, int objectId, QObject* parent = nullptr);

    virtual QString objectType() const override;
    virtual QmlEnums::MeepleType meeple() const override;
    virtual int objectId() const override;

    QJsonObject serialize() const override;
};

class MeepleInfoModel: public QAbstractListModel
{
    Q_OBJECT
    
    std::vector<MeepleInfo> m_meeples;

public:
    MeepleInfoModel(QObject* parent = nullptr);
    Q_INVOKABLE virtual int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    Q_INVOKABLE virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    virtual QHash<int, QByteArray> roleNames() const override;
    
    void add(const std::vector<MeepleInfo>& meeples);
};

class FieldMeepleReleaseLogRecord : public PlayerSpecificLogRecord
{
    Q_OBJECT

    MeepleInfoModel m_meeplesModel;

public:
    explicit FieldMeepleReleaseLogRecord(QColor color, QString name, const std::vector<MeepleInfo>& meeples, QObject* parent = nullptr);

    virtual MeepleInfoModel* meeples() override;

    QJsonObject serialize() const override;
};

class RoadLeadLogRecord : public PlayerSpecificLogRecord
{
    Q_OBJECT

    int m_objectSize;

public:
    explicit RoadLeadLogRecord(QColor color, QString name, int objectSize, QObject* parent = nullptr);

    virtual int objectSize() const override;

    QJsonObject serialize() const override;
};

class TownLeadLogRecord : public PlayerSpecificLogRecord
{
    Q_OBJECT

    int m_objectSize;

public:
    explicit TownLeadLogRecord(QColor color, QString name, int objectSize, QObject* parent = nullptr);

    virtual int objectSize() const override;

    QJsonObject serialize() const override;
};

class ResourceLeadLogRecord : public PlayerSpecificLogRecord
{
    Q_OBJECT

    int m_total, m_extra;
    QmlEnums::BonusType m_resourceType;

public:
    explicit ResourceLeadLogRecord(QColor color, QString name, int total, int extra, QmlEnums::BonusType resourceType, QObject* parent = nullptr);

    virtual int objectSize() const override; // total
    virtual int points() const override; // extra
    virtual QmlEnums::BonusType resourceType() const override;

    QJsonObject serialize() const override;
};

class ResourceLogRecord : public PlayerSpecificLogRecord
{
    Q_OBJECT

    int m_extra;
    QmlEnums::BonusType m_resourceType;

public:
    explicit ResourceLogRecord(QColor color, QString name, int extra, QmlEnums::BonusType resourceType, QObject* parent = nullptr);

    virtual int points() const override;
    virtual QmlEnums::BonusType resourceType() const override;

    QJsonObject serialize() const override;
};

class TilePlaceLogRecord : public PlayerSpecificLogRecord
{
    Q_OBJECT

    Tile* m_tile;
    int tileIndex;

public:
    explicit TilePlaceLogRecord(QColor color, QString name, Tile* tile, int tileIndex, QObject* parent = nullptr);

    virtual Tile* tile() const override;

    QJsonObject serialize() const override;
};

#endif // LOGRECORDS_H
