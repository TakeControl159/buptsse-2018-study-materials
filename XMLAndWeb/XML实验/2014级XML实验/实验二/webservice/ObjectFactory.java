
package webservice;

import javax.xml.bind.JAXBElement;
import javax.xml.bind.annotation.XmlElementDecl;
import javax.xml.bind.annotation.XmlRegistry;
import javax.xml.namespace.QName;


/**
 * This object contains factory methods for each 
 * Java content interface and Java element interface 
 * generated in the webservice package. 
 * <p>An ObjectFactory allows you to programatically 
 * construct new instances of the Java representation 
 * for XML content. The Java representation of XML 
 * content can consist of schema derived interfaces 
 * and classes representing the binding of schema 
 * type definitions, element declarations and model 
 * groups.  Factory methods for each of these are 
 * provided in this class.
 * 
 */
@XmlRegistry
public class ObjectFactory {

    private final static QName _CompareStrResponse_QNAME = new QName("http://webservice/", "compareStrResponse");
    private final static QName _CompareStr_QNAME = new QName("http://webservice/", "compareStr");
    private final static QName _LinkStrResponse_QNAME = new QName("http://webservice/", "linkStrResponse");
    private final static QName _LinkStr_QNAME = new QName("http://webservice/", "linkStr");

    /**
     * Create a new ObjectFactory that can be used to create new instances of schema derived classes for package: webservice
     * 
     */
    public ObjectFactory() {
    }

    /**
     * Create an instance of {@link CompareStrResponse }
     * 
     */
    public CompareStrResponse createCompareStrResponse() {
        return new CompareStrResponse();
    }

    /**
     * Create an instance of {@link CompareStr }
     * 
     */
    public CompareStr createCompareStr() {
        return new CompareStr();
    }

    /**
     * Create an instance of {@link LinkStrResponse }
     * 
     */
    public LinkStrResponse createLinkStrResponse() {
        return new LinkStrResponse();
    }

    /**
     * Create an instance of {@link LinkStr }
     * 
     */
    public LinkStr createLinkStr() {
        return new LinkStr();
    }

    /**
     * Create an instance of {@link JAXBElement }{@code <}{@link CompareStrResponse }{@code >}}
     * 
     */
    @XmlElementDecl(namespace = "http://webservice/", name = "compareStrResponse")
    public JAXBElement<CompareStrResponse> createCompareStrResponse(CompareStrResponse value) {
        return new JAXBElement<CompareStrResponse>(_CompareStrResponse_QNAME, CompareStrResponse.class, null, value);
    }

    /**
     * Create an instance of {@link JAXBElement }{@code <}{@link CompareStr }{@code >}}
     * 
     */
    @XmlElementDecl(namespace = "http://webservice/", name = "compareStr")
    public JAXBElement<CompareStr> createCompareStr(CompareStr value) {
        return new JAXBElement<CompareStr>(_CompareStr_QNAME, CompareStr.class, null, value);
    }

    /**
     * Create an instance of {@link JAXBElement }{@code <}{@link LinkStrResponse }{@code >}}
     * 
     */
    @XmlElementDecl(namespace = "http://webservice/", name = "linkStrResponse")
    public JAXBElement<LinkStrResponse> createLinkStrResponse(LinkStrResponse value) {
        return new JAXBElement<LinkStrResponse>(_LinkStrResponse_QNAME, LinkStrResponse.class, null, value);
    }

    /**
     * Create an instance of {@link JAXBElement }{@code <}{@link LinkStr }{@code >}}
     * 
     */
    @XmlElementDecl(namespace = "http://webservice/", name = "linkStr")
    public JAXBElement<LinkStr> createLinkStr(LinkStr value) {
        return new JAXBElement<LinkStr>(_LinkStr_QNAME, LinkStr.class, null, value);
    }

}
