#include <stdbool.h>
#include <stdio.h>
#include <libxml/parser.h>
#include <libxml/tree.h>
#include <libxml/xmlreader.h>
#include <libxml/xmlstring.h>

#include "prefs.h"

#define LENGTH 32

prefs_bool prefs_appearance_audience;
prefs_bool prefs_appearance_band;
prefs_char prefs_appearance_theme[LENGTH];

void prefs_processNode(xmlTextReaderPtr reader) {
  const xmlChar *name, *value;

  name = xmlTextReaderConstName(reader);
  if (name == NULL)
    name = BAD_CAST "--";

  printf("%s\n", name);
  
  value = xmlTextReaderConstValue(reader);

  return;
}

void prefs_parseXML(const char *filename) {
  xmlTextReaderPtr reader;
  int ret;
  
  reader = xmlReaderForFile(filename, NULL,
                            XML_PARSE_DTDATTR |  /* default DTD attributes */
                            XML_PARSE_NOENT);   /* substitute entities */

  /* Scan preferences file */
  if (reader != NULL) {
    ret = xmlTextReaderRead(reader);
    while (ret == 1) {
      prefs_processNode(reader);
      ret = xmlTextReaderRead(reader);
    }
    fprintf(stdout, "Done parsing preferences.\n");
    xmlFreeTextReader(reader);
  }

  return;
}

bool validateXML(const char *filename) {
  xmlParserCtxtPtr ctxt; /* the parser context */
  xmlDocPtr doc; /* the resulting document tree */

  /* create a parser context */
  ctxt = xmlNewParserCtxt();
  if (ctxt == NULL) {
    fprintf(stderr, "Failed to allocate parser context\n");
    return false;
  }
  
  /* parse the file, activating the DTD validation option */
  doc = xmlCtxtReadFile(ctxt, filename, NULL, XML_PARSE_DTDVALID);
  
  /* check if parsing suceeded */
  if (doc == NULL) {
    fprintf(stderr, "Failed to parse %s\n", filename);
    xmlFreeDoc(doc);
    xmlFreeParserCtxt(ctxt);
    return false;
  }
  else {
    /* check if validation suceeded */
    if (ctxt->valid == 0) {
      fprintf(stderr, "Failed to validate %s\n", filename);
      xmlFreeDoc(doc);
      xmlFreeParserCtxt(ctxt);
      return false;
    }
    /* free up the resulting document */
    xmlFreeDoc(doc);
  }
  
  /* free up the parser context */
  xmlFreeParserCtxt(ctxt);
  
  return true;
}

int main(int argc, char *argv[]) {
  if (argc != 2) {
    fprintf(stdout, "Usage: %s <XML file>\n", argv[0]);
    return 1;
  }
  
  LIBXML_TEST_VERSION
  
  if (validateXML(argv[1])) {
#ifdef __DEBUG__
    fprintf(stdout, "%s validates.\n\n", argv[1]);
#endif
    prefs_parseXML(argv[1]);
  }
  else {
    fprintf(stderr, "%s does not validate.\n", argv[1]);
    return 1;
  }
  
  return 0;
}
