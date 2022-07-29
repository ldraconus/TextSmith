#include <QFile>
#include <QImage>
#include <QJsonArray>
#include <QJsonObject>
#include <QObject>
#include <QStandardPaths>
#include <QTemporaryFile>
#include <QTextStream>

#include "errors.h"
#include "globals.h"
#include "rtf.h"

RTF_DOCUMENT_FORMAT rtfDocFormat;					// RTF document formatting params
RTF_SECTION_FORMAT rtfSecFormat;					// RTF section formatting params
RTF_PARAGRAPH_FORMAT rtfParFormat;					// RTF paragraph formatting params
RTF_TABLEROW_FORMAT rtfRowFormat;					// RTF table row formatting params
RTF_TABLECELL_FORMAT rtfCellFormat;					// RTF table cell formatting params

// RTF library global params
QFile rtfFile;
QTextStream out;
QString rtfFontTable;
QString rtfColorTable;
QImage rtfPicture;

// Creates new RTF document
int rtf_open(QString filename, QString fonts, QString colors) {
	// Initialize global params
	rtf_init();

	// Set RTF document font table
    if (!fonts.isEmpty()) rtf_set_fonttable(fonts);

	// Set RTF document color table
    if (!colors.isEmpty()) rtf_set_colortable(colors);

	// Create RTF document
    rtfFile.setFileName(filename);

    if (rtfFile.open(QFile::WriteOnly)) {
		// Write RTF document header
        if (!rtf_write_header()) return RTF_HEADER_ERROR;

		// Write RTF document formatting properties
        if (!rtf_write_documentformat()) return RTF_DOCUMENTFORMAT_ERROR;

		// Create first RTF document section with default formatting
		rtf_write_sectionformat();
    } else return RTF_OPEN_ERROR;

	// Return error flag
    return RTF_SUCCESS;
}

// Closes created RTF document
int rtf_close() {
	// Write RTF document end part
    out << "\n\\par}";

	// Close RTF document
    rtfFile.close();

	// Return error flag
    return RTF_SUCCESS;
}

// Writes RTF document header
bool rtf_write_header() {
	// Standard RTF document header
    QString rtfText = "{\\rtf1\\ansi\\ansicpg1252\\deff0{\\fonttbl";
    rtfText += rtfFontTable;
    rtfText += "}{\\colortbl";
    rtfText += rtfColorTable;
    rtfText += "}{\\*\\generator TextSmith ver. 1.0;}";
    rtfText +="\n{\\info{\\author TextSmith ver. 1.0}{\\company SoftwareOnHand.}}";

	// Writes standard RTF document header part
    out.setDevice(&rtfFile);
    out << rtfText;

	// Return error flag
    return true;
}

// Sets global RTF library params
void rtf_init() {
	// Set RTF document default font table
    rtfFontTable = "{\\f0\\froman\\fcharset0\\cpg1252 Times New Roman}";
    rtfFontTable += "{\\f1\\fswiss\\fcharset0\\cpg1252 Arial}";
    rtfFontTable += "{\\f2\\fmodern\\fcharset0\\cpg1252 Courier New}";
    rtfFontTable += "{\\f3\\fscript\\fcharset0\\cpg1252 Cursive}";
    rtfFontTable += "{\\f4\\fdecor\\fcharset0\\cpg1252 Old English}";
    rtfFontTable += "{\\f5\\ftech\\fcharset0\\cpg1252 Symbol}";
    rtfFontTable += "{\\f6\\fbidi\\fcharset0\\cpg1252 Miriam}";

	// Set RTF document default color table
    rtfColorTable = "\\red0\\green0\\blue0;";
    rtfColorTable += "\\red255\\green0\\blue0;";
    rtfColorTable += "\\red0\\green255\\blue0;";
    rtfColorTable += "\\red0\\green0\\blue255;";
    rtfColorTable += "\\red255\\green255\\blue0;";
    rtfColorTable += "\\red255\\green0\\blue255;";
    rtfColorTable += "\\red0\\green255\\blue255;";
    rtfColorTable += "\\red255\\green255\\blue255;";
    rtfColorTable += "\\red128\\green0\\blue0;";
    rtfColorTable += "\\red0\\green128\\blue0;";
    rtfColorTable += "\\red0\\green0\\blue128;";
    rtfColorTable += "\\red128\\green128\\blue0;";
    rtfColorTable += "\\red128\\green0\\blue128;";
    rtfColorTable += "\\red0\\green128\\blue128;";
    rtfColorTable += "\\red128\\green128\\blue128;";

	// Set default formatting
	rtf_set_defaultformat();
}

// Sets default RTF document formatting
void rtf_set_defaultformat() {
	// Set default RTF document formatting properties
    RTF_DOCUMENT_FORMAT df = { RTF_DOCUMENTVIEWKIND_PAGE, 100, 12240, 15840, 1800, 1800, 1440, 1440, false, 0, false };
	rtf_set_documentformat(&df);

	// Set default RTF section formatting properties
    RTF_SECTION_FORMAT sf = { RTF_SECTIONBREAK_CONTINUOUS, false, true, 12240, 15840, 1800, 1800, 1440, 1440, 0, 720, 720, false, 720, 720, false, 1, 720, false };
	rtf_set_sectionformat(&sf);

    // Set default RTF paragraph formatting properties
    RTF_PARAGRAPH_FORMAT pf = { RTF_PARAGRAPHBREAK_NONE, false, true, RTF_PARAGRAPHALIGN_LEFT, 0, 0, 0, 0, 0, 0,
                                (char*) "", false, false, false, { }, false, { }, false, { }, false, { }, { } };
	pf.BORDERS.borderColor = 0;
	pf.BORDERS.borderKind = RTF_PARAGRAPHBORDERKIND_NONE;
	pf.BORDERS.borderSpace = 0;
	pf.BORDERS.borderType = RTF_PARAGRAPHBORDERTYPE_STHICK;
	pf.BORDERS.borderWidth = 0;
	pf.CHARACTER.animatedCharacter = false;
	pf.CHARACTER.backgroundColor = 0;
	pf.CHARACTER.boldCharacter = false;
	pf.CHARACTER.capitalCharacter = false;
	pf.CHARACTER.doublestrikeCharacter = false;
	pf.CHARACTER.embossCharacter = false;
	pf.CHARACTER.engraveCharacter = false;
	pf.CHARACTER.expandCharacter = 0;
	pf.CHARACTER.fontNumber = 0;
	pf.CHARACTER.fontSize = 24;
	pf.CHARACTER.foregroundColor = 0;
	pf.CHARACTER.italicCharacter = false;
	pf.CHARACTER.kerningCharacter = 0;
	pf.CHARACTER.outlineCharacter = false;
	pf.CHARACTER.scaleCharacter = 100;
	pf.CHARACTER.shadowCharacter = false;
	pf.CHARACTER.smallcapitalCharacter = false;
	pf.CHARACTER.strikeCharacter = false;
	pf.CHARACTER.subscriptCharacter = false;
	pf.CHARACTER.superscriptCharacter = false;
	pf.CHARACTER.underlineCharacter = 0;
	pf.NUMS.numsChar = char(0x95);
	pf.NUMS.numsLevel = 11;
	pf.NUMS.numsSpace = 360;
	pf.SHADING.shadingBkColor = 0;
	pf.SHADING.shadingFillColor = 0;
	pf.SHADING.shadingIntensity = 0;
	pf.SHADING.shadingType = RTF_PARAGRAPHSHADINGTYPE_FILL;
	pf.TABS.tabKind = RTF_PARAGRAPHTABKIND_NONE;
	pf.TABS.tabLead = RTF_PARAGRAPHTABLEAD_NONE;
	pf.TABS.tabPosition = 0;
	rtf_set_paragraphformat(&pf);

	// Set default RTF table row formatting properties
    RTF_TABLEROW_FORMAT rf = { RTF_ROWTEXTALIGN_LEFT, 0, 0, 0, 0, 0, 0 };
	rtf_set_tablerowformat(&rf);

	// Set default RTF table cell formatting properties
    RTF_TABLECELL_FORMAT cf = { RTF_CELLTEXTALIGN_CENTER, 0, 0, 0, 0, RTF_CELLTEXTDIRECTION_LRTB, false, { }, { }, { }, { }, { } };
	cf.SHADING.shadingBkColor = 0;
	cf.SHADING.shadingFillColor = 0;
	cf.SHADING.shadingIntensity = 0;
	cf.SHADING.shadingType = RTF_PARAGRAPHSHADINGTYPE_FILL;
	cf.borderBottom.border = false;
	cf.borderBottom.BORDERS.borderColor = 0;
	cf.borderBottom.BORDERS.borderKind = RTF_PARAGRAPHBORDERKIND_NONE;
	cf.borderBottom.BORDERS.borderSpace = 0;
	cf.borderBottom.BORDERS.borderType = RTF_PARAGRAPHBORDERTYPE_STHICK;
	cf.borderBottom.BORDERS.borderWidth = 5;
	cf.borderLeft.border = false;
	cf.borderLeft.BORDERS.borderColor = 0;
	cf.borderLeft.BORDERS.borderKind = RTF_PARAGRAPHBORDERKIND_NONE;
	cf.borderLeft.BORDERS.borderSpace = 0;
	cf.borderLeft.BORDERS.borderType = RTF_PARAGRAPHBORDERTYPE_STHICK;
	cf.borderLeft.BORDERS.borderWidth = 5;
	cf.borderRight.border = false;
	cf.borderRight.BORDERS.borderColor = 0;
	cf.borderRight.BORDERS.borderKind = RTF_PARAGRAPHBORDERKIND_NONE;
	cf.borderRight.BORDERS.borderSpace = 0;
	cf.borderRight.BORDERS.borderType = RTF_PARAGRAPHBORDERTYPE_STHICK;
	cf.borderRight.BORDERS.borderWidth = 5;
	cf.borderTop.border = false;
	cf.borderTop.BORDERS.borderColor = 0;
	cf.borderTop.BORDERS.borderKind = RTF_PARAGRAPHBORDERKIND_NONE;
	cf.borderTop.BORDERS.borderSpace = 0;
	cf.borderTop.BORDERS.borderType = RTF_PARAGRAPHBORDERTYPE_STHICK;
	cf.borderTop.BORDERS.borderWidth = 5;
	rtf_set_tablecellformat(&cf);
}

// Sets new RTF document font table
void rtf_set_fonttable(QString fonts) {
	// Clear old font table
    rtfFontTable = "";

	// Create new RTF document font table
	int font_number = 0;
    QStringList list = fonts.split(";");
    for (const auto& token: list) {
		// Format font table entry
        rtfFontTable += QString::asprintf("{\\f%d\\fnil\\fcharset0\\cpg1252 %s}", font_number, token.toStdString().c_str());
		font_number++;
	}
}

// Sets new RTF document color table
void rtf_set_colortable(QString colors) {
	// Clear old color table
    rtfColorTable = "";

	// Create new RTF document color table
    QStringList list = colors.split(";");
    for (auto token = list.begin(); token != list.end(); ++token) {
		// Red
        rtfColorTable += "\\red" + *token;

		// Green
        if (++token != list.end()) rtfColorTable += "\\green" + *token;

		// Blue
        if (++token != list.end()) rtfColorTable += "\\blue" + *token;
	}
}

// Sets RTF document formatting properties
void rtf_set_documentformat(RTF_DOCUMENT_FORMAT* df) {
	// Set new RTF document formatting properties
    memcpy(&rtfDocFormat, df, sizeof(RTF_DOCUMENT_FORMAT));
}

// Writes RTF document formatting properties
bool rtf_write_documentformat() {
	// RTF document text
    QString rtfText;

    rtfText = QString::asprintf("\\viewkind%d\\viewscale%d\\paperw%d\\paperh%d\\margl%d\\margr%d\\margt%d\\margb%d\\gutter%d",
                                rtfDocFormat.viewKind, rtfDocFormat.viewScale, rtfDocFormat.paperWidth, rtfDocFormat.paperHeight,
                                rtfDocFormat.marginLeft, rtfDocFormat.marginRight, rtfDocFormat.marginTop, rtfDocFormat.marginBottom,
                                rtfDocFormat.gutterWidth);

    if (rtfDocFormat.facingPages) rtfText += "\\facingp";
    if (rtfDocFormat.readOnly) rtfText += "\\annotprot";

	// Writes RTF document formatting properties
    out << rtfText;

	// Return error flag
    return true;
}

// Sets RTF section formatting properties
void rtf_set_sectionformat(RTF_SECTION_FORMAT* sf) {
	// Set new RTF section formatting properties
    memcpy(&rtfSecFormat, sf, sizeof(RTF_SECTION_FORMAT));
}

// Writes RTF section formatting properties
bool rtf_write_sectionformat() {
	// RTF document text
    QString rtfText;

	// Format new section
    QString text;
    if (rtfSecFormat.newSection) text += "\\sect";
    if (rtfSecFormat.defaultSection) text += "\\sectd";
    if (rtfSecFormat.showPageNumber) text += QString::asprintf("\\pgnx%d\\pgny%d", rtfSecFormat.pageNumberOffsetX, rtfSecFormat.pageNumberOffsetY);
	
	// Format section break
    QString sbr;
    switch (rtfSecFormat.sectionBreak) {
    case RTF_SECTIONBREAK_CONTINUOUS: sbr += "\\sbknone"; break; // Continuous break
    case RTF_SECTIONBREAK_COLUMN:     sbr += "\\sbkcol";  break; // Column break;
    case RTF_SECTIONBREAK_PAGE:       sbr += "\\sbkpage"; break; // Page break
    case RTF_SECTIONBREAK_EVENPAGE:   sbr += "\\sbkeven"; break; // Even-page break
    case RTF_SECTIONBREAK_ODDPAGE:    sbr += "\\sbkodd";  break; // Odd-page break
	}

	// Format section columns
    QString cols;
    if (rtfSecFormat.cols == true) {
		// Format columns
        cols = QString::asprintf("\\cols%d\\colsx%d", rtfSecFormat.colsNumber, rtfSecFormat.colsDistance);

        if (rtfSecFormat.colsLineBetween) cols += "\\linebetcol";
	}

    rtfText = QString::asprintf("\n%s%s%s\\pgwsxn%d\\pghsxn%d\\marglsxn%d\\margrsxn%d\\margtsxn%d\\margbsxn%d\\guttersxn%d\\headery%d\\footery%d",
                                text.toStdString().c_str(), sbr.toStdString().c_str(), cols.toStdString().c_str(), rtfSecFormat.pageWidth,
                                rtfSecFormat.pageHeight, rtfSecFormat.pageMarginLeft, rtfSecFormat.pageMarginRight, rtfSecFormat.pageMarginTop,
                                rtfSecFormat.pageMarginBottom, rtfSecFormat.pageGutterWidth, rtfSecFormat.pageHeaderOffset, rtfSecFormat.pageFooterOffset);

    // Writes RTF section formatting properties
    out << rtfText;

    // Return error flag
    return true;
}

// Starts new RTF section
int rtf_start_section()
{
	// Set new section flag
	rtfSecFormat.newSection = true;

	// Starts new RTF section
    return rtf_write_sectionformat() ? RTF_SUCCESS : RTF_SECTIONFORMAT_ERROR;
}

// Sets RTF paragraph formatting properties
void rtf_set_paragraphformat(RTF_PARAGRAPH_FORMAT* pf) {
	// Set new RTF paragraph formatting properties
    memcpy(&rtfParFormat, pf, sizeof(RTF_PARAGRAPH_FORMAT));
}

// Writes RTF paragraph formatting properties
bool rtf_write_paragraphformat() {
	// RTF document text
    QString rtfText;

	// Format new paragraph
    QString text;
    if (rtfParFormat.newParagraph) text += "\\par";
    if (rtfParFormat.defaultParagraph) text += "\\pard";
    if (rtfParFormat.tableText == false) text += "\\plain";
    else text += "\\intbl";
	
    switch (rtfParFormat.paragraphBreak) {
    case RTF_PARAGRAPHBREAK_NONE:                       break; // No break
    case RTF_PARAGRAPHBREAK_PAGE:   text += "\\page";   break; // Page break;
    case RTF_PARAGRAPHBREAK_COLUMN: text += "\\column"; break; // Column break;
    case RTF_PARAGRAPHBREAK_LINE:   text += "\\line";   break; // Line break;
	}

	// Format aligment
    switch (rtfParFormat.paragraphAligment) {
    case RTF_PARAGRAPHALIGN_LEFT:    text += "\\ql"; break; // Left aligned paragraph
    case RTF_PARAGRAPHALIGN_CENTER:  text += "\\qc"; break; // Center aligned paragraph
    case RTF_PARAGRAPHALIGN_RIGHT:   text += "\\qr"; break; // Right aligned paragraph
    case RTF_PARAGRAPHALIGN_JUSTIFY: text += "\\qj"; break; // Justified aligned paragraph
	}

	// Format tabs
    if (rtfParFormat.paragraphTabs == true) {
		// Set tab kind
        switch (rtfParFormat.TABS.tabKind) {
        case RTF_PARAGRAPHTABKIND_NONE:                       break; // No tab
        case RTF_PARAGRAPHTABKIND_CENTER:  text += "\\tqc";   break; // Centered tab
        case RTF_PARAGRAPHTABKIND_RIGHT:   text += "\\tqr";   break; // Flush-right tab
        case RTF_PARAGRAPHTABKIND_DECIMAL: text += "\\tqdec"; break; // Decimal tab
		}

		// Set tab leader
        switch (rtfParFormat.TABS.tabLead) {
        case RTF_PARAGRAPHTABLEAD_NONE:	                         break; // No lead
        case RTF_PARAGRAPHTABLEAD_DOT:       text += "\\tldot";  break; // Leader dots
        case RTF_PARAGRAPHTABLEAD_MDOT:      text += "\\tlmdot"; break; // Leader middle dots
        case RTF_PARAGRAPHTABLEAD_HYPH:      text += "\\tlhyph"; break; // Leader hyphens
        case RTF_PARAGRAPHTABLEAD_UNDERLINE: text += "\\tlul";   break; // Leader underline
        case RTF_PARAGRAPHTABLEAD_THICKLINE: text += "\\tlth";   break; // Leader thick line
        case RTF_PARAGRAPHTABLEAD_EQUAL:     text += "\\tleq";   break; // Leader equal sign
		}

		// Set tab position
        text += QString::asprintf("\\tx%d", rtfParFormat.TABS.tabPosition);
	}

	// Format bullets and numbering
    if (rtfParFormat.paragraphNums == true) text += QString::asprintf("{\\*\\pn\\pnlvl%d\\pnsp%d\\pntxtb %c}",
                                                                      rtfParFormat.NUMS.numsLevel, rtfParFormat.NUMS.numsSpace,
                                                                      rtfParFormat.NUMS.numsChar);

	// Format paragraph borders
    if (rtfParFormat.paragraphBorders == true) {
        QString border;

		// Format paragraph border kind
        switch (rtfParFormat.BORDERS.borderKind) {
        case RTF_PARAGRAPHBORDERKIND_NONE:                        break; // No border
        case RTF_PARAGRAPHBORDERKIND_TOP:    border += "\\brdrt"; break; // Border top
        case RTF_PARAGRAPHBORDERKIND_BOTTOM: border += "\\brdrb"; break; // Border bottom
        case RTF_PARAGRAPHBORDERKIND_LEFT:   border += "\\brdrl"; break; // Border left
        case RTF_PARAGRAPHBORDERKIND_RIGHT:  border += "\\brdrr"; break; // Border right
        case RTF_PARAGRAPHBORDERKIND_BOX:    border += "\\box";   break; // Border box
		}

		// Format paragraph border type
        border += rtf_get_bordername(rtfParFormat.BORDERS.borderType);

		// Set paragraph border width
        border += QString::asprintf("\\brdrw%d\\brsp%d", rtfParFormat.BORDERS.borderWidth, rtfParFormat.BORDERS.borderSpace);
        text += border;

		// Set paragraph border color
        text += QString::asprintf("\\brdrcf%d", rtfParFormat.BORDERS.borderColor);
    }

	// Format paragraph shading
    if (rtfParFormat.paragraphShading == true) {
        text += QString::asprintf("\\shading%d", rtfParFormat.SHADING.shadingIntensity);

		// Format paragraph shading
        text += rtf_get_shadingname(rtfParFormat.SHADING.shadingType, false);

		// Set paragraph shading color
        text += QString::asprintf("\\cfpat%d\\cbpat%d", rtfParFormat.SHADING.shadingFillColor, rtfParFormat.SHADING.shadingBkColor);
	}

	// Format paragraph font
    QString font = QString::asprintf("\\animtext%d\\expndtw%d\\kerning%d\\charscalex%d\\f%d\\fs%d\\cf%d", rtfParFormat.CHARACTER.animatedCharacter,
                                     rtfParFormat.CHARACTER.expandCharacter, rtfParFormat.CHARACTER.kerningCharacter, rtfParFormat.CHARACTER.scaleCharacter,
                                     rtfParFormat.CHARACTER.fontNumber, rtfParFormat.CHARACTER.fontSize, rtfParFormat.CHARACTER.foregroundColor);
    if (rtfParFormat.CHARACTER.boldCharacter) font += "\\b";
    else font += "\\b0";
    if (rtfParFormat.CHARACTER.capitalCharacter) font += "\\caps";
    else font += "\\caps0";
    if (rtfParFormat.CHARACTER.doublestrikeCharacter) font += "\\striked1";
    else font += "\\striked0";
    if (rtfParFormat.CHARACTER.embossCharacter) font += "\\embo";
    if (rtfParFormat.CHARACTER.engraveCharacter) font += "\\impr";
    if (rtfParFormat.CHARACTER.italicCharacter) font += "\\i";
    else font += "\\i0";
    if (rtfParFormat.CHARACTER.outlineCharacter) font += "\\outl";
    else font += "\\outl0";
    if (rtfParFormat.CHARACTER.shadowCharacter) font += "\\shad";
    else font += "\\shad0";
    if (rtfParFormat.CHARACTER.smallcapitalCharacter) font += "\\scaps";
    else font += "\\scaps0";
    if (rtfParFormat.CHARACTER.strikeCharacter) font += "\\strike";
    else font += "\\strike0";
    if (rtfParFormat.CHARACTER.subscriptCharacter) font += "\\sub";
    if (rtfParFormat.CHARACTER.superscriptCharacter) font += "\\super";
	
    switch (rtfParFormat.CHARACTER.underlineCharacter) {
    case  0: font += "\\ulnone";     break; // None underline
    case  1: font += "\\ul";         break; // Continuous underline
    case  2: font += "\\uld";        break; // Dotted underline
    case  3: font += "\\uldash";     break; // Dashed underline
    case  4: font += "\\uldashd";    break; // Dash-dotted underline
    case  5: font += "\\uldashdd";   break; // Dash-dot-dotted underline
    case  6: font += "\\uldb";       break; // Double underline
    case  7: font += "\\ulhwave";    break; // Heavy wave underline
    case  8: font += "\\ulldash";    break; // Long dashed underline
    case  9: font += "\\ulth";       break; // Thick underline
    case 10: font += "\\ulthd";      break; // Thick dotted underline
    case 11: font += "\\ulthdash";   break; // Thick dashed underline
    case 12: font += "\\ulthdashd";  break; // Thick dash-dotted underline
    case 13: font += "\\ulthdashdd"; break; // Thick dash-dot-dotted underline
    case 14: font += "\\ulthldash";  break; // Thick long dashed underline
    case 15: font += "\\ululdbwave"; break; // Double wave underline
    case 16: font += "\\ulw";        break; // Word underline
    case 17: font += "\\ulwave";     break; // Wave underline
	}

	// Set paragraph tabbed text
    if (rtfParFormat.tabbedText == false)
        rtfText = QString::asprintf("\n%s\\fi%d\\li%d\\ri%d\\sb%d\\sa%d\\sl%d%s %s", text.toStdString().c_str(),
			rtfParFormat.firstLineIndent, rtfParFormat.leftIndent, rtfParFormat.rightIndent, rtfParFormat.spaceBefore, 
            rtfParFormat.spaceAfter, rtfParFormat.lineSpacing, font.toStdString().c_str(), rtfParFormat.paragraphText.toStdString().c_str());
    else rtfText = QString::asprintf("\\tab %s", rtfParFormat.paragraphText.toStdString().c_str());

    // Writes RTF section formatting properties
    out << rtfText;

    // Return error flag
    return true;
}

// Starts new RTF paragraph
int rtf_start_paragraph(QString text, bool newPar) {
	// Copy paragraph text
    rtfParFormat.paragraphText = text;

	// Set new paragraph
	rtfParFormat.newParagraph = newPar;

	// Starts new RTF paragraph
    return rtf_write_paragraphformat() ? RTF_SUCCESS : RTF_PARAGRAPHFORMAT_ERROR;
}

// Gets RTF document formatting properties
RTF_DOCUMENT_FORMAT* rtf_get_documentformat() {
	// Get current RTF document formatting properties
	return &rtfDocFormat;
}

// Gets RTF section formatting properties
RTF_SECTION_FORMAT* rtf_get_sectionformat() {
	// Get current RTF section formatting properties
	return &rtfSecFormat;
}

// Gets RTF paragraph formatting properties
RTF_PARAGRAPH_FORMAT* rtf_get_paragraphformat() {
	// Get current RTF paragraph formatting properties
	return &rtfParFormat;
}

// Loads image from file
int rtf_load_image(QString image) {
	// Check image type
    if (image.right(4) != ".bmp" &&
        image.right(4) != ".jpg" &&
        image.right(4) != ".png" &&
        image.right(4) != ".gif") return RTF_IMAGE_ERROR;

    // Read image file
    rtfPicture.load(image);

    // If image is loaded
    if (!rtfPicture.isNull()) {
        // Calculate image size
        long hmWidth = rtfPicture.width();
        long hmHeight = rtfPicture.height();

        // if not a jpeg, save to a temp file as a jpeg, reset image to temp name
        if (image.right(4) != ".jpg") {
            QTemporaryFile temp;
            image = temp.fileName() + ".jpg";
            rtfPicture.save(image, "JPG");
        }

        // load the image as a byte array
        QFile file(image);
        if (!file.open(QIODevice::ReadOnly)) return RTF_IMAGE_ERROR;
        QByteArray buffer(file.readAll());
        file.close();

        // Convert metafile binary data to hexadecimal
        QString str = buffer.toHex();

        // Format picture paragraph
        RTF_PARAGRAPH_FORMAT* pf = rtf_get_paragraphformat();
        pf->paragraphText = "";
        rtf_write_paragraphformat();

        // Writes RTF picture data
        QString rtfText = QString::asprintf("\n{\\pict\\jpegblip\\picw%ld\\pich%ld\n", hmWidth, hmHeight);
        out << rtfText << str << "}";
    }

	// Return error flag
    return RTF_SUCCESS;
}

// Starts new RTF table row
int rtf_start_tablerow() {
    QString tblrw;
	// Format table row aligment
    switch (rtfRowFormat.rowAligment) {
    case RTF_ROWTEXTALIGN_LEFT:   tblrw += "\\trql"; break; // Left align
    case RTF_ROWTEXTALIGN_CENTER: tblrw += "\\trqc"; break; // Center align
    case RTF_ROWTEXTALIGN_RIGHT:  tblrw += "\\trqr"; break; // Right align
	}

	// Writes RTF table data
    QString rtfText = QString::asprintf("\n\\trowd\\trgaph115%s\\trleft%d\\trrh%d\\trpaddb%d\\trpaddfb3\\trpaddl%d\\trpaddfl3\\trpaddr%d\\trpaddfr3\\trpaddt%d\\trpaddft3",
                                        tblrw.toStdString().c_str(), rtfRowFormat.rowLeftMargin, rtfRowFormat.rowHeight, rtfRowFormat.marginTop, rtfRowFormat.marginBottom,
                                        rtfRowFormat.marginLeft, rtfRowFormat.marginRight);
    out << rtfText;

    return RTF_SUCCESS;
}


// Ends RTF table row
int rtf_end_tablerow() {
	// Writes RTF table data
    out << "\n\\trgaph115\\row\\pard";

    return RTF_SUCCESS;
}


// Starts new RTF table cell
int rtf_start_tablecell(int rightMargin) {
    QString tblcla;
	// Format table cell text aligment
    switch (rtfCellFormat.textVerticalAligment) {
    case RTF_CELLTEXTALIGN_TOP:    tblcla +="\\clvertalt";  break; // Top align
    case RTF_CELLTEXTALIGN_CENTER: tblcla += "\\clvertalc"; break; // Center align
    case RTF_CELLTEXTALIGN_BOTTOM: tblcla += "\\clvertalb"; break; // Bottom align
	}

    QString tblcld;
	// Format table cell text direction
    switch (rtfCellFormat.textDirection) {
    case RTF_CELLTEXTDIRECTION_LRTB:  tblcld += "\\cltxlrtb";  break; // Left to right, top to bottom
    case RTF_CELLTEXTDIRECTION_RLTB:  tblcld += "\\cltxtbrl";  break; // Right to left, top to bottom
    case RTF_CELLTEXTDIRECTION_LRBT:  tblcld += "\\cltxbtlr";  break; // Left to right, bottom to top
    case RTF_CELLTEXTDIRECTION_LRTBV: tblcld += "\\cltxlrtbv"; break; // Left to right, top to bottom, vertical
    case RTF_CELLTEXTDIRECTION_RLTBV: tblcld += "\\cltxtbrlv"; break; // Right to left, top to bottom, vertical
	}

    QString tbclbrb;
    QString tbclbrl;
    QString tbclbrr;
    QString tbclbrt;
	// Format table cell border
    if (rtfCellFormat.borderBottom.border == true) {
		// Bottom cell border
        QString tbclbt = "\\clbrdrb";

        QString border = rtf_get_bordername(rtfCellFormat.borderBottom.BORDERS.borderType);

        tbclbrb = QString::asprintf("%s%s\\brdrw%d\\brsp%d\\brdrcf%d", tbclbt.toStdString().c_str(), border.toStdString().c_str(),
                                    rtfCellFormat.borderBottom.BORDERS.borderWidth, rtfCellFormat.borderBottom.BORDERS.borderSpace,
                                    rtfCellFormat.borderBottom.BORDERS.borderColor);
	}
    if (rtfCellFormat.borderLeft.border == true) {
		// Left cell border
        QString tbclbt = "\\clbrdrl";

        QString border = rtf_get_bordername(rtfCellFormat.borderLeft.BORDERS.borderType);

        tbclbrl = QString::asprintf("%s%s\\brdrw%d\\brsp%d\\brdrcf%d", tbclbt.toStdString().c_str(), border.toStdString().c_str(),
                                    rtfCellFormat.borderLeft.BORDERS.borderWidth, rtfCellFormat.borderLeft.BORDERS.borderSpace,
                                    rtfCellFormat.borderLeft.BORDERS.borderColor);
	}
    if (rtfCellFormat.borderRight.border == true) {
		// Right cell border
        QString tbclbt = "\\clbrdrr";

        QString border = rtf_get_bordername(rtfCellFormat.borderRight.BORDERS.borderType);

        tbclbrr = QString::asprintf("%s%s\\brdrw%d\\brsp%d\\brdrcf%d", tbclbt.toStdString().c_str(), border.toStdString().c_str(),
                                    rtfCellFormat.borderRight.BORDERS.borderWidth, rtfCellFormat.borderRight.BORDERS.borderSpace,
                                    rtfCellFormat.borderRight.BORDERS.borderColor);
	}
    if (rtfCellFormat.borderTop.border == true) {
		// Top cell border
        QString tbclbt = "\\clbrdrt";

        QString border = rtf_get_bordername(rtfCellFormat.borderTop.BORDERS.borderType);

        tbclbrt = QString::asprintf("%s%s\\brdrw%d\\brsp%d\\brdrcf%d", tbclbt.toStdString().c_str(), border.toStdString().c_str(),
                                    rtfCellFormat.borderTop.BORDERS.borderWidth, rtfCellFormat.borderTop.BORDERS.borderSpace,
                                    rtfCellFormat.borderTop.BORDERS.borderColor);
	}

	// Format table cell shading
    QString shading;
    if (rtfCellFormat.cellShading == true) {
        QString sh = rtf_get_shadingname(rtfCellFormat.SHADING.shadingType, true);

		// Set paragraph shading color
        shading = QString::asprintf("%s\\clshdgn%d\\clcfpat%d\\clcbpat%d", sh.toStdString().c_str(), rtfCellFormat.SHADING.shadingIntensity,
                                    rtfCellFormat.SHADING.shadingFillColor, rtfCellFormat.SHADING.shadingBkColor);
	}

	// Writes RTF table data
    QString rtfText = QString::asprintf("\n\\tcelld%s%s%s%s%s%s%s\\cellx%d", tblcla.toStdString().c_str(), tblcld.toStdString().c_str(),
                                        tbclbrb.toStdString().c_str(), tbclbrl.toStdString().c_str(), tbclbrr.toStdString().c_str(),
                                        tbclbrt.toStdString().c_str(), shading.toStdString().c_str(), rightMargin);

    out << rtfText;

    return RTF_SUCCESS;
}


// Ends RTF table cell
int rtf_end_tablecell() {
	// Writes RTF table data
    QString rtfText = "\n\\cell ";

    out << rtfText;

    return RTF_SUCCESS;
}


// Gets RTF table row formatting properties
RTF_TABLEROW_FORMAT* rtf_get_tablerowformat() {
	// Get current RTF table row formatting properties
	return &rtfRowFormat;
}


// Sets RTF table row formatting properties
void rtf_set_tablerowformat(RTF_TABLEROW_FORMAT* rf) {
	// Set new RTF table row formatting properties
    memcpy(&rtfRowFormat, rf, sizeof(RTF_TABLEROW_FORMAT));
}


// Gets RTF table cell formatting properties
RTF_TABLECELL_FORMAT* rtf_get_tablecellformat() {
	// Get current RTF table cell formatting properties
	return &rtfCellFormat;
}


// Sets RTF table cell formatting properties
void rtf_set_tablecellformat(RTF_TABLECELL_FORMAT* cf) {
	// Set new RTF table cell formatting properties
    memcpy(&rtfCellFormat, cf, sizeof(RTF_TABLECELL_FORMAT));
}


// Gets border name
QString rtf_get_bordername(int border_type) {
    switch (border_type) {
    case RTF_PARAGRAPHBORDERTYPE_STHICK:     return "\\brdrs";          // Single-thickness border
    case RTF_PARAGRAPHBORDERTYPE_DTHICK:     return "\\brdrth";         // Double-thickness border
    case RTF_PARAGRAPHBORDERTYPE_SHADOW:     return "\\brdrsh";         // Shadowed border
    case RTF_PARAGRAPHBORDERTYPE_DOUBLE:     return "\\brdrdb";         // Double border
    case RTF_PARAGRAPHBORDERTYPE_DOT:        return "\\brdrdot";        // Dotted border
    case RTF_PARAGRAPHBORDERTYPE_DASH:       return "\\brdrdash";       // Dashed border
    case RTF_PARAGRAPHBORDERTYPE_HAIRLINE:   return "\\brdrhair";       // Hairline border
    case RTF_PARAGRAPHBORDERTYPE_INSET:      return "\\brdrinset";      // Inset border
    case RTF_PARAGRAPHBORDERTYPE_SDASH:      return "\\brdrdashsm";     // Dashed border (small)
    case RTF_PARAGRAPHBORDERTYPE_DOTDASH:    return "\\brdrdashd";      // Dot-dashed border
    case RTF_PARAGRAPHBORDERTYPE_DOTDOTDASH: return "\\brdrdashdd";     // Dot-dot-dashed border
    case RTF_PARAGRAPHBORDERTYPE_OUTSET:     return "\\brdroutset";     // Outset border
    case RTF_PARAGRAPHBORDERTYPE_TRIPLE:     return "\\brdrtriple";     // Triple border
    case RTF_PARAGRAPHBORDERTYPE_WAVY:       return "\\brdrwavy";       // Wavy border
    case RTF_PARAGRAPHBORDERTYPE_DWAVY:      return "\\brdrwavydb";     // Double wavy border
    case RTF_PARAGRAPHBORDERTYPE_STRIPED:    return "\\brdrdashdotstr"; // Striped border
    case RTF_PARAGRAPHBORDERTYPE_EMBOSS:     return "\\brdremboss";     // Embossed border
    case RTF_PARAGRAPHBORDERTYPE_ENGRAVE:    return "\\brdrengrave";    // Engraved border
	}

    return "";
}


// Gets shading name
QString rtf_get_shadingname(int shading_type, bool cell) {
    if (cell == false) {
        switch (shading_type) {
        case RTF_PARAGRAPHSHADINGTYPE_FILL:    return "";             // Fill shading
        case RTF_PARAGRAPHSHADINGTYPE_HORIZ:   return "\\bghoriz";    // Horizontal background pattern
        case RTF_PARAGRAPHSHADINGTYPE_VERT:    return "\\bgvert";     // Vertical background pattern
        case RTF_PARAGRAPHSHADINGTYPE_FDIAG:   return "\\bgfdiag";    // Forward diagonal background pattern
        case RTF_PARAGRAPHSHADINGTYPE_BDIAG:   return "\\bgbdiag";    // Backward diagonal background pattern
        case RTF_PARAGRAPHSHADINGTYPE_CROSS:   return "\\bgcross";    // Cross background pattern
        case RTF_PARAGRAPHSHADINGTYPE_CROSSD:  return "\\bgdcross";   // Diagonal cross background pattern
        case RTF_PARAGRAPHSHADINGTYPE_DHORIZ:  return "\\bgdkhoriz";  // Dark horizontal background pattern
        case RTF_PARAGRAPHSHADINGTYPE_DVERT:   return "\\bgdkvert";   // Dark vertical background pattern
        case RTF_PARAGRAPHSHADINGTYPE_DFDIAG:  return "\\bgdkfdiag";  // Dark forward diagonal background pattern
        case RTF_PARAGRAPHSHADINGTYPE_DBDIAG:  return "\\bgdkbdiag";  // Dark backward diagonal background pattern
        case RTF_PARAGRAPHSHADINGTYPE_DCROSS:  return "\\bgdkcross";  // Dark cross background pattern
        case RTF_PARAGRAPHSHADINGTYPE_DCROSSD: return "\\bgdkdcross"; // Dark diagonal cross background pattern
		}
    } else {
        switch (shading_type) {
        case RTF_CELLSHADINGTYPE_FILL:    return "";               // Fill shading
        case RTF_CELLSHADINGTYPE_HORIZ:   return "\\clbghoriz";    // Horizontal background pattern
        case RTF_CELLSHADINGTYPE_VERT:    return "\\clbgvert";     // Vertical background pattern
        case RTF_CELLSHADINGTYPE_FDIAG:   return "\\clbgfdiag";    // Forward diagonal background pattern
        case RTF_CELLSHADINGTYPE_BDIAG:   return "\\clbgbdiag";    // Backward diagonal background pattern
        case RTF_CELLSHADINGTYPE_CROSS:   return "\\clbgcross";    // Cross background pattern
        case RTF_CELLSHADINGTYPE_CROSSD:  return "\\clbgdcross";   // Diagonal cross background pattern
        case RTF_CELLSHADINGTYPE_DHORIZ:  return "\\clbgdkhoriz";  // Dark horizontal background pattern
        case RTF_CELLSHADINGTYPE_DVERT:   return "\\clbgdkvert";   // Dark vertical background pattern
        case RTF_CELLSHADINGTYPE_DFDIAG:  return "\\clbgdkfdiag";  // Dark forward diagonal background pattern
        case RTF_CELLSHADINGTYPE_DBDIAG:  return "\\clbgdkbdiag";  // Dark backward diagonal background pattern
        case RTF_CELLSHADINGTYPE_DCROSS:  return "\\clbgdkcross";  // Dark cross background pattern
        case RTF_CELLSHADINGTYPE_DCROSSD: return "\\clbgdkdcross"; // Dark diagonal cross background pattern
		}
	}

    return "";
}

RTF::Scene RTF::objectToScene(const QJsonObject& obj)
{
    RTF::Scene scene;
    scene._html = obj["doc"].toString("");
    scene._name = obj["name"].toString("");
    const QJsonArray& tags = obj["tags"].toArray();
    for (auto tag: tags) {
        QString aTag = tag.toString("").toLower();
        if (aTag == "cover") _cover = scene._html;
        scene._tags.append(aTag);
    }
    return scene;
}

RTF::Scene RTF::objectToItem(const QJsonObject& obj) {
    RTF::Scene scene = objectToScene(obj);
    const QJsonArray& children = obj["children"].toArray();
    for (auto child: children) scene._children.append(objectToItem(child.toObject()));
    return scene;
}

void RTF::processAlignment(QString style) {
    enum { LEFT, CENTER, RIGHT, JUSTIFY } type = LEFT;

    RTF_PARAGRAPH_FORMAT* para = rtf_get_paragraphformat();
    _align = para->paragraphAligment;

    int pos = style.indexOf("align=\"");
    if (pos == -1) return;
    QString align = style.mid(pos + 7);
    pos = align.indexOf("\"");
    if (pos == -1) return;
    align = align.left(pos).toUpper();

    if (align == "CENTER") type = CENTER;
    else if (align == "RIGHT") type = RIGHT;
    else if (align == "JUSTIFY") type = JUSTIFY;

    switch (type) {
    case LEFT:    para->paragraphAligment = RTF_PARAGRAPHALIGN_LEFT;    break;
    case CENTER:  para->paragraphAligment = RTF_PARAGRAPHALIGN_CENTER;  break;
    case RIGHT:   para->paragraphAligment = RTF_PARAGRAPHALIGN_RIGHT;   break;
    case JUSTIFY: para->paragraphAligment = RTF_PARAGRAPHALIGN_JUSTIFY; break;
    }

    pos = style.indexOf("-qt-block-indent:1");
    if (pos == -1) {
        para->leftIndent = 0;
        return;
    }
    para->leftIndent = 720;
}

void RTF::resetAlignment() {
    RTF_PARAGRAPH_FORMAT* para = rtf_get_paragraphformat();
    para->paragraphAligment = _align;
}

#define BOLD      1
#define ITALIC    2
#define UNDERLINE 4

bool RTF::processCharacters(QString& text, bool first) {
    RTF_PARAGRAPH_FORMAT* para = rtf_get_paragraphformat();

    int pos = text.indexOf("<");
    if (pos == -1) return false;
    QString out = text.left(pos);
    text = text.mid(pos);

    rtf_start_paragraph(out, first);

    if (text.left(13) == "<span style=\"") {
        pos = text.indexOf("\">");
        QString type = text.mid(13, pos - 13);
        text = text.mid(pos + 2);
        int flag = 0;
        while ((pos = type.indexOf(";")) != -1) {
            QString what = type.left(pos);
            type = type.mid(pos + 1);
            if (what.left(7).toUpper() == " FONT-W") {
                flag |= BOLD;
                para->CHARACTER.boldCharacter = true;
            } else if (what.left(7).toUpper() == " FONT-S") {
                flag |= ITALIC;
                para->CHARACTER.italicCharacter = true;
            } else if (what.left(7).toUpper() == " TEXT-D") {
                flag |= UNDERLINE;
                para->CHARACTER.underlineCharacter = 1;
            }
        }
        _stack.push_back(flag);
        return true;
    } else if (text.left(7) == "</span>") {
        text = text.mid(7);
        int flags = _stack.back();
        _stack.pop_back();
        if (flags & BOLD) para->CHARACTER.boldCharacter = false;
        if (flags & ITALIC) para->CHARACTER.italicCharacter = false;
        if (flags & UNDERLINE) para->CHARACTER.underlineCharacter = 0;
        return true;
    } else if (text.left(10) == "<img src=\"") {
        pos = text.indexOf("\" />");
        QString filename = text.mid(10, pos - 10);
        int npos = filename.indexOf("\"");
        if (npos == -1) return true;
        filename = filename.left(npos);
        QString ext = filename.right(4).toLower();
        if (ext != ".jpg" && ext != ".gif" && ext != ".png") ext = ".jpg";
        else ext = "";
        npos = filename.lastIndexOf("/");
        QString path = _dir;
        if (npos != -1) {
            path = filename.left(npos + 1);
            filename = filename.mid(npos + 1);
        } else {
            path = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation);
            if (path.right(1) != "/") path += "/";
        }
        filename += ext;
        if (path.isEmpty()) path += "./";
        filename = path + filename;
        rtf_load_image(filename);
        return true;
    }

    return false;
}

void RTF::resetCharacters() {
    RTF_PARAGRAPH_FORMAT* para = rtf_get_paragraphformat();
    para->CHARACTER.boldCharacter = false;
    para->CHARACTER.italicCharacter = false;
    para->CHARACTER.underlineCharacter = 0;
}

bool RTF::processParagraph(QString& html) {
    // strip out to just past '<p '
    RTF_PARAGRAPH_FORMAT* para = rtf_get_paragraphformat();
    para->firstLineIndent = 720;
    int pos = html.indexOf("<p ", 0, Qt::CaseInsensitive);
    if (pos == -1) return false;
    html = html.mid(pos + 3);
    pos = html.indexOf(">");
    if (pos == -1) return false;
    QString style = html.left(pos);
    html = html.mid(pos + 1);

    processAlignment(style);

    pos = html.indexOf("</p>", 0, Qt::CaseInsensitive);
    if (pos == -1) return false;
    QString text = html.left(pos);
    html = html.mid(pos + 4);

    bool first = true;
    while (processCharacters(text, first)) first = false;
    rtf_start_paragraph(text, first);

    resetCharacters();
    resetAlignment();

    rtf_start_paragraph("\r\n", true);

    return true;
}

void RTF::sceneToRTF(QString html) {
    // strip out to just past '<body '
    int pos = html.indexOf("<body ", 0, Qt::CaseInsensitive);
    if (pos == -1) return;
    html = html.mid(pos + 6);
    pos = html.indexOf(">");
    if (pos == -1) return;
    html = html.mid(pos + 1);

    // strip out everything starting with </body>
    pos = html.indexOf("</body>", 0, Qt::CaseInsensitive);
    if (pos == -1) return;
    html = html.left(pos);

    while (processParagraph(html))
        ;
}

void RTF::sceneToRTF(RTF::Scene scene) {
    enum { NONE, COVER, CHAPTER, SCENE, TRASH } type = NONE;
    for (const auto& tag: scene._tags) {
        if (tag == "cover") type = COVER;
        else if (tag == "chapter") type = CHAPTER;
        else if (tag == "trash") type = TRASH;
        else if (tag == "scene") type = SCENE;
    }
    if (type == COVER || type == TRASH) return;

    if (type == CHAPTER) {
        RTF_PARAGRAPH_FORMAT* para = rtf_get_paragraphformat();
        para->paragraphBreak = RTF_PARAGRAPHBREAK_PAGE;
        rtf_start_paragraph("\r\n", true);
        para->paragraphBreak = RTF_PARAGRAPHBREAK_NONE;
        rtf_start_paragraph("\r\n", true);
        rtf_start_paragraph("\r\n", true);
    }

    if (type != NONE) sceneToRTF(scene._html);
    for (auto& child: scene._children) sceneToRTF(child);
}

void RTF::novelToBook(QJsonObject obj, Tree& tree)
{
    const QJsonObject& doc = obj["document"].toObject();
    const QJsonObject& root = doc["root"].toObject();
    tree._top = objectToItem(root);

    if (!_cover.isEmpty()) {
        QString filename = _cover;
        if (_cover.left(2) == "<!") {
            int pos = _cover.indexOf("img src=");
            if (pos == -1) return;
            filename = _cover.mid(pos + 9);
            pos = filename.indexOf("\"");
            if (pos == -1) return;
            filename = filename.left(pos);
            QString path = _dir;
            pos = filename.lastIndexOf("/");
            if (pos != -1) {
                path = filename.left(pos + 1);
                filename = filename.mid(pos + 1);
            }
            if (path.isEmpty()) path += _dir;
            filename = path + filename;
            if (filename.right(3) != "jpg") filename += ".jpg";
            _cover = filename;
        }
    }
}


RTF::RTF(QString dir, QJsonObject obj) {
    if (dir == "") dir = "./";
    if (dir.right(1) != "/") dir += "/";

    // RTF document font and color table definition
    QString font_list = "Times New Roman;Arial;";
    QString color_list = "0;0;0;255;0;0;192;192;192";

    // Create new RTF document
    novelToBook(obj, _tree);
    rtf_open(dir + _tree._top._name + ".rtf", font_list, color_list);
    rtf_load_image(_cover);
    sceneToRTF(_tree._top);

    // Close RTF document
    rtf_close();
}
