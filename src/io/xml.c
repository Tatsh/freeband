#include "../freeband.h"

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
