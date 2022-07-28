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
                           { objectManager.GenerateField(), { {0, 0}, {2, 0}, {4, 0} } },
                           { objectManager.GenerateRoad(2), { {0, 2}, {4, 2} } },
                           { objectManager.GenerateField(), { {0, 4}, {4, 4} } },
                           { objectManager.GenerateTown(1), { {2, 4} } }
                       });
    tiles.emplace_back(std::vector<TileObject> {
                           { objectManager.GenerateField(), { {0, 0}, {2, 0}, {4, 0}, {4, 2}, {4, 4} } },
                           { objectManager.GenerateTown(2), { {0, 2}, {0, 4}, {2, 4} } }
                       });
    tiles.emplace_back(std::vector<TileObject> {
                           { objectManager.GenerateTown(2), { {0, 0}, {0, 2}, {0, 4}, {2, 4}, {4, 0}, {4, 4} } },
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
                           { objectManager.GenerateTown(1), { {0, 0}, {0, 4}, {2, 4}, {4, 0}, {4, 4} } }
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
                           { objectManager.GenerateTown(2), { {0, 2}, {4, 2} } },
                           { objectManager.GenerateTown(2), { {2, 0}, {2, 4} } },
                           { objectManager.GenerateField(), { {0, 0} } },
                           { objectManager.GenerateField(), { {0, 4} } },
                           { objectManager.GenerateField(), { {4, 0} } },
                           { objectManager.GenerateField(), { {4, 4} } }
                       });
    tiles.emplace_back(std::vector<TileObject> {
                           { objectManager.GenerateRoad(2), { {0, 2}, {4, 2} } },
                           { objectManager.GenerateRoad(2), { {2, 0}, {2, 4} } },
                           { objectManager.GenerateField(), { {0, 0} } },
                           { objectManager.GenerateField(), { {0, 4} } },
                           { objectManager.GenerateField(), { {4, 0} } },
                           { objectManager.GenerateField(), { {4, 4} } }
                       });

    std::cout << std::endl;

    //std::cout << (int)Direction::North << ' ' << tile1.CanConnect(tile2, Direction::North) << std::endl;

//    tile1.Connect(tile2, Direction::South);
//    tile2.Connect(tile3, Direction::South);
//    tile3.Connect(tile4, Direction::South);

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

    qmlRegisterUncreatableType<Tile>("com.app.abc", 1, 0, "TileData", "");

    QmlPresenter presenter(objectManager);

    presenter.AddTiles(tiles);

    app.setWindowIcon(QIcon(":/img/icon.png"));

    engine.rootContext()->setContextProperty("engine", &presenter);

    engine.load(url);
    return app.exec();
}
