<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
                version="1.0">
 
    <xsl:output method="xml"/>

    <xsl:template match="/">
      <root>
          <xsl:for-each select="//book_start">
              <book>
                  <details>
                      <xsl:call-template name="displayBook">
                          <xsl:with-param name="here" select="following-sibling::*[1]/details/*[1]"/>
                      </xsl:call-template>
                  </details>
              </book>
          </xsl:for-each>
      </root>
    </xsl:template>

    <xsl:template name="displayBook">
        <xsl:param name="here"/>
        <xsl:choose>
            <xsl:when test="name($here) != 'book_end'">
                <xsl:element name="{name($here)}">
                    <xsl:value-of select="$here"/>
                </xsl:element>
                <xsl:call-template name="displayBook">
                    <xsl:with-param name="here" select="following-sibling::*[1]"/>
                </xsl:call-template>
            </xsl:when>
        </xsl:choose>
    </xsl:template>

</xsl:stylesheet>