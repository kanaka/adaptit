/////////////////////////////////////////////////////////////////////////////
/// \project		adaptit
/// \file			AdaptitConstants.h
/// \author			Bruce Waters, revised for wxWidgets by Bill Martin
/// \date_created	6 January 2005
/// \rcs_id $Id$
/// \copyright		2008 Bruce Waters, Bill Martin, SIL International
/// \license		The Common Public License or The GNU Lesser General Public License (see license directory)
/// \description	This is a header file containing some constants used by Adapt It. 
/// BEW added 15Feb10: set VERSION_NUMBER to 5 for the ai_codefixes refactor job
/////////////////////////////////////////////////////////////////////////////

// constants used by Adapt It

// the following improves GCC compilation performance
#if defined(__GNUG__) && !defined(__APPLE__)
    #pragma interface "AdaptitConstants.h"
#endif

// version 5 stores endmarkers on the CSourcePhrase they belong on, rather than the next,
// in a new member called m_endMarkers. It also stores the filtered info formerly put in
// m_markers and wrapped by filter bracket markers, into separate members: m_freeTrans,
// m_note, m_collectedBackTrans, (these last three store just the string, no markers such
// as \free & \free*, \note & \note*, \bt - although these are explicitly added in
// exports) and other filtered info is in m_filteredInfo, and each filtered string and any
// markers there are wrapped by filter bracket markers, \~FILTER and \~FILTER* with no
// delimiting space between each such pair; 
// BEW 19Apr10 supporting Save As... to allow saving for doc version 4 requires a new
// #define, DOCVERSION4 - we'll set the version to be used for saving by a CAdapt_ItDoc
// class public function SetDocVersion(int index) which returns void. Internally,
// index 0 will return whatever VERSION_NUMBER is, and index 1 will return DOCVERSION4. We
// use indices because the wxFileDialog function, for a save dialog, returns the index of
// the doc type from the combobox choice - and the top choice, index = 0, will always be
// the default (ie. current doc version number). We will use a private doc class member int
// m_docVersionCurrent which will be used by saves of the doc and KB (the KB xml structure
// for doc versions 4 and 5 is the same), and we will use a new function
// RestoreCurrentDocVersion() returning void, to reset m_docVersionCurrent back to the
// VERSION_NUMBER value after the Save As... is done; and an access function
// GetCurrentDocVersion() to get its value whenever needed.

// The following is also defined at line 31 in Adapt_It.h 
// *********** IMPORTANT:  commment out both together or uncomment out both together *********
#define USE_LEGACY_PARSER

#if !defined(USE_LEGACY_PARSER)
#define VERSION_NUMBER      10  // as of 21 April17, for support of new member m_filteredInfo_After in CSourcePhrase
#else
#define VERSION_NUMBER	9	// as of 9Jul14, for ZWSP support in exports for SE Asian languages
#endif
//#define VERSION_NUMBER	8	// as of 29Oct12
//#define VERSION_NUMBER	7	// as of 20Apr12
//#define VERSION_NUMBER	6   // as of 13Feb12
//#define VERSION_NUMBER	5   // superceded on 13Feb12
#define DOCVERSION4			4

//#define VERSION_NUMBER		4 // version 2: from 3rd Jan 2001, flags on CSourcePhrase for start
							  // and end of a retranslation; from 14th May 2003, capacity to do
							  // and see a glossing line as well as adapting line is version 3
							  // From 23 June 2005, five bool members added to CSourcePhrase for
							  // support of free translations (3), notes (1) and bookmarks (1).
							  // whm Note: Since the wx version only reads xml data we are 100%
							  // compatible with the MFC version number scheme for version 4.

// BEW 3May10: kbVersion 2 will have a version number in the xml file-- attribute
// kbVersion="2" in the <KB element, replacing the docVersion attribute there - which is
// not good design, we want KB and Doc to be independently versionable). 
// Prior to 3May10, the KB was not versioned.

#define KB_VERSION3			3	// adding new fields for source and target language codes
#define KB_VERSION2			2	// to coincide with the introduction of docVersion 5 (at 5.3.0?)
#define KB_VERSION1			1	// legacy KBs, from 1.0.0 to 5.2.x

//#define MAKEPUBLIC		// temporary, to conditionally compile access to CTargetUnit::m_uuid
							// directly, and if undefined, by access functions - later
							// test the impact the access functions have on speed

#define VERT_SPACE			4
#define MAX_WORDS			10	// maximum # of words allowed in a src phrase before Adapt It chokes
#define MAX_STRIPS			6000
#define MAX_PILES			36  // per strip
#define MAX_CELLS			3   // per pile (version 4)
#define WORK_SPAN			60  // how many extra elements beyond the prec & foll context to 
								// allow for a move
#define NUM_PREWORDS		40  // how many words to allow in preceding context (max)
#define NUM_FOLLWORDS		30  // how many words to allow in the following context (max)
#define RH_SLOP				60  // leave 60 pixels of white space at end of strip, when strip-wrap
								// is on
#define MAXPUNCTPAIRS		26  //24  // maximum number of paired src & target punct chars which can be 
								// handled by the dialog
#define MAXTWOPUNCTPAIRS	10  //8
#define WIDECHARBUFSIZE		512 // big enough for anything probably, eg. CChooseTranslation, etc.

// unicode-based filepaths, and deep nesting of files with long names can override the microsoft 
// default buffer sizes (and this happened at CTC 2002 demo!), so increase this to safe limits - 
// see _MAX_PATH in STDLIB.H for the old limits (about 230 or so)
#define AI_MAX_PATH   860 /* max. length of full pathname */
#define AI_MAX_DRIVE  64   /* max. length of drive component */
#define AI_MAX_DIR    850 /* max. length of path component */
#define AI_MAX_FNAME  850 /* max. length of file name component */
#define AI_MAX_EXT    850 /* max. length of extension component */
#define MIN_FONT_SIZE	6
#define MAX_FONT_SIZE	72
#define MAX_DLG_FONT_SIZE	24
#define MIN_DLG_FONT_SIZE	11

// for free translation support - added BEW on 24Jun05, changed to ..._WORDS on 28Apr06
//#define MIN_FREE_TRANS_WORDS	5
// BEW 13Jan12, try skipping no words before halt location for free trans is looked for
// (Kim finds it annoying, as did Bill)
#define MIN_FREE_TRANS_WORDS	0
// BEW 19Nov13 Use a wider inter-pile gap when free translating, default it to 40 pixels
// (but if the user has a wider gap in normal adapting, we use the wider gap for free
// translating as well)
#define FREE_TRANS_INTER_PILE_GAP   40

// for changing punctuation characters on the fly, the parser needs to be able to find if
// there is an inline binding marker a few characters ahead of one or more characters
// shunted to m_precPunct from off of the wordProper earlier when it/they were made
// punctuation characters and now the user wants to undo that punctuation set change;
// allowing for 5 such characters should probably be enough for any real situation
#define MAX_MOVED_FORMER_PUNCTS   5

// a CSourcePhrase count for limiting the span of source text being checked for belonging
// to a source text string and also belonging to the same string after being edited outside
// of the application, -- looking for an unchanged subspan (we assume at the constraints on
// scripture meaning won't allow a verse to be edited so as to have all different words,
// and so a limit small enough to encompass the averge verse size, plus a bit extra, will
// suffice for keeping the algorithm efficient (we don't want to have to check hundreds and
// hundreds of words) at every iteration)
#define SPAN_LIMIT 80
//#define SPAN_LIMIT 300
#define DISPARATE_SIZES_NUMERATOR 3
#define DISPARATE_SIZES_DENOMINATOR 2

#define NUM_OLD_USERPROFILES_FILES_TO_KEEP 4

#define NUM_OLD_DOC_CREATION_FILES_TO_KEEP 5

// NUMINSERTS is the maximum number of consecutive auto-inserts before the m_nInsertCount
// is reset to 0 for the next sequence of that many. Thaw() calls are done at the OnePass()
// call which is penultimate to this NUMINSERTS call.
#define NUMINSERTS 8

// Next two for how long to leave up the info Wait msg when discovering
//#if defined(_KBSERVER)
#define MSG_SECONDS 1
#define MSG_MILLISECONDS 300
//#endif

