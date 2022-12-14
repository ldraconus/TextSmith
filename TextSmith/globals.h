#ifndef GLOBALS_H
#define GLOBALS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <io.h>
#include <olectl.h>

// Paragraph break defs
#define RTF_PARAGRAPHBREAK_NONE				0
#define RTF_PARAGRAPHBREAK_PAGE				1
#define RTF_PARAGRAPHBREAK_COLUMN			2
#define RTF_PARAGRAPHBREAK_LINE				3

// Paragraph align defs
#define RTF_PARAGRAPHALIGN_LEFT				0
#define RTF_PARAGRAPHALIGN_CENTER			1
#define RTF_PARAGRAPHALIGN_RIGHT			2
#define RTF_PARAGRAPHALIGN_JUSTIFY			3

// Paragraph tab kind defs
#define RTF_PARAGRAPHTABKIND_NONE			0
#define RTF_PARAGRAPHTABKIND_CENTER			1
#define RTF_PARAGRAPHTABKIND_RIGHT			2
#define RTF_PARAGRAPHTABKIND_DECIMAL		3

// Paragraph tab lead defs
#define RTF_PARAGRAPHTABLEAD_NONE			0
#define RTF_PARAGRAPHTABLEAD_DOT			1
#define RTF_PARAGRAPHTABLEAD_MDOT			2
#define RTF_PARAGRAPHTABLEAD_HYPH			3
#define RTF_PARAGRAPHTABLEAD_UNDERLINE		4
#define RTF_PARAGRAPHTABLEAD_THICKLINE		5
#define RTF_PARAGRAPHTABLEAD_EQUAL			6

// Paragraph border kind defs
#define RTF_PARAGRAPHBORDERKIND_NONE		0
#define RTF_PARAGRAPHBORDERKIND_TOP			1
#define RTF_PARAGRAPHBORDERKIND_BOTTOM		2
#define RTF_PARAGRAPHBORDERKIND_LEFT		3
#define RTF_PARAGRAPHBORDERKIND_RIGHT		4
#define RTF_PARAGRAPHBORDERKIND_BOX			5

// Paragraph border type defs
#define RTF_PARAGRAPHBORDERTYPE_STHICK		0
#define RTF_PARAGRAPHBORDERTYPE_DTHICK		1
#define RTF_PARAGRAPHBORDERTYPE_SHADOW		2
#define RTF_PARAGRAPHBORDERTYPE_DOUBLE		3
#define RTF_PARAGRAPHBORDERTYPE_DOT			4
#define RTF_PARAGRAPHBORDERTYPE_DASH		5
#define RTF_PARAGRAPHBORDERTYPE_HAIRLINE	6
#define RTF_PARAGRAPHBORDERTYPE_INSET		7
#define RTF_PARAGRAPHBORDERTYPE_SDASH		8
#define RTF_PARAGRAPHBORDERTYPE_DOTDASH		9
#define RTF_PARAGRAPHBORDERTYPE_DOTDOTDASH	10
#define RTF_PARAGRAPHBORDERTYPE_OUTSET		11
#define RTF_PARAGRAPHBORDERTYPE_TRIPLE		12
#define RTF_PARAGRAPHBORDERTYPE_WAVY		13
#define RTF_PARAGRAPHBORDERTYPE_DWAVY		14
#define RTF_PARAGRAPHBORDERTYPE_STRIPED		15
#define RTF_PARAGRAPHBORDERTYPE_EMBOSS		16
#define RTF_PARAGRAPHBORDERTYPE_ENGRAVE		17

// Paragraph shading type defs
#define RTF_PARAGRAPHSHADINGTYPE_FILL		0
#define RTF_PARAGRAPHSHADINGTYPE_HORIZ		1
#define RTF_PARAGRAPHSHADINGTYPE_VERT		2
#define RTF_PARAGRAPHSHADINGTYPE_FDIAG		3
#define RTF_PARAGRAPHSHADINGTYPE_BDIAG		4
#define RTF_PARAGRAPHSHADINGTYPE_CROSS		5
#define RTF_PARAGRAPHSHADINGTYPE_CROSSD		6
#define RTF_PARAGRAPHSHADINGTYPE_DHORIZ		7
#define RTF_PARAGRAPHSHADINGTYPE_DVERT		8
#define RTF_PARAGRAPHSHADINGTYPE_DFDIAG		9
#define RTF_PARAGRAPHSHADINGTYPE_DBDIAG		10
#define RTF_PARAGRAPHSHADINGTYPE_DCROSS		11
#define RTF_PARAGRAPHSHADINGTYPE_DCROSSD	12

// Section break defs
#define RTF_SECTIONBREAK_CONTINUOUS			0
#define RTF_SECTIONBREAK_COLUMN				1
#define RTF_SECTIONBREAK_PAGE				2
#define RTF_SECTIONBREAK_EVENPAGE			3
#define RTF_SECTIONBREAK_ODDPAGE			4

// Table row text align defs
#define RTF_ROWTEXTALIGN_LEFT				0
#define RTF_ROWTEXTALIGN_CENTER				1
#define RTF_ROWTEXTALIGN_RIGHT				2

// Table cell text vertical align defs
#define RTF_CELLTEXTALIGN_TOP				0
#define RTF_CELLTEXTALIGN_CENTER			1
#define RTF_CELLTEXTALIGN_BOTTOM			2

// Table cell text direction defs
#define RTF_CELLTEXTDIRECTION_LRTB			0
#define RTF_CELLTEXTDIRECTION_RLTB			1
#define RTF_CELLTEXTDIRECTION_LRBT			2
#define RTF_CELLTEXTDIRECTION_LRTBV			3
#define RTF_CELLTEXTDIRECTION_RLTBV			4

// Table cell shading type defs
#define RTF_CELLSHADINGTYPE_FILL			0
#define RTF_CELLSHADINGTYPE_HORIZ			1
#define RTF_CELLSHADINGTYPE_VERT			2
#define RTF_CELLSHADINGTYPE_FDIAG			3
#define RTF_CELLSHADINGTYPE_BDIAG			4
#define RTF_CELLSHADINGTYPE_CROSS			5
#define RTF_CELLSHADINGTYPE_CROSSD			6
#define RTF_CELLSHADINGTYPE_DHORIZ			7
#define RTF_CELLSHADINGTYPE_DVERT			8
#define RTF_CELLSHADINGTYPE_DFDIAG			9
#define RTF_CELLSHADINGTYPE_DBDIAG			10
#define RTF_CELLSHADINGTYPE_DCROSS			11
#define RTF_CELLSHADINGTYPE_DCROSSD			12

// Document view kind defs
#define RTF_DOCUMENTVIEWKIND_NONE			0
#define RTF_DOCUMENTVIEWKIND_PAGE			1
#define RTF_DOCUMENTVIEWKIND_OUTLINE		2
#define RTF_DOCUMENTVIEWKIND_MASTER			3
#define RTF_DOCUMENTVIEWKIND_NORMAL			4

#endif
