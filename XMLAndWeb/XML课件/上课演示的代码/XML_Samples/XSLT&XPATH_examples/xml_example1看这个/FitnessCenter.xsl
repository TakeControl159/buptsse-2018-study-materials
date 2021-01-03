<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
                version="1.0">
 
    <xsl:output method="xml"/>

    <xsl:template match="/">
        <xsl:apply-templates/>
    </xsl:template>

    <xsl:template match="FitnessCenter">
        <xsl:element name="FitnessCenter">
            <xsl:apply-templates/>
        </xsl:element>
    </xsl:template>

    <xsl:template match="Member">
        <xsl:element name="Member">
            <xsl:apply-templates/>
        </xsl:element>
    </xsl:template>

    <xsl:template match="Name">
        <xsl:element name="Name">
            <xsl:apply-templates/>
        </xsl:element>
    </xsl:template>

    <xsl:template match="Phone">
        <xsl:element name="Phone">
            <xsl:apply-templates/>
        </xsl:element>
    </xsl:template>

    <xsl:template match="FavoriteColor">
        <xsl:element name="FavoriteColor">
            <xsl:apply-templates/>
        </xsl:element>
    </xsl:template>

    <xsl:template match="text()">
	<xsl:value-of select="."/>
    </xsl:template>

</xsl:stylesheet>