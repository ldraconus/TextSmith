#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "fullscreen.h"

#include <QBasicTimer>
#include <QAction>
#include <QJsonObject>
#include <QMainWindow>
#include <QMessageBox>
#include <QtTextToSpeech/QTextToSpeech>
#include <QTreeWidgetItem>

#include <lua.hpp>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

extern QApplication& getApp();

class Scene {
private:
    QList<QString> _tags;
    QString _doc;
    QString _name;
    bool _root;
    int _wc;

public:
    Scene(const QString& n, bool r = false): _doc(""), _name(n), _root(r), _wc(0) { }
    Scene(const Scene& s) = default;
    Scene(Scene&& s) = default;
    virtual ~Scene() {}

    Scene& operator=(const Scene& x) = default;
    Scene& operator=(Scene&& x) = default;

    QList<QString>& tags() { return _tags; }

    QString doc() const    { return _doc; }
    QString doc(QString d) { _doc = d; return doc(); }

    QString name() const    { return _name; }
    QString name(QString n) { _name = n; return name(); }

    bool root() const { return _root; }
    bool root(bool r) { _root = r; return root(); }

    int wc() const { return _wc; }
    int wc(int w)  { _wc = w; return wc(); }
};

namespace Ui {
class FindDialog;
}

enum SearchType { byNone, bySelection, byScene, bySceneChildren, bySiblingChildren, byAll };

class FindDialog : public QDialog
{
    Q_OBJECT

public:
    explicit FindDialog(bool selection, QWidget *parent = nullptr);
    FindDialog(const FindDialog&) = delete;
    FindDialog(FindDialog&&) = delete;
    ~FindDialog() override;

    FindDialog& operator=(const FindDialog&) = delete;
    FindDialog& operator=(FindDialog&&) = delete;

    SearchType getType();
    QString getSearchString();
    void setSearchString(QString x);

public slots:
    void changedText(QString);

private:
    Ui::FindDialog *ui;
};


namespace Ui {
    class ReplaceDialog;
}

class ReplaceDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ReplaceDialog(bool selection, QWidget *parent = nullptr);
    ReplaceDialog(const ReplaceDialog&) = delete;
    ReplaceDialog(ReplaceDialog&&) = delete;
    ~ReplaceDialog() override;

    ReplaceDialog& operator=(const ReplaceDialog&) = delete;
    ReplaceDialog& operator=(ReplaceDialog&&) = delete;

    SearchType getType();
    QString getSearchString();
    QString getReplaceString();
    void setSearchString(QString x);
    void setReplaceString(QString x);

public slots:
    void changedText(const QString &text);

private:
    Ui::ReplaceDialog *ui;
};

class MainWindow : public QMainWindow {
    Q_OBJECT

public slots:
    void newMenuItem()    { newAction(); }
    void openMenuItem()   { openAction(); }
    void saveMenuItem()   { save(); }
    void saveAsMenuItem() { if (saveAs()) save(); }
    void aboutToShowExportMenu() { }
    void aboutToHideExportMenu() { }
    void pdfMenuItem()          { pdfAction(); }
    void epubMenuItem()         { epubAction(); }
    void htmlMenuItem()         { htmlAction(); }
    void markdownMenuItem()     { markdownAction(); }
    void rtfMenuItem()          { rtfAction(); }
    void standardTextMenuItem() { standardTextAction(); }
    void aboutToShowImportMenu() { }
    void aboutToHideImportMenu() { }
    void imageMenuItem() { imageAction(); }
    void textMenuItem()  { textAction(); }
    void exitClicked()    { close(); }

    void newSceneMenuItem()    { newSceneAction(); }
    void removeSceneMenuItem() { removeSceneAction(); }
    void moveUpMenuItem()      { moveUpAction(); }
    void moveDownMenuItem()    { moveDownAction(); }
    void moveInMenuItem()      { moveInAction(); }
    void moveOutMenuItem()     { moveOutAction(); }
    void tagsMenuItem()        { tagsAction(); }

    void undoMenuItem()             { undoAction(); }
    void redoMenuItem()             { redoAction(); }
    void cutMenuItem()              { cutAction(); }
    void copyMenuItem()             { copyAction(); }
    void pasteMenuItem()            { pasteAction(); }
    void searchMenuItem()           { findAction(); }
    void replaceMenuItem()          { replaceAction(); }
    void replaceSelectionMenuItem() { replaceSelectionAction(); }
    void replaceAllMenuItem()       { replaceAllAction(); }
    void findNextMenuItem()         { findNextAction(); }
    void boldMenuItem()             { boldAction(); }
    void italicMenuItem()           { italicAction(); }
    void underlineMenuItem()        { underlineAction(); }
    void leftJustifyMenuItem()      { leftJustifyAction(); }
    void centerMenuItem()           { centerAction(); }
    void fullJustifyMenuItem()      { fullJustifyAction(); }
    void rightJustifyMenuItem()     { rightJustifyAction(); }
    void indentMenuItem()           { indentAction(); }

    void fullScreenMenuItem()  { fullScreenAction(); }
    void scriptsMenuItem()     { scriptsAction(); }
    void wordCountMenuItem()   { wordCountAction(); }
    void readAloudMenuItem()   { readAloudAction(); }

    void aboutMenuItem()         { aboutAction(); }
    void documentationMenuItem() { documentationAction(); }
    void optionsMenuItem()       { optionsAction(); }

    void currentItemChanged(QTreeWidgetItem* current, QTreeWidgetItem* previous) { itemChangedAction(current, previous); }
    void itemDoubleClicked(QTreeWidgetItem* current, int column)                 { itemDoubleClickedAction(current, column); }

    void redoAvailable(bool available) { redoAvailableAction(available); }
    void setEditButtons();
    void undoAvailable(bool available) { undoAvailableAction(available); }
    void textChanged();

    void autoSave();
    void checkDarkMode();
    void cleanIt() { _cleanItTimer->stop(); clean(); };

public:
    explicit MainWindow(const QString& file, QWidget *parent = nullptr);
    MainWindow(const MainWindow&) = delete;
    MainWindow(MainWindow&&) = delete;
    ~MainWindow() override;

    MainWindow& operator=(const MainWindow&) = delete;
    MainWindow& operator=(MainWindow&&) = delete;

private:
    QRect _aboutDialog   { -1, -1, 0, 0 };
    QRect _findDialog    { -1, -1, 0, 0 };
    QRect _optionsDialog { -1, -1, 0, 0 };
    QRect _replaceDialog { -1, -1, 0, 0 };
    QRect _scriptsDialog { -1, -1, 0, 0 };
    QRect _tagsDialog    { -1, -1, 0, 0 };
    QList<int> _fullscreenDialog { 0, 0 };

public:
    static MainWindow* main_window() { return _main_window; }

    QRect& tagsDialog()      { return _tagsDialog; }
    QString dir()            { return _dir; }
    QTextToSpeech* speech()  { return _speech; }
    Scene& scene(int idx)    { return _scenes[idx]; }
    bool typewriterSounds()  { return _typewriterSounds; }
    void dir(QString x)      { _dir = x; }
    void filename(QString x) { _filename = x; }
    void message(QString x);

    class Position {
    private:
        int _scene;
        int _offset;

    public:
        Position(int s = -1, int o = -1): _scene(s), _offset(o) { }
        Position(const Position& p) = default;
        Position(Position&& p) = default;
        virtual ~Position() { }

        Position& operator=(const Position& p) = default;
        Position& operator=(Position&& p) = default;

        bool unset() { return _scene == -1 && _offset == -1; }

        int scene(int s = -1) { if (s >= 0) _scene = s; return _scene; }
        int offset(int o = -1) { if (o >= 0) _offset = o; return _offset; }

        void nil() { _scene = _offset = -1; }
    };

    class Search {
    private:
        SearchType _range {};
        Position _current {};
        Position _start {};
        Position _stop {};
        QList<int> _stack;
        QString _look;
        QString _with;

        void init(SearchType r);

    public:
        Search(): _range(byNone), _look("") { }
        Search(QString& l, SearchType r);
        Search(QString& l, SearchType r, QString& w);

        Position current() { return _current; }
        Position findNext();
        Position findNextChild(Position current);
        QString look() { return _look; }
        QString with() { return _with; }
        bool searchValid() { return _range != byNone; }
        void current(Position& f) { _current = f; }
        void invalidate() { _range = byNone; }
        void set(QString l, SearchType r) { _look = l; init(r); }
        void set(QString l, QString w, SearchType r) { _look = l; _with = w, init(r); }
    };

private:
    Ui::MainWindow *ui;

    // Saved
    QList<Scene> _scenes;
    QRect _ok          { -1, -1, 0, 0 };
    QRect _okcancel    { -1, -1, 0, 0 };
    QRect _question    { -1, -1, 0, 0 };
    QRect _statement   { -1, -1, 0, 0 };
    QRect _yesno       { -1, -1, 0, 0 };
    QRect _yesnocancel { -1, -1, 0, 0 };
    QString _dir = "";
    QString _textFont = "Segoe UI:9";
    QTextToSpeech* _speech;
    bool _autosave = false;
    bool _openItems = false;
    bool _typewriterSounds = false;
    int _autosaveInterval = 0;
    int _voice = -1;

    // Not saved
    enum displayMode { None, Dark, Light };

    typedef unsigned short ATOM;

    ATOM _appAtom { };
    ATOM _systemTopicAtom { };
    QMap<QMenu*, QMap<displayMode, QString>> _menuIcons;
    QMap<QAction*, QMap<displayMode, QString>> _actionIcons;
    QMap<QString, QAction*> _buttons;
    QString _appAtomName;
    QString _filename = "";
    QString _systemTopicAtomName;
    QBasicTimer* _autoSaveTimer;
    QBasicTimer* _cleanItTimer;
    Search _request {};
    bool _dirty = false;
    bool _ignore = false;
    int _totalWc {};
    lua_State* _L {};

    QTreeWidgetItem* getItemByItemIndex(QTreeWidgetItem* item, int idx);
    void clean();
    void dirty();
    void createToolBarItem(QToolBar* tb, const QString icon, const QString name, const QString tip, const char* signal, const char* slot);
    void enableShellOpen();
    void registerExtensionHandler();
    void registerSignals();
    void setMenuIcons(QAction* action, QString icon, QString darkIcon);
    void setMenuIcons(QMenu* menu, QString icon, QString darkIcon);
    void setMoveButtons();
    void setWinTitle();
    void switchIcons(displayMode to);
    bool windowsDarkThemeAvailable();
    bool windowsIsInDarkTheme();

    static constexpr int BaseTextIndent = 20;
    static constexpr int Minutes = 60000;

public:
    lua_State* Lua() { return _L; }
    QJsonArray listToArray(QList<int> sizes);
    QList<int> arrayToList(QJsonArray sizes);
    QJsonObject dialogToObject(QRect& x);
    QJsonObject itemToObject(const QTreeWidgetItem* scene);
    QJsonObject sceneToObject(Scene& scene);
    QJsonObject widgetToObject(QWidget* w);
    QList<int> getChildren(int idx);
    QTreeWidgetItem* getItemByIndex(int idx);
    QTreeWidgetItem* objectToItem(const QJsonObject& obj, int& total);
    Scene objectToScene(const QJsonObject& obj);
    Ui::MainWindow *UI() { return ui; }
    bool checkClose();
    bool save();
    bool saveAs();
    int OKCancel(const char* msg, const char* title = nullptr);
    int OK(const char* msg, const char* title = nullptr);
    int Question(const char* msg, const char* title, QFlags<QMessageBox::StandardButton> buttons);
    int Statement(const char* msg);
    int YesNoCancel(const char* msg, const char* title = nullptr);
    int YesNo(const char* msg, const char* title = nullptr);
    int countWords(int idx);
    int getParent(int idx);
    void aboutAction();
    void boldAction();
    void centerAction();
    void checkScreens(QRect& r);
    void copyAction();
    void cutAction();
    void documentationAction();
    void epubAction();
    void findAction();
    void findNextAction();
    void fullJustifyAction();
    void fullScreenAction();
    void htmlAction();
    void imageAction();
    void italicAction();
    void indentAction();
    void itemChangedAction(QTreeWidgetItem* current, QTreeWidgetItem* previous);
    void itemDoubleClickedAction(QTreeWidgetItem* current, int column);
    void leftJustifyAction();
    void loadOptions();
    void markdownAction();
    void moveDownAction();
    void moveInAction();
    void moveOutAction();
    void moveUpAction();
    void newAction();
    void newSceneAction();
    void openAction(QString file = "");
    void openAllItems();
    void openItem(QTreeWidgetItem* item);
    void objectToWidget(const QJsonObject& widget, QWidget* w);
    void optionsAction();
    void pasteAction();
    void pdfAction();
    void readAloudAction();
    void redoAction();
    void redoAvailableAction(bool available);
    void removeSceneAction();
    void replaceAction();
    void replaceAllAction();
    void replaceSelectionAction();
    void rightJustifyAction();
    void rtfAction();
    void saveDialog(QDialog* dig, QRect& rect);
    void saveOptions();
    void setAllScenes(QTreeWidgetItem* root, QString font, int pnts);
    void setScene(QTreeWidgetItem* scene, QString font, int pnts);
    void setParagraphIndent();
    void setupDialog(QDialog* dig, QRect& rect);
    void scriptsAction();
    void standardTextAction();
    void syncFullScreen(FullScreen& dlg);
    void syncScene();
    void tagsAction();
    void textAction();
    void toDialog(const QJsonObject& windows, const QString& name, QRect& dlg);
    void underlineAction();
    void undoAction();
    void undoAvailableAction(bool available);
    void wordCountAction();

    void closeEvent(QCloseEvent* event) override;
    void keyReleaseEvent(QKeyEvent* event) override;
    void timerEvent(QTimerEvent* event) override;

private:
    static MainWindow* _main_window; // NOLINT

#include <connect>

};
#endif // MAINWINDOW_H
