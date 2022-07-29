#ifndef TEXTEDIT_H
#define TEXTEDIT_H

#include <QFileInfo>
#include <QKeyEvent>
#include <QImageReader>
#include <QImageWriter>
#include <QMap>
#include <QMimeData>
#include <QTextEdit>

//====[Custom Widget]=============================================
class TextEdit : public QTextEdit {
private:
    QMap<QUrl, QImage> Images;
    bool NewImages = false;
    const bool Save = true;
    QString _dir = ".";
    static size_t _base;
    bool _allowTextPaste = false;

    QImage loadImage(const QUrl& url) {
        QString path = url.adjusted(QUrl::RemoveFilename).path();
        if (path.isEmpty()) path = _dir;
        QString filename = url.fileName();
        if (filename.right(3) != "jpg") filename += ".jpg";
        QImageReader reader(path + "/" + filename, "jpg");
        QImage img = reader.read();
        document()->addResource(QTextDocument::ImageResource, url, img);
        return img;
    }

    void saveImage(const QUrl& url, const QImage& img) {
        QString path = url.adjusted(QUrl::RemoveFilename).path();
        if (path.isEmpty()) path = _dir;
        QString filename = url.fileName();
        if (filename.right(3) != "jpg") filename += ".jpg";
        QImageWriter writer(path + "/" + filename, "jpg");
        writer.write(img);
    }

    void dropImage(const QString& file, const QImage& image, bool save = false) {
        if (!image.isNull()) {
            if (save) {
                Images[file] = image;
                NewImages = true;
            }
            document()->addResource(QTextDocument::ImageResource, file, image);
            textCursor().insertImage(file);
        }
    }

    void dropImage(const QUrl& url, const QImage& image, bool save = false) {
        if (!image.isNull()) {
            if (save) {
                Images[url] = image;
                NewImages = true;
            }
            document()->addResource(QTextDocument::ImageResource, url, image);
            textCursor().insertImage(url.toString());
        }
    }

    void dropTextFile(const QUrl& url) {
        QString path = url.adjusted(QUrl::RemoveFilename).path();
        if (path.isEmpty()) path = _dir;
        else if (path.right(1) != "/") path += "/";
        QFile file(path + url.fileName());
        if (file.open(QIODevice::ReadOnly | QIODevice::Text)) textCursor().insertText(file.readAll());
    }

public:
    TextEdit(QString dir = ".", QWidget* parent = nullptr): QTextEdit(parent) {
        _dir = dir;
        document()->setResourceProvider([this](const QUrl& url) -> QVariant { return loadImage(url); });
        if (_base == 0) _base = time(nullptr);
    }

    TextEdit(QWidget* parent = nullptr): QTextEdit(parent) {
        _dir = ".";
        document()->setResourceProvider([this](const QUrl& url) -> QVariant { return loadImage(url); });
        if (_base == 0) _base = time(nullptr);
    }

    void insertFromMimeData(const QMimeData* source) override {
        if (source->hasImage()) {
            static size_t i = _base;
            QUrl url(QString("dropped_image_%1").arg(i++));
            dropImage(url, qvariant_cast<QImage>(source->imageData()), Save);
        } else if (source->hasUrls()) {
            foreach (QUrl url, source->urls()) {
                QFileInfo info(url.fileName());
                if (QImageReader::supportedImageFormats().contains(info.suffix().toLower().toLatin1())) dropImage(url, QImage(info.filePath()));
                else dropTextFile(url);
            }
        } else if (_allowTextPaste) QTextEdit::insertFromMimeData(source);
    }

    void saveImages() {
        for (auto x = Images.begin(); x != Images.end(); ++x) saveImage(x.key(), x.value());
        NewImages = false;
    }

    bool canInsertFromMimeData(const QMimeData* source) const override { return source->hasImage() || source->hasUrls() || QTextEdit::canInsertFromMimeData(source); }
    bool hasNewImages()                                                { return NewImages; }
    void allowTextPaste()                                              { _allowTextPaste = true; }
    void denyTextPaste()                                               { _allowTextPaste = false; }
    void insertFromFile(const QString& file)                           { dropImage(file, QImage(file)); }
    void setDir(QString dir)                                           { _dir = dir; }
};
//=================================================================

#endif // TEXTEDIT_H
