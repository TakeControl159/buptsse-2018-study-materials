
package buptsse.jaxws;

import javax.xml.bind.annotation.XmlAccessType;
import javax.xml.bind.annotation.XmlAccessorType;
import javax.xml.bind.annotation.XmlElement;
import javax.xml.bind.annotation.XmlRootElement;
import javax.xml.bind.annotation.XmlType;

@XmlRootElement(name = "CompareString", namespace = "http://buptsse/")
@XmlAccessorType(XmlAccessType.FIELD)
@XmlType(name = "CompareString", namespace = "http://buptsse/", propOrder = {
    "str1",
    "str2"
})
public class CompareString {

    @XmlElement(name = "str1", namespace = "")
    private String str1;
    @XmlElement(name = "str2", namespace = "")
    private String str2;

    /**
     * 
     * @return
     *     returns String
     */
    public String getStr1() {
        return this.str1;
    }

    /**
     * 
     * @param str1
     *     the value for the str1 property
     */
    public void setStr1(String str1) {
        this.str1 = str1;
    }

    /**
     * 
     * @return
     *     returns String
     */
    public String getStr2() {
        return this.str2;
    }

    /**
     * 
     * @param str2
     *     the value for the str2 property
     */
    public void setStr2(String str2) {
        this.str2 = str2;
    }

}
