#include "textureloader.h"


#include <QApplication>
#include <QDir>
#include <QDebug>

#include <IL/il.h>
#include <IL/ilu.h>
#include <IL/ilut.h>


TextureLoader::TextureLoader()
{
}

void TextureLoader::init()
{
    ilutRenderer(ILUT_OPENGL);
    ilInit();
    iluInit();
    ilutInit();
    ilutRenderer(ILUT_OPENGL);
}

void TextureLoader::load_textures()
{
    QDir dir = QApplication::applicationDirPath();
    qDebug() << dir.absolutePath();
    if (!dir.cd("../resourses"))
    {
        qDebug() << "resourses directory not found";
        return;
    }

    foreach (QString file, dir.entryList(QDir::Files)) {
        qDebug() << file;
        textures[file] = load(dir.absoluteFilePath(file));
    }

}

GLuint TextureLoader::texture(const QString &name) const
{
    if (textures.contains(name))
        return textures[name];

    qDebug() << "no such texture";
    return -1;
}

GLuint TextureLoader::load(const QString &file_name)
{
    ILuint image_id;
    GLuint texture_id;
    ILboolean success;
    ILenum error;
    ilGenImages(1, &image_id);
    ilBindImage(image_id);
    success = ilLoadImage(file_name.toStdString().c_str());
    if (success)
    {
        ILinfo image_info;
        iluGetImageInfo(&image_info);
        if (image_info.Origin == IL_ORIGIN_UPPER_LEFT)
            iluFlipImage();

        success = ilConvertImage(IL_RGB, IL_UNSIGNED_BYTE);
        if (!success)
        {
            error = ilGetError();
            qDebug() << "image " << file_name << " convertion faild:" << error << "-" << iluErrorString(error);
            return -1;
        }

        glGenTextures(1, &texture_id);
        glBindTexture(GL_TEXTURE_2D, texture_id);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

        glTexImage2D(GL_TEXTURE_2D,
                     0,
                     ilGetInteger(IL_IMAGE_FORMAT),
                     ilGetInteger(IL_IMAGE_WIDTH),
                     ilGetInteger(IL_IMAGE_HEIGHT),
                     0,
                     ilGetInteger(IL_IMAGE_FORMAT),
                     GL_UNSIGNED_BYTE,
                     ilGetData());
    }
    else
    {
        error = ilGetError();
        qDebug() << "image " << file_name << " load failed: " << error << "-" << iluErrorString(error);
        return -1;
    }
    ilDeleteImages(1, &image_id);
    qDebug() << "texture - " << file_name << " : success";
    return texture_id;
}



