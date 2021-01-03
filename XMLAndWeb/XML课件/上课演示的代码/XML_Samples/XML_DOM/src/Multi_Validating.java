import javax.xml.transform.sax.SAXResult;
import javax.xml.transform.sax.SAXSource;
import javax.xml.transform.stream.StreamSource;
import javax.xml.validation.Schema;
import javax.xml.validation.SchemaFactory;
import javax.xml.validation.Validator;
import org.xml.sax.InputSource;
import org.xml.sax.SAXException;
import org.xml.sax.helpers.DefaultHandler;
//import org.xml.sax.*; 
import org.xml.sax.XMLReader; 
import javax.xml.parsers.*; //XML解析器接口 
import javax.xml.parsers.DocumentBuilder.*;
import org.w3c.dom.Document; //XML的DOM实现 
import javax.xml.transform.Source;
 
public class Multi_Validating {
	 public static void main(String[] args) {
		 ;
	 } 
	 void DOM_well_formed()
	 {
		 try{
			 DocumentBuilderFactory factory = DocumentBuilderFactory.newInstance();
			 factory.setValidating(false);
			 factory.setNamespaceAware(true);

			 DocumentBuilder builder = factory.newDocumentBuilder();

			 builder.setErrorHandler(new SimpleErrorHandler());

			 Document document = builder.parse(new InputSource("document.xml"));

		 }   catch (SAXException ex) {
	      // we are here if the document is not valid:
	      // ... process validation error...
	      ex.printStackTrace();
	    } catch (Exception ex) {
	      ex.printStackTrace();
	    }
	 }
	 void SAX_well_formed()
	 {
		 try{ 
			 SAXParserFactory factory = SAXParserFactory.newInstance();
			 factory.setValidating(false);
			 factory.setNamespaceAware(true);

			 SAXParser parser = factory.newSAXParser();

			 XMLReader reader = parser.getXMLReader();
			 reader.setErrorHandler(new SimpleErrorHandler());
			 reader.parse(new InputSource("document.xml"));
		 }   catch (SAXException ex) {
		      // we are here if the document is not valid:
		      // ... process validation error...
		      ex.printStackTrace();
		    } catch (Exception ex) {
		      ex.printStackTrace();
		    }
		 }
	 
	 void internal_val_DOM_DTD()
	 {
        try{  
        	DocumentBuilderFactory factory = DocumentBuilderFactory.newInstance();
        	factory.setValidating(true);
        	factory.setNamespaceAware(true);

        	DocumentBuilder builder = factory.newDocumentBuilder();

        	builder.setErrorHandler(new SimpleErrorHandler());

        	Document document = builder.parse(new InputSource("document.xml"));

        }   catch (SAXException ex) {
		      // we are here if the document is not valid:
		      // ... process validation error...
		      ex.printStackTrace();
		    } catch (Exception ex) {
		      ex.printStackTrace();
		    }
		 }
	 
	 
	 void internal_val_SAX_DTD()
	 {
	    try{	 
	    	SAXParserFactory factory = SAXParserFactory.newInstance();
	    	factory.setValidating(true);
	    	factory.setNamespaceAware(true);

	    	SAXParser parser = factory.newSAXParser();

	    	XMLReader reader = parser.getXMLReader();
	    	reader.setErrorHandler(new SimpleErrorHandler());
	    	reader.parse(new InputSource("document.xml"));
	    }   catch (SAXException ex) {
		      // we are here if the document is not valid:
		      // ... process validation error...
		      ex.printStackTrace();
		    } catch (Exception ex) {
		      ex.printStackTrace();
		    }
		 }
	 
	 void internal_val_DOM_XSD()
	 {
	    try{  
	    	DocumentBuilderFactory factory = DocumentBuilderFactory.newInstance();
	    	factory.setValidating(true);
	    	factory.setNamespaceAware(true);
	    	factory.setAttribute("http://java.sun.com/xml/jaxp/properties/schemaLanguage", 
	    	      "http://www.w3.org/2001/XMLSchema");

	    	DocumentBuilder builder = factory.newDocumentBuilder();

	    	builder.setErrorHandler(new SimpleErrorHandler());

	    	Document document = builder.parse(new InputSource("document.xml"));

	        }catch (SAXException ex) {
			      // we are here if the document is not valid:
			      // ... process validation error...
			      ex.printStackTrace();
			    } catch (Exception ex) {
			      ex.printStackTrace();
			    }
			 }
	    
	    void  internal_val_SAX_XSD()
		 {
		    try{ 
		    	 
		    	SAXParserFactory factory = SAXParserFactory.newInstance();
		    	factory.setValidating(true);
		    	factory.setNamespaceAware(true);

		    	SAXParser parser = factory.newSAXParser();
		    	parser.setProperty("http://java.sun.com/xml/jaxp/properties/schemaLanguage", 
		    	      "http://www.w3.org/2001/XMLSchema");

		    	XMLReader reader = parser.getXMLReader();
		    	reader.setErrorHandler(new SimpleErrorHandler());
		    	reader.parse(new InputSource("document.xml"));

		        }catch (SAXException ex) {
				      // we are here if the document is not valid:
				      // ... process validation error...
				      ex.printStackTrace();
				    } catch (Exception ex) {
				      ex.printStackTrace();
				    }
				 }
	    
	    void  external_val_DOM_XSD()
		 {
		    try{ 
		    	DocumentBuilderFactory factory = DocumentBuilderFactory.newInstance();
		    	factory.setValidating(false);
		    	factory.setNamespaceAware(true);

		    	SchemaFactory schemaFactory = 
		    	    SchemaFactory.newInstance("http://www.w3.org/2001/XMLSchema");

		    	factory.setSchema(schemaFactory.newSchema(
		    	    new Source[] {new StreamSource("contacts.xsd")}));

		    	DocumentBuilder builder = factory.newDocumentBuilder();

		    	builder.setErrorHandler(new SimpleErrorHandler());

		    	Document document = builder.parse(new InputSource("document.xml"));

		        }catch (SAXException ex) {
				      // we are here if the document is not valid:
				      // ... process validation error...
				      ex.printStackTrace();
				    } catch (Exception ex) {
				      ex.printStackTrace();
				    }
				 }
	    
	    
	    void  external_val_SAX_XSD()
		 {
		    try{ 
		    	SAXParserFactory factory = SAXParserFactory.newInstance();
		    	factory.setValidating(false);
		    	factory.setNamespaceAware(true);

		    	SchemaFactory schemaFactory = 
		    	    SchemaFactory.newInstance("http://www.w3.org/2001/XMLSchema");

		    	factory.setSchema(schemaFactory.newSchema(
		    	    new Source[] {new StreamSource("contacts.xsd")}));

		    	SAXParser parser = factory.newSAXParser();

		    	XMLReader reader = parser.getXMLReader();
		    	reader.setErrorHandler(new SimpleErrorHandler());
		    	reader.parse(new InputSource("document.xml"));

		        }catch (SAXException ex) {
				      // we are here if the document is not valid:
				      // ... process validation error...
				      ex.printStackTrace();
				    } catch (Exception ex) {
				      ex.printStackTrace();
				    }
			}
}
