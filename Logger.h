#ifndef LOGGER_H
#define LOGGER_H

#include <QAbstractListModel>
#include <QColor>
#include <QJsonArray>
#include <memory>
#include "LogRecords.h"
#include "TilesModel.h"

class EffectsModel: public QAbstractListModel
{
    Q_OBJECT

    std::vector<std::shared_ptr<LogRecord>> effectRecords;

public:
    explicit EffectsModel(QObject* parent = nullptr);

    void logEffect(std::shared_ptr<LogRecord> effectRecord);

    Q_INVOKABLE int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    Q_INVOKABLE QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    virtual QHash<int,QByteArray> roleNames() const override;
    QJsonArray serialize() const;
};

class TurnLog: public QAbstractListModel
{
    Q_OBJECT

    // [ action -> [ effects ] ]
    std::vector<std::pair<std::shared_ptr<LogRecord>, std::shared_ptr<EffectsModel>>> actionRecords;

    std::shared_ptr<LogRecord> fromJson(const QJsonObject& json, const std::vector<std::shared_ptr<Tile>>& tiles) const;

public:
    explicit TurnLog(QObject* parent = nullptr);
    explicit TurnLog(const QJsonArray &json, const std::vector<std::shared_ptr<Tile>>& tiles);

    void logAction(std::shared_ptr<LogRecord> actionRecord);
    void logEffect(std::shared_ptr<LogRecord> effectRecord);

    Q_INVOKABLE int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    Q_INVOKABLE QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    virtual QHash<int,QByteArray> roleNames() const override;
    QJsonArray serialize() const;
};

class Logger: public QAbstractListModel
{
    Q_OBJECT

    std::vector<std::pair<std::shared_ptr<NewTurnLogRecord>, std::shared_ptr<TurnLog>>> m_turnLogs;
    static Logger* m_instance;
    explicit Logger(QObject* parent = nullptr);
    static int m_turn;

public:
    static int incrementTurn();
    static Logger* instance();
    int currentTurn() const;
    void logNewTurn(const std::shared_ptr<NewTurnLogRecord> &record);
    void logAction(const std::shared_ptr<LogRecord> &record);
    void logEffect(const std::shared_ptr<LogRecord> &record);
    Q_INVOKABLE int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    Q_INVOKABLE QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    virtual QHash<int,QByteArray> roleNames() const override;
    QJsonArray serialize() const;
    void deserialize(const QJsonArray& json, const std::vector<std::shared_ptr<Tile>>& tiles);
};

#endif // LOGGER_H
