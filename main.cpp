#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "TileData.h"
#include "ObjectManager.h"
#include "QmlPresenter.h"
#include <iostream>
#include <memory>
#include <list>
#include <QIcon>

int main(int argc, char *argv[])
{
    ObjectManager objectManager;

    std::list<Tile> tiles;
    tiles.emplace_back(std::vector<TileObject> {
        { objectManager.GenerateField(), { {0, 0}, {0, 2}, {0, 4} } },
        { objectManager.GenerateRoad(2), { {2, 0}, {2, 4} } },
        { objectManager.GenerateField(), { {4, 0}, {4, 4} } },
        { objectManager.GenerateTown(1), { {4, 2} } }
    });
    tiles.emplace_back(std::vector<TileObject> {
        { objectManager.GenerateField(), { {0, 0}, {0, 2}, {0, 4}, {2, 0}, {4, 0} } },
        { objectManager.GenerateRoad(1), { {4, 2} } },
        { objectManager.GenerateField(), { {4, 4} } },
        { objectManager.GenerateTown(1), { {2, 4} } },
        { objectManager.GenerateRoad(1), { {2, 0} } },
        { objectManager.GenerateField(), { {0, 0} } },
        { objectManager.GenerateTown(1), { {0, 2} } }
    });
    tiles.emplace_back(std::vector<TileObject> {
        { objectManager.GenerateTown(2, BonusType::Shield), { {0, 2}, {4, 2} } },
        { objectManager.GenerateTown(2, BonusType::Barrel), { {2, 0}, {2, 4} } },
        { objectManager.GenerateField(), { {0, 0} } },
        { objectManager.GenerateField(), { {0, 4} } },
        { objectManager.GenerateField(), { {4, 0} } },
        { objectManager.GenerateField(), { {4, 4} } }
    });
    tiles.emplace_back(std::vector<TileObject> {
        { objectManager.GenerateField(), { {0, 0}, {0, 2}, {0, 4} } },
        { objectManager.GenerateRoad(2), { {2, 0}, {2, 4} } },
        { objectManager.GenerateField(), { {4, 0}, {4, 4} } },
        { objectManager.GenerateTown(1), { {4, 2} } }
    });
    tiles.emplace_back(std::vector<TileObject> {
        { objectManager.GenerateField(), { {0, 0}, {0, 4} } },
        { objectManager.GenerateRoad(2), { {0, 2}, {4, 2} } },
        { objectManager.GenerateField(), { {4, 0} } },
        { objectManager.GenerateField(), { {4, 4} } },
        { objectManager.GenerateTown(2, BonusType::Wheat), { {2, 0}, {2, 4} } }
    });
    tiles.emplace_back(std::vector<TileObject> {
        { objectManager.GenerateTown(4, BonusType::DoubleShield), { {0, 0}, {2, 0}, {4, 0}, {2, 4}, {0, 2}, {4, 2}, {0, 4}, {4, 4} } }
    });
    tiles.emplace_back(std::vector<TileObject> {
        { objectManager.GenerateField(), { {0, 4}, {2, 4}, {4, 4} } },
        { objectManager.GenerateRoad(1), { {4, 2} } },
        { objectManager.GenerateField(), { {4, 0} } },
        { objectManager.GenerateTown(2, BonusType::Cloth), { {0, 0}, {0, 2}, {2, 0} } }
    });
    tiles.emplace_back(std::vector<TileObject> {
        { objectManager.GenerateMonastery(), { {2, 2} } },
        { objectManager.GenerateRoad(1), { {2, 0} } },
        { objectManager.GenerateRoad(1), { {0, 2} } },
        { objectManager.GenerateRoad(1), { {2, 4} } },
        { objectManager.GenerateField(), { {0, 0} } },
        { objectManager.GenerateField(), { {0, 4} } },
        { objectManager.GenerateField(), { {4, 0}, {4, 2}, {4, 4} } }
    });
    tiles.emplace_back(std::vector<TileObject> {
        { objectManager.GenerateField(), { {0, 0}, {2, 0}, {4, 0}, {4, 2}, {4, 4} } },
        { objectManager.GenerateTown(2), { {0, 2}, {0, 4}, {2, 4} } }
    });
    tiles.emplace_back(std::vector<TileObject> {
        { objectManager.GenerateTown(2, BonusType::Wheat), { {0, 0}, {0, 2}, {0, 4}, {2, 4}, {4, 0}, {4, 4} } },
        { objectManager.GenerateField(), { {2, 0} } },
        { objectManager.GenerateField(), { {4, 2} } }
    });
    tiles.emplace_back(std::vector<TileObject> {
        { objectManager.GenerateField(), { {0, 0} } },
        { objectManager.GenerateRoad(3), { {0, 2}, {2, 0}, {4, 2} } },
        { objectManager.GenerateField(), { {4, 0} } },
        { objectManager.GenerateField(), { {0, 4}, {4, 4} } },
        { objectManager.GenerateTown(1), { {2, 4} } }
    });
    tiles.emplace_back(std::vector<TileObject> {
        { objectManager.GenerateField(), { {0, 0}, {2, 0}, {4, 0}, {4, 2}, {4, 4}, {2, 4}, {0, 4} } },
        { objectManager.GenerateRoad(1), { {0, 2} } }
    });
    tiles.emplace_back(std::vector<TileObject> {
        { objectManager.GenerateField(), { {0, 2} } },
        { objectManager.GenerateField(), { {2, 0} } },
        { objectManager.GenerateField(), { {4, 2} } },
        { objectManager.GenerateTown(1, BonusType::Barrel), { {0, 0}, {0, 4}, {2, 4}, {4, 0}, {4, 4} } }
    });
    tiles.emplace_back(std::vector<TileObject> {
        { objectManager.GenerateField(), { {0, 0}, {2, 0}, {4, 0} } },
        { objectManager.GenerateRoad(2), { {0, 2}, {2, 4} } },
        { objectManager.GenerateField(), { {0, 4} } },
        { objectManager.GenerateField(), { {4, 4} } },
        { objectManager.GenerateTown(1), { {4, 2} } }
    });
    tiles.emplace_back(std::vector<TileObject> {
        { objectManager.GenerateField(), { {0, 0}, {2, 0}, {4, 0}, {4, 4} } },
        { objectManager.GenerateRoad(2), { {0, 2}, {2, 4} } },
        { objectManager.GenerateField(), { {0, 4} } },
        { objectManager.GenerateTown(1), { {4, 2} } }
    });
    tiles.emplace_back(std::vector<TileObject> {
        { objectManager.GenerateField(), { {0, 0}, {4, 4} } },
        { objectManager.GenerateRoad(2), { {0, 2}, {2, 4} } },
        { objectManager.GenerateRoad(2), { {2, 0}, {4, 2} } },
        { objectManager.GenerateField(), { {0, 4} } },
        { objectManager.GenerateField(), { {4, 0} } }
    });
    tiles.emplace_back(std::vector<TileObject> {
        { objectManager.GenerateField(), { {0, 0}, {0, 4}, {4, 0}, {4, 4} } },
        { objectManager.GenerateRoad(1), { {0, 2} } },
        { objectManager.GenerateRoad(1), { {2, 0} } },
        { objectManager.GenerateRoad(1), { {2, 4} } },
        { objectManager.GenerateRoad(1), { {4, 2} } }
    });
    tiles.emplace_back(std::vector<TileObject> {
        { objectManager.GenerateRoad(2), { {0, 2}, {4, 2} } },
        { objectManager.GenerateRoad(2), { {2, 0}, {2, 4} } },
        { objectManager.GenerateField(), { {0, 0} } },
        { objectManager.GenerateField(), { {0, 4} } },
        { objectManager.GenerateField(), { {4, 0} } },
        { objectManager.GenerateField(), { {4, 4} } }
    });

#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);

    qmlRegisterUncreatableType<Tile>("com.carcassonne.cppTypes", 1, 0, "TileData", "");
    qmlRegisterUncreatableType<Player>("com.carcassonne.cppTypes", 1, 0, "Player", "");
    qmlRegisterUncreatableType<QmlPresenter>("QmlPresenter", 1, 0, "GameEngine",
                                                       "QmlPresenter class defines the game engine");
    qmlRegisterUncreatableMetaObject(QmlEnums::staticMetaObject, "EngineEnums", 1, 0, "EngineEnums", "Error: only enums");

    QmlPresenter presenter(objectManager);

    presenter.AddTiles(tiles);

    app.setWindowIcon(QIcon(":/img/bigMeeple.png"));

    engine.rootContext()->setContextProperty("engine", &presenter);

    engine.load(url);
    return app.exec();
}
