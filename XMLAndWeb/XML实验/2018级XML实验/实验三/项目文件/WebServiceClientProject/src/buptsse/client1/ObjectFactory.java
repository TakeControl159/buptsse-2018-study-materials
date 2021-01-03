
package buptsse.client1;

import javax.xml.bind.JAXBElement;
import javax.xml.bind.annotation.XmlElementDecl;
import javax.xml.bind.annotation.XmlRegistry;
import javax.xml.namespace.QName;

/**
 * This object contains factory methods for each Java content interface and Java
 * element interface generated in the buptsse.client1 package.
 * <p>
 * An ObjectFactory allows you to programatically construct new instances of the
 * Java representation for XML content. The Java representation of XML content
 * can consist of schema derived interfaces and classes representing the binding
 * of schema type definitions, element declarations and model groups. Factory
 * methods for each of these are provided in this class.
 * 
 */
@XmlRegistry
public class ObjectFactory {

	private final static QName _AddStringResponse_QNAME = new QName("http://buptsse/", "AddStringResponse");
	private final static QName _CompareStringResponse_QNAME = new QName("http://buptsse/", "CompareStringResponse");
	private final static QName _AddString_QNAME = new QName("http://buptsse/", "AddString");
	private final static QName _CompareString_QNAME = new QName("http://buptsse/", "CompareString");

	/**
	 * Create a new ObjectFactory that can be used to create new instances of schema
	 * derived classes for package: buptsse.client1
	 * 
	 */
	public ObjectFactory() {
	}

	/**
	 * Create an instance of {@link CompareString }
	 * 
	 */
	public CompareString createCompareString() {
		return new CompareString();
	}

	/**
	 * Create an instance of {@link AddString }
	 * 
	 */
	public AddString createAddString() {
		return new AddString();
	}

	/**
	 * Create an instance of {@link AddStringResponse }
	 * 
	 */
	public AddStringResponse createAddStringResponse() {
		return new AddStringResponse();
	}

	/**
	 * Create an instance of {@link CompareStringResponse }
	 * 
	 */
	public CompareStringResponse createCompareStringResponse() {
		return new CompareStringResponse();
	}

	/**
	 * Create an instance of {@link JAXBElement }{@code <}{@link AddStringResponse
	 * }{@code >}}
	 * 
	 */
	@XmlElementDecl(namespace = "http://buptsse/", name = "AddStringResponse")
	public JAXBElement<AddStringResponse> createAddStringResponse(AddStringResponse value) {
		return new JAXBElement<AddStringResponse>(_AddStringResponse_QNAME, AddStringResponse.class, null, value);
	}

	/**
	 * Create an instance of {@link JAXBElement
	 * }{@code <}{@link CompareStringResponse }{@code >}}
	 * 
	 */
	@XmlElementDecl(namespace = "http://buptsse/", name = "CompareStringResponse")
	public JAXBElement<CompareStringResponse> createCompareStringResponse(CompareStringResponse value) {
		return new JAXBElement<CompareStringResponse>(_CompareStringResponse_QNAME, CompareStringResponse.class, null,
				value);
	}

	/**
	 * Create an instance of {@link JAXBElement }{@code <}{@link AddString
	 * }{@code >}}
	 * 
	 */
	@XmlElementDecl(namespace = "http://buptsse/", name = "AddString")
	public JAXBElement<AddString> createAddString(AddString value) {
		return new JAXBElement<AddString>(_AddString_QNAME, AddString.class, null, value);
	}

	/**
	 * Create an instance of {@link JAXBElement }{@code <}{@link CompareString
	 * }{@code >}}
	 * 
	 */
	@XmlElementDecl(namespace = "http://buptsse/", name = "CompareString")
	public JAXBElement<CompareString> createCompareString(CompareString value) {
		return new JAXBElement<CompareString>(_CompareString_QNAME, CompareString.class, null, value);
	}

}
