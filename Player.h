#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>
#include <QColor>
#include <QTimer>

#include "ObjectManager.h"

class Player : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QColor Color MEMBER color CONSTANT)
    Q_PROPERTY(bool IsActive READ isActive WRITE setActive NOTIFY isActiveChanged)
    Q_PROPERTY(QString Name MEMBER name NOTIFY nameChanged)
    Q_PROPERTY(int Score READ getScore WRITE setScore NOTIFY scoreChanged)
    Q_PROPERTY(int Place READ getPlace WRITE setPlace NOTIFY placeChanged)
    Q_PROPERTY(int Wheat READ getWheat WRITE setWheat NOTIFY wheatChanged)
    Q_PROPERTY(int Barrels READ getBarrels WRITE setBarrels NOTIFY barrelsChanged)
    Q_PROPERTY(int Cloth READ getCloth WRITE setCloth NOTIFY clothChanged)
    Q_PROPERTY(bool WheatLead READ getWheatLead WRITE setWheatLead NOTIFY wheatLeadChanged)
    Q_PROPERTY(bool BarrelsLead READ getBarrelsLead WRITE setBarrelsLead NOTIFY barrelsLeadChanged)
    Q_PROPERTY(bool ClothLead READ getClothLead WRITE setClothLead NOTIFY clothLeadChanged)
    Q_PROPERTY(bool TownLead READ getTownLead WRITE setTownLead NOTIFY townLeadChanged)
    Q_PROPERTY(bool RoadLead READ getRoadLead WRITE setRoadLead NOTIFY roadLeadChanged)
    Q_PROPERTY(int PreviousTime MEMBER prevTurnsSeconds NOTIFY prevTurnsSecondsChanged)
    Q_PROPERTY(int CurrentTime MEMBER currentTurnSeconds NOTIFY currentTurnSecondsChanged)

    QColor color;
    bool active;
    QString name;
    std::shared_ptr<Tile> abbeyTile;
    int score = 0;
    int place = 0;
    int wheat = 0, barrels = 0, cloth = 0;
    bool wheatLead = false, barrelsLead = false, clothLead = false;
    bool townLead = false, roadLead = false;
    int prevTurnsSeconds = 0;
    int currentTurnSeconds = 0;
    QTimer turnTimer;

    void setScore(int value);
    void setWheat(int value);
    void setBarrels(int value);
    void setCloth(int value);

    void addToPreviousTime(int seconds);

public:
    Player(QColor color, QString name, QObject *parent = nullptr);
    Player(Player&& other) noexcept;

    QColor getColor() const;

    bool isActive() const;
    void setActive(bool value);

    void createAbbeyTile(ObjectManager& objectManager);
    Tile* getAbbeyTile();

    Q_INVOKABLE void scorePoints(int points);
    int getScore() const;
    int getWheat() const;
    int getBarrels() const;
    int getCloth() const;
    Q_INVOKABLE void setWheatLead(bool value);
    Q_INVOKABLE void setBarrelsLead(bool value);
    Q_INVOKABLE void setClothLead(bool value);
    bool getWheatLead() const;
    bool getBarrelsLead() const;
    bool getClothLead() const;
    void addWheat(int amount);
    void addBarrels(int amount);
    void addCloth(int amount);
    Q_INVOKABLE void setTownLead(bool value);
    bool getTownLead() const;
    Q_INVOKABLE void setRoadLead(bool value);
    bool getRoadLead() const;

    QString getName() const;

    void setPlace(int value);
    int getPlace() const;

signals:
    void isActiveChanged();
    void nameChanged();
    void scoreChanged();
    void placeChanged();
    void wheatChanged();
    void barrelsChanged();
    void clothChanged();
    void wheatLeadChanged();
    void barrelsLeadChanged();
    void clothLeadChanged();
    void townLeadChanged();
    void roadLeadChanged();
    void prevTurnsSecondsChanged();
    void currentTurnSecondsChanged();
};
Q_DECLARE_METATYPE(Player*)

#endif // PLAYER_H
