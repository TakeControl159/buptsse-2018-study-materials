<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
                version="1.0">
 
    <xsl:variable name="lcase" select="'abcdefghijklmnopqrstuvwxyz'"/>
    <xsl:variable name="ucase" select="'ABCDEFGHIJKLMNOPQRSTUVWXYZ'"/>

    <xsl:output method="xml"/>

    <xsl:template match="*">
        <xsl:element name="{translate(name(.), $lcase, $ucase)}">
            <xsl:for-each select="@*">
                <xsl:attribute name="{translate(name(.), $lcase, $ucase)}">
                    <xsl:value-of select="."/>
                </xsl:attribute>
            </xsl:for-each>
            <xsl:apply-templates/>
        </xsl:element>
    </xsl:template>

</xsl:stylesheet>