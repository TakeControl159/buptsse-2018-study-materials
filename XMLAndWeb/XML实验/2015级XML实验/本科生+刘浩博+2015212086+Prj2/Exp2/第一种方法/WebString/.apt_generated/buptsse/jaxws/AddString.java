
package buptsse.jaxws;

import javax.xml.bind.annotation.XmlAccessType;
import javax.xml.bind.annotation.XmlAccessorType;
import javax.xml.bind.annotation.XmlElement;
import javax.xml.bind.annotation.XmlRootElement;
import javax.xml.bind.annotation.XmlType;

@XmlRootElement(name = "addString", namespace = "http://buptsse/")
@XmlAccessorType(XmlAccessType.FIELD)
@XmlType(name = "addString", namespace = "http://buptsse/", propOrder = {
    "a",
    "b"
})
public class AddString {

    @XmlElement(name = "a", namespace = "")
    private String a;
    @XmlElement(name = "b", namespace = "")
    private String b;

    /**
     * 
     * @return
     *     returns String
     */
    public String getA() {
        return this.a;
    }

    /**
     * 
     * @param a
     *     the value for the a property
     */
    public void setA(String a) {
        this.a = a;
    }

    /**
     * 
     * @return
     *     returns String
     */
    public String getB() {
        return this.b;
    }

    /**
     * 
     * @param b
     *     the value for the b property
     */
    public void setB(String b) {
        this.b = b;
    }

}
