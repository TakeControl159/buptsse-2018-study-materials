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
            <xsl:element name="GoldMembers">  
                <xsl:for-each select="Member[@level='gold']">
                    <xsl:apply-templates select="Name" mode="footnote"/>
                </xsl:for-each>
            </xsl:element>
        </xsl:element>
    </xsl:template>

    <xsl:template match="Member">
        <xsl:element name="Member">
            <xsl:for-each select="@*">
                <xsl:attribute name="{name(.)}">
                    <xsl:value-of select="."/>
                </xsl:attribute>
            </xsl:for-each>
            <xsl:apply-templates mode="Normal"/>
        </xsl:element>
    </xsl:template>

    <xsl:template match="Name" mode="Normal">
        <xsl:element name="Name">
            <xsl:apply-templates/>
        </xsl:element>
    </xsl:template>

    <xsl:template match="Name" mode="footnote">
        <xsl:element name="Name">
            <xsl:text>***</xsl:text>
                <xsl:apply-templates/>
            <xsl:text>***</xsl:text>
        </xsl:element>
    </xsl:template>

    <xsl:template match="Phone" mode="Normal">
        <xsl:element name="Phone">
            <xsl:apply-templates/>
        </xsl:element>
    </xsl:template>

    <xsl:template match="FavoriteColor" mode="Normal">
        <xsl:element name="FavoriteColor">
            <xsl:apply-templates/>
        </xsl:element>
    </xsl:template>

    <xsl:template match="text()">
	<xsl:value-of select="."/>
    </xsl:template>

</xsl:stylesheet>