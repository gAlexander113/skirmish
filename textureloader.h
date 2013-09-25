#ifndef TEXTURELOADER_H
#define TEXTURELOADER_H

#include <GL/gl.h>
#include <GL/glu.h>

#include <QString>
#include <QMap>

class TextureLoader
{
public:
    TextureLoader();

    void init();
    void load_textures();
    GLuint texture(const QString &name) const;

private:
    QMap<QString, GLuint> textures;

    GLuint load(const QString &file_name);
};

#endif // TEXTURELOADER_H
