#ifndef RTF_H
#define RTF_H

#include <QObject>

#include "globals.h"
#include "structures.h"

// RTF library interface
int rtf_open(QString filename, QString fonts, QString colors);			// Creates new RTF document
int rtf_close();														// Closes created RTF document
bool rtf_write_header();												// Writes RTF document header
void rtf_init();														// Sets global RTF library params
void rtf_set_fonttable(QString fonts);									// Sets new RTF document font table
void rtf_set_colortable(QString colors);								// Sets new RTF document color table
RTF_DOCUMENT_FORMAT* rtf_get_documentformat();							// Gets RTF document formatting properties
void rtf_set_documentformat(RTF_DOCUMENT_FORMAT* df);					// Sets RTF document formatting properties
bool rtf_write_documentformat();										// Writes RTF document formatting properties
RTF_SECTION_FORMAT* rtf_get_sectionformat();							// Gets RTF section formatting properties
void rtf_set_sectionformat(RTF_SECTION_FORMAT* sf);						// Sets RTF section formatting properties
bool rtf_write_sectionformat();											// Writes RTF section formatting properties
int rtf_start_section();												// Starts new RTF section
RTF_PARAGRAPH_FORMAT* rtf_get_paragraphformat();						// Gets RTF paragraph formatting properties
void rtf_set_paragraphformat(RTF_PARAGRAPH_FORMAT* pf);					// Sets RTF paragraph formatting properties
bool rtf_write_paragraphformat();										// Writes RTF paragraph formatting properties
int rtf_start_paragraph(QString text, bool newPar);						// Starts new RTF paragraph
int rtf_load_image(QString image);                          			// Loads image from file
void rtf_set_defaultformat();											// Sets default RTF document formatting
int rtf_start_tablerow();												// Starts new RTF table row
int rtf_end_tablerow();													// Ends RTF table row
int rtf_start_tablecell(int rightMargin);								// Starts new RTF table cell
int rtf_end_tablecell();												// Ends RTF table cell
RTF_TABLEROW_FORMAT* rtf_get_tablerowformat();							// Gets RTF table row formatting properties
void rtf_set_tablerowformat(RTF_TABLEROW_FORMAT* rf);					// Sets RTF table row formatting properties
RTF_TABLECELL_FORMAT* rtf_get_tablecellformat();						// Gets RTF table cell formatting properties
void rtf_set_tablecellformat(RTF_TABLECELL_FORMAT* cf);					// Sets RTF table cell formatting properties
QString rtf_get_bordername(int border_type);        					// Gets border name
QString rtf_get_shadingname(int shading_type, bool cell);				// Gets shading name

class RTF {
private:
    struct Scene {
        QList<QString> _tags;
        QString _html;
        QString _name;
        QList<struct Scene> _children;

        Scene(): _html("") { }
        Scene(const Scene& s): _tags(s._tags), _html(s._html), _name(s._name), _children(s._children) { }

        Scene& operator=(const Scene& s) { if (this != &s) { _tags = s._tags; _html = s._html; _name = s._name; _children = s._children; } return *this; }
    };

    struct Tree {
        Scene _top;
    };

    QString _cover;
    QString _dir;
    Tree _tree;
    int _align = RTF_PARAGRAPHALIGN_LEFT;
    QList<int> _stack;

    Scene objectToItem(const QJsonObject& obj);
    Scene objectToScene(const QJsonObject& obj);
    bool processCharacters(QString& text, bool first);
    bool processParagraph(QString& html);
    void novelToBook(QJsonObject obj, Tree& tree);
    void processAlignment(QString style);
    void resetAlignment();
    void resetCharacters();
    void sceneToRTF(QString html);
    void sceneToRTF(RTF::Scene scene);

public:
    RTF(QString dir, QJsonObject obj);
};

#endif
