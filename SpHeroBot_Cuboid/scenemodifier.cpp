#include "scenemodifier.h"

#include <QtCore/QDebug>

/**
 * @brief SceneModifier::SceneModifier costruttore di SceneModifier
 * @param rootEntity QEntity
 */
SceneModifier::SceneModifier(Qt3DCore::QEntity *rootEntity)
    : m_rootEntity(rootEntity)
{

    // Cuboid shape data
    Qt3DExtras::QCuboidMesh *cuboid = new Qt3DExtras::QCuboidMesh();

    // CuboidMesh Transform
    Qt3DCore::QTransform *cuboidTransform = new Qt3DCore::QTransform();
    cuboidTransform->setScale(4.0f);
    cuboidTransform->setTranslation(QVector3D(0.0f, 0.0f, 0.0f));

    Qt3DExtras::QPhongMaterial *cuboidMaterial = new Qt3DExtras::QPhongMaterial();
    cuboidMaterial->setDiffuse(QColor(QRgb(0x665423)));

    //Cuboid
    m_cuboidEntity = new Qt3DCore::QEntity(m_rootEntity);
    m_cuboidEntity->addComponent(cuboid);
    m_cuboidEntity->addComponent(cuboidMaterial);
    m_cuboidEntity->addComponent(cuboidTransform);

}
/**
 * @brief SceneModifier::~SceneModifier distruttore di SceneModifier
 */
SceneModifier::~SceneModifier(){}

/**
 * @brief SceneModifier::enableCuboid abilita o non abilita la visione del cuboide
 * @param enabled bool
 */
void SceneModifier::enableCuboid(bool enabled)
{
    m_cuboidEntity->setEnabled(enabled);
}

