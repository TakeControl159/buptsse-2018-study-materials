<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
                version="1.0">
 
    <xsl:output method="xml"/>

    <xsl:template match="juicers">
        <xsl:element name="JuicerCatalogue">
            <xsl:apply-templates/>
        </xsl:element>
    </xsl:template>

    <xsl:template match="juicer">
        <xsl:element name="Juicer">
            <xsl:attribute name="id">
                <xsl:value-of select="@id"/>
            </xsl:attribute>
            <xsl:element name="Type">               
                <xsl:value-of select="@type"/>
            </xsl:element>
            <xsl:apply-templates/>
        </xsl:element>
    </xsl:template>

    <xsl:template match="name">
        <xsl:element name="Name">
            <xsl:apply-templates/>
        </xsl:element>
    </xsl:template>

    <xsl:template match="image">
        <!-- Drop it -->
    </xsl:template>

    <xsl:template match="description">
        <xsl:element name="Description">
            <xsl:apply-templates/>
        </xsl:element>
    </xsl:template>

    <xsl:template match="warranty">
        <!-- Drop it -->
    </xsl:template>

    <xsl:template match="weight">
        <!-- Drop it -->
    </xsl:template>

    <xsl:template match="cost">
        <!-- Drop it -->
    </xsl:template>

    <xsl:template match="retailer">
        <!-- Drop it -->
    </xsl:template>

</xsl:stylesheet>