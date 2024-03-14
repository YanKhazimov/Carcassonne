#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "DataTypes.h"
#include "QmlPresenter.h"
#include <QIcon>
#include <QSurfaceFormat>
#include <QList>

int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_DisableHighDpiScaling);
#endif

    QGuiApplication app(argc, argv);

    QSurfaceFormat format;
    format.setSamples(8); // smoothing out arc shapes
    QSurfaceFormat::setDefaultFormat(format);

    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);

    qmlRegisterUncreatableType<TileObject>("com.carcassonne.cppTypes", 1, 0, "TileObject", "");
    qmlRegisterUncreatableType<Tile>("com.carcassonne.cppTypes", 1, 0, "TileData", "");
    qmlRegisterUncreatableType<Player>("com.carcassonne.cppTypes", 1, 0, "Player", "");
    qmlRegisterUncreatableType<QmlPresenter>("QmlPresenter", 1, 0, "GameEngine",
                                                       "QmlPresenter class defines the game engine");
    qmlRegisterUncreatableMetaObject(QmlEnums::staticMetaObject, "EngineEnums", 1, 0, "EngineEnums", "Error: only enums");
    // qRegisterMetaType<QList<QmlEnums::TileRegion>>("TileRegionList");
    qRegisterMetaType<QList<MeepleInfo>>("MeepleInfoList");
    app.setWindowIcon(QIcon(":/img/bigMeeple.png"));

    QmlPresenter presenter;
    engine.rootContext()->setContextProperty("engine", &presenter);

    engine.load(url);
    return app.exec();
}
