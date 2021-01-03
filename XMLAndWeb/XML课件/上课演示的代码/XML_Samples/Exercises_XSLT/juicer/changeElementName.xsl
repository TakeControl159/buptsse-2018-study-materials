<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
                version="1.0">
 
    <xsl:output method="xml"/>
    <xsl:param name="nameOfElementToChange"/>
    <xsl:param name="newNameOfElement"/>

    <xsl:template match="*">
        <xsl:if test="name(.) != $nameOfElementToChange">
            <xsl:element name="{name(.)}">
                <xsl:for-each select="@*">
                    <xsl:attribute name="{name(.)}">
                        <xsl:value-of select="."/>
                    </xsl:attribute>
                </xsl:for-each>
                <xsl:apply-templates/>
            </xsl:element>
        </xsl:if>
        <xsl:if test="name(.) = $nameOfElementToChange">
            <xsl:element name="{$newNameOfElement}">
                <xsl:for-each select="@*">
                    <xsl:attribute name="{name(.)}">
                        <xsl:value-of select="."/>
                    </xsl:attribute>
                </xsl:for-each>
                <xsl:apply-templates/>
            </xsl:element>
        </xsl:if>
    </xsl:template>

</xsl:stylesheet>