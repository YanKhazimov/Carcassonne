#include "Player.h"
#include "Tile.h"
#include "DeckBuilder.h"
#include "Logger.h"

#include <QQmlEngine>
#include <QDebug>

Player::Player(QColor _color, QString _name, QObject *parent)
    : QObject(parent), color(_color), active(false), name(_name), resources {-1, 0, 0, 0}
{
    QQmlEngine::setObjectOwnership(this, QQmlEngine::CppOwnership);
    turnTimer.setTimerType(Qt::VeryCoarseTimer);
    turnTimer.setInterval(1000);
    connect(&turnTimer, &QTimer::timeout, this, [this](){
        currentTurnSeconds++;
        emit currentTurnSecondsChanged();
    });
}

Player::Player(const QJsonObject& json, QObject *parent)
    : QObject(parent)
{
    QQmlEngine::setObjectOwnership(this, QQmlEngine::CppOwnership);
    turnTimer.setTimerType(Qt::VeryCoarseTimer);
    turnTimer.setInterval(1000);
    connect(&turnTimer, &QTimer::timeout, this, [this](){
        currentTurnSeconds++;
        emit currentTurnSecondsChanged();
    });

    color = json["color"].toString();
    name = json["name"].toString();
    active = json["isActive"].toBool();
    score = json["score"].toInt();
    place = json["place"].toInt();
    resources[QmlEnums::BonusType::None] = -1;
    resources[QmlEnums::BonusType::Wheat] = json["wheat"].toInt();
    resources[QmlEnums::BonusType::Barrel] = json["barrels"].toInt();
    resources[QmlEnums::BonusType::Cloth] = json["cloth"].toInt();
    wheatLead = json["wheatLead"].toBool();
    barrelsLead = json["barrelsLead"].toBool();
    clothLead = json["clothLead"].toBool();
    biggestTown = json["biggestTown"].toInt();
    biggestRoad = json["biggestRoad"].toInt();
    townLead = json["townLead"].toBool();
    roadLead = json["roadLead"].toBool();
    prevTurnsSeconds = json["prevTurnsSeconds"].toInt();
    currentTurnSeconds = json["currentTurnSeconds"].toInt();

    abbeyTile = DeckBuilder::readAbbeyTile(json["abbeyTile"].toObject());
}

Player::Player(Player &&other) noexcept
    : color(other.color), name(other.name)
{
    QQmlEngine::setObjectOwnership(this, QQmlEngine::CppOwnership);
}

QColor Player::getColor() const
{
    return color;
}

bool Player::isActive() const
{
    return active;
}

void Player::setActive(bool value)
{
    if (active != value)
    {
        active = value;
        emit isActiveChanged();

        if (active)
        {
            turnTimer.start();
        }
        else
        {
            turnTimer.stop();

            addToPreviousTime(currentTurnSeconds + 1); // rounding seconds up to avoid 0s turns
            currentTurnSeconds = 0;
            emit currentTurnSecondsChanged();
        }
    }
}

std::shared_ptr<Tile> Player::createAbbeyTile()
{
    return abbeyTile = DeckBuilder::createAbbeyTile("img/pnp/tiles", "png");
}

void Player::deserializeAbbeyTile(const QJsonObject &json)
{
    abbeyTile = DeckBuilder::readAbbeyTile(json);
}

Tile* Player::getAbbeyTile()
{
    return abbeyTile.get();
}

void Player::scorePoints(int points)
{
    setScore(getScore() + points);
    Logger::instance()->logEffect(std::make_shared<ScoringLogRecord>(color, name, points));
}

int Player::getScore() const
{
    return score;
}

int Player::getResource(QmlEnums::BonusType resourceType)
{
    return resources[resourceType];
}

void Player::setResourceLead(QmlEnums::BonusType resourceType, bool value)
{
    switch (resourceType) {
    case QmlEnums::BonusType::Barrel:
        setBarrelsLead(value);
        break;
    case QmlEnums::BonusType::Wheat:
        setWheatLead(value);
        break;
    case QmlEnums::BonusType::Cloth:
        setClothLead(value);
        break;
    default:
        break;
    }
}

int Player::getWheat() const
{
    return resources[QmlEnums::BonusType::Wheat];
}

int Player::getBarrels() const
{
    return resources[QmlEnums::BonusType::Barrel];
}

int Player::getCloth() const
{
    return resources[QmlEnums::BonusType::Cloth];
}

void Player::setWheatLead(bool value)
{
    if (wheatLead != value)
    {
        wheatLead = value;
        emit wheatLeadChanged();
    }
}

void Player::setBarrelsLead(bool value)
{
    if (barrelsLead != value)
    {
        barrelsLead = value;
        emit barrelsLeadChanged();
    }
}

void Player::setClothLead(bool value)
{
    if (clothLead != value)
    {
        clothLead = value;
        emit clothLeadChanged();
    }
}

int Player::getBiggestTown() const
{
    return biggestTown;
}

int Player::getBiggestRoad() const
{
    return biggestRoad;
}

bool Player::getWheatLead() const
{
    return wheatLead;
}

bool Player::getBarrelsLead() const
{
    return barrelsLead;
}

bool Player::getClothLead() const
{
    return clothLead;
}

void Player::addResource(int amount, QmlEnums::BonusType resourceType)
{
    switch (resourceType) {
    case QmlEnums::BonusType::Barrel:
        setBarrels(resources[resourceType] + amount);
        break;
    case QmlEnums::BonusType::Wheat:
        setWheat(resources[resourceType] + amount);
        break;
    case QmlEnums::BonusType::Cloth:
        setCloth(resources[resourceType] + amount);
        break;
    default:
        qCritical() << "adding unknown resource type" << resourceType;
        break;
    }
}

void Player::setTownLead(bool value)
{
    if (townLead != value)
    {
        townLead = value;
        emit townLeadChanged();
    }
}

bool Player::getTownLead() const
{
    return townLead;
}

void Player::setRoadLead(bool value)
{
    if (roadLead != value)
    {
        roadLead = value;
        emit roadLeadChanged();
    }
}

bool Player::getRoadLead() const
{
    return roadLead;
}

QString Player::getName() const
{
    return name;
}

void Player::setPlace(int value)
{
    if (place != value)
    {
        place = value;
        emit placeChanged();
    }
}

int Player::getPlace() const
{
    return place;
}

int Player::getPrevTurnsSeconds() const
{
    return prevTurnsSeconds;
}

int Player::getCurrentTurnSeconds() const
{
    return currentTurnSeconds;
}

void Player::setTimerRunning(bool value)
{
    if (value)
        turnTimer.start();
    else
        turnTimer.stop();
}

QJsonObject Player::serialilze() const
{
    return QJsonObject({
                        { "color", color.name(QColor::HexArgb) },
                        { "isActive", active },
                        { "name", name },
                        { "score", score },
                        { "place", place },
                        { "wheat", resources[QmlEnums::BonusType::Wheat] },
                        { "barrels", resources[QmlEnums::BonusType::Barrel] },
                        { "cloth", resources[QmlEnums::BonusType::Cloth] },
                        { "wheatLead", wheatLead },
                        { "barrelsLead", barrelsLead },
                        { "clothLead", clothLead },
                        { "biggestTown", biggestTown },
                        { "biggestRoad", biggestRoad },
                        { "townLead", townLead },
                        { "roadLead", roadLead },
                        { "prevTurnsSeconds", prevTurnsSeconds },
                        { "currentTurnSeconds",currentTurnSeconds },
                        { "abbeyTile", abbeyTile->serialize() }
    });
}

void Player::addToPreviousTime(int seconds)
{
    if (seconds != 0)
    {
        prevTurnsSeconds += seconds;
        emit prevTurnsSecondsChanged();
    }
}

void Player::setScore(int value)
{
    if (score != value)
    {
        score = value;
        emit scoreChanged();
    }
}

void Player::setWheat(int value)
{
    if (resources[QmlEnums::BonusType::Wheat] != value)
    {
        resources[QmlEnums::BonusType::Wheat] = value;
        emit wheatChanged();
    }
}

void Player::setBarrels(int value)
{
    if (resources[QmlEnums::BonusType::Barrel] != value)
    {
        resources[QmlEnums::BonusType::Barrel] = value;
        emit barrelsChanged();
    }
}

void Player::setCloth(int value)
{
    if (resources[QmlEnums::BonusType::Cloth] != value)
    {
        resources[QmlEnums::BonusType::Cloth] = value;
        emit clothChanged();
    }
}

void Player::setBiggestTown(int value)
{
    if (biggestTown != value)
    {
        biggestTown = value;
        emit biggestTownChanged();
    }
}

void Player::setBiggestRoad(int value)
{
    if (biggestRoad != value)
    {
        biggestRoad = value;
        emit biggestRoadChanged();
    }
}
