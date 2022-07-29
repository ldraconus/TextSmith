#include "optionsdialog.h"
#include "mainwindow.h"
#include "ui_optionsdialog.h"

#include <QFontDialog>

OptionsDialog* OptionsDialog::_options = nullptr;

OptionsDialog::OptionsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::OptionsDialog)
{
    ui->setupUi(this);
    _options = this;

    _speech = MainWindow::main_window()->speech();
    auto voices = _speech->availableVoices();
    QStringList available;
    for (const auto& x: voices) available.push_back(x.name());
    ui->voiceComboBox->addItems(available);

    connect(ui->fontButton, SIGNAL(clicked(bool)), SLOT(fontClicked(bool)));

    connect(ui->voiceComboBox, SIGNAL(currentIndexChanged(int)), SLOT(currentIndexChanged(int)));
}

OptionsDialog::~OptionsDialog()
{
    delete ui;
}

bool OptionsDialog::autoSave() {
    return ui->autoSaveCheckBox->isChecked();
}

int OptionsDialog::autosaveInterval() {
    return ui->minuteSpinBox->value();
}

bool OptionsDialog::openItems() {
    return ui->openCheckBox->isChecked();
}

QString OptionsDialog::textFont() {
    return _font;
}

bool OptionsDialog::typewriterSounds() {
    return ui->soundsCheckBox->isChecked();
}

void OptionsDialog::setAutoSave(bool autosave, int autosaveInterval) {
    ui->autoSaveCheckBox->setChecked(autosave);
    ui->minuteSpinBox->setValue(autosaveInterval);
}

void OptionsDialog::setOpenItems(bool openItems) {
    ui->openCheckBox->setChecked(openItems);
}

void OptionsDialog::setTextFont(QString textFont) {
    _font = textFont;
    int pos = textFont.indexOf(":");
    QString font = textFont.left(pos);
    QString str = textFont.mid(pos + 1);
    int pnts = str.toInt();
    ui->fontExampleTextEdit->selectAll();
    ui->fontExampleTextEdit->setFontFamily(font);
    ui->fontExampleTextEdit->setFontPointSize(pnts);
    auto cursor = ui->fontExampleTextEdit->textCursor();
    cursor.setPosition(0);
    ui->fontExampleTextEdit->setTextCursor(cursor);
    ui->fontExampleTextEdit->ensureCursorVisible();
}

void OptionsDialog::setTypewriterSounds(bool typewriterSounds) {
    ui->soundsCheckBox->setChecked(typewriterSounds);
}

void OptionsDialog::setVoice(int voice) {
    _speakOff = true;
    ui->voiceComboBox->setCurrentIndex(voice);
    _speakOff = false;
}

void OptionsDialog::currentIndexChanged(int x) {
    if (x == -1) return;
    _voice = x;
    auto voices = _speech->availableVoices();
    _speech->setVoice(voices[x]);
    if (_speakOff) return;
    _speech->say(ui->fontExampleTextEdit->toPlainText());
}

void OptionsDialog::fontClicked(bool) {
    QFontDialog dlg;
    dlg.exec();
    auto font = dlg.currentFont();
    setTextFont(QString::asprintf("%s:%d", font.family().toStdString().c_str(), font.pointSize()));
}

int OptionsDialog::voice() {
    return _voice;
}
