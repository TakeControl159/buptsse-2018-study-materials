<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
                version="1.0">
 
    <xsl:output method="html"/>

    <xsl:template match="/">
        <HTML>
            <HEAD>
                <TITLE>Fitness Center</TITLE>
            </HEAD>
            <BODY>
                <xsl:call-template name="displayNameWithFont">
                    <xsl:with-param name="fontFace" select="'Impact'"/>
                    <xsl:with-param name="name" 
                            select="/FitnessCenter/Member[1]/Name"/>
                </xsl:call-template>
                <BR/>
                <xsl:call-template name="displayNameWithFont">
                    <xsl:with-param name="fontFace" select="'Lucida Console'"/>
                    <xsl:with-param name="name" 
                            select="/FitnessCenter/Member[2]/Name"/>
                </xsl:call-template>
                <BR/>
                <xsl:call-template name="displayNameWithFont">
                    <xsl:with-param name="name" 
                            select="/FitnessCenter/Member[3]/Name"/>
                </xsl:call-template>
            </BODY>
        </HTML>
    </xsl:template>

    <xsl:template name="displayNameWithFont">
        <xsl:param name="fontFace" select="'Braggadocio'"/> <!-- default font -->
        <xsl:param name="name"/>
        <FONT face="{$fontFace}">
            <xsl:value-of select="$name"/>
        </FONT>
    </xsl:template>

</xsl:stylesheet>