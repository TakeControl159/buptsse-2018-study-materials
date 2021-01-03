<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
                version="1.0">

    <xsl:output method="xml"/>

    <xsl:template match="company_data">
        <xsl:element name="{name(.)}">
            <xsl:for-each select="@*">
                <xsl:attribute name="{name(.)}">
                    <xsl:value-of select="."/>
                </xsl:attribute>
            </xsl:for-each>
            <xsl:apply-templates select="*"/>
        <xsl:text>
</xsl:text>
        </xsl:element>
    </xsl:template>

    <xsl:template match="data">
        <xsl:text>
    </xsl:text>
        <xsl:element name="{name(.)}">
            <xsl:for-each select="@*">
                <xsl:attribute name="{name(.)}">
                    <xsl:value-of select="."/>
                </xsl:attribute>
            </xsl:for-each>
            <xsl:apply-templates/>
        </xsl:element>
    </xsl:template>

    <xsl:template match="data[@classification='top-secret']">
        <!-- Delete the top-secret data -->
    </xsl:template>

</xsl:stylesheet>