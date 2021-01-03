import javax.xml.transform.sax.SAXResult;
	import javax.xml.transform.sax.SAXSource;
	import javax.xml.transform.stream.StreamSource;
	import javax.xml.validation.Schema;
	import javax.xml.validation.SchemaFactory;
	import javax.xml.validation.Validator;

	import org.xml.sax.InputSource;
	import org.xml.sax.SAXException;
	import org.xml.sax.helpers.DefaultHandler;

public class Validating_Test {
	
	/**
	 * A sample application which shows how to perform a
	 * XML document validation while parsing XML with SAX.
	 */ 
	 
	  public static void main(String[] args) {
	    try {
	      // create schema by from an XSD file:
	      String schemaLang = "http://www.w3.org/2001/XMLSchema";
	      SchemaFactory jaxp = SchemaFactory.newInstance(schemaLang);
	      Schema schema = jaxp.newSchema(new StreamSource("shipOrder.xsd"));
	      // prepare document validator:
	      Validator validator = schema.newValidator();

	      // prepare SAX handler and SAX result receiving validate data:
	      SaxHandler handler = new SaxHandler();
	      SAXResult sax = new SAXResult(handler);

	      // at last send valid data to out SAX handler:
	      SAXSource source = new SAXSource(new InputSource("shipOrder.xml"));
	      validator.validate(source, sax);

	    }catch (SAXException ex) {
	      // we are here if the document is not valid:
	      // ... process validation error...
	      ex.printStackTrace();
	    } catch (Exception ex) {
	      ex.printStackTrace();
	    }
	  }

	  // our SAX handler receiving validated data:
	  private static final class SaxHandler extends DefaultHandler {
	    // ...
	  }
	
}
