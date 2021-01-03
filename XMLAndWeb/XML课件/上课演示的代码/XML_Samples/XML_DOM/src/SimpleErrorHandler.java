import javax.xml.transform.sax.SAXResult;
import javax.xml.transform.sax.SAXSource;
import javax.xml.transform.stream.StreamSource;
import javax.xml.validation.Schema;
import javax.xml.validation.SchemaFactory;
import javax.xml.validation.Validator;

import org.xml.sax.InputSource;
import org.xml.sax.SAXException;
import org.xml.sax.helpers.DefaultHandler;
import org.xml.sax.SAXParseException;
import org.xml.sax.ErrorHandler;
public class SimpleErrorHandler implements ErrorHandler {
	    public void warning(SAXParseException e) throws SAXException {
	        System.out.println(e.getMessage());
	    }

	    public void error(SAXParseException e) throws SAXException {
	        System.out.println(e.getMessage());
	    }

	    public void fatalError(SAXParseException e) throws SAXException {
	        System.out.println(e.getMessage());
	    }
	}

