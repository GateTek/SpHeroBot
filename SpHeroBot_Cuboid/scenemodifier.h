#ifndef SCENEMODIFIER_H
#define SCENEMODIFIER_H

#include <QtCore/QObject>

#include <Qt3DCore/qentity.h>
#include <Qt3DCore/qtransform.h>

#include <Qt3DExtras/QCuboidMesh>
#include <Qt3DExtras/QPhongMaterial>

class SceneModifier : public QObject
{
    Q_OBJECT

public:
    explicit SceneModifier(Qt3DCore::QEntity *rootEntity);
    ~SceneModifier();

public slots:
    void enableCuboid(bool enabled);

private:
    Qt3DCore::QEntity *m_rootEntity;
    Qt3DCore::QEntity *m_cuboidEntity;
};

#endif // SCENEMODIFIER_H

