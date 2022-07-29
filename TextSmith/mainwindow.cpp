#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "aboutdialog.h"
#include "epub.h"
#include "html.h"
#include "markdown.h"
#include "optionsdialog.h"
#include "pdf.h"
#include "rtf.h"
#include "scriptsdialog.h"
#include "text.h"
#include "TextEdit.h"
#include "tagsdialog.h"

#include <QClipboard>
#include <QCloseEvent>
#include <QDesktopServices>
#include <QFileDialog>
#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QMessageBox>
#include <QOperatingSystemVersion>
#include <QScreen>
#include <QSettings>
#include <QStandardPaths>
#include <QTextStream>
#include <QTimer>

MainWindow* MainWindow::_main_window;

//====[lua Interface]=============================================
static int luaExit(lua_State* lua) {
    MainWindow* mw = MainWindow::main_window();
    lua_gettop(lua);
    mw->close();
    return 0;
}

static int luaNew(lua_State* lua) {
    MainWindow* mw = MainWindow::main_window();
    lua_gettop(lua);
    mw->newAction();
    return 0;
}

static int luaSave(lua_State* lua) {
    MainWindow* mw = MainWindow::main_window();
    lua_pushboolean(lua, mw->save());
    return 1;
}

static int luaSaveAs(lua_State* lua) {
    MainWindow* mw = MainWindow::main_window();
    switch(lua_gettop(lua)) {
    case 0:
        if (!mw->saveAs()) {
            lua_pushboolean(lua, false);
            return 1;
        }
        break;
    case 1:
        if (lua_type(lua, 1) != LUA_TSTRING) {
            lua_pushboolean(lua, false);
            return 1;
        }
        mw->filename(lua_tostring(lua, 1));
        break;
    default:
        if (lua_type(lua, 1) != LUA_TSTRING || lua_type(lua, 2) != LUA_TSTRING) {
            lua_pushboolean(lua, false);
            return 1;
        }
        mw->dir(lua_tostring(lua, 1));
        mw->filename(lua_tostring(lua, 2));
    }
    lua_pushboolean(lua, mw->save());
    return 1;
}

static bool msgArgs(lua_State* lua, const char*& msg, const char*& title) {
    switch (lua_gettop(lua)) {
    case 0: return false;
    case 1:
        if (lua_type(lua, 1) != LUA_TSTRING) return false;
        msg = lua_tostring(lua, 1);
        break;
    default:
        if (lua_type(lua, 1) != LUA_TSTRING || lua_type(lua, 2) != LUA_TSTRING) return false;
        msg = lua_tostring(lua, 1);
        title = lua_tostring(lua, 2);
    }
    return true;
}

static bool getInt(lua_State* lua, int& num) {
    switch (lua_gettop(lua)) {
    case 0: return false;
    default:
        if (lua_type(lua, 1) != LUA_TNUMBER) return false;
        num = lua_tonumber(lua, 1);
    }
    return true;
}

static int getIntAndOrTable(lua_State* lua, int& num, int& tbl) {
    switch (lua_gettop(lua)) {
    case 0: return 0;
    case 2:
        if (lua_type(lua, 2) != LUA_TTABLE) return 0;
        tbl = 2;
    case 1:
        if (lua_type(lua, 1) != LUA_TNUMBER) return 0;
        num = lua_tonumber(lua, 1);
        return lua_gettop(lua);
    }
    return 0;
}

static int luaYesNo(lua_State* lua) {
    MainWindow* mw = MainWindow::main_window();
    const char* msg = nullptr;
    const char* title = nullptr;
    if (!msgArgs(lua, msg, title)) {
        lua_pushnumber(lua, -1);
        return 1;
    }
    switch (mw->YesNo(msg, title)) {
    case QMessageBox::Yes: lua_pushnumber(lua, 0);  break;
    case QMessageBox::No:  lua_pushnumber(lua, 1);  break;
    default:               lua_pushnumber(lua, -1); break;
    }

    return 1;
}

static int luaYesNoCancel(lua_State* lua) {
    MainWindow* mw = MainWindow::main_window();
    const char* msg = nullptr;
    const char* title = nullptr;
    if (!msgArgs(lua, msg, title)) {
        lua_pushnumber(lua, -1);
        return 1;
    }
    switch (mw->YesNoCancel(msg, title)) {
    case QMessageBox::Yes:    lua_pushnumber(lua, 0);  break;
    case QMessageBox::No:     lua_pushnumber(lua, 1);  break;
    case QMessageBox::Cancel: lua_pushnumber(lua, 2);  break;
    default:                  lua_pushnumber(lua, -1); break;
    }

    return 1;
}

static int luaOk(lua_State* lua) {
    MainWindow* mw = MainWindow::main_window();
    const char* msg = nullptr;
    const char* title = nullptr;
    if (!msgArgs(lua, msg, title)) {
        lua_pushnumber(lua, -1);
        return 1;
    }
    switch (mw->OK(msg, title)) {
    case QMessageBox::Ok: lua_pushnumber(lua, 0);  break;
    default:              lua_pushnumber(lua, -1); break;
    }

    return 1;
}

static int luaOkCancel(lua_State* lua) {
    MainWindow* mw = MainWindow::main_window();
    const char* msg = nullptr;
    const char* title = nullptr;
    if (!msgArgs(lua, msg, title)) {
        lua_pushnumber(lua, -1);
        return 1;
    }
    switch (mw->OKCancel(msg, title)) {
    case QMessageBox::Ok:     lua_pushnumber(lua, 0);  break;
    case QMessageBox::Cancel: lua_pushnumber(lua, 1);  break;
    default:                  lua_pushnumber(lua, -1); break;
    }

    return 1;
}

static int luaQuestion(lua_State* lua) {
    return luaYesNo(lua);
}

static int luaStatement(lua_State* lua) {
    return luaOk(lua);
}

static int luaCountWords(lua_State* lua) {
    MainWindow* mw = MainWindow::main_window();
    int idx;
    if (!getInt(lua, idx)) {
        lua_pushnumber(lua, -1);
        return 1;
    }
    int num = mw->countWords(idx);
    lua_pushnumber(lua, num);
    return 1;
}

static int luaGetParent(lua_State* lua) {
    MainWindow* mw = MainWindow::main_window();
    int idx;
    if (!getInt(lua, idx)) {
        lua_pushnumber(lua, -1);
        return 1;
    }
    int num = mw->getParent(idx);
    lua_pushnumber(lua, num);
    return 1;
}

static int lua_rootIndex(lua_State* lua)  {
    lua_gettop(lua);
    MainWindow* mw = MainWindow::main_window();
    QTreeWidget* tree = mw->UI()->treeWidget;
    QTreeWidgetItem* root = tree->topLevelItem(0);
    int rootIdx = root->data(0, Qt::ItemDataRole::UserRole).toInt();
    lua_pushnumber(lua, rootIdx);
    return 1;
}

static int lua_sceneChildren(lua_State* lua) {
    int idx;
    if (!getInt(lua, idx)) {
        lua_pushnumber(lua, -1);
        return 1;
    }
    MainWindow* mw = MainWindow::main_window();
    QTreeWidgetItem* item = mw->getItemByIndex(idx);
    int num = item->childCount();
    lua_createtable(lua, num, 0);
    int tbl = lua_gettop(lua);
    for (int i = 0; i < num; ++i) {
        QTreeWidgetItem* child = item->child(i);
        lua_pushinteger(lua, child->data(0, Qt::ItemDataRole::UserRole).toInt());
        lua_rawseti(lua, tbl, 1);
    }
    return 1;
}

static int lua_sceneTags(lua_State* lua) {
    int idx = 0;
    int tbl = 0;
    int args = getIntAndOrTable(lua, idx, tbl);
    if (args == 0) {
        lua_pushnumber(lua, -1);
        return 1;
    }
    MainWindow* mw = MainWindow::main_window();
    Scene& scene = mw->scene(idx);
    if (args == 2) {
        lua_rawlen(lua, tbl);
        int num = lua_tonumber(lua, tbl + 1);
        lua_pop(lua, 1);
        QList<QString> tags;
        for (int i = 1; i <= num; i++) {
            lua_geti(lua, tbl, i);
            QString x = lua_tostring(lua, tbl + 1);
            tags.append(x);
            lua_pop(lua, 1);
            scene.tags() = tags;
        }
        return 0;
    }
    int num = scene.tags().count();
    lua_createtable(lua, num, 0);
    tbl = lua_gettop(lua);
    for (int i = 0; i < num; ++i) {
        QString tag = scene.tags()[i];
        lua_pushstring(lua, tag.toStdString().c_str());
        lua_rawseti(lua, tbl, 1);
    }
    return 1;
}

// Let me edit a scene ts_Edit(idx, cursor[, len][, txt]) -- current scene == idx, then do it in the displayed textEdit, otherwise in a local textEdit, sync it back after, of course
static int lua_editScene(lua_State* lua) {
    int idx = 0;
    int cursor = 0;
    int len = 0;
    QString txt = "";
    switch (lua_gettop(lua)) {
    case 4:
        txt = lua_tostring(lua, 4);
    case 3:
        if (lua_isstring(lua, 3)) txt = lua_tostring(lua, 3);
        else len = lua_tonumber(lua, 3);
    case 2:
        cursor = lua_tonumber(lua, 2);
        idx = lua_tonumber(lua, 1);
        break;
    default:
        lua_pushnumber(lua, -1);
        return 1;
    }

    MainWindow::main_window()->syncScene();
    Scene& scene = MainWindow::main_window()->scene(idx);
    QTreeWidget* tree = MainWindow::main_window()->UI()->treeWidget;
    QTreeWidgetItem* current = tree->currentItem();
    int currentIdx = current->data(0, Qt::ItemDataRole::UserRole).toInt();
    TextEdit* edit = MainWindow::main_window()->UI()->textEdit;
    TextEdit local(MainWindow::main_window()->dir());
    if (currentIdx != idx) {
        edit = &local;
        edit->setHtml(scene.doc());
    }

    auto selection = edit->textCursor();
    selection.setPosition(cursor);
    selection.movePosition(QTextCursor::MoveOperation::NextCharacter, QTextCursor::MoveMode::KeepAnchor, len);
    edit->setTextCursor(selection);
    edit->insertPlainText(txt);
    scene.doc(edit->toHtml());

    lua_pushnumber(lua, 0);
    return 1;
}

static int lua_setScene(lua_State* lua) {
    int idx = 0;
    switch (lua_gettop(lua)) {
    case 1:
        idx = lua_tonumber(lua, 1);
        break;
    default:
        lua_pushnumber(lua, -1);
        return 1;
    }

    QTreeWidget* tree = MainWindow::main_window()->UI()->treeWidget;
    QTreeWidgetItem* item = MainWindow::main_window()->getItemByIndex(idx);
    tree->setCurrentItem(item);

    lua_pushnumber(lua, 0);
    return 1;
}

static int lua_getScene(lua_State* lua) {
    switch (lua_gettop(lua)) {
    case 0: break;
    default:
        lua_pushnumber(lua, -1);
        return 1;
    }

    QTreeWidget* tree = MainWindow::main_window()->UI()->treeWidget;
    QTreeWidgetItem* item = tree->currentItem();
    int currentIdx = item->data(0, Qt::ItemDataRole::UserRole).toInt();
    lua_pushnumber(lua, currentIdx);
    return 1;
}

static int lua_getText(lua_State* lua) {
    int idx = 0;
    if (lua_gettop(lua) != 1) {
        lua_pushnumber(lua, -1);
        return 1;
    }
    else idx = lua_tonumber(lua, 1);
    MainWindow::main_window()->syncScene();
    Scene& scene = MainWindow::main_window()->scene(idx);
    TextEdit edit(MainWindow::main_window()->dir());
    edit.setHtml(scene.doc());
    QString txt = edit.toPlainText();
    lua_pushstring(lua, txt.toStdString().c_str());
    return 1;

}

static int lua_getHtml(lua_State* lua) {
    int idx = 0;
    if (lua_gettop(lua) != 1) {
        lua_pushnumber(lua, -1);
        return 1;
    }
    else idx = lua_tonumber(lua, 1);
    MainWindow::main_window()->syncScene();
    Scene& scene = MainWindow::main_window()->scene(idx);
    lua_pushstring(lua, scene.doc().toStdString().c_str());
    return 1;

}

// Give me/let me set the name of the scene ts_Name(txt[, str])
static int lua_sceneName(lua_State* lua) {
    int idx = 0;
    QString txt = "";
    switch (lua_gettop(lua)) {
    case 2:
        txt = lua_tostring(lua, 2);
    case 1:
        idx = lua_tonumber(lua, 1);
        break;
    default:
        lua_pushnumber(lua, -1);
        return 1;
    }

    MainWindow::main_window()->syncScene();
    Scene& scene = MainWindow::main_window()->scene(idx);
    if (!txt.isEmpty()) {
        QTreeWidgetItem* item = MainWindow::main_window()->getItemByIndex(idx);
        scene.name(txt);
        item->setText(0, txt);
        lua_pushnumber(lua, 0);
    } else lua_pushstring(lua, scene.name().toStdString().c_str());
    return 1;
}

#define SIMPLE_LUA(x) static int lua_##x(lua_State*) {\
    MainWindow* mw = MainWindow::main_window();\
    mw->x();\
    return 0;\
}

SIMPLE_LUA(aboutAction)
SIMPLE_LUA(boldAction)
SIMPLE_LUA(centerAction)
SIMPLE_LUA(copyAction)
SIMPLE_LUA(cutAction)
SIMPLE_LUA(epubAction)
SIMPLE_LUA(findAction)
SIMPLE_LUA(findNextAction)
SIMPLE_LUA(fullJustifyAction)
SIMPLE_LUA(fullScreenAction)
SIMPLE_LUA(htmlAction)
SIMPLE_LUA(imageAction)
SIMPLE_LUA(italicAction)
SIMPLE_LUA(indentAction)
SIMPLE_LUA(leftJustifyAction)
SIMPLE_LUA(markdownAction)
SIMPLE_LUA(moveDownAction)
SIMPLE_LUA(moveInAction)
SIMPLE_LUA(moveOutAction)
SIMPLE_LUA(moveUpAction)
SIMPLE_LUA(newAction)
SIMPLE_LUA(newSceneAction)
SIMPLE_LUA(openAction)
SIMPLE_LUA(optionsAction)
SIMPLE_LUA(pasteAction)
SIMPLE_LUA(pdfAction)
SIMPLE_LUA(redoAction)
SIMPLE_LUA(removeSceneAction)
SIMPLE_LUA(replaceAction)
SIMPLE_LUA(replaceAllAction)
SIMPLE_LUA(replaceSelectionAction)
SIMPLE_LUA(rightJustifyAction)
SIMPLE_LUA(rtfAction)
SIMPLE_LUA(tagsAction)
SIMPLE_LUA(underlineAction)
SIMPLE_LUA(undoAction)

//-----------------------------------------------------------------
static void luaRegister(lua_State* lua, lua_CFunction func, const char* name) {
    lua_pushcfunction(lua, func);
    lua_setglobal(lua, name);
}

static void registerFunctions(lua_State* lua) {
    luaRegister(lua, luaExit,                    "ts_Exit");
    luaRegister(lua, luaNew,                     "ts_New");
    luaRegister(lua, luaSave,                    "ts_save");
    luaRegister(lua, luaSaveAs,                  "ts_saveAs");
    luaRegister(lua, luaYesNo,                   "ts_YesNo");
    luaRegister(lua, luaYesNoCancel,             "ts_YesNoCancel");
    luaRegister(lua, luaOk,                      "ts_Ok");
    luaRegister(lua, luaOkCancel,                "ts_OkCancel");
    luaRegister(lua, luaQuestion,                "ts_Question");
    luaRegister(lua, luaStatement,               "ts_Statement");
    luaRegister(lua, luaCountWords,              "ts_CountWords");
    luaRegister(lua, luaGetParent,               "ts_GetParent");
    luaRegister(lua, lua_aboutAction,            "ts_About");
    luaRegister(lua, lua_boldAction,             "ts_Bold");
    luaRegister(lua, lua_centerAction,           "ts_Center");
    luaRegister(lua, lua_copyAction,             "ts_Copy");
    luaRegister(lua, lua_cutAction,              "ts_Cut");
    luaRegister(lua, lua_epubAction,             "ts_EPUB");
    luaRegister(lua, lua_findAction,             "ts_Find");
    luaRegister(lua, lua_findNextAction,         "ts_FindNext");
    luaRegister(lua, lua_fullJustifyAction,      "ts_FullJustify");
    luaRegister(lua, lua_fullScreenAction,       "ts_FullScreen");
    luaRegister(lua, lua_htmlAction,             "ts_HTML");
    luaRegister(lua, lua_imageAction,            "ts_Image");
    luaRegister(lua, lua_italicAction,           "ts_Italic");
    luaRegister(lua, lua_indentAction,           "ts_Indent");
    luaRegister(lua, lua_leftJustifyAction,      "ts_LeftJustify");
    luaRegister(lua, lua_markdownAction,         "ts_MARKDOWN");
    luaRegister(lua, lua_moveDownAction,         "ts_moveDown");
    luaRegister(lua, lua_moveInAction,           "ts_moveIn");
    luaRegister(lua, lua_moveOutAction,          "ts_moveOut");
    luaRegister(lua, lua_moveUpAction,           "ts_moveUp");
    luaRegister(lua, lua_newAction,              "ts_New");
    luaRegister(lua, lua_newSceneAction,         "ts_NewScene");
    luaRegister(lua, lua_openAction,             "ts_Open");
    luaRegister(lua, lua_optionsAction,          "ts_Options");
    luaRegister(lua, lua_pasteAction,            "ts_Paste");
    luaRegister(lua, lua_pdfAction,              "ts_PDF");
    luaRegister(lua, lua_redoAction,             "ts_Redo");
    luaRegister(lua, lua_removeSceneAction,      "ts_RemoveScene");
    luaRegister(lua, lua_replaceAction,          "ts_Replace");
    luaRegister(lua, lua_replaceAllAction,       "ts_ReplaceAll");
    luaRegister(lua, lua_replaceSelectionAction, "ts_ReplaceAll");
    luaRegister(lua, lua_rightJustifyAction,     "ts_RightJustify");
    luaRegister(lua, lua_rtfAction,              "ts_RFT");
    luaRegister(lua, lua_tagsAction,             "ts_Tags");
    luaRegister(lua, lua_underlineAction,        "ts_Underline");
    luaRegister(lua, lua_undoAction,             "ts_Undo");
    luaRegister(lua, lua_rootIndex,              "ts_RootIndex");
    luaRegister(lua, lua_sceneChildren,          "ts_SceneChildren");
    luaRegister(lua, lua_sceneTags,              "ts_SceneTags");
    luaRegister(lua, lua_editScene,              "ts_EditScene");
    luaRegister(lua, lua_setScene,               "ts_SetScene");
    luaRegister(lua, lua_getScene,               "ts_GetScene");
    luaRegister(lua, lua_getText,                "ts_GetText");
    luaRegister(lua, lua_getHtml,                "ts_GetHtml");
    luaRegister(lua, lua_sceneName,              "ts_SceneName");
}

//=================================================================

//====[Message Box]================================================
static int showMsgBox(QMessageBox& msgBox, QRect& save) {
    QRect pos = msgBox.geometry();
    int width = pos.width();
    int height = pos.height();
    if (save.top() >= 0) {
        pos.setTop(save.top());
        if (save.left() >= 0) pos.setLeft(save.left());
        pos.setWidth(width);
        pos.setHeight(height);
        msgBox.setGeometry(pos);
    }
    int res = msgBox.exec();
    pos = msgBox.geometry();
    save.setLeft(pos.left());
    save.setTop(pos.top());
    return res;
}

int MainWindow::YesNo(const char* msg, const char* title) {
    QMessageBox msgBox;
    msgBox.setIcon(QMessageBox::Question);
    msgBox.setText(title ? title : "Are you sure?");
    msgBox.setInformativeText(msg);
    msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    msgBox.setDefaultButton(QMessageBox::No);
    return showMsgBox(msgBox, _yesno);
}

int MainWindow::YesNoCancel(const char* msg, const char* title) {
    QMessageBox msgBox;
    msgBox.setIcon(QMessageBox::Question);
    msgBox.setText(title ? title : "Are you really sure?");
    msgBox.setInformativeText(msg);
    msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);
    msgBox.setDefaultButton(QMessageBox::Cancel);
    return showMsgBox(msgBox, _yesnocancel);
}

int MainWindow::OK(const char* msg, const char* title) {
    QMessageBox msgBox;
    msgBox.setIcon(QMessageBox::Warning);
    msgBox.setText(title ? title : "Something has happened.");
    msgBox.setInformativeText(msg);
    msgBox.setStandardButtons(QMessageBox::Ok);
    msgBox.setDefaultButton(QMessageBox::Ok);
    return showMsgBox(msgBox, _ok);
}

int MainWindow::OKCancel(const char* msg, const char* title) {
    QMessageBox msgBox;
    msgBox.setIcon(QMessageBox::Critical);
    msgBox.setText(title ? title : "Something bad is about to happened.");
    msgBox.setInformativeText(msg);
    msgBox.setStandardButtons(QMessageBox::Ok);
    msgBox.setDefaultButton(QMessageBox::Ok);
    return showMsgBox(msgBox, _okcancel);
}

int MainWindow::Question(const char* msg, const char* title, QFlags<QMessageBox::StandardButton> buttons) {
    QMessageBox msgBox;
    msgBox.setIcon(QMessageBox::Question);
    msgBox.setText(title ? title : "Are you sure?");
    msgBox.setInformativeText(msg);
    msgBox.setStandardButtons(buttons);
    return showMsgBox(msgBox, _question);
}

int MainWindow::Statement(const char* msg) {
    QMessageBox msgBox;
    msgBox.setInformativeText(msg);
    msgBox.setStandardButtons(QMessageBox::Ok);
    return showMsgBox(msgBox, _statement);
}
//=================================================================

//====[Utilities]=============================================
MainWindow::Search::Search(QString& l, SearchType r): _look(l), _with("") {
    init(r);
}

MainWindow::Search::Search(QString& l, SearchType r, QString& w): _look(l), _with(w) {
    init(r);
}

MainWindow::Position MainWindow::Search::findNextChild(Position current) {
    int at = current.scene();
    QList<int> children = MainWindow::main_window()->getChildren(at);
    if (!children.isEmpty()) {
        _stack.append(children[0]);
        return Position(children[0]);
    }

    _stack.pop_back();

    while (!_stack.isEmpty()) {
        int parentIdx = MainWindow::main_window()->getParent(at);
        children = MainWindow::main_window()->getChildren(parentIdx);
        int cnt = children.count() - 1;
        for (int x = 0; x < cnt; ++x) if (children[x] == at) {
            _stack.append(children[x + 1]);
            return Position(children[x + 1]);
        }
        at = _stack.last();
        _stack.pop_back();
    }

    return Position();
}

MainWindow::Position MainWindow::Search::findNext() {
    QTextEdit work;
    int idx = _current.scene();
    int offset = _current.offset();
    Scene& scene = MainWindow::main_window()->_scenes[idx];
    _current.nil();
    work.setHtml(scene.doc());
    for (; ; ) {
        int start = offset + 1;
        QString txt = work.toPlainText();
        int at = txt.indexOf(_look, start);
        if (at == -1) { // nothing left in this scene, get the next scene (if any)
            switch (_range) {
            case byNone:
            case bySelection:
            case byScene:
                return Position();
            case bySceneChildren:
            case bySiblingChildren:
            case byAll:
                {
                    Position next = findNextChild(Position(idx));
                    if (next.unset()) return Position();
                    idx = next.scene();
                    Scene& scene = MainWindow::main_window()->_scenes[idx];
                    work.setHtml(scene.doc());
                    offset = -1;
                }
                break;
            }
        }
        else {
            if (_range == bySelection) {
                if (at > _stop.offset() - _look.length() + 1) return Position();
            }
            return Position(idx, at);
        }
    }
}

void MainWindow::Search::init(SearchType r) {
    _stack.clear();
    _range = r;
    QTreeWidget* tree = MainWindow::main_window()->UI()->treeWidget;
    QTreeWidgetItem* current = tree->currentItem();
    int currentIdx = current->data(0, Qt::ItemDataRole::UserRole).toInt();

    switch (_range) {
    case bySelection:
        {
            QTextEdit* text = MainWindow::main_window()->UI()->textEdit;
            QTextCursor cursor = text->textCursor();
            int offset = cursor.selectionStart();
            int end = cursor.selectionEnd();
            _start.nil();
            _start.scene(currentIdx);
            _start.offset(offset);
            _stop.scene(currentIdx);
            _stop.offset(end);
        }
        break;
    case byScene:
    case bySceneChildren:
        _start.nil();
        _start.scene(currentIdx);
        break;
    case bySiblingChildren:
        {
            QTreeWidgetItem* parent = current->parent();
            int parentIdx = parent->data(0, Qt::ItemDataRole::UserRole).toInt();
            QList<int> children = MainWindow::main_window()->getChildren(parentIdx);
            _start.nil();
            _start.scene(children[0]);
        }
        break;
    case byAll:
        {
            QTreeWidgetItem* root = tree->topLevelItem(0);
            int rootIdx = root->data(0, Qt::ItemDataRole::UserRole).toInt();
            _start.nil();
            _start.scene(rootIdx);
        }
        break;
    case byNone:
        return;
    }

    _current = _start;
    _stack.append(_current.scene());
}

QList<int> MainWindow::arrayToList(QJsonArray sizes) {
    QList<int> list;
    for (int i = 0; i < sizes.count(); ++i) list.append(sizes[i].toInt());
    return list;
}

static int middle(int sw, int w) {
    return (sw - w) / 2;
}

static void adjustGeometry(QRect sr, QRect& r) {
    int topHeight = QApplication::style()->pixelMetric(QStyle::PM_TitleBarHeight);
    int windowFrame = QApplication::style()->pixelMetric(QStyle::PM_DefaultFrameWidth);
    if (sr.height() < r.height() + windowFrame + topHeight) {
        r.setTop(sr.top() + topHeight);
        r.setBottom(sr.bottom() - windowFrame);
    } else {
        int h = r.height();
        r.setTop(sr.top() + middle(sr.height(), h + topHeight + windowFrame));
        r.setHeight(h);
    }
    if (sr.width() < r.width() + 2 * windowFrame) {
        r.setLeft(sr.left() + windowFrame);
        r.setRight(sr.right() - windowFrame);
    } else {
        int w = r.width();
        r.setLeft(sr.left() + middle(sr.width(), w + 2 * windowFrame));
        r.setWidth(w);
    }
}

void MainWindow::checkScreens(QRect& r) {
    auto screens = screen()->virtualSiblings();

    for (const auto& x: screens) {
        QRect sr = x->geometry();
        if (sr.contains(r)) return;
    }

    for (const auto& x: screens) {
        QRect sr = x->geometry();
        if (sr.contains(r.topLeft()) ||
            sr.contains(r.topRight()) ||
            sr.contains(r.bottomLeft()) ||
            sr.contains(r.bottomRight())) {
            adjustGeometry(sr, r);
            return;
        }
    }

    bool first = true;
    double dist = 0;
    auto scr = screens[0];
    for (const auto& x: screens) {
        QRect sr = x->geometry();
        double d = sqrt(sr.topLeft().dotProduct(r.topLeft(), sr.topLeft()));
        if (first) {
            first = false;
            dist = d;
            scr = x;
        } else if (d < dist) {
            dist = d;
            scr = x;
        }
    }
    QRect sr = scr->geometry();
    adjustGeometry(sr, r);
}

void MainWindow::clean() {
    _dirty = false;
    ui->action_Save->setEnabled(_dirty);
}

int MainWindow::countWords(int idx) {
    QTreeWidget* tree = ui->treeWidget;
    QTreeWidgetItem* root = tree->topLevelItem(0);
    int rootIdx = root->data(0, Qt::ItemDataRole::UserRole).toInt();

    TextEdit txt(_dir);
    int wc = 0;
    if (idx != rootIdx) {
        txt.setHtml(_scenes[idx].doc());
        QString text = txt.toPlainText();
        bool inWord = false;
        for (int i = 0; i < text.length(); ++i) if (text[i].isSpace()) {
            if (inWord) {
                ++wc;
                inWord = false;
            }
        } else inWord = true;
        if (inWord) ++wc;
        _scenes[idx].wc(wc);
    }
    return wc;
}

QJsonObject MainWindow::dialogToObject(QRect& x) {
    QJsonObject o;
    o.insert("left", x.left());
    o.insert("top", x.top());
    return o;
}

void MainWindow::dirty() {
    _dirty = true;
    ui->action_Save->setEnabled(_dirty);
    setEditButtons();
}

QList<int> MainWindow::getChildren(int idx)
{
    QList<int> children;
    QTreeWidgetItem* item = getItemByIndex(idx);
    int count = item->childCount();
    for (int i = 0; i < count; ++i) children.append(item->child(i)->data(0, Qt::ItemDataRole::UserRole).toInt());
    return children;
}

QTreeWidgetItem* MainWindow::getItemByItemIndex(QTreeWidgetItem* item, int idx) {
    if (item->data(0, Qt::ItemDataRole::UserRole).toInt() == idx) return item;
    int count = item->childCount();
    for (int i = 0; i < count; ++i) {
        QTreeWidgetItem* found = getItemByItemIndex(item->child(i), idx);
        if (found) return found;
    }
    return nullptr;
}

QTreeWidgetItem* MainWindow::getItemByIndex(int idx) {
    QTreeWidget* tree = findChild<QTreeWidget*>("treeWidget");
    QTreeWidgetItem* root = tree->topLevelItem(0);
    return getItemByItemIndex(root, idx);
}

int MainWindow::getParent(int idx)
{
    QTreeWidgetItem* item = getItemByIndex(idx);
    QTreeWidgetItem* parent = item->parent();
    return parent->data(0, Qt::ItemDataRole::UserRole).toInt();
}

QJsonObject MainWindow::itemToObject(const QTreeWidgetItem* scene) {
    int idx = scene->data(0, Qt::ItemDataRole::UserRole).toInt();
    QJsonObject sceneObject = sceneToObject(_scenes[idx]);
    QJsonArray children;
    int num = scene->childCount();
    for (int i = 0; i < num; ++i) children.append(itemToObject(scene->child(i)));
    sceneObject.insert("children", children);
    return sceneObject;
}

void MainWindow::loadOptions() {
    QString dir = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    QDir dirOp;
    dirOp.mkpath(dir);
    QFile file(dir + "/options.json");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) return;

    QByteArray data(file.readAll());
    QString jsonStr(data);
    file.close();
    QJsonDocument json = QJsonDocument::fromJson(jsonStr.toUtf8());

    // scan the json structure in for valid novel
    const QJsonObject& top = json.object();
    if (top.contains("options")) {
        QJsonObject options = top["options"].toObject();
        _openItems = options["openCheckbox"].toBool();
        _autosave = options["autoSave"].toBool();
        _autosaveInterval = options["autoSaveInterval"].toInt();
        _typewriterSounds = options["typewriterSounds"].toBool();
        _textFont = options["textFont"].toString();
        _voice = options["voice"].toInt(-1);
    }

    int p = _textFont.indexOf(":");
    QString font = _textFont.left(p);
    QString s = _textFont.mid(p + 1);
    int size = s.toInt();
    ui->textEdit->setFontFamily(font);
    ui->textEdit->setFontPointSize(size);
}

QJsonArray MainWindow::listToArray(QList<int> sizes) {
    QJsonArray array;
    for (auto i = sizes.begin(); i != sizes.end(); ++i) array.append(*i);
    return array;
}

QTreeWidgetItem* MainWindow::objectToItem(const QJsonObject& obj, int& total) {
    Scene scene = objectToScene(obj);
    total += scene.wc();
    QTreeWidgetItem* item = new QTreeWidgetItem(static_cast<QTreeWidgetItem*>(nullptr),
                                                QStringList(scene.name().isEmpty() ? "<unnamed>" : scene.name()));
    const QJsonArray& children = obj["children"].toArray();
    for (auto child: children) item->addChild(objectToItem(child.toObject(), total));
    item->setData(0, Qt::ItemDataRole::UserRole, QVariant(this->_scenes.size()));
    _scenes.append(scene);
    return item;
}

Scene MainWindow::objectToScene(const QJsonObject& obj) {
    QString name = obj["name"].toString("");
    bool root = obj["root"].toBool(false);
    Scene scene(name, root);
    scene.doc(obj["doc"].toString(""));
    scene.wc(obj["wc"].toInt(0));
    const QJsonArray& tags = obj["tags"].toArray();
    for (auto tag: tags) scene.tags().append(tag.toString(""));
    return scene;
}

void MainWindow::objectToWidget(const QJsonObject& widget, QWidget* w) {
    QRect r;
    r.setTop(widget["top"].toInt());
    r.setLeft(widget["left"].toInt());
    r.setBottom(widget["bottom"].toInt());
    r.setRight(widget["right"].toInt());
    checkScreens(r);
    w->setGeometry(r);
}

void MainWindow::openAllItems() {
    QTreeWidget* tree = ui->treeWidget;
    QTreeWidgetItem* root = tree->topLevelItem(0);
    openItem(root);
}

void MainWindow::openItem(QTreeWidgetItem* item) {
    if (!item->isExpanded()) item->setExpanded(true);
    int num = item->childCount();
    for (int i = 0; i < num; ++i) openItem(item->child(i));
}

void MainWindow::saveDialog(QDialog* dlg, QRect& save) {
    QRect pos = dlg->geometry();
    save.setLeft(pos.left());
    save.setWidth(pos.width());
    save.setTop(pos.top());
    save.setHeight(pos.height());
}

void MainWindow::saveOptions() {
    QJsonObject options;
    options["openCheckbox"] = _openItems;
    options["autoSave"] = _autosave;
    options["autoSaveInterval"] = _autosaveInterval;
    options["typewriterSounds"] = _typewriterSounds;
    options["textFont"] = _textFont;
    options["voice"] = _voice;
    QJsonObject top;
    top.insert("options", options);
    QJsonDocument json;
    json.setObject(top);
    QString dir = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    QDir dirOp;
    dirOp.mkpath(dir);
    QFile file(dir + "/options.json");
    if (!file.open(QIODevice::WriteOnly | QIODevice::Truncate | QIODevice::Text)) {
        OK(("Can't save to \"" + _filename + ".options\" in the %AppData% folder.").toStdString().c_str());
        return;
    }
    QTextStream out(&file);
    out << json.toJson();
    file.close();

}

QJsonObject MainWindow::sceneToObject(Scene& scene) {
    QJsonObject obj;
    obj.insert("name", scene.name());
    obj.insert("root", scene.root());
    obj.insert("doc", scene.doc());
    obj.insert("wc", scene.wc());
    QJsonArray tags;
    for (const auto& tag: scene.tags()) tags.append(tag);
    obj.insert("tags", tags);
    return obj;
}

void MainWindow::setAllScenes(QTreeWidgetItem* root, QString font, int pnts) {
    int num = root->childCount();
    for (int i = 0; i < num; ++i) setScene(root->child(i), font, pnts);
}

void MainWindow::setMoveButtons() {
    if (_buttons["Move Scene Up"] == nullptr) return;

    QTreeWidget* tree = ui->treeWidget;
    QTreeWidgetItem* current = tree ? tree->currentItem() : nullptr;
    QTreeWidgetItem* parent = current ? current->parent() : nullptr;

    bool canMoveUp = parent != nullptr && parent->indexOfChild(current) != 0;
    bool canMoveDown = parent != nullptr && parent->indexOfChild(current) != parent->childCount() - 1;
    bool canMoveIn = parent != nullptr && parent->indexOfChild(current) != 0;
    bool canMoveOut = parent != nullptr && parent->parent() != nullptr;

    _buttons["Move Scene Up"]->setEnabled(canMoveUp);
    _buttons["Move Scene Down"]->setEnabled(canMoveDown);
    _buttons["Move Scene In"]->setEnabled(canMoveIn);
    _buttons["Move Scene Out"]->setEnabled(canMoveOut);

    ui->actionMove_Up->setEnabled(canMoveUp);
    ui->actionMove_Down->setEnabled(canMoveDown);
    ui->actionMove_In->setEnabled(canMoveIn);
    ui->actionMove_Out->setEnabled(canMoveOut);
    ui->actionRemove_Scene->setEnabled(parent != nullptr);
    ui->action_Distraction_Free->setEnabled(parent != nullptr);
    ui->actionRead_Aloud->setEnabled(_voice != -1 && parent != nullptr);
}

void MainWindow::setScene(QTreeWidgetItem* scene, QString font, int pnts) {
    int idx = scene->data(0, Qt::ItemDataRole::UserRole).toInt();
    Scene& scn = _scenes[idx];
    TextEdit text(_dir);
    text.setHtml(scn.doc());
    text.selectAll();
    text.setFontFamily(font);
    text.setFontPointSize(pnts);
    scn.doc(text.toHtml());
    int num = scene->childCount();
    for (int i = 0; i < num; ++i) setScene(scene->child(i), font, pnts);
}

void MainWindow::setupDialog(QDialog* dlg, QRect& save) {
    if (save.left() != -1) {
        QRect r = dlg->geometry();
        checkScreens(r);
        r.setLeft(save.left());
        r.setWidth(save.width());
        r.setTop(save.top());
        r.setHeight(save.height());
        dlg->setGeometry(r);
    }
}

void MainWindow::syncFullScreen(FullScreen& dlg) {
    _ignore = true;
    ui->textEdit->setHtml(dlg.text());
    _ignore = false;
    auto x = ui->textEdit->textCursor();
    x.setPosition(dlg.cursor());
    ui->textEdit->setTextCursor(x);
    syncScene();
}

void MainWindow::syncScene() {
    TextEdit* text = dynamic_cast<TextEdit*>(ui->textEdit);
    QTreeWidget* tree = ui->treeWidget;
    QTreeWidgetItem* current = tree->currentItem();
    if (current) {
        int currentIdx = current->data(0, Qt::ItemDataRole::UserRole).toInt();
        if (currentIdx < _scenes.size()) {
            Scene& currentScene = _scenes[currentIdx];
            if (!currentScene.root()) {
                currentScene.doc(text->toHtml());
                text->saveImages();
            }
        }
    }
}

void MainWindow::toDialog(const QJsonObject& windows, const QString& name, QRect& dlg) {
    if (windows.contains(name)) {
        const QJsonObject& dialog = windows[name].toObject();
        dlg.setLeft(dialog["left"].toInt());
        dlg.setTop(dialog["top"].toInt());
    }
}

QJsonObject MainWindow::widgetToObject(QWidget* w) {
    QJsonObject widget;
    QRect r = w->geometry();
    widget.insert("top", r.top());
    widget.insert("left", r.left());
    widget.insert("bottom", r.bottom());
    widget.insert("right", r.right());
    return widget;
}
//=================================================================

//====[Event Handlers]=============================================
void MainWindow::closeEvent(QCloseEvent* event) {
    if (checkClose()) event->accept();
    else event->ignore();
}

void MainWindow::keyReleaseEvent(QKeyEvent* ke) {
    static QKeyCombination Paste(Qt::CTRL, Qt::Key_V);

    if (ke->keyCombination() == Paste) pasteAction();
}

void MainWindow::timerEvent(QTimerEvent* event) {
    if (event->timerId() == _autoSaveTimer->timerId()) autoSave();
    else if (event->timerId() == _cleanItTimer->timerId()) cleanIt();
}
//=================================================================

//====[Actions]====================================================
void MainWindow::aboutAction() {
    AboutDialog about;

    setupDialog(&about, _aboutDialog);
    about.exec();
    saveDialog(&about, _aboutDialog);
}

void MainWindow::boldAction() {
    TextEdit* text = ui->textEdit;
    QTextCursor cursor = text->textCursor();
    QTextCharFormat is = cursor.charFormat();
    QTextCharFormat fmt;
    fmt.setFontWeight(is.fontWeight() != QFont::Bold ? QFont::Bold : QFont::Normal);
    cursor.mergeCharFormat(fmt);
    text->mergeCurrentCharFormat(fmt);
    dirty();
}

void MainWindow::centerAction() {
    ui->textEdit->setAlignment(Qt::AlignCenter);
    dirty();
}

bool MainWindow::checkClose() {
    if (_dirty) {
        switch (YesNoCancel("Do you want to save your changes first?", "The current document has been changed!")) {
        case QMessageBox::Yes: if (save()) break; else return false;
        case QMessageBox::No:  break;
        default:               return false;
        }
    } else {
        switch (YesNo("Are you sure you want to quit?", "")) {
        case QMessageBox::Yes: break;
        default:               return false;
        }
    }
    return true;
}

void MainWindow::copyAction() {
    ui->textEdit->copy();
}

void MainWindow::cutAction() {
    ui->textEdit->cut();
    dirty();
}

void MainWindow::documentationAction() {
    QDesktopServices::openUrl("file:///" + QFileInfo(QCoreApplication::applicationFilePath()).absolutePath() + "/documentaion.html");
}

void MainWindow::epubAction() {
    QTreeWidget* tree = ui->treeWidget;
    QTreeWidgetItem* rootItem = tree->topLevelItem(0);

    syncScene();

    QJsonObject root;
    root.insert("root", itemToObject(rootItem));
    QJsonObject top;
    top.insert("document", root);
    EPUB epub(_dir, top);
    message("EPUB created");
}

void MainWindow::findAction() {
    QTreeWidget* tree = ui->treeWidget;
    QTreeWidgetItem* current = tree->currentItem();
    QTreeWidgetItem* parent = current->parent();
    if (parent == nullptr) return;

    QTextEdit* text = ui->textEdit;
    QTextCursor cursor = text->textCursor();
    syncScene();

    FindDialog find(cursor.hasSelection());
    if (_request.searchValid()) find.setSearchString(_request.look());

    setupDialog(&find, _findDialog);
    int res = find.exec();
    saveDialog(&find, _findDialog);

    if (!res) return;

    QString look = find.getSearchString();
    SearchType searchRange = find.getType();
    if (look.isEmpty()) return;

    _request.set(look, "", searchRange);

    findNextAction();
}

void MainWindow::findNextAction() {
    if (!_request.searchValid()) return;

    QTreeWidget* tree = ui->treeWidget;

    QTextEdit* text = ui->textEdit;
    QTextCursor cursor = text->textCursor();
    syncScene();

    QTextCursor oldCursor = text->textCursor();
    QTextCursor noSelection = oldCursor;
    noSelection.setPosition(oldCursor.position());
    text->setTextCursor(noSelection);

    bool savedDirty = _dirty;

    MainWindow::Position found = _request.findNext();
    if (found.unset()) {
        _request.current(found);
        _request.invalidate();
        setEditButtons();
        OK("Search complete", "Nothing more found");
    }
    else {
        _request.current(found);
        QString look = _request.look();

        QTreeWidgetItem* item = getItemByIndex(found.scene());
        if (tree->currentItem() != item) tree->setCurrentItem(item);

        cursor.setPosition(found.offset());
        cursor.movePosition(QTextCursor::MoveOperation::NextCharacter, QTextCursor::MoveMode::KeepAnchor, look.size());
        text->setTextCursor(cursor);
        text->ensureCursorVisible();
    }

    _dirty = savedDirty;
}

void MainWindow::fullJustifyAction() {
    ui->textEdit->setAlignment(Qt::AlignJustify);
    dirty();
}

void MainWindow::fullScreenAction() {
    FullScreen dlg;

    if (_fullscreenDialog[0] != 0) dlg.setSizes(_fullscreenDialog);
    syncScene();
    dlg.dir(_dir);
    QTreeWidget* tree = ui->treeWidget;
    QTreeWidgetItem* current = tree->currentItem();
    int currentIdx = current->data(0, Qt::ItemDataRole::UserRole).toInt();
    Scene& currentScene = _scenes[currentIdx];
    dlg.setText(currentScene.doc());
    auto x = ui->textEdit->textCursor();
    dlg.setCursor(x.anchor());
    dlg.clean();
    dlg.exec();
    syncFullScreen(dlg);
    _fullscreenDialog = dlg.sizes();
    if (dlg.dirty()) dirty();
}

void MainWindow::htmlAction() {
    QTreeWidget* tree = ui->treeWidget;
    QTreeWidgetItem* rootItem = tree->topLevelItem(0);

    syncScene();

    QJsonObject root;
    root.insert("root", itemToObject(rootItem));
    QJsonObject top;
    top.insert("document", root);
    HTML html(_dir, top);
    message("HTML files created");
}

void MainWindow::imageAction() {
    QString fname = QFileDialog::getOpenFileName(this, "Import Image", _dir, "Images (*.gif *.jpg *.png)");
    if (fname.isEmpty()) return;
    ui->textEdit->insertFromFile(fname);
    dirty();
}

void MainWindow::italicAction() {
    TextEdit* text = ui->textEdit;
    QTextCursor cursor = text->textCursor();
    QTextCharFormat is = cursor.charFormat();
    QTextCharFormat fmt;
    fmt.setFontItalic(!is.fontItalic());
    cursor.mergeCharFormat(fmt);
    text->mergeCurrentCharFormat(fmt);
    dirty();
}

void MainWindow::indentAction() {
    TextEdit* text = ui->textEdit;
    QTextCursor cursor = text->textCursor();
    QTextBlockFormat blk = cursor.blockFormat();
    int indent = blk.indent();
    if (indent == 0) blk.setIndent(indent + 1);
    else blk.setIndent(indent - 1);
    cursor.setBlockFormat(blk);
    text->setTextCursor(cursor);
    dirty();
}

void MainWindow::itemChangedAction(QTreeWidgetItem* current, QTreeWidgetItem* previous) {
    bool wasDirty = _dirty;
    TextEdit* text = ui->textEdit;
    if (current) {
        int currentIdx = current->data(0, Qt::ItemDataRole::UserRole).toInt();
        int previousIdx = 0;
        if (previous) previousIdx = previous->data(0, Qt::ItemDataRole::UserRole).toInt();
        if (currentIdx < _scenes.size()) {
            Scene& currentScene = _scenes[currentIdx];
            if (previousIdx < _scenes.size()) {
                Scene& previousScene = _scenes[previousIdx];
                if (previous && !previousScene.root()) {
                    previousScene.doc(text->toHtml());
                    text->saveImages();
                }
                else text->setEnabled(true);
            }

            if (!currentScene.root()) {
                text->setHtml(currentScene.doc());
                if (currentScene.doc().isEmpty()) {
                    QTextCursor cursor = text->textCursor();
                    QTextBlockFormat blk = cursor.blockFormat();
                    blk.setTextIndent(20.0);
                    blk.setBottomMargin(10.0);
                    cursor.setBlockFormat(blk);
                    text->setTextCursor(cursor);
                }
                if (wasDirty) dirty();
                setMoveButtons();
                return;
            }
        }
    }

    text->clear();
    text->setEnabled(false);
    if (wasDirty) dirty();
    setMoveButtons();
}

void MainWindow::itemDoubleClickedAction(QTreeWidgetItem* current, int) {
    int currentIdx = current->data(0, Qt::ItemDataRole::UserRole).toInt();
    Scene& currentScene = _scenes[currentIdx];

    Scene x(currentScene);
    TagsDialog tags(x);

    setupDialog(&tags, _tagsDialog);
    int res = tags.exec();
    saveDialog(&tags, _tagsDialog);

    if (res) {
        currentScene = x;
        if (x.name().isEmpty()) x.name("<untitled>");
        current->setText(0, x.name());
        dirty();
    }
}

void MainWindow::leftJustifyAction() {
    ui->textEdit->setAlignment(Qt::AlignLeft);
    dirty();
}

void MainWindow::markdownAction() {
    QTreeWidget* tree = ui->treeWidget;
    QTreeWidgetItem* rootItem = tree->topLevelItem(0);

    syncScene();

    QJsonObject root;
    root.insert("root", itemToObject(rootItem));
    QJsonObject top;
    top.insert("document", root);
    Markdown markdown(_dir, top);
    message("Markdown created");
}

void MainWindow::message(QString msg) {
    ui->statusbar->showMessage(msg, 10000);
}

void MainWindow::moveDownAction() {
    QTreeWidget* tree = ui->treeWidget;
    QTreeWidgetItem* current = tree->currentItem();
    QTreeWidgetItem* parent = current->parent();
    if (parent == nullptr) return;
    int idx = parent->indexOfChild(current);
    if (idx == parent->childCount() - 1) return;
    parent->removeChild(current);
    parent->insertChild(idx + 1, current);
    tree->setCurrentItem(current);
    dirty();
}

void MainWindow::moveInAction() {
    QTreeWidget* tree = ui->treeWidget;
    QTreeWidgetItem* current = tree->currentItem();
    QTreeWidgetItem* parent = current->parent();
    if (parent == nullptr) return;
    int idx = parent->indexOfChild(current);
    if (idx == 0) return;
    QTreeWidgetItem* newParent = parent->child(idx - 1);
    parent->removeChild(current);
    newParent->addChild(current);
    newParent->setExpanded(true);
    tree->setCurrentItem(current);
    dirty();
}

void MainWindow::moveOutAction() {
    QTreeWidget* tree = ui->treeWidget;
    QTreeWidgetItem* current = tree->currentItem();
    QTreeWidgetItem* parent = current->parent();
    if (parent == nullptr || parent->parent() == nullptr) return;
    QTreeWidgetItem* grandParent = parent->parent();
    int idx = grandParent->indexOfChild(parent);
    parent->removeChild(current);
    grandParent->insertChild(idx + 1, current);
    tree->setCurrentItem(current);
    dirty();
}

void MainWindow::moveUpAction() {
    QTreeWidget* tree = ui->treeWidget;
    QTreeWidgetItem* current = tree->currentItem();
    QTreeWidgetItem* parent = current->parent();
    if (parent == nullptr) return;
    int idx = parent->indexOfChild(current);
    if (idx == 0) return;
    parent->removeChild(current);
    parent->insertChild(idx - 1, current);
    tree->setCurrentItem(current);
    dirty();
}

void MainWindow::newAction() {
    if (_dirty) {
        switch (YesNoCancel("Do you want to save your changes first?", "The current document has been changed!")) {
        case QMessageBox::Yes:    if (save()) break; else return;
        case QMessageBox::Cancel: return;
        default: break;
        }
    }

    QTreeWidget* tree = ui->treeWidget;
    tree->clear();
    _scenes.clear();
    QTreeWidgetItem* topLevel = new QTreeWidgetItem(static_cast<QTreeWidget*>(nullptr), QStringList("<untitled>"));
    _scenes.append(Scene("", true));
    topLevel->setData(0, Qt::ItemDataRole::UserRole, QVariant(0));
    tree->insertTopLevelItem(0, topLevel);
    QTreeWidgetItem* scene = new QTreeWidgetItem(static_cast<QTreeWidget*>(nullptr), QStringList("<untitled>"));
    Scene scn("");
    TextEdit text(_dir);
    int p = _textFont.indexOf(":");
    QString font = _textFont.left(p);
    QString s = _textFont.mid(p + 1);
    int size = s.toInt();
    text.setFontFamily(font);
    text.setFontPointSize(size);
    text.selectAll();
    auto cursor = text.textCursor();
    auto blk = cursor.blockFormat();
    blk.setTextIndent(20);
    cursor.setBlockFormat(blk);
    text.setTextCursor(cursor);
    scn.doc(text.toHtml());
    _scenes.append(scn);
    ui->textEdit->setFontFamily(font);
    ui->textEdit->setFontPointSize(size);
    scene->setData(0, Qt::ItemDataRole::UserRole, QVariant(1));
    topLevel->insertChild(0, scene);
    if (_openItems) openAllItems();
    clean();
}

void MainWindow::newSceneAction() {
    QTreeWidget* tree = ui->treeWidget;
    QTreeWidgetItem* parent = tree->currentItem();
    if (parent == nullptr) parent = tree->topLevelItem(0);
    int idx = parent->childCount();
    QTreeWidgetItem* scene = new QTreeWidgetItem(static_cast<QTreeWidget*>(nullptr), QStringList("<untitled>"));
    Scene scn("");
    TextEdit text(_dir);
    int p = _textFont.indexOf(":");
    QString font = _textFont.left(p);
    QString s = _textFont.mid(p + 1);
    int size = s.toInt();
    text.setFontFamily(font);
    text.setFontPointSize(size);
    text.selectAll();
    auto cursor = text.textCursor();
    auto blk = cursor.blockFormat();
    blk.setTextIndent(20);
    cursor.setBlockFormat(blk);
    text.setTextCursor(cursor);
    scn.doc(text.toHtml());
    _scenes.append(scn);
    scene->setData(0, Qt::ItemDataRole::UserRole, QVariant(this->_scenes.size() - 1));
    parent->insertChild(idx, scene);
    dirty();
}

void MainWindow::openAction(QString infile) {
    if (_dirty) {
        switch (YesNoCancel("Do you want to save your changes first?", "The current document has been changed!")) {
        case QMessageBox::Yes:    if (save()) break; else return;
        case QMessageBox::Cancel: return;
        default: break;
        }
    }

    QString  fname;
    if (infile.isEmpty()) {
        fname = QFileDialog::getOpenFileName(this, "Open File", _dir, "Novels (*.novel)");
        if (fname.isEmpty()) return;
    }
    else fname = infile;

    QTreeWidget* tree = ui->treeWidget;

    int ext = fname.lastIndexOf(".novel");
    if (ext != -1) fname = fname.left(ext);
    int sep = fname.lastIndexOf("/");
    if (sep != -1) {
        _dir = fname.left(sep + 1);
        fname = fname.mid(sep + 1);
    }
    sep = fname.lastIndexOf("\\");
    if (sep != -1) {
        _dir = fname.left(sep + 1);
        fname = fname.mid(sep + 1);
    }

    _filename = fname;

    QFile file(_dir + "/" + _filename + ".novel");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        message("Can't open '" + _dir + "/" + _filename + ".novel' for reading, permissions");
        return;
    }

    QByteArray data(file.readAll());
    QString jsonStr(data);
    file.close();
    QJsonDocument json = QJsonDocument::fromJson(jsonStr.toUtf8());

    // scan the json structure in for valid novel
    const QJsonObject& top = json.object();
    if (!top.contains("document")) {
        message("'" + _dir + "/" + _filename + ".novel' is not a valid novel");
        return;
    }

    const QJsonObject& doc = top["document"].toObject();
    const QJsonObject& root = doc["root"].toObject();
    tree->clear();
    _scenes.clear();
    tree->addTopLevelItem(objectToItem(root, _totalWc));

    if (top.contains("options")) {
        QJsonObject options = top["options"].toObject();
        _openItems = options["openCheckbox"].toBool();
        bool startSaving = false;
        if (!_autosave && options["autosave"].toBool()) startSaving = true;
        _autosave = options["autoSave"].toBool();
        _autosaveInterval = options["autoSaveInterval"].toInt();
        _typewriterSounds = options["typewriterSounds"].toBool();
        _textFont = options["textFont"].toString();
        _voice = options["voice"].toInt(-1);
        if (startSaving) {
            if (!_autoSaveTimer) _autoSaveTimer = new QBasicTimer();
            _autoSaveTimer->start(_autosaveInterval * 60000, this);
        }
    }
    if (top.contains("windows")) {
        const QJsonObject& windows = top["windows"].toObject();
        QJsonObject mainwindow = windows["mainwindow"].toObject();
        objectToWidget(mainwindow, (QWidget*) this);
        if (mainwindow.contains("splitter")) {
            QSplitter* splitter = findChild<QSplitter*>("splitter");
            splitter->setSizes(arrayToList(mainwindow["splitter"].toArray()));
        }
        if (windows.contains("fullscreen")) {
            const QJsonObject& fullscr = windows["fullscreen"].toObject();
            _fullscreenDialog = arrayToList(fullscr["sizes"].toArray());
        }
        // load options
        toDialog(windows, "aboutdialog", _aboutDialog);
        toDialog(windows, "finddialog", _findDialog);
        toDialog(windows, "optionsdialog", _optionsDialog);
        toDialog(windows, "replacedialog", _replaceDialog);
        toDialog(windows, "scriptsdialog", _scriptsDialog);
        toDialog(windows, "tagsdialog", _tagsDialog);
        toDialog(windows, "ok", _ok);
        toDialog(windows, "okcancel", _okcancel);
        toDialog(windows, "yesno", _yesno);
        toDialog(windows, "yesnocancel", _yesnocancel);
        toDialog(windows, "question", _question);
        toDialog(windows, "statement", _statement);
    }

    TextEdit* text = ui->textEdit;

    int pos = _textFont.indexOf(":");
    QString font = _textFont.left(pos);
    QString s = _textFont.mid(pos + 1);
    int size = s.toInt();
    auto cursor = text->textCursor();
    pos = cursor.anchor();
    text->selectAll();
    text->setFontFamily(font);
    text->setFontPointSize(size);
    cursor.setPosition(pos);
    text->setTextCursor(cursor);
    setAllScenes(tree->topLevelItem(0), font, size);
    ui->textEdit->setFontFamily(font);
    ui->textEdit->setFontPointSize(size);
    if (_openItems) openAllItems();
    clean();
    _ignore = false;
}

void MainWindow::optionsAction() {
    OptionsDialog options;

    // set current in force options
    options.setOpenItems(_openItems);
    options.setAutoSave(_autosave, _autosaveInterval);
    options.setTypewriterSounds(_typewriterSounds);
    options.setTextFont(_textFont);
    options.setVoice(_voice);

    setupDialog(&options, _optionsDialog);
    int res = options.exec();
    saveDialog(&options, _optionsDialog);

    if (!res) return;

    if ((_openItems != options.openItems()) ||
        (_autosave != options.autoSave()) ||
        (_autosaveInterval != options.autosaveInterval()) ||
        (_typewriterSounds != options.typewriterSounds()) ||
        (_textFont != options.textFont() && !options.textFont().isEmpty()) ||
        (_voice != options.voice())) dirty();

    _openItems = options.openItems();
    bool startSaving = false;
    if (!_autosave && options.autoSave()) startSaving = true;
    _autosave = options.autoSave();
    _autosaveInterval = options.autosaveInterval();
    _typewriterSounds = options.typewriterSounds();
    _voice = options.voice();
    if (_textFont != options.textFont() && !options.textFont().isEmpty()) {
        _textFont = options.textFont();

        int p = _textFont.indexOf(":");
        QString font = _textFont.left(p);
        QString s = _textFont.mid(p + 1);
        int size = s.toInt();
        TextEdit* text = ui->textEdit;
        auto cursor = text->textCursor();
        p = cursor.anchor();
        text->selectAll();
        text->setFontFamily(font);
        text->setFontPointSize(size);
        cursor.setPosition(p);
        text->setTextCursor(cursor);
        QTreeWidget* tree = ui->treeWidget;
        setAllScenes(tree->topLevelItem(0), font, size);
    }
    if (startSaving) {
        if (!_autoSaveTimer) _autoSaveTimer = new QBasicTimer();
        _autoSaveTimer->start(_autosaveInterval * 60000, this);
    }
    saveOptions();
    setMoveButtons();
}

void MainWindow::pasteAction() {
    TextEdit text(_dir);
    text.allowTextPaste();

    if (text.canPaste()) {
        TextEdit* edit = ui->textEdit;
        const QClipboard* cb = QApplication::clipboard();
        const QMimeData* md = cb->mimeData();
        if (md->hasText() || md->hasHtml()) {
            text.paste();
            QString txt = text.toPlainText();
            edit->insertPlainText(txt);
        } else if (md->hasImage()) edit->paste();
        else return;
        dirty();
    }
}

void MainWindow::pdfAction() {
    QTreeWidget* tree = ui->treeWidget;
    QTreeWidgetItem* rootItem = tree->topLevelItem(0);

    syncScene();

    QJsonObject root;
    root.insert("root", itemToObject(rootItem));
    QJsonObject top;
    top.insert("document", root);
    PDF pdf(_dir, top);
    message("PDF file created");
}

void MainWindow::readAloudAction() {
    if (_voice == -1) return;

    QTreeWidget* tree = ui->treeWidget;
    QTreeWidgetItem* current = tree ? tree->currentItem() : nullptr;
    QTreeWidgetItem* parent = current ? current->parent() : nullptr;

    if (parent == nullptr) return;
    QString text = ui->textEdit->textCursor().selectedText();
    if (text.isEmpty()) text = ui->textEdit->toPlainText();

    auto voices = _speech->availableVoices();
    _speech->setVoice(voices[_voice]);
    _speech->say(text);
}

void MainWindow::redoAction() {
    ui->textEdit->redo();
    dirty();
}

void MainWindow::redoAvailableAction(bool available) {
    ui->action_Redo->setEnabled(available);
}

void MainWindow::removeSceneAction() {
    QTreeWidget* tree = ui->treeWidget;
    QTreeWidgetItem* current = tree->currentItem();
    QTreeWidgetItem* parent = current->parent();
    if (parent == nullptr) return;
    switch (YesNo("Abort?", "This action cannot be undone!")) {
    case QMessageBox::Yes: return;
    default:               break;
    }
    parent->removeChild(current);
    dirty();
}

void MainWindow::replaceAction() {
    QTextEdit* text = ui->textEdit;
    QTextCursor cursor = text->textCursor();
    syncScene();

    ReplaceDialog replace(cursor.hasSelection());
    if (_request.searchValid()) {
        replace.setSearchString(_request.look());
        replace.setReplaceString(_request.with());
    }

    setupDialog(&replace, _replaceDialog);
    int res = replace.exec();
    saveDialog(&replace, _replaceDialog);

    if (!res) return;

    QString look = replace.getSearchString();
    QString with = replace.getReplaceString();
    SearchType searchRange = replace.getType();
    if (look.isEmpty()) return;

    _request.set(look, with, searchRange);

    findNextAction();
}

void MainWindow::replaceAllAction() {
    QTreeWidget* tree = ui->treeWidget;
    QTreeWidgetItem* current = tree->currentItem();
    QTreeWidgetItem* parent = current->parent();

    if (parent == nullptr || !_request.searchValid() || _request.with().isEmpty()) return;

    while (!_request.current().unset()) {
        replaceSelectionAction();
        findNextAction();
    }
}

void MainWindow::replaceSelectionAction() {
    QTreeWidget* tree = ui->treeWidget;
    QTreeWidgetItem* current = tree->currentItem();
    QTreeWidgetItem* parent = current->parent();

    if (parent == nullptr || !_request.searchValid() || _request.with().isEmpty()) return;

    QTextEdit* text = ui->textEdit;
    QTextCursor cursor = text->textCursor();
    syncScene();

    if (cursor.selectedText().length() < 1) return;

    text->insertPlainText(_request.with());
}

void MainWindow::rightJustifyAction() {
    ui->textEdit->setAlignment(Qt::AlignRight);
    dirty();
}

void MainWindow::rtfAction() {
    QTreeWidget* tree = ui->treeWidget;
    QTreeWidgetItem* rootItem = tree->topLevelItem(0);

    syncScene();

    QJsonObject root;
    root.insert("root", itemToObject(rootItem));
    QJsonObject top;
    top.insert("document", root);
    RTF rtf(_dir, top);
}

void MainWindow::setEditButtons() {
    if (_buttons["Paste"] == nullptr) return;

    QTreeWidget* tree = ui->treeWidget;
    QTreeWidgetItem* current = tree ? tree->currentItem() : nullptr;
    QTreeWidgetItem* parent = current ? current->parent() : nullptr;

    QTextCursor cursor = ui->textEdit->textCursor();
    QTextCharFormat is = cursor.charFormat();
    QTextBlockFormat blk = cursor.blockFormat();

    TextEdit tmp("");
    tmp.allowTextPaste();
    _buttons["Paste"]->setEnabled(parent != nullptr && tmp.canPaste());

    _buttons["Bold Text"]->setChecked(parent != nullptr && is.fontWeight() == QFont::Bold);
    _buttons["Italic Text"]->setChecked(parent != nullptr && is.fontItalic());
    _buttons["Underline Text"]->setChecked(parent != nullptr && is.fontUnderline());

    ui->action_Paste->setEnabled(parent != nullptr && ui->textEdit->canPaste());

    ui->action_Search->setEnabled(parent != nullptr);
    ui->actionFind_Next->setEnabled(parent != nullptr && _request.searchValid());
    ui->actionRepl_ace->setEnabled(parent != nullptr);
    ui->actionReplace_Selection->setEnabled(parent != nullptr && _request.searchValid() && !_request.with().isEmpty());
    ui->actionReplace_All->setEnabled(parent != nullptr && _request.searchValid() && !_request.with().isEmpty());

    ui->action_Bold->setChecked(parent != nullptr && is.fontWeight() == QFont::Bold);
    ui->action_Italic->setChecked(parent != nullptr && is.fontItalic());
    ui->action_Underline->setChecked(parent != nullptr && is.fontUnderline());

    ui->action_Left_JUstify->setChecked(parent != nullptr && ui->textEdit->alignment() == Qt::AlignLeft);
    ui->action_Center->setChecked(parent != nullptr && ui->textEdit->alignment() == Qt::AlignCenter);
    ui->action_Right_Justify->setChecked(parent != nullptr && ui->textEdit->alignment() == Qt::AlignRight);
    ui->action_Full_Justify->setChecked(parent != nullptr && ui->textEdit->alignment() == Qt::AlignJustify);

    ui->actionIndent->setChecked(parent != nullptr && blk.indent() != 0);
}

void MainWindow::standardTextAction() {
    QTreeWidget* tree = ui->treeWidget;
    QTreeWidgetItem* rootItem = tree->topLevelItem(0);

    syncScene();

    QJsonObject root;
    root.insert("root", itemToObject(rootItem));
    QJsonObject top;
    top.insert("document", root);
    xTEXT text(_dir, top);
    message("Text exported");
}

bool MainWindow::save() {
    if (!_dirty) return true;
    if (_filename.isEmpty() && !saveAs()) return true;

    QTreeWidget* tree = ui->treeWidget;
    QTreeWidgetItem* rootItem = tree->topLevelItem(0);
    if (_filename == "") if (!saveAs()) return false;

    syncScene();

    QJsonObject root;
    root.insert("root", itemToObject(rootItem));
    QJsonObject windows;
    QJsonObject mainwindow = widgetToObject((QWidget*) this);
    mainwindow.insert("splitter", listToArray(findChild<QSplitter*>("splitter")->sizes()));
    windows.insert("mainwindow", mainwindow);
    if (FullScreen::fullscreen() != nullptr) {
        QJsonObject fullscr;
        fullscr.insert("sizes", listToArray(_fullscreenDialog));
        windows.insert("fullscreen", fullscr);
    }
    QJsonObject options;
    options["openCheckbox"] = _openItems;
    options["autoSave"] = _autosave;
    options["autoSaveInterval"] = _autosaveInterval;
    options["typewriterSounds"] = _typewriterSounds;
    options["textFont"] = _textFont;
    options["voice"] = _voice;
    windows.insert("aboutdialog", dialogToObject(_aboutDialog));
    windows.insert("finddialog", dialogToObject(_findDialog));
    windows.insert("optionsdialog", dialogToObject(_optionsDialog));
    windows.insert("replacedialog", dialogToObject(_replaceDialog));
    windows.insert("scritsdialog", dialogToObject(_scriptsDialog));
    windows.insert("tagsdialog", dialogToObject(_tagsDialog));
    windows.insert("ok", dialogToObject(_ok));
    windows.insert("okcancel", dialogToObject(_okcancel));
    windows.insert("yesno", dialogToObject(_yesno));
    windows.insert("yesnocancel", dialogToObject(_yesnocancel));
    windows.insert("question", dialogToObject(_question));
    windows.insert("statement", dialogToObject(_statement));
    QJsonObject top;
    top.insert("document", root);
    top.insert("options", options);
    top.insert("windows", windows);
    QJsonDocument json;
    json.setObject(top);
    QFile file(_dir + "/" + _filename + ".novel");
    if (!file.open(QIODevice::WriteOnly | QIODevice::Truncate | QIODevice::Text)) {
        OK(("Can't save to \"" + _filename + ".novel\" in the \"" + _dir + "\" folder.").toStdString().c_str());
        return false;
    }
    QTextStream out(&file);
    out << json.toJson();
    file.close();

    message("Novel saved");

    clean();
    return true;
}

bool MainWindow::saveAs() {
    QString filename = QFileDialog::getSaveFileName(this, "Save File", _dir, "Novels (*.novel)");
    if (filename.isEmpty()) return false;
    int ext = filename.lastIndexOf(".novel");
    if (ext != -1) filename = filename.left(ext);
    int sep = filename.lastIndexOf("/");
    if (sep != -1) {
        _dir = filename.left(sep + 1);
        ui->textEdit->setDir(_dir);
        _filename = filename.mid(sep + 1);
    }

    return true;
}

void MainWindow::scriptsAction() {
    ScriptsDialog scripts;

    setupDialog(&scripts, _scriptsDialog);
    scripts.exec();
    saveDialog(&scripts, _scriptsDialog);
}

void MainWindow::tagsAction() {
    QTreeWidget* tree = ui->treeWidget;
    QTreeWidgetItem* current = tree->currentItem();
    itemDoubleClickedAction(current, 0);
}

void MainWindow::textAction() {
    QString fname = QFileDialog::getOpenFileName(this, "Import Text", _dir, "Text files (*.txt);;All files (*.*)");
    if (fname.isEmpty()) return;

    QFile file(_dir + "/" + fname);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) return;

    QByteArray data(file.readAll());
    QString str(data);
    file.close();

    ui->textEdit->insertPlainText(str);
    dirty();
}

void MainWindow::underlineAction() {
    TextEdit* text = ui->textEdit;
    QTextCursor cursor = text->textCursor();
    QTextCharFormat is = cursor.charFormat();
    QTextCharFormat fmt;
    fmt.setFontUnderline(!is.fontUnderline());
    cursor.mergeCharFormat(fmt);
    text->mergeCurrentCharFormat(fmt);
    dirty();
}

void MainWindow::undoAction() {
    ui->textEdit->undo();
    dirty();
}

void MainWindow::undoAvailableAction(bool available) {
    ui->action_Undo->setEnabled(available);
}

void MainWindow::wordCountAction() {
    syncScene();
    QTreeWidget* tree = ui->treeWidget;
    QTreeWidgetItem* root = tree->topLevelItem(0);
    int idx = root->data(0, Qt::ItemDataRole::UserRole).toInt();
    int lastWC = _scenes[idx].wc();

    int wc = 0;
    for (int i = 0; i < _scenes.count(); ++i) wc += countWords(i);

    Statement(QString::asprintf("Previous word count: %d\nCurrent word count: %d\nChange in word count: %d", lastWC, wc, wc - lastWC).toStdString().c_str());
    _scenes[idx].wc(wc);
    _totalWc = wc;
}
//=================================================================

//====[Initialization]=============================================
void MainWindow::createToolBarItem(QToolBar* tb, const QString icon, const QString name, const QString tip, const char* signal, const char* slot) {
    QAction* action = tb->addAction(QIcon(icon), name);
    QString darkIcon = icon.left(2) + "dark/dark" + icon[2].toUpper() + icon.mid(3);
    _buttons[name] = action;
    _actionIcons[action][Light] = icon;
    _actionIcons[action][Dark] = darkIcon;
    action->setToolTip(tip);
    action->connect(action, signal, this, slot);
}

void MainWindow::setMenuIcons(QAction* action, QString icon, QString darkIcon) {
    _actionIcons[action][Light] = icon;
    _actionIcons[action][Dark] = darkIcon;
}

void MainWindow::setMenuIcons(QMenu* action, QString icon, QString darkIcon) {
    _menuIcons[action][Light] = icon;
    _menuIcons[action][Dark] = darkIcon;
}

bool MainWindow::windowsDarkThemeAvailable() {
    if (QOperatingSystemVersion::current().majorVersion() == 10) return QOperatingSystemVersion::current().microVersion() >= 17763;
    else if (QOperatingSystemVersion::current().majorVersion() > 10) return true;
    return false;
}

bool MainWindow::windowsIsInDarkTheme() {
    QSettings settings("HKEY_CURRENT_USER\\Software\\Microsoft\\Windows\\CurrentVersion\\Themes\\Personalize", QSettings::NativeFormat);
    return settings.value("AppsUseLightTheme", 1).toInt() == 0;
}

#ifdef Q_OS_WINDOWS
static bool SetHkcrUserRegKey(QString key, const QString& value, const QString& valueName = nullptr)
{
    HKEY hKey;
    key.prepend("SoftwareClasses");
    LONG lRetVal = RegCreateKey(HKEY_CURRENT_USER, (const wchar_t*) key.utf16(), &hKey);
    if (ERROR_SUCCESS == lRetVal) {
        LONG lResult = ::RegSetValueExW(hKey, valueName.isEmpty() ? 0 : (const wchar_t*) valueName.utf16(), (DWORD) 0, (DWORD) REG_SZ, (CONST BYTE*) value.utf16(), (DWORD) (value.length() + 1) * sizeof(wchar_t));
        if(::RegCloseKey(hKey) == ERROR_SUCCESS && lResult == ERROR_SUCCESS) return true;
        QMessageBox::warning(0, QString("Error in setting Registry values"),
        QString("registration database update failed for key '%s'.").arg(key));
    }
    else {
        wchar_t buffer[4096];
        ::FormatMessageW(FORMAT_MESSAGE_FROM_SYSTEM, 0, lRetVal, 0, buffer, 4096, 0);
        QString szText = QString::fromUtf16((char16_t*) buffer);
        QMessageBox::warning(0, QString("Error in setting Registry values"), szText);
    }
    return false;
}

static void registerFileType(const QString& documentId, const QString& fileTypeName, const QString& fileExtension, qint32 appIconIndex) {
    // first register the type ID of our server
    if (!SetHkcrUserRegKey(documentId, fileTypeName)) return;
    if (!SetHkcrUserRegKey(QString("%1DefaultIcon").arg(documentId), QString("\"%1\",%2").arg(QDir::toNativeSeparators(qApp->applicationFilePath())).arg(appIconIndex))) return;
    LONG lSize = _MAX_PATH * 2;
    wchar_t szTempBuffer[_MAX_PATH * 2];
    LONG lResult = ::RegQueryValue(HKEY_CLASSES_ROOT, (const wchar_t*) fileExtension.utf16(), szTempBuffer, &lSize);
    QString temp = QString::fromUtf16((char16_t*) szTempBuffer);
    if (lResult != ERROR_SUCCESS || temp.isEmpty() || temp == documentId) {
        // no association for that suffix
        if (!SetHkcrUserRegKey(fileExtension, documentId)) return;
        SetHkcrUserRegKey(QString("%1ShellNew").arg(fileExtension), QLatin1String(""), QLatin1String("NullFile"));
    }
}
#endif

void MainWindow::enableShellOpen() {
#ifdef Q_OS_WINDOWS
    if (0 != _appAtom || 0 != _systemTopicAtom) return;
    _appAtom = ::GlobalAddAtomW((const wchar_t*) _appAtomName.utf16());
    _systemTopicAtom = ::GlobalAddAtomW((const wchar_t*) _systemTopicAtomName.utf16());
#endif
}

void MainWindow::registerExtensionHandler() {
#ifdef Q_OS_WINDOWS
    QFileInfo fi(qApp->applicationFilePath());
    _appAtomName = fi.baseName();

    registerFileType("BookSmith.Document", "BookSmith Novel Document", ".novel", 0);
#endif
}

void MainWindow::registerSignals() {
    connect(ui->action_New,    SIGNAL(triggered()), SLOT(newMenuItem()));
    connect(ui->action_Open,   SIGNAL(triggered()), SLOT(openMenuItem()));
    connect(ui->action_Save,   SIGNAL(triggered()), SLOT(saveMenuItem()));
    connect(ui->actionSave_As, SIGNAL(triggered()), SLOT(saveAsMenuItem()));
    connect(ui->menu_Export, SIGNAL(aboutToShow()), SLOT(aboutToShowExportMenu()));
    connect(ui->menu_Export, SIGNAL(aboutToHide()), SLOT(aboutToHideExportMenu()));
    connect(ui->action_PDF,           SIGNAL(triggered()), SLOT(pdfMenuItem()));
    connect(ui->action_EPUB,          SIGNAL(triggered()), SLOT(epubMenuItem()));
    connect(ui->action_HTML,          SIGNAL(triggered()), SLOT(htmlMenuItem()));
    connect(ui->action_Markdown,      SIGNAL(triggered()), SLOT(markdownMenuItem()));
    connect(ui->action_RTF,           SIGNAL(triggered()), SLOT(rtfMenuItem()));
    connect(ui->action_Standard_Text, SIGNAL(triggered()), SLOT(standardTextMenuItem()));
    connect(ui->menu_Import, SIGNAL(aboutToShow()), SLOT(aboutToShowImportMenu()));
    connect(ui->menu_Import, SIGNAL(aboutToHide()), SLOT(aboutToHideImportMenu()));
    connect(ui->action_Image, SIGNAL(triggered()), SLOT(imageMenuItem()));
    connect(ui->action_Text,  SIGNAL(triggered()), SLOT(textMenuItem()));
    connect(ui->actionE_xit,   SIGNAL(triggered()), SLOT(exitClicked()));
    setMenuIcons(ui->action_New,    ":/new.ico",    ":/dark/darkNew.ico");
    setMenuIcons(ui->action_Open,   ":/file.ico",   ":/dark/darkFile.ico");
    setMenuIcons(ui->action_Save,   ":/save.ico",   ":/dark/darkSave.ico");
    setMenuIcons(ui->actionSave_As, ":/saveAs.ico", ":/dark/darkSaveAs.ico");
    setMenuIcons(ui->menu_Export,   ":/export.ico", ":/dark/darkExport.ico");
    setMenuIcons(ui->menu_Import,   ":/import.ico", ":/dark/darkImport.ico");
    setMenuIcons(ui->actionE_xit,   ":/exit.ico",   ":/dark/darkExit.ico");
    setMenuIcons(ui->action_PDF,           ":/pdf.ico",      ":/dark/darkPdf.ico");
    setMenuIcons(ui->action_EPUB,          ":/epub.ico",     ":/dark/darkEpub.ico");
    setMenuIcons(ui->action_HTML,          ":/html.ico",     ":/dark/darkHtml.ico");
    setMenuIcons(ui->action_Markdown,      ":/markdown.ico", ":/dark/darkMarkdown.ico");
    setMenuIcons(ui->action_RTF,           ":/rtf.ico",      ":/dark/darkRtf.ico");
    setMenuIcons(ui->action_Standard_Text, ":/text.ico",     ":/dark/darkText.ico");
    setMenuIcons(ui->action_Image, ":/image.ico",    ":/dark/darkImage.ico");
    setMenuIcons(ui->action_Text,  ":/imp_text.ico", ":/dark/darkImp_text.ico");

    connect(ui->actionNew_Scene,    SIGNAL(triggered()), SLOT(newSceneMenuItem()));
    connect(ui->actionRemove_Scene, SIGNAL(triggered()), SLOT(removeSceneMenuItem()));
    connect(ui->actionMove_Up,      SIGNAL(triggered()), SLOT(moveUpMenuItem()));
    connect(ui->actionMove_Down,    SIGNAL(triggered()), SLOT(moveDownMenuItem()));
    connect(ui->actionMove_In,      SIGNAL(triggered()), SLOT(moveInMenuItem()));
    connect(ui->actionMove_Out,     SIGNAL(triggered()), SLOT(moveOutMenuItem()));
    connect(ui->actionTags,         SIGNAL(triggered()), SLOT(tagsMenuItem()));
    setMenuIcons(ui->actionNew_Scene,    ":/scene.ico",    ":/dark/darkScene.ico");
    setMenuIcons(ui->actionRemove_Scene, ":/delete.ico",   ":/dark/darkDelete.ico");
    setMenuIcons(ui->actionMove_Up,      ":/moveUp.ico",   ":/dark/darkMoveUp.ico");
    setMenuIcons(ui->actionMove_Down,    ":/moveDown.ico", ":/dark/darkMoveDown.ico");
    setMenuIcons(ui->actionMove_In,      ":/moveIn.ico",   ":/dark/darkMoveIn.ico");
    setMenuIcons(ui->actionMove_Out,     ":/moveOut.ico",  ":/dark/darkMoveOut.ico");
    setMenuIcons(ui->actionTags,         ":/tags.ico",     ":/dark/darkTags.ico");

    connect(ui->action_Undo,             SIGNAL(triggered()), SLOT(undoMenuItem()));
    connect(ui->action_Redo,             SIGNAL(triggered()), SLOT(redoMenuItem()));
    connect(ui->action_Cut,              SIGNAL(triggered()), SLOT(cutMenuItem()));
    connect(ui->actionC_opy,             SIGNAL(triggered()), SLOT(copyMenuItem()));
    connect(ui->action_Paste,            SIGNAL(triggered()), SLOT(pasteMenuItem()));
    connect(ui->action_Search,           SIGNAL(triggered()), SLOT(searchMenuItem()));
    connect(ui->actionFind_Next,         SIGNAL(triggered()), SLOT(findNextMenuItem()));
    connect(ui->actionRepl_ace,          SIGNAL(triggered()), SLOT(replaceMenuItem()));
    connect(ui->actionReplace_Selection, SIGNAL(triggered()), SLOT(replaceSelectionMenuItem()));
    connect(ui->actionReplace_All,       SIGNAL(triggered()), SLOT(replaceAllMenuItem()));
    connect(ui->action_Bold,             SIGNAL(triggered()), SLOT(boldMenuItem()));
    connect(ui->action_Italic,           SIGNAL(triggered()), SLOT(italicMenuItem()));
    connect(ui->action_Underline,        SIGNAL(triggered()), SLOT(underlineMenuItem()));
    connect(ui->action_Left_JUstify,     SIGNAL(triggered()), SLOT(leftJustifyMenuItem()));
    connect(ui->action_Center,           SIGNAL(triggered()), SLOT(centerMenuItem()));
    connect(ui->action_Full_Justify,     SIGNAL(triggered()), SLOT(fullJustifyMenuItem()));
    connect(ui->action_Right_Justify,    SIGNAL(triggered()), SLOT(rightJustifyMenuItem()));
    connect(ui->actionIndent,            SIGNAL(triggered()), SLOT(indentMenuItem()));
    setMenuIcons(ui->action_Undo,             ":/undo.ico",         ":/dark/darkUndo.ico");
    setMenuIcons(ui->action_Redo,             ":/redo.ico",         ":/dark/darkRedo.ico");
    setMenuIcons(ui->action_Cut,              ":/cut.ico",          ":/dark/darkCut.ico");
    setMenuIcons(ui->actionC_opy,             ":/copy.ico",         ":/dark/darkCopy.ico");
    setMenuIcons(ui->action_Paste,            ":/paste.ico",        ":/dark/darkPaste.ico");
    setMenuIcons(ui->action_Search,           ":/search.ico",       ":/dark/darkSearch.ico");
    setMenuIcons(ui->actionFind_Next,         ":/search.ico",       ":/dark/darkSearch.ico");
    setMenuIcons(ui->actionRepl_ace,          ":/replace.ico",      ":/dark/darkReplace.ico");
    setMenuIcons(ui->actionReplace_Selection, ":/replace.ico",      ":/dark/darkReplace.ico");
    setMenuIcons(ui->actionReplace_All,       ":/replace.ico",      ":/dark/darkReplace.ico");
    setMenuIcons(ui->action_Bold,             ":/bold.ico",         ":/dark/darkBold.ico");
    setMenuIcons(ui->action_Italic,           ":/italic.ico",       ":/dark/darkItalic.ico");
    setMenuIcons(ui->action_Underline,        ":/underline.ico",    ":/dark/darkUnderline.ico");
    setMenuIcons(ui->action_Left_JUstify,     ":/leftJustify.ico",  ":/dark/darkReplace.ico");
    setMenuIcons(ui->action_Center,           ":/center.ico",       ":/dark/darkCenter.ico");
    setMenuIcons(ui->action_Full_Justify,     ":/fullJustify.ico",  ":/dark/darkFullJustify.ico");
    setMenuIcons(ui->action_Right_Justify,    ":/rightJustify.ico", ":/dark/darkRightJustify.ico");
    setMenuIcons(ui->actionIndent,            ":/indent.ico",       ":/dark/darkIndent.ico");
    ui->action_Bold->setCheckable(true);
    ui->action_Italic->setCheckable(true);
    ui->action_Underline->setCheckable(true);
    ui->action_Left_JUstify->setCheckable(true);
    ui->action_Center->setCheckable(true);
    ui->action_Full_Justify->setCheckable(true);
    ui->action_Right_Justify->setCheckable(true);
    ui->actionIndent->setCheckable(true);

    connect(ui->action_Distraction_Free, SIGNAL(triggered()), SLOT(fullScreenMenuItem()));
    connect(ui->action_Scripts,          SIGNAL(triggered()), SLOT(scriptsMenuItem()));
    connect(ui->action_Word_Count,       SIGNAL(triggered()), SLOT(wordCountMenuItem()));
    connect(ui->actionRead_Aloud,        SIGNAL(triggered()), SLOT(readAloudMenuItem()));
    setMenuIcons(ui->action_Distraction_Free, ":/fullScreen.ico", ":/dark/darkFullScreen.ico");
    setMenuIcons(ui->action_Scripts,          ":/script.ico",     ":/dark/darkScript.ico");
    setMenuIcons(ui->action_Word_Count,       ":/wc.ico",         ":/dark/darkWc.ico");
    setMenuIcons(ui->actionRead_Aloud,        ":/speech.ico",     ":/dark/darkSpeech.ico");

    connect(ui->action_About,         SIGNAL(triggered()), SLOT(aboutMenuItem()));
    connect(ui->action_Documentation, SIGNAL(triggered()), SLOT(documentationMenuItem()));
    connect(ui->action_Options,       SIGNAL(triggered()), SLOT(optionsMenuItem()));
    setMenuIcons(ui->action_About,         ":/about.ico",    ":/dark/darkAbout.ico");
    setMenuIcons(ui->action_Documentation, ":/help.ico",     ":/dark/darkHelp.ico");
    setMenuIcons(ui->action_Options,       ":/settings.ico", ":/dark/darkSettings.ico");

    connect(ui->treeWidget, SIGNAL(currentItemChanged(QTreeWidgetItem*,QTreeWidgetItem*)), SLOT(currentItemChanged(QTreeWidgetItem*,QTreeWidgetItem*)));
    connect(ui->treeWidget, SIGNAL(itemDoubleClicked(QTreeWidgetItem*,int)),               SLOT(itemDoubleClicked(QTreeWidgetItem*,int)));

    connect(ui->textEdit, SIGNAL(redoAvailable(bool)),     SLOT(redoAvailable(bool)));
    connect(ui->textEdit, SIGNAL(cursorPositionChanged()), SLOT(setEditButtons()));
    connect(ui->textEdit, SIGNAL(selectionChanged()),      SLOT(setEditButtons()));
    connect(ui->textEdit, SIGNAL(textChanged()),           SLOT(textChanged()));
    connect(ui->textEdit, SIGNAL(undoAvailable(bool)),     SLOT(undoAvailable(bool)));

    auto tb = ui->toolBar;
    createToolBarItem(tb, ":/moveUp.ico",     "Move Scene Up",     "Move the current scene up in the group",      SIGNAL(triggered()), SLOT(moveUpMenuItem()));
    createToolBarItem(tb, ":/moveDown.ico",   "Move Scene Down",   "Move the current scene down in the group",    SIGNAL(triggered()), SLOT(moveDownMenuItem()));
    createToolBarItem(tb, ":/moveIn.ico",     "Move Scene In",     "Move the current scene into the above group", SIGNAL(triggered()), SLOT(moveInMenuItem()));
    createToolBarItem(tb, ":/moveOut.ico",    "Move Scene Out",    "Move the current scene out of the group",     SIGNAL(triggered()), SLOT(moveOutMenuItem()));
    createToolBarItem(tb, ":/tags.ico",       "Edit Tags",         "Rename and/or add/remove tags for the scene", SIGNAL(triggered()), SLOT(tagsMenuItem()));
    tb->addSeparator();
    createToolBarItem(tb, ":/cut.ico",        "Cut",               "Cut selected text",                           SIGNAL(triggered()), SLOT(cutMenuItem()));
    createToolBarItem(tb, ":/copy.ico",       "Copy",              "Copy selected text",                          SIGNAL(triggered()), SLOT(copyMenuItem()));
    createToolBarItem(tb, ":/paste.ico",      "Paste",             "Paste item on clipboard into text",           SIGNAL(triggered()), SLOT(pasteMenuItem()));
    tb->addSeparator();
    createToolBarItem(tb, ":/bold.ico",       "Bold Text",         "Bold text",                                   SIGNAL(triggered()), SLOT(boldMenuItem()));
    createToolBarItem(tb, ":/italic.ico",     "Italic Text",       "Italic text",                                 SIGNAL(triggered()), SLOT(italicMenuItem()));
    createToolBarItem(tb, ":/underline.ico",  "Underline Text",    "Underline text",                              SIGNAL(triggered()), SLOT(underlineMenuItem()));
    _buttons["Bold Text"]->setCheckable(true);
    _buttons["Italic Text"]->setCheckable(true);
    _buttons["Underline Text"]->setCheckable(true);
    tb->addSeparator();
    createToolBarItem(tb, ":/fullScreen.ico", "Distraction Free", "Distraction free editing",                     SIGNAL(triggered()), SLOT(fullScreenMenuItem()));
    createToolBarItem(tb, ":/wc.ico",         "Word Count",       "Word count",                                   SIGNAL(triggered()), SLOT(wordCountMenuItem()));
    tb->addSeparator();
    createToolBarItem(tb, ":/settings.ico",   "Settings",         "Settings",                                     SIGNAL(triggered()), SLOT(optionsMenuItem()));

    checkDarkMode();
}

MainWindow::MainWindow(const QString& file, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , _dirty(false) {
    ui->setupUi(this);
    _main_window = this;

    _L = luaL_newstate();
    luaL_openlibs(_L);
    registerFunctions(_L);
    registerSignals();
    loadOptions();

    _speech = new QTextToSpeech(nullptr);

    _dir = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation);
    ui->textEdit->setDir(_dir);

    setUnifiedTitleAndToolBarOnMac(true);
    registerExtensionHandler();
    _cleanItTimer = new QBasicTimer();
    _cleanItTimer->start(100, this);

    if (_autosave) {
        _autoSaveTimer = new QBasicTimer();
        _autoSaveTimer->start(_autosaveInterval * 60000, this);
    }
    if (file.isEmpty()) newMenuItem();
    else openAction(file);
}

MainWindow::~MainWindow() {
    lua_close(_L);

    if (0 != _appAtom) {
        ::GlobalDeleteAtom(_appAtom);
        _appAtom = 0;
    }
    if (0 != _systemTopicAtom) {
        ::GlobalDeleteAtom(_systemTopicAtom);
        _systemTopicAtom = 0;
    }

    delete ui;
}
//=================================================================

//====[SLOTS]======================================================
void MainWindow::autoSave() {
    if (!_dirty) return;
    if (_filename.isEmpty()) return;
    if (!_autosave) return;

    _autoSaveTimer->stop();

    save();

    _autoSaveTimer->start(_autosaveInterval * 60000, this);
}

void MainWindow::switchIcons(displayMode to) {
    for (auto x = _menuIcons.begin(); x != _menuIcons.end(); ++x) {
        QMenu* menu = x.key();
        QMap<displayMode, QString>& mode = x.value();
        menu->setIcon(QIcon(mode[to]));
    }
    for (auto x = _actionIcons.begin(); x != _actionIcons.end(); ++x) {
        QAction* action = x.key();
        QMap<displayMode, QString>& mode = x.value();
        action->setIcon(QIcon(mode[to]));
    }
}

void MainWindow::checkDarkMode() {
    static enum displayMode _current = None;

    if (windowsIsInDarkTheme()) {
        if (_current != Dark) {
            QFile f(":qdarkstyle/theme/darkstyle.qss");
            if (!f.exists()) return;
            else  {
               f.open(QFile::ReadOnly | QFile::Text);
               QTextStream ts(&f);
               getApp().setStyleSheet(ts.readAll());
               f.close();
               _current = Dark;
               switchIcons(Dark);
            }
        }
    } else if (_current != Light) {
        getApp().setStyleSheet("");
        _current = Light;
        switchIcons(Light);
    }

    QTimer::singleShot(1000, this, SLOT(checkDarkMode()));
}

void MainWindow::textChanged() {
    if (_ignore) return;
    dirty();
}

//=================================================================
