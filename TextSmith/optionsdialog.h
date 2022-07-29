#ifndef OPTIONSDIALOG_H
#define OPTIONSDIALOG_H

#include <QAction>
#include <QDialog>
#include <QtTextToSpeech/QTextToSpeech>

namespace Ui {
class OptionsDialog;
}

class OptionsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit OptionsDialog(QWidget *parent = nullptr);
    ~OptionsDialog();

    bool autoSave();
    int autosaveInterval();
    bool openItems();
    QString textFont();
    bool typewriterSounds();
    int voice();

    void setAutoSave(bool autosave, int autosaveInterval);
    void setOpenItems(bool openItems);
    void setTextFont(QString textFont);
    void setTypewriterSounds(bool typewriterSounds);
    void setVoice(int voice);

    static OptionsDialog* options() { return _options; }

private:
    Ui::OptionsDialog *ui;
    QString _font;
    QTextToSpeech* _speech;
    bool _speakOff = false;
    int _voice = -1;

    static OptionsDialog* _options;

#include "connect"

public slots:
    void currentIndexChanged(int);
    void fontClicked(bool);
};

#endif // OPTIONSDIALOG_H
